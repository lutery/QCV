#include "camerafilter.h"
#include "camerafilterrunnable.h"
#include "faceIdentify/faceidentifydaemon.h"
#include "faceIdentify/facerecognitiondaemon.h"
#include "camerabridgeface.h"
#include <QDebug>

namespace onechchy {

    CameraFilter::CameraFilter(QObject *parent) : QAbstractVideoFilter(parent)
    {
        mpFaceIdentifyDaemon = new FaceIdentifyDaemon(this);
        QObject::connect(mpFaceIdentifyDaemon, SIGNAL(faceRects(QList<QRect>)), this, SLOT(setFaceROI(QList<QRect>)));
        QObject::connect(mpFaceIdentifyDaemon, SIGNAL(testRects()), this, SLOT(testSlot()));
        QObject::connect(CameraBridgeFace::getInstance(), SIGNAL(startFaceIdentify(bool, QString)), mpFaceIdentifyDaemon, SLOT(faceIdentify(bool, QString)));
        mpFaceIdentifyDaemon->start();

        mpFaceRecognitionDaemon = new FaceRecognitionDaemon(this);
        mpFaceRecognitionDaemon->start();
        mpFaceIdentifyDaemon->setMpFaceRecognitionDaemon(mpFaceRecognitionDaemon);
    }

    CameraFilter::~CameraFilter()
    {
        qDebug() << "CameraFilter quit";
        if (mpFaceRecognitionDaemon != nullptr)
        {
            mpFaceRecognitionDaemon->quit();
        }

        if (mpFaceIdentifyDaemon != nullptr)
        {
            mpFaceIdentifyDaemon->quit();
        }

        if (mpFaceIdentifyDaemon != nullptr)
        {
            qDebug() << "FaceIdentifyDeamon quit";

//            mpFaceIdentifyDaemon->quit();

            while (mpFaceIdentifyDaemon->isRunning()) {}
            delete mpFaceIdentifyDaemon;
        }

        if (mpFaceRecognitionDaemon != nullptr)
        {
            while (mpFaceRecognitionDaemon->isRunning()) {}
            delete mpFaceRecognitionDaemon;
        }
    }

    /**
     * @brief CameraFilter::createFilterRunnable 创建过滤器运行对象
     * @return
     */
    QVideoFilterRunnable* CameraFilter::createFilterRunnable()
    {
        mpFilter = new CameraFilterRunnable(this);
        return mpFilter;
    }

    void CameraFilter::testSlot()
    {
        qDebug() << "testSlots";
    }

    void CameraFilter::setFaceROI(const QList<QRect> &faceRects)
    {
        qDebug() << "faceRects size " << faceRects.size();
        if (mpFilter != nullptr)
        {
            mpFilter->setFaceROI(faceRects);
        }
    }

    void CameraFilter::faceMat(cv::Mat& frameMat)
    {
        mpFaceIdentifyDaemon->faceMat(frameMat);
    }
}
