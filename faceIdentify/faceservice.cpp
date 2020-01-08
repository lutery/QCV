#include "faceservice.h"
#include "FaceDected.h"
#include "facedectedcv.h"
#include "facedecteddlib.h"
#include "camera/camerabridgeface.h"
#include "faceutil.h"
#include "facerecognition.h"
#include "camera/camerabridgeface.h"
#include <mutex>
#include <QDir>
#include <QDirIterator>

namespace FaceIdentifion {

    /**
     * @brief The FaceServiceImpl class 人脸识别服务实现类
     */
    class FaceServiceImpl : public IFaceService, public IFaceDected, public IFaceRecognition
    {
    protected:
        FaceServiceImpl();
        virtual ~FaceServiceImpl(){}

        // IFaceService interface
    public:
        static FaceServiceImpl* getInstance();

        void switchFaceDectedMethod(int methodId) override;

    private:
        std::unique_ptr<FaceRecognition> mpFaceRecognition;
        // 人脸检测方法接口
        std::unique_ptr<FaceDected> mpFaceDected;
        // 人脸识别服务静态单例
        static FaceServiceImpl* mpSInstance;
        // 多线程锁
        static std::mutex sMutex;

    public:
//        // 人脸信息路径
//        static QString sFaceInfoPath;

        // IFaceDected interface
    public:
        std::vector<cv::Rect> dectedROI(const cv::Mat &) override;
        std::vector<cv::Mat> dectedMat(const cv::Mat &) override;
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat) override;

        // IFaceRecognition interface
    public:
        QStringList scanFaceInfos() override;
        void RecordFace(std::vector<QString> faceId, std::vector<cv::Mat> faceMat) override;
        void save() override;
    };

    FaceServiceImpl* FaceServiceImpl::mpSInstance = nullptr;
