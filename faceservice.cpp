#include "faceservice.h"
#include "FaceDected.h"
#include "facedectedcv.h"
#include "facedecteddlib.h"
#include "camerabridgeface.h"
#include <mutex>

namespace FaceIdentify {

    class FaceServiceImpl : public IFaceService
    {
    protected:
        FaceServiceImpl();
        virtual ~FaceServiceImpl(){}

        // IFaceService interface
    public:
        static IFaceService* getInstance();

        void switchFaceDectedMethod(int methodId) override;

    private:
        std::unique_ptr<FaceDected> mpFaceDected;
        static IFaceService* mpSInstance;
        static std::mutex sMutex;
    };

    IFaceService* FaceServiceImpl::mpSInstance = nullptr;
    std::mutex FaceServiceImpl::sMutex;

    FaceServiceImpl::FaceServiceImpl():mpFaceDected(new FaceDected())
    {

    }

    IFaceService *FaceServiceImpl::getInstance()
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

    FaceService::FaceService(QObject *parent) : QObject(parent), mpFaceServiceImpl(FaceServiceImpl::getInstance())
    {
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curFps(QString)), this, SIGNAL(sigFps(QString)));
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curPixelFormat(QString)), this, SIGNAL(sigPixelFormat(QString)));
    }

    void FaceService::switchFaceDectedMethod(int methodId)
    {
        if (mpFaceServiceImpl != nullptr)
        {
            mpFaceServiceImpl->switchFaceDectedMethod(methodId);
        }
    }
}
