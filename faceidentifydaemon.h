#ifndef FACEIDENTIFYDAEMON_H
#define FACEIDENTIFYDAEMON_H

#include <QThread>
#include <QRect>
#include <QList>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include <memory>

namespace onechchy {

    /**
     * @brief The FaceIdentifyDaemon class 人脸识别后台线程
     */
    class FaceIdentifyDaemon : public QThread
    {
        Q_OBJECT
        void run() override;

    public:
        explicit FaceIdentifyDaemon(QObject* parent = nullptr);
        virtual ~FaceIdentifyDaemon();

    signals:
        void testRects();
        void faceRects(QList<QRect>);

    public slots:
        void faceMat(cv::Mat &);
        void quit();

    protected:
        // 是否运行
        bool mbExit = false;
        // 识别矩阵锁
        QMutex mLock;
        // 图像识别矩阵
        std::shared_ptr<cv::Mat> mpMat = nullptr;
    };

}

#endif // FACEIDENTIFYDAEMON_H
