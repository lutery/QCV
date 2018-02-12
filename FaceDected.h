#pragma once
#include <opencv2\opencv.hpp>
#include <vector>

namespace FaceIdentify {

    class FaceDected
    {
    public:
        FaceDected();
        ~FaceDected();

        std::vector<cv::Rect> dectedROI(const cv::Mat&);
        std::vector<cv::Mat> dectedMat(const cv::Mat&);
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect>& faceROIs, const cv::Mat& srcMat);

        static const cv::String scFaceCascadeName;
        static const cv::String scTrainingFaces;

    private:
        bool mbLoad = false;
        cv::Size mMinFace;
        cv::Size mMaxFace;
        cv::CascadeClassifier mFaceCascade;
    };

}
