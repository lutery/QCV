#ifndef FACESERVICE_H
#define FACESERVICE_H

#include <QObject>
#include <memory>
#include "ifaceservice.h"
#include "ifacedected.h"

namespace FaceIdentify {

    class FaceService : public QObject, public IFaceService, public IFaceDected
    {
        Q_OBJECT
        Q_ENUMS(DectedMethod)

    public:
        explicit FaceService(QObject *parent = nullptr);
        virtual ~FaceService(){}

        enum class DectedMethod
        {
            OpencvHaarcascade,
            Dlib
        };

    signals:
        void sigFps(QString curFps);
        void sigPixelFormat(QString curPF);
        void sigFaceCount(int curCount);

    public slots:

        // IFaceService interface
    public:
        Q_INVOKABLE void switchFaceDectedMethod(int methodId) override;

    private:
        IFaceService* mpFaceServiceImpl;
        IFaceDected* mpFaceDectedImpl;

        // IFaceDected interface
    public:
        std::vector<cv::Rect> dectedROI(const cv::Mat &) override;
        std::vector<cv::Mat> dectedMat(const cv::Mat &) override;
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat) override;
    };

}

#endif // FACESERVICE_H
