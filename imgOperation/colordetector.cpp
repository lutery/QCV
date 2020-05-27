#include "colordetector.h"

namespace onechchy {

    cv::Mat FloodDectector::detector(const cv::Mat &srcMat, cv::Vec3b &dstColor)
    {
        cv::Mat output = srcMat.clone();

        cv::floodFill(output,
                      cv::Point(100, 50),
                      cv::Scalar(255, 255, 255),
                      (cv::Rect*)0,
                      cv::Scalar(35, 35, 35),
                      cv::Scalar(35, 35, 35),
                      cv::FLOODFILL_FIXED_RANGE);

        return output;
    }

    int FloodDectector::getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor)
    {
        return -1;
    }

    cv::Mat onechchy::AbsdiffDectector::detector(const cv::Mat &srcMat, cv::Vec3b &dstColor)
    {
        cv::Mat output;
        cv::absdiff(srcMat, cv::Scalar(dstColor), output);

        // 把通道分割成3幅图像
        std::vector<cv::Mat> images;
        cv::split(output, images);

        output = images[0] + images[1] + images[2];

        cv::threshold(output, output, mMaxDist, 255, cv::THRESH_BINARY_INV);

        return output;
    }

    int AbsdiffDectector::getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor)
    {
        return -1;
    }

    cv::Mat NormDectector::detector(const cv::Mat &srcMat, cv::Vec3b &dstColor)
    {
        cv::Mat result(srcMat.size(), CV_8U);

        cv::Mat_<cv::Vec3b>::const_iterator it = srcMat.begin<cv::Vec3b>();
        cv::Mat_<cv::Vec3b>::const_iterator itend = srcMat.end<cv::Vec3b>();
        cv::Mat_<uchar>::iterator itout = result.begin<uchar>();

        for(; it != itend; ++itout)
        {
            if(getDistanceToTargetColor(*it, dstColor) <= mMaxDist){
                *itout = 255;
            }
            else{
                *itout = 0;
            }
        }

        return result;
    }

    int NormDectector::getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor)
    {
        return static_cast<int>(
                    cv::norm<int, 3>(cv::Vec3i(color[0] - detectColor[0],
                                    color[1] - detectColor[1],
                                    color[2] - detectColor[2]))
                    );
    }

    cv::Mat SimpleDectector::detector(const cv::Mat &srcMat, cv::Vec3b &dstColor)
    {
        cv::Mat result(srcMat.size(), CV_8U);
        // #e88e6c
        cv::Mat_<cv::Vec3b>::const_iterator it = srcMat.begin<cv::Vec3b>();
        cv::Mat_<cv::Vec3b>::const_iterator itend = srcMat.end<cv::Vec3b>();
        cv::Mat_<uchar>::iterator itout = result.begin<uchar>();

        for(; it != itend; ++itout, ++it)
        {
            if(getDistanceToTargetColor(*it, dstColor) <= mMaxDist){
                *itout = 255;
            }
            else{
                *itout = 0;
            }
        }

        return result;
    }

    int SimpleDectector::getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor)
    {
        return abs(color[0] - detectColor[0]) +
                abs(color[1] - detectColor[1]) +
                abs(color[2] - detectColor[2]);
    }
    
    int IColorDetector::getMaxDist() const
    {
        return mMaxDist;
    }
    
    void IColorDetector::setMaxDist(int maxDist)
    {
        mMaxDist = maxDist;
    }
    
}
