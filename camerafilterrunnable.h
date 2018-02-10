#ifndef CAMERAFILTERRUNNABLE_H
#define CAMERAFILTERRUNNABLE_H

#include <QVideoFilterRunnable>
#include <QAbstractVideoFilter>

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

    private:
        // 保存相机过滤器
        QAbstractVideoFilter* pCameraFilter = nullptr;
    };

}
#endif // CAMERAFILTERRUNNABLE_H
