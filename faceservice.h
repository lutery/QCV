#ifndef FACESERVICE_H
#define FACESERVICE_H

#include <QObject>
#include <memory>
#include <QList>
#include "ifaceservice.h"
#include "ifacedected.h"
#include "ifacerecognition.h"

namespace FaceIdentify {

    /**
     * @brief The FaceService class 人脸识别服务器类
     */
    class FaceService : public QObject, public IFaceService, public IFaceDected, public IFaceRecognition
    {
        Q_OBJECT
        Q_ENUMS(DectedMethod)

    public:
        explicit FaceService(QObject *parent = nullptr);
        virtual ~FaceService(){}

        // 人脸检测方法枚举
        enum class DectedMethod
        {
            OpencvHaarcascade,
            CVFrontalFaceAltTree,
            CVFrontalFaceAlt,
            CVFrontalFaceAlt2,
            CVFrontalFace,
            CVFrontalFaceExtended,
            Dlib,
        };

    signals:
        void sigFps(QString curFps);
        void sigPixelFormat(QString curPF);
        void sigFaceCount(int curCount);

    public slots:

        // IFaceService interface
    public:
        Q_INVOKABLE FaceService* createFaceService();
        Q_INVOKABLE void switchFaceDectedMethod(int methodId) override;

    private:
        // 服务实现类
        IFaceService* mpFaceServiceImpl;
        // 人脸检测服务
        IFaceDected* mpFaceDectedImpl;
        // 人脸识别服务
        IFaceRecognition* mpFaceRecongnition;

        // IFaceDected interface
    public:
        std::vector<cv::Rect> dectedROI(const cv::Mat &) override;
        std::vector<cv::Mat> dectedMat(const cv::Mat &) override;
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat) override;

        // IFaceRecognition interface
    public:
        Q_INVOKABLE QStringList scanFaceInfos() override;
    };

}

#endif // FACESERVICE_H
