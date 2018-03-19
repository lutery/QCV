#ifndef FACEDECTEDCV_H
#define FACEDECTEDCV_H

#include "ifacedected.h"

namespace FaceIdentify {

    class FaceDectedCV : public IFaceDected
    {
    public:
        FaceDectedCV(cv::String cascadeName);
        virtual ~FaceDectedCV();

        // IFaceDected interface
    public:
        std::vector<cv::Rect> dectedROI(const cv::Mat &) override;
        std::vector<cv::Mat> dectedMat(const cv::Mat &) override;
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat) override;

        static cv::String scFaceCascadeName;
        static cv::String scFrontalFaceAltTree;
        static cv::String scFrontalFaceAlt;
        static cv::String scFrontalFaceAlt2;
        static cv::String scFrontalFace;
        static cv::String scFrontalFaceExtended;
        static cv::String scTrainingFaces;

    private:
        bool mbLoad = false;
        cv::Size mMinFace;
        cv::Size mMaxFace;
        cv::CascadeClassifier mFaceCascade;
    };

}

#endif // FACEDECTEDCV_H
