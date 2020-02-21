#include "resizecubicopencv.h"

namespace onechchy {

    ResizeCubicOpencv::ResizeCubicOpencv(QObject *parent) : ITransformImg(parent)
    {

    }

    cv::Mat ResizeCubicOpencv::transform(const cv::Mat &src, ImageOperaParam *imgOprParam)
    {
        cv::Mat dst;
        cv::resize(src, dst, cv::Size(imgOprParam->widthParam(), imgOprParam->heightParam()), 0, 0, cv::INTER_CUBIC);

        return dst;
    }

}
