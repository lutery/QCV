#ifndef CAMERAFILTERRUNNABLE_H
#define CAMERAFILTERRUNNABLE_H

#include <QVideoFilterRunnable>
#include <QAbstractVideoFilter>

namespace onechchy {

    class CameraFilterRunnable : public QVideoFilterRunnable
    {
    public:
        CameraFilterRunnable(QAbstractVideoFilter* cameraFilter);
        virtual ~CameraFilterRunnable();

        // QVideoFilterRunnable interface
    public:
        QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

    private:
        QAbstractVideoFilter* pCameraFilter = nullptr;
    };

}
#endif // CAMERAFILTERRUNNABLE_H
