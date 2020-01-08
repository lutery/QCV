#ifndef FACEIDENTIFYDAEMON_H
#define FACEIDENTIFYDAEMON_H

#include <QThread>
#include <QRect>
#include <QList>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include <memory>

namespace onechchy {

    class FaceRecognitionDaemon;

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

        void setMpFaceRecognitionDaemon(FaceRecognitionDaemon *value);

    signals:
        void testRects();
        void faceRects(QList<QRect>);

    public slots:
        void faceMat(cv::Mat &);
        void quit();
        void faceIdentify(bool bstart, QString faceId);

    protected:
        // 是否运行
        bool mbExit = false;
        bool mbFaceRecognition = false;
        QString mCurFaceId;
        // 识别矩阵锁
        QMutex mLock;
        // 图像识别矩阵
        std::shared_ptr<cv::Mat> mpMat = nullptr;
        FaceRecognitionDaemon* mpFaceRecognitionDaemon;
    };

}

#endif // FACEIDENTIFYDAEMON_H
