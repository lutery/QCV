#include "scannyerodetrimborder.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy {

    SCannyErodeTrimBorder::SCannyErodeTrimBorder()
    {
        mcErodeElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    }

    cv::Mat SCannyErodeTrimBorder::trimBorder(const cv::Mat &srcMat, int border, QColor bgColor)
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

        cv::erode(mat, mat, mcErodeElement);

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
