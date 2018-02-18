#include "camerafilterrunnable.h"
#include "util.h"
#include "imageutil.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "faceutil.h"
#include "camerafilter.h"
#include <QMutexLocker>

namespace onechchy {

    CameraFilterRunnable::CameraFilterRunnable(QAbstractVideoFilter *cameraFilter)
    {
        pCameraFilter = cameraFilter;
        mFaceROIs.clear();
    }

    CameraFilterRunnable::~CameraFilterRunnable()
    {

    }

    /**
     * @brief CameraFilterRunnable::run
     * @param input 图像输入帧，但是图像是倒过来的，而QVideoFrame之间的复制构造函数是共享缓存的
     * @param surfaceFormat 看文档 关于摄像头的额外信息
     * @param flags 看文档 关于过滤器的额外信息
     * @return
     */
    QVideoFrame CameraFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags)
    {
        int millisecond = onechchy::clock<std::chrono::milliseconds>();

        int fps = 1 / ((float)millisecond / 1000);

        qDebug() << "fps = " << fps;

        qDebug() << "input pixelFormat " << input->pixelFormat();

        cv::Mat frameMat = onechchy::QVideoFrame2cvMat(*input);

        qDebug() << "mFaceRects size " << mFaceROIs.size();
        {
            QMutexLocker locker(&this->mFaceROILocker);
            if (mFaceROIs.size() > 0)
            {
    //            auto faceRIOs = mFaceROIs[0];
    //            mFaceROIs.removeFirst();

                for (const auto& faceRIO : mFaceROIs)
                {
                    cv::rectangle(frameMat, onechchy::qRect2cvRect(faceRIO), cv::Scalar(0, 0, 255), 3);
                }
            }
        }

        static_cast<CameraFilter*>(this->pCameraFilter)->faceMat(frameMat);

//        FaceIdentify::FaceDectedHelper(frameMat);

//        cv::imwrite(R"(D:\Test\frameMat.jpg)", frameMat);

        return *input;
    }

    void CameraFilterRunnable::setFaceROI(const QList<QRect> &faceRects)
    {
        if (faceRects.size() <= 0)
        {
            return;
        }

        QMutexLocker locker(&this->mFaceROILocker);
        mFaceROIs = faceRects;
    }
}
