#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QObject>
#include <QVector>
#include <opencv2/core.hpp>
#include <QPair>
#include "ifacerecognition.h"
#include "FaceIdentify.h"
#include <memory>

namespace FaceIdentifion {

    /**
     * @brief The FaceRecognition class 面部识别类
     */
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
        void RecordFace(std::vector<QString> faceId, std::vector<cv::Mat> faceMat) override;
        void save() override;

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

        // 面部识别主功能类
        std::unique_ptr<FaceIdentify> mpFaceIDentify;
    };

}

#endif // FACERECOGNITION_H
