#pragma once
#include <string>
#include <opencv2\face.hpp>
#include <vector>

namespace FaceIdentifion {

    class FaceIdentify
    {
    public:
        FaceIdentify();
        ~FaceIdentify();

        void trainEigenModel(std::vector<cv::Mat> faceImgs, std::vector<int> faceLabels);
        void trainFisherModel(std::vector<cv::Mat> faceImgs, std::vector<int> faceLabels);
        void trainLBPModel(std::vector<cv::Mat> faceImgs, std::vector<int> faceLabels);

        void saveModel();

        int predictEigenModel(cv::Mat faceImg);
        int predictFisherModel(cv::Mat faceImg);
        int predictLBPModel(cv::Mat faceImg);

    private:
        static const std::string scEigenModelPath;
        static const std::string scFisherModelPath;
        static const std::string scLBPHModelPath;

        bool mbLoadEigen = false;
        bool mbLoadFisher = false;
        bool mbLoadLBP = false;

        cv::Ptr<cv::face::FaceRecognizer> mEigenModel;
        cv::Ptr<cv::face::FaceRecognizer> mFisherModel;
        cv::Ptr<cv::face::FaceRecognizer> mLBPModel;
    };

}

