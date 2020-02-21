#ifndef RESIZELINEAROPENCV_H
#define RESIZELINEAROPENCV_H

#include "itransformimg.h"

namespace onechchy {
    class ResizeLinearOpencv : public ITransformImg
    {
    public:
        explicit ResizeLinearOpencv(QObject *parent = nullptr);

    signals:


        // ITransformImg interface
    public:
        cv::Mat transform(const cv::Mat &, ImageOperaParam *imgOprParam) override;
    };
}

#endif // RESIZELINEAROPENCV_H
