#include "simpletrimborder.h"
#include "imageutil.h"
#include <range/v3/core.hpp>
#include <range/v3/view.hpp>
#include <QDebug>
#include "simageservice.h"

namespace onechchy {
    SimpleTrimBorder::SimpleTrimBorder(QObject *parent) : ITrimingBorder(parent)
    {

    }

    cv::Mat SimpleTrimBorder::trimBorder(const cv::Mat& srcMat, int border, QColor bgColor)
    {
        cv::Mat bwMat = ImageUtil::convertGray(srcMat);

        if (bwMat.empty())
        {
            return srcMat;
        }

//        if (srcMat.channels() == 4)
//        {
//            cv::cvtColor(srcMat, bwMat, CV_BGRA2GRAY);
//        }
//        else if (srcMat.channels() == 3)
//        {
//            cv::cvtColor(srcMat, bwMat, CV_BGR2GRAY);
//        }
//        else if (srcMat.channels() == 1)
//        {
//            bwMat = srcMat;
//        }
//        else
//        {
//            qDebug() << "mat channel error";
//            return srcMat;
//        }

        int left = 0;
        int right = srcMat.cols;
        int top = 0;
        int bottom = srcMat.rows;

        if ((border & SImageService::Left) != 0x00)
        {
            left = this->leftBorder(bwMat, bgColor);
        }

        if ((border & SImageService::Right) != 0x00)
        {
            right = this->rightBorder(bwMat, bgColor);
        }

        if ((border & SImageService::Top) != 0x00)
        {
            top = this->topBorder(bwMat, bgColor);
        }

        if ((border & SImageService::Bottom) != 0x00)
        {
            bottom = this->bottomBorder(bwMat, bgColor);
        }

        cv::Rect trimRect(left, top, right - left, bottom - top);

        if (trimRect.width > 0 && trimRect.height > 0)
        {
            return srcMat(trimRect);
        }

        return srcMat;
    }

    int SimpleTrimBorder::topBorder(const cv::Mat &mat, const QColor& bgColor)
    {
        int width = mat.cols;
        int height = mat.rows;
        uchar* pStart = mat.data;

        int threshold = ImageUtil::rgb2gray(bgColor.red(), bgColor.green(), bgColor.blue()) + this->thresholdShake;

//        for (int y = 0; y < height; ++y)
//        {
//            uchar* pRow = pStart + y * width;
//            for (int x = 0; x < width; ++x)
//            {
//                if (pRow[x] > threshold)
//                {
//                    return 0;
//                }
//            }
//        }

        for (const auto& y : ranges::view::ints(0, height)/* | ranges::view::reverse*/)
        {
            uchar* pRow = pStart + y * width;
            for (const auto& x : ranges::view::ints(0, width))
            {
                if (pRow[x] > threshold)
                {
                    return y;
                }
            }
        }

        return 0;
    }

    int SimpleTrimBorder::bottomBorder(const cv::Mat &mat, const QColor& bgColor)
    {
        int width = mat.cols;
        int height = mat.rows;
        uchar* pStart = mat.data;

        int threshold = ImageUtil::rgb2gray(bgColor.red(), bgColor.green(), bgColor.blue()) + this->thresholdShake;

        for (const auto& y : ranges::view::ints(0, height) | ranges::view::reverse)
        {
            uchar* pRow = pStart + y * width;
            for (const auto& x : ranges::view::ints(0, width)/* | ranges::view::reverse*/)
            {
                if (pRow[x] > threshold)
                {
                    return y;
                }
            }
        }


        return mat.cols;
    }

    int SimpleTrimBorder::leftBorder(const cv::Mat &mat, const QColor& bgColor)
    {
        int width = mat.cols;
        int height = mat.rows;
        uchar* pStart = mat.data;

        int threshold = ImageUtil::rgb2gray(bgColor.red(), bgColor.green(), bgColor.blue()) + this->thresholdShake;

        for (const auto& x : ranges::view::ints(0, width)/* | ranges::view::reverse*/)
        {
            for (const auto& y : ranges::view::ints(0, height))
            {
                if (pStart[width * y + x] > threshold)
                {
                    return x;
                }
            }
        }

        return 0;
    }

    int SimpleTrimBorder::rightBorder(const cv::Mat &mat, const QColor& bgColor)
    {
        int width = mat.cols;
        int height = mat.rows;
        uchar* pStart = mat.data;

        int threshold = ImageUtil::rgb2gray(bgColor.red(), bgColor.green(), bgColor.blue()) + this->thresholdShake;

        for (const auto& x : ranges::view::ints(0, width) | ranges::view::reverse)
        {
            for (const auto& y : ranges::view::ints(0, height)/* | ranges::view::reverse*/)
            {
                if (pStart[width * y + x] > threshold)
                {
                    return x;
                }
            }
        }

        return mat.rows;
    }
}
