#include "bopencvhandle.h"
#include "simageservice.h"

namespace onechchy{
    BOpenCVHandle::BOpenCVHandle()
    {

    }

    BOpenCVHandle::~BOpenCVHandle()
    {

    }

    bool BOpenCVHandle::canHanlde(int method)
    {
        return method == (int)SImageService::GBMethodType::CustomBinaryOpenCV;
    }

    cv::Mat BOpenCVHandle::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        cv::Mat dstMat;

        if (srcMat.empty())
        {
            return dstMat;
        }

        int threshold = param->gbParam();

        if (threshold < 0)
        {
            threshold = 1;
        }
        else if (threshold > 255)
        {
            threshold = 254;
        }

        cv::threshold(srcMat, dstMat, threshold, 255, cv::THRESH_BINARY);

        return dstMat;
    }
}
