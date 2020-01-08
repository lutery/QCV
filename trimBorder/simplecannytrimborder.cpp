#include "simplecannytrimborder.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy {
    SimpleCannyTrimBorder::SimpleCannyTrimBorder()
    {

    }

    cv::Mat SimpleCannyTrimBorder::trimBorder(const cv::Mat &srcMat, int border, QColor bgColor)
    {
        cv::Mat mat;

        // 如果图像不是灰度图，那么将其转换为灰度图
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

        // 根据网络上的资料显示，threshold1与threshold2之间的参数比值在1:2或1:3之间比较好，这里选用25:50可以尽可能的保留边界信息的情况下减少冗余边界信息
        cv::Canny(mat, mat, 25, 50);

        int left = 0;
        int right = mat.cols;
        int top = 0;
        int bottom = mat.rows;

        if ((border & SImageService::Left) != 0x00)
        {
            left = this->leftBorder(mat, bgColor);
        }

        if ((border & SImageService::Right) != 0x00)
        {
            right = this->rightBorder(mat, bgColor);
        }

        if ((border & SImageService::Top) != 0x00)
        {
            top = this->topBorder(mat, bgColor);
        }

        if ((border & SImageService::Bottom) != 0x00)
        {
            bottom = this->bottomBorder(mat, bgColor);
        }

        qDebug() << " left " << left << " right " << right << " top " << top << " bottom " << bottom;

        cv::Rect trimRect(left, top, right - left, bottom - top);

        if (trimRect.width > 0 && trimRect.height > 0)
        {
            return srcMat(trimRect);
        }

        return srcMat;
    }
}
