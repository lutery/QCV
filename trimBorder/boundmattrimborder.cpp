#include "boundmattrimborder.h"
//#include <range/v3/core.hpp>
//#include <range/v3/view.hpp>
//#include <range/v3/view/iota.hpp>

namespace onechchy {

    BoundMatTrimBorder::BoundMatTrimBorder()
    {

    }

    cv::Mat BoundMatTrimBorder::trimBorder(const cv::Mat &srcMat, int border, QColor bgColor)
    {
        cv::Mat mat;

        if (srcMat.channels() == 4)
        {
            cv::cvtColor(srcMat, mat, cv::COLOR_BGRA2GRAY);
        }
        else if (srcMat.channels() == 3)
        {
            cv::cvtColor(srcMat, mat, cv::COLOR_BGR2GRAY);
        }
        else if (srcMat.channels() == 1)
        {
            mat = srcMat;
        }
        else
        {
            return mat;
        }

        // 采用自适应阈值进行二值化
//        cv::threshold(mat, mat, 0, 255, cv::THRESH_OTSU);
        cv::adaptiveThreshold(mat, mat, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 3, 5);

        std::vector<std::vector<cv::Point>> contours;
//        std::vector<cv::Vec4i> hierachy;

        // 查询外接多边形
//        cv::findContours(mat, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
        cv::findContours(mat, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        std::vector<std::vector<cv::Point>> contours_poly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());

        // 判断外接多边形
//        for (const auto& index : ranges::view::ints(0, (int)contours.size()))
        for (int index = 0, count = contours.size(); index < count; ++index)
        {
            // 对多边形矩阵做逼近处理
            cv::approxPolyDP(cv::Mat(contours[index]), contours_poly[index], 3, true);
            boundRect[index] = cv::boundingRect(cv::Mat(contours_poly[index]));
        }

        // 如果存在外接多边形，则寻找最大的矩形
        if (boundRect.size() > 0)
        {
            cv::Rect maxRect = boundRect[0];

            for (const auto& rect : boundRect)
            {
                if (maxRect.area() < rect.area())
                {
                    maxRect = rect;
                }
            }

            srcMat(maxRect).copyTo(mat);
        }

        return mat;
    }

}
