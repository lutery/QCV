#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QObject>
#include <QVector>
#include <opencv2/core.hpp>
#include <QPair>
#include "ifacerecognition.h"

namespace FaceIdentify {

    class FaceRecognition : public QObject, public IFaceRecognition
    {
        Q_OBJECT
    public:
        explicit FaceRecognition(QObject *parent = nullptr);

    signals:

    public slots:

        // IFaceRecognition interface
    public:
        QStringList scanFaceInfos() override;

    private:
        void normalizeData(cv::Mat& faceImg);
        void normalizeDatas(QVector<cv::Mat>& faceImgs);

    private:
        // 人脸信息路径
        static QString sFaceInfoDir;
        static QString sFaceInfoJson;
        static QString sFaceConfig;

        int mNormalWidth = 64;
        int mNormalHeight = 64;
        QVector<QPair<QString, int>> mFaceInfos;
    };

}

#endif // FACERECOGNITION_H
