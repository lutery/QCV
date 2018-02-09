#include "camerafilterrunnable.h"
#include "util.h"
#include "imageutil.h"
#include <QDebug>
#include <opencv2/opencv.hpp>

namespace onechchy {

    CameraFilterRunnable::CameraFilterRunnable(QAbstractVideoFilter *cameraFilter)
    {
        pCameraFilter = cameraFilter;
    }

    CameraFilterRunnable::~CameraFilterRunnable()
    {

    }

    QVideoFrame CameraFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags)
    {
        int millisecond = onechchy::clock<std::chrono::milliseconds>();

        int fps = 1 / ((float)millisecond / 1000);

        qDebug() << "fps = " << fps;

        qDebug() << "input pixelFormat " << input->pixelFormat();

//        cv::Mat frameMat = onechchy::QVideoFrame2cvMat(*input);

//        cv::imwrite(R"(D:\Test\frameMat.jpg)", frameMat);

        return *input;
    }

}
