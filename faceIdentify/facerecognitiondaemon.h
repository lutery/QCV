#ifndef FACERECOGNITIONDAEMON_H
#define FACERECOGNITIONDAEMON_H

#include <QThread>
#include <QMutex>
#include <QMap>
#include <QVector>
#include <QString>
#include <opencv2/opencv.hpp>

namespace onechchy {

    /**
     * @brief The FaceRecognitionDaemon class
     * 面部识别服务
     */
    class FaceRecognitionDaemon : public QThread
    {
        Q_OBJECT
        void run() override;

    public:
        explicit FaceRecognitionDaemon(QObject *parent = nullptr);
        virtual ~FaceRecognitionDaemon();

    signals:

    public slots:
        void pushFaces(QString faceId, QVector<cv::Mat> faces);
        void quit();

    protected:
        bool mbExit = false;
        QMutex mLock;
        QMap<QString, QVector<cv::Mat>> mFacesIds;
    };

}

#endif // FACERECOGNITIONDAEMON_H
