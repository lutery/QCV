#ifndef FACEUTIL_H
#define FACEUTIL_H

#include <string>
#include <vector>
#include <dlib/opencv.h>
#include <opencv2\opencv.hpp>
#include <vector>
#include <QVector>

namespace FaceIdentifion {
    void FaceDectedHelper(cv::Mat& mat);
    std::vector<cv::Rect> FaceRectHelper(cv::Mat &mat);
    void FaceIDentifyHelper(std::vector<QString> faceId, QVector<cv::Mat> faces);
    void readCSVData(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
    void resizeData(std::vector<cv::Mat>& images, const cv::Size& size);
    std::vector<cv::Rect> dlibRect2cvRect(std::vector<dlib::rectangle> dlibRects);
    int string2int(QString strValue);
}

#endif // FACEUTIL_H
