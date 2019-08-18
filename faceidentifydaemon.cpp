#include "faceidentifydaemon.h"
#include <QMutexLocker>
#include "faceutil.h"
#include "imageutil.h"
#include "facerecognitiondaemon.h"
#include "util.h"
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QVector>
#include <QUuid>
#include <QCryptographicHash>

namespace onechchy {

    FaceIdentifyDaemon::FaceIdentifyDaemon(QObject *parent):QThread(parent)
    {
        mCurFaceId = QUuid::createUuid().toString();
    }

    FaceIdentifyDaemon::~FaceIdentifyDaemon()
    {

    }

    /**
     * @brief FaceIdentifyDaemon::faceMat 设置人脸矩阵
     * @param mat
     */
    void FaceIdentifyDaemon::faceMat(cv::Mat& mat)
    {
        if (mpMat == nullptr)
        {
            QMutexLocker locker(&this->mLock);
            mpMat = std::shared_ptr<cv::Mat>(new cv::Mat());
            mat.copyTo(*mpMat);
        }
    }

    void FaceIdentifyDaemon::run()
    {
        while (!mbExit)
        {
            emit testRects();
            QThread::msleep(200);
            QMutexLocker locker(&this->mLock);

            qDebug() << "start locker";

            if (mpMat == nullptr)
            {
                continue;
            }

            // 这里将所有的矩阵类型转换为3通道，因为dlib目前只能将三通道的opencv图像转换为可处理的类型
            cv::Mat mat3;
#ifdef IDEBUG
            auto& [costTime1, matTmp1] = onechchy::funClock<std::chrono::milliseconds>(onechchy::cvMatAlign3, *mpMat);
            mat3 = matTmp1;
            qDebug() << "cvMatAlign3 cost time: " << costTime1;
#else
            mat3 = onechchy::cvMatAlign3(*mpMat);
#endif
//            cv::Mat mat3 = onechchy::cvMatAlign3(*mpMat);

//            qDebug() << "FaceRectHelper";

//            cv::imwrite(R"(D:\Test\frameMat.jpg)", mat3);

            std::vector<cv::Rect> faces;
#ifdef IDEBUG
            auto& [costTime2, facesTmp] = onechchy::funClock<std::chrono::milliseconds>(FaceIdentifion::FaceRectHelper, mat3);
            faces = facesTmp;
            qDebug() << "FaceRectHelper cost time: " << costTime2;
            qDebug() << "faces size is " << faces.size();
#else
            faces = FaceIdentifion::FaceRectHelper(mat3);
#endif
//            auto faces = FaceIdentifion::FaceRectHelper(mat3);
//            qDebug() << "FaceRectHelper cost time: " << costTime;
//            qDebug() << "faces size is " << faces.size();

            QList<QRect> qlistFaces;
            long heightMat = mpMat->rows;
#ifdef IDEBUG
            auto costTime3 = onechchy::funNClock<std::chrono::milliseconds>([&qlistFaces, &faces, &heightMat]{
                for (auto& faceRect : faces)
                {
                    faceRect.y = heightMat - (faceRect.y + faceRect.height);
                    qlistFaces.append(onechchy::cvRect2qRect(faceRect));
                }
            });

            qDebug() << "cv Rect 2 Qt QRect cost time: " << costTime3;
#else
            for (auto& faceRect : faces)
            {
                faceRect.y = heightMat - (faceRect.y + faceRect.height);
                qlistFaces.append(onechchy::cvRect2qRect(faceRect));
            }
#endif

//            QList<QRect> qlistFaces;

//            for (auto& faceRect : faces)
//            {
////                QRect qrect{faceRect.x, faceRect.y, faceRect.width, faceRect.height};

//                qlistFaces.append(onechchy::cvRect2qRect(faceRect));
////                qlistFaces.append(faceRect);
//            }

//            qDebug() << "cv Rect 2 Qt QRect cost time: " << costTime;
            qDebug() << "emit signal faceRects";
            emit faceRects(qlistFaces);

            if (mbFaceRecognition)
            {
                QVector<cv::Mat> curFaces;

                cv::Rect maxFace{0, 0, 0, 0};

                for (auto& face: faces)
                {
                    if (face.area() > maxFace.area())
                    {
                        maxFace = face;
                    }
                }

                cv::Mat curFace = (*mpMat)(maxFace).clone();
                curFaces.push_back(curFace);

                this->mpFaceRecognitionDaemon->pushFaces(mCurFaceId, curFaces);
            }

            mpMat = nullptr;
        }
    }

    void FaceIdentifyDaemon::quit()
    {
        QThread::quit();

        QMutexLocker locker(&this->mLock);
        mbExit = true;
    }

    void FaceIdentifyDaemon::faceIdentify(bool bstart, QString faceId)
    {
        mbFaceRecognition = bstart;
        mCurFaceId = faceId;
    }

    void FaceIdentifyDaemon::setMpFaceRecognitionDaemon(FaceRecognitionDaemon *value)
    {
        mpFaceRecognitionDaemon = value;
    }

}
