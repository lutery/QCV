#include "faceidentifydaemon.h"
#include <QMutexLocker>
#include "faceutil.h"
#include "imageutil.h"
#include <QDebug>

namespace onechchy {

    FaceIdentifyDaemon::FaceIdentifyDaemon(QObject *parent):QThread(parent)
    {

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
            cv::Mat mat3 = onechchy::cvMatAlign3(*mpMat);

            qDebug() << "FaceRectHelper";

            cv::imwrite(R"(D:\Test\frameMat.jpg)", mat3);

            auto faces = FaceIdentify::FaceRectHelper(mat3);

            qDebug() << "faces size is " << faces.size();

            QList<QRect> qlistFaces;

            for (auto& faceRect : faces)
            {
//                QRect qrect{faceRect.x, faceRect.y, faceRect.width, faceRect.height};

                qlistFaces.append(onechchy::cvRect2qRect(faceRect));
//                qlistFaces.append(faceRect);
            }

            qDebug() << "emit signal faceRects";
            emit faceRects(qlistFaces);

            mpMat = nullptr;
        }
    }

    void FaceIdentifyDaemon::quit()
    {
        QThread::quit();

        QMutexLocker locker(&this->mLock);
        mbExit = true;
    }

}
