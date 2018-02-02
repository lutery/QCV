#include "gopencvhandle.h"
#include "simageservice.h"

namespace onechchy {
    GOpenCVHandle::GOpenCVHandle()
    {

    }

    GOpenCVHandle::~GOpenCVHandle()
    {

    }

    bool GOpenCVHandle::canHanlde(int method)
    {
        return method == (int)SImageService::GBMethodType::GeneralGrayOpenCV;
    }

    cv::Mat GOpenCVHandle::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        cv::Mat dstMat;

        if (srcMat.empty())
        {
            return dstMat;
        }

        if (srcMat.channels() == 4)
        {
            cv::cvtColor(srcMat, dstMat, CV_BGRA2GRAY);
        }
        else if (srcMat.channels() == 3)
        {
            cv::cvtColor(srcMat, dstMat, CV_BGR2GRAY);
        }

        return dstMat;
    }
}
