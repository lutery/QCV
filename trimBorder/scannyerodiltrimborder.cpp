#include "scannyerodiltrimborder.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy {

    ScannyEroDilTrimBorder::ScannyEroDilTrimBorder()
    {
        // 将腐蚀因子扩大到16x16的大小，这种大小情况下会对原图的区域产生很大的影响，需要进行膨胀操作
        mcErodeElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(16, 16));
    }

    cv::Mat ScannyEroDilTrimBorder::trimBorder(const cv::Mat &srcMat, int border, QColor bgColor)
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

        // 对图像进行膨胀和腐蚀操作，膨胀和腐蚀的参数因子需要使用相同的参数因子，这样才可以保证区域大致与原图相同
        cv::erode(mat, mat, mcErodeElement);

        cv::dilate(mat, mat, mcErodeElement);

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
