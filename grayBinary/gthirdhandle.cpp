#include "gthirdhandle.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy {
    GThirdHandle::GThirdHandle()
    {

    }

    bool onechchy::GThirdHandle::canHanlde(int method)
    {
        qDebug() << "GThridHandle canHandle method " << method;
        return method == (int)SImageService::GBMethodType::GeneralGrayThird;
    }

    cv::Mat onechchy::GThirdHandle::InnerGBHandler(int method, onechchy::ImageOperaParam *param, cv::Mat &srcMat)
    {
        cv::Mat dstMat(srcMat.rows, srcMat.cols, CV_8UC1);

        if (srcMat.channels() == 4)
        {
            this->bgra2gray(srcMat, dstMat, param);
        }
        else if (srcMat.channels() == 3)
        {
            this->bgr2gray(srcMat, dstMat, param);
        }

        return dstMat;
    }

    void GThirdHandle::bgra2gray(cv::Mat &srcMat, cv::Mat &dstMat, onechchy::ImageOperaParam *param)
    {
        for (int y = 0; y < srcMat.rows; ++y)
        {
            uchar* sptr = srcMat.ptr(y);
            uchar* dptr = dstMat.ptr(y);
            for (int x = 0; x < srcMat.cols; ++x)
            {
                dptr[x] = (uchar)((sptr[x * 4 + 2]*19595 + sptr[x * 4 + 1]*38469 + sptr[x * 4 + 0]*7472) >> 16);
            }
        }
    }

    void GThirdHandle::bgr2gray(cv::Mat &srcMat, cv::Mat &dstMat, onechchy::ImageOperaParam *param)
    {
        for (int y = 0; y < srcMat.rows; ++y)
        {
            uchar* sptr = srcMat.ptr(y);
            uchar* dptr = dstMat.ptr(y);
            for (int x = 0; x < srcMat.cols; ++x)
            {
                dptr[x] = (uchar)((sptr[x * 3 + 2]*19595 + sptr[x * 3 + 1]*38469 + sptr[x * 3 + 0]*7472) >> 16);
            }
        }
    }
}

