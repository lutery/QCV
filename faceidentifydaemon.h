#ifndef FACEIDENTIFYDAEMON_H
#define FACEIDENTIFYDAEMON_H

#include <QThread>
#include <QRect>
#include <QList>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include <memory>

namespace onechchy {

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
        bool mbExit = false;
        QMutex mLock;
        std::shared_ptr<cv::Mat> mpMat = nullptr;
    };

}

#endif // FACEIDENTIFYDAEMON_H
