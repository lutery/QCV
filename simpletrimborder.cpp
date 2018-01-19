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

    /**
     * @brief SimpleTrimBorder::trimBorder 切边函数
     * @param srcMat 源图形
     * @param border 切边信息
     * @param bgColor 背景颜色
     * @return 返回切边后的图形
     */
    cv::Mat SimpleTrimBorder::trimBorder(const cv::Mat& srcMat, int border, QColor bgColor)
    {
        // 现在默认只支持灰度图裁边，也就是背景为黑色的图形
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

    /**
     * @brief SimpleTrimBorder::topBorder 顶部切边
     * @param mat
     * @param bgColor
     * @return 返回边界索引
     */
    int SimpleTrimBorder::topBorder(const cv::Mat &mat, const QColor& bgColor)
    {
        int width = mat.cols;
        int height = mat.rows;
        uchar* pStart = mat.data;

        // 将背景转换为灰度信息
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

        // 使用range-v3标准库进行循环遍历扫描。
        // 因为寻找的是顶边，所以这里以行进行扫描，一旦一个行有一个亮点，那么这行将被认为是边界
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

    /**
     * @brief SimpleTrimBorder::leftBorder 寻找左边界
     * @param mat
     * @param bgColor
     * @return 返回左边界索引
     */
    int SimpleTrimBorder::leftBorder(const cv::Mat &mat, const QColor& bgColor)
    {
        int width = mat.cols;
        int height = mat.rows;
        uchar* pStart = mat.data;

        int threshold = ImageUtil::rgb2gray(bgColor.red(), bgColor.green(), bgColor.blue()) + this->thresholdShake;

        // 因为是左边界，进行的是列扫描，一旦该列存在一个点事亮点，就认为该索引是边界返回
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