//    QString FaceServiceImpl::sFaceInfoPath = "FaceInfo";
    std::mutex FaceServiceImpl::sMutex;

    FaceServiceImpl::FaceServiceImpl():mpFaceDected(new FaceDected()), mpFaceRecognition(new FaceRecognition())
    {

    }

    /**
     * @brief FaceServiceImpl::getInstance 获取人脸识别服务单例
     * @return
     */
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

    /**
     * @brief FaceServiceImpl::switchFaceDectedMethod 切换人脸检测方法
     * @param methodId 人脸检测方法
     */
    void FaceServiceImpl::switchFaceDectedMethod(int methodId)
    {
        switch (methodId) {
        case FaceService::DectedMethod::Dlib:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedDlib>(new FaceDectedDlib));
            break;

        case FaceService::DectedMethod::CVFrontalFace:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedCV>(new FaceDectedCV(FaceDectedCV::scFrontalFace)));
            break;

        case FaceService::DectedMethod::CVFrontalFaceAlt:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedCV>(new FaceDectedCV(FaceDectedCV::scFrontalFaceAlt)));
            break;

        case FaceService::DectedMethod::CVFrontalFaceAlt2:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedCV>(new FaceDectedCV(FaceDectedCV::scFrontalFaceAlt2)));
            break;

        case FaceService::DectedMethod::CVFrontalFaceAltTree:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedCV>(new FaceDectedCV(FaceDectedCV::scFrontalFaceAltTree)));
            break;

        case FaceService::DectedMethod::CVFrontalFaceExtended:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedCV>(new FaceDectedCV(FaceDectedCV::scFrontalFaceExtended)));
            break;

        default:
            mpFaceDected->setMpFaceDected(std::shared_ptr<FaceDectedCV>(new FaceDectedCV(FaceDectedCV::scFaceCascadeName)));
            break;
        }
    }

    /**
     * @brief FaceServiceImpl::dectedROI 人测人脸区域
     * @param srcMat 被检测的图像矩阵
     * @return 返回所有检测到人脸的区域
     */
    std::vector<cv::Rect> FaceServiceImpl::dectedROI(const cv::Mat &srcMat)
    {
        return mpFaceDected->dectedROI(srcMat);
    }

    /**
     * @brief FaceServiceImpl::dectedMat 人脸检测图像
     * @param srcMat 被检测的图像矩阵
     * @return 返回所有人脸图像矩阵
     */
    std::vector<cv::Mat> FaceServiceImpl::dectedMat(const cv::Mat &srcMat)
    {
        return mpFaceDected->dectedMat(srcMat);
    }

    /**
     * @brief FaceServiceImpl::acquireFace 根据检测到的人脸区域裁剪图像矩阵
     * @param faceROIso 检测到的人脸区域
     * @param srcMat 图像矩阵
     * @return 返回所有人脸图像矩阵
     */
    std::vector<cv::Mat> FaceServiceImpl::acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat)
    {
        return mpFaceDected->acquireFace(faceROIs, srcMat);
    }

    /**
     * @brief FaceServiceImpl::scanFaceInfos 扫描人脸识别文件的路径
     * @return 返回所有人脸识别文件的路径
     */
    QStringList FaceServiceImpl::scanFaceInfos()
    {
//        QStringList faceInfoPaths;

//        QDir dir(FaceServiceImpl::sFaceInfoPath);
//        if (!dir.exists())
//        {
//            dir.mkdir(FaceServiceImpl::sFaceInfoPath);
//            return faceInfoPaths;
//        }

//        QStringList filters;
//        filters << QString("*.xml");

//        QDirIterator dir_iterator(FaceServiceImpl::sFaceInfoPath, filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
//        while (dir_iterator.hasNext())
//        {
//            dir_iterator.next();
//            QFileInfo file_info = dir_iterator.fileInfo();
//            faceInfoPaths.append(file_info.absoluteFilePath());
//        }

//        return faceInfoPaths;

        return mpFaceRecognition->scanFaceInfos();
    }

    void FaceServiceImpl::RecordFace(std::vector<QString> faceId, std::vector<cv::Mat> faceMat)
    {
        mpFaceRecognition->RecordFace(faceId, faceMat);
    }

    void FaceServiceImpl::save()
    {
        mpFaceRecognition->save();
    }

    /**
     * @brief FaceService::FaceService 人脸识别服务器，使用实现类单例
     * @param parent
     */
    FaceService::FaceService(QObject *parent) : QObject(parent), mpFaceServiceImpl(FaceServiceImpl::getInstance()), mpFaceDectedImpl(FaceServiceImpl::getInstance()), mpFaceRecongnition(FaceServiceImpl::getInstance())
    {
        // 利用摄像头桥接类实现从摄像头过滤类发送信息到qml界面
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curFps(QString)), this, SIGNAL(sigFps(QString)));
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curPixelFormat(QString)), this, SIGNAL(sigPixelFormat(QString)));
        connect(onechchy::CameraBridgeFace::getInstance(), SIGNAL(curFaceCount(int)), this, SIGNAL(sigFaceCount(int)));
    }

    FaceService *FaceService::createFaceService()
    {
        return new FaceService();
    }

    /**
     * @brief FaceService::switchFaceDectedMethod 切换人脸识别方法，主要调用的实现类对应的方法
     * @param methodId
     */
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

    QStringList FaceService::scanFaceInfos()
    {
        if (mpFaceServiceImpl != nullptr)
        {
            return mpFaceRecongnition->scanFaceInfos();
        }
    }

    void FaceService::RecordFace(std::vector<QString> faceId, std::vector<cv::Mat> faceMat)
    {
        if (mpFaceRecongnition != nullptr)
        {
            mpFaceRecongnition->RecordFace(faceId, faceMat);
        }
    }

    void FaceService::save()
    {
        if (mpFaceRecongnition != nullptr)
        {
            mpFaceRecongnition->save();
        }
    }

    void FaceService::addFace(QString faceId)
    {
        
    }
}
