#include "boundmattrimborder.h"
#include <range/v3/core.hpp>
#include <range/v3/view.hpp>

namespace onechchy {

    BoundMatTrimBorder::BoundMatTrimBorder()
    {

    }

    cv::Mat BoundMatTrimBorder::trimBorder(const cv::Mat &srcMat, int border, QColor bgColor)
    {
        cv::Mat mat;

        if (srcMat.channels() == 4)
        {
            cv::cvtColor(srcMat, mat, CV_BGRA2GRAY);
        }
        else if (srcMat.channels() == 3)
        {
            cv::cvtColor(srcMat, mat, CV_BGR2GRAY);
        }
        else if (srcMat.channels() == 1)
        {
            mat = srcMat;
        }
        else
        {
            return mat;
        }

//        cv::threshold(mat, mat, 0, 255, cv::THRESH_OTSU);
        cv::adaptiveThreshold(mat, mat, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 3, 5);

        std::vector<std::vector<cv::Point>> contours;
//        std::vector<cv::Vec4i> hierachy;

        cv::findContours(mat, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

        std::vector<std::vector<cv::Point>> contours_poly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());

        for (const auto& index : ranges::view::ints(0, (int)contours.size()))
        {
            cv::approxPolyDP(cv::Mat(contours[index]), contours_poly[index], 3, true);
            boundRect[index] = cv::boundingRect(cv::Mat(contours_poly[index]));
        }

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
