#ifndef FACEUTIL_H
#define FACEUTIL_H

#include <string>
#include <vector>
#include <opencv2\opencv.hpp>
#include <vector>
#include <dlib/opencv.h>

namespace FaceIdentify {
    void FaceDectedHelper(cv::Mat& mat);
    std::vector<cv::Rect> FaceRectHelper(cv::Mat &mat);
    void readCSVData(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
    void resizeData(std::vector<cv::Mat>& images, const cv::Size& size);
    std::vector<cv::Rect> dlibRect2cvRect(std::vector<dlib::rectangle> dlibRects);
}

#endif // FACEUTIL_H
