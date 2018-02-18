#include "camerafilter.h"
#include "camerafilterrunnable.h"
#include "faceidentifydaemon.h"
#include <QDebug>

namespace onechchy {

    CameraFilter::CameraFilter(QObject *parent) : QAbstractVideoFilter(parent)
    {
        mpFaceIdentifyDaemon = new FaceIdentifyDaemon(this);
        QObject::connect(mpFaceIdentifyDaemon, SIGNAL(faceRects(QList<QRect>)), this, SLOT(setFaceROI(QList<QRect>)));
        QObject::connect(mpFaceIdentifyDaemon, SIGNAL(testRects()), this, SLOT(testSlot()));
        mpFaceIdentifyDaemon->start();
    }

    CameraFilter::~CameraFilter()
    {
        qDebug() << "CameraFilter quit";
        if (mpFaceIdentifyDaemon != nullptr)
        {
            qDebug() << "FaceIdentifyDeamon quit";

            mpFaceIdentifyDaemon->quit();

            while (mpFaceIdentifyDaemon->isRunning()) {}
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
