#ifndef IFACEDECTED_H
#define IFACEDECTED_H

#include <opencv2\opencv.hpp>
#include <vector>

namespace FaceIdentify {

    class IFaceDected
    {
    public:
        // 侦测面部区域
        virtual std::vector<cv::Rect> dectedROI(const cv::Mat&) = 0;
        // 获取面部图片
        virtual std::vector<cv::Mat> dectedMat(const cv::Mat&) = 0;
        // 根据面部区域与原始图片获取面部图片
        virtual std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect>& faceROIs, const cv::Mat& srcMat) = 0;
    };

}

#endif // IFACEDECTED_H
