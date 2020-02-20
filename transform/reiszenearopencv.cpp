#include "reiszenearopencv.h"

namespace onechchy {
    ReiszeNearOpencv::ReiszeNearOpencv()
    {

    }

    cv::Mat onechchy::ReiszeNearOpencv::transform(const cv::Mat &src, onechchy::ImageOperaParam* imgOprParam)
    {
        cv::Mat dst;

        cv::resize(src, dst, cv::Size(imgOprParam->widthParam(), imgOprParam->heightParam()), 0, 0, cv::INTER_NEAREST);

        return dst;
    }
}
