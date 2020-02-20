#ifndef REISZENEAROPENCV_H
#define REISZENEAROPENCV_H

#include <QObject>
#include "itransformimg.h"

namespace onechchy {
    class ReiszeNearOpencv : public ITransformImg
    {
    public:
        ReiszeNearOpencv();



        // ITransformImg interface
    public:
        cv::Mat transform(const cv::Mat &, ImageOperaParam* imgOprParam) override;
    };
}

#endif // REISZENEAROPENCV_H
