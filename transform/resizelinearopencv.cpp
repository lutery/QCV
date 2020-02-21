#include "resizelinearopencv.h"

namespace onechchy {

    ResizeLinearOpencv::ResizeLinearOpencv(QObject *parent) : ITransformImg(parent)
    {

    }

    cv::Mat ResizeLinearOpencv::transform(const cv::Mat &src, ImageOperaParam *imgOprParam)
    {
        cv::Mat dst;
        cv::resize(src, dst, cv::Size(imgOprParam->widthParam(), imgOprParam->heightParam()), 0, 0, cv::INTER_LINEAR);

        return dst;
    }
}
