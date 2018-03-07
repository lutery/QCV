#include "faceservice.h"
#include "FaceDected.h"
#include "facedectedcv.h"
#include "facedecteddlib.h"
#include "camerabridgeface.h"
#include <mutex>

namespace FaceIdentify {

    class FaceServiceImpl : public IFaceService, public IFaceDected
    {
    protected:
        FaceServiceImpl();
        virtual ~FaceServiceImpl(){}

        // IFaceService interface
    public:
        static FaceServiceImpl* getInstance();

        void switchFaceDectedMethod(int methodId) override;

    private:
        std::unique_ptr<FaceDected> mpFaceDected;
        static FaceServiceImpl* mpSInstance;
        static std::mutex sMutex;

        // IFaceDected interface
    public:
        std::vector<cv::Rect> dectedROI(const cv::Mat &) override;
        std::vector<cv::Mat> dectedMat(const cv::Mat &) override;
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat) override;
    };

    FaceServiceImpl* FaceServiceImpl::mpSInstance = nullptr;
    std::mutex FaceServiceImpl::sMutex;

    FaceServiceImpl::FaceServiceImpl():mpFaceDected(new FaceDected())
    {

    }

    FaceServiceImpl *FaceServiceImpl::getInstance()
    {
        if (mpSInstance == nullptr)
        {
            std::unique_lock<std::mutex> lock(sMutex);
            if (mpSInstance == nullptr)
            {
                mpSInstance = new FaceServiceImpl();
            }
        }

        return mpSInstance;
    }

    void FaceServiceImpl::switchFaceDectedMethod(int methodId)
    {
        switch (methodId) {
        case FaceService::DectedMethod::Dlib:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedDlib>(new FaceDectedDlib));
            break;

        default:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedCV>(new FaceDectedCV));
            break;
        }
    }

    std::vector<cv::Rect> FaceServiceImpl::dectedROI(const cv::Mat &srcMat)
    {
        return mpFaceDected->dectedROI(srcMat);
    }

    std::vector<cv::Mat> FaceServiceImpl::dectedMat(const cv::Mat &srcMat)
    {
        return mpFaceDected->dectedMat(srcMat);
    }

    std::vector<cv::Mat> FaceServiceImpl::acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat)
    {
        return mpFaceDected->acquireFace(faceROIs, srcMat);
    }

    FaceService::FaceService(QObject *parent) : QObject(parent), mpFaceServiceImpl(FaceServiceImpl::getInstance()), mpFaceDectedImpl(FaceServiceImpl::getInstance())
    {
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curFps(QString)), this, SIGNAL(sigFps(QString)));
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curPixelFormat(QString)), this, SIGNAL(sigPixelFormat(QString)));
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curFaceCount(int)), this, SIGNAL(sigFaceCount(int)));
    }

    void FaceService::switchFaceDectedMethod(int methodId)
    {
        if (mpFaceServiceImpl != nullptr)
        {
            mpFaceServiceImpl->switchFaceDectedMethod(methodId);
        }
    }

    std::vector<cv::Rect> FaceService::dectedROI(const cv::Mat &srcMat)
    {
        if (mpFaceServiceImpl != nullptr)
        {
            return mpFaceDectedImpl->dectedROI(srcMat);
        }
    }

    std::vector<cv::Mat> FaceService::dectedMat(const cv::Mat &srcMat)
    {
        if (mpFaceServiceImpl != nullptr)
        {
            return mpFaceDectedImpl->dectedMat(srcMat);
        }
    }

    std::vector<cv::Mat> FaceService::acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat)
    {
        if (mpFaceServiceImpl != nullptr)
        {
            return mpFaceDectedImpl->acquireFace(faceROIs, srcMat);
        }
    }
}
