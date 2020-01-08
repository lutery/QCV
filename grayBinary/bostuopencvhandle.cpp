#include "bostuopencvhandle.h"
#include "simageservice.h"

namespace onechchy {
    BOSTUOpenCVHandle::BOSTUOpenCVHandle()
    {

    }

    BOSTUOpenCVHandle::~BOSTUOpenCVHandle()
    {

    }

    bool BOSTUOpenCVHandle::canHanlde(int method)
    {
        return method == (int)SImageService::GBMethodType::OSTUOpenCV;
    }

    cv::Mat BOSTUOpenCVHandle::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        cv::Mat dstMat;

        if (srcMat.empty())
        {
            return dstMat;
        }

        int threshold = cv::threshold(srcMat, dstMat, 0, 255, cv::THRESH_OTSU);

        return dstMat;
    }
}
