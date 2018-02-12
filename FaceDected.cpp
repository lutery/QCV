#include "FaceDected.h"
#include <iostream>

namespace FaceIdentify {

    const cv::String FaceDected::scFaceCascadeName = R"(F:\Projects\Windows\C++\VC\FaceDetectedIdentify\FaceDetectedIdentify\haarcascades\haarcascade_frontalface_default.xml)";
    const cv::String FaceDected::scTrainingFaces = R"(F:\Projects\Windows\C++\VC\FaceDetectedIdentify\FaceDetectedIdentify\data\faces.txt)";

    FaceDected::FaceDected() : mMinFace(10, 10), mMaxFace(1000, 1000)
    {
        mbLoad = mFaceCascade.load(FaceDected::scFaceCascadeName);

        if (!mbLoad)
        {
            std::cout << "load file identify file failed" << std::endl;
        }
    }


    FaceDected::~FaceDected()
    {

    }

    std::vector<cv::Mat> FaceDected::dectedMat(const cv::Mat& srcMat)
    {
        std::vector<cv::Rect> faces = this->dectedROI(srcMat);
        std::vector<cv::Mat> faceMats;

        for (const auto& face : faces)
        {
            cv::Mat tmp;
            srcMat(face).copyTo(tmp);
            faceMats.push_back(std::move(tmp));
        }

        return faceMats;
    }

    std::vector<cv::Mat> FaceDected::acquireFace(const std::vector<cv::Rect>& faceROIs, const cv::Mat & srcMat)
    {
        std::vector<cv::Mat> faceMats;

        for (const auto& face : faceROIs)
        {
            cv::Mat tmp;
            srcMat(face).copyTo(tmp);
            faceMats.push_back(tmp);
        }

        return faceMats;
    }

    std::vector<cv::Rect> FaceDected::dectedROI(const cv::Mat& srcMat)
    {
        std::vector<cv::Rect> faces;

        do
        {
            if (!mbLoad)
            {
                break;
            }

            if (srcMat.channels() > 1 && srcMat.empty())
            {
                std::cout << "mat is invalid, only gray mat" << std::endl;
                break;
            }

            //关键在最后两个参数是检测脸的最小尺寸以及最大的尺寸，如果不在这两个尺寸范围内的点是检测不出来的
            mFaceCascade.detectMultiScale(srcMat, faces, 1.1, 4, CV_HAAR_DO_ROUGH_SEARCH, mMinFace, mMaxFace);

        } while (false);

        return faces;
    }

}
