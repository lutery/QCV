#ifndef CAMERAFILTERRUNNABLE_H
#define CAMERAFILTERRUNNABLE_H

#include <QVideoFilterRunnable>
#include <QAbstractVideoFilter>
#include <QObject>
#include <QRect>
#include <opencv2/opencv.hpp>
#include <QMutex>

namespace onechchy {
    /**
     * @brief The CameraFilterRunnable class 相机帧过滤器
     */
    class CameraFilterRunnable : public QVideoFilterRunnable
    {
    public:
        CameraFilterRunnable(QAbstractVideoFilter* cameraFilter);
        virtual ~CameraFilterRunnable();

        // QVideoFilterRunnable interface
    public:
        QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;
        void setFaceROI(const QList<QRect> &faceRects);

    private:
        // 保存相机过滤器
        QAbstractVideoFilter* pCameraFilter = nullptr;
        QList<QRect> mFaceROIs;
        QMutex mFaceROILocker;
    };

}
#endif // CAMERAFILTERRUNNABLE_H
