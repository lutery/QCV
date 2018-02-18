#ifndef CAMERAFILTER_H
#define CAMERAFILTER_H

#include <QVideoFilterRunnable>
#include <opencv2/opencv.hpp>

namespace onechchy {

    class FaceIdentifyDaemon;
    class CameraFilterRunnable;

    /**
     * @brief The CameraFilter class 相机帧过滤器
     */
    class CameraFilter : public QAbstractVideoFilter
    {
        Q_OBJECT
    public:
        CameraFilter(QObject* parent = Q_NULLPTR);
        virtual ~CameraFilter();

        // QAbstractVideoFilter interface
    public:
        QVideoFilterRunnable *createFilterRunnable() override;

    public slots:
        void testSlot();
        void setFaceROI(const QList<QRect> &faceRects);
        void faceMat(cv::Mat &frameMat);

    protected:
        FaceIdentifyDaemon* mpFaceIdentifyDaemon;
        CameraFilterRunnable* mpFilter;
    };

}

#endif // CAMERAFILTER_H
