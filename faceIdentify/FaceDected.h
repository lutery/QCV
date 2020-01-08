#pragma once
#include "ifacedected.h"
#include <memory>
#include <QMutex>

namespace FaceIdentifion {

    class FaceDected : public IFaceDected
    {
    public:
        FaceDected();
        ~FaceDected();

        std::vector<cv::Rect> dectedROI(const cv::Mat&) override;
        std::vector<cv::Mat> dectedMat(const cv::Mat&) override;
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect>& faceROIs, const cv::Mat& srcMat) override;

//        static const cv::String scFaceCascadeName;
//        static const cv::String scTrainingFaces;

        void setMpFaceDected(const std::shared_ptr<IFaceDected> &value);

    private:
        QMutex mFaceLock;
        std::shared_ptr<IFaceDected> mpFaceDected;
        //        bool mbLoad = false;
//        cv::Size mMinFace;
//        cv::Size mMaxFace;
//        cv::CascadeClassifier mFaceCascade;
    };

}
