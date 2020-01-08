#ifndef BOPENCVHANDLE_H
#define BOPENCVHANDLE_H

#include "vgbhandle.h"

namespace onechchy{
    class BOpenCVHandle : public VGBHandle
    {
    public:
        BOpenCVHandle();
        virtual ~BOpenCVHandle();

    private:
        bool canHanlde(int method) override;
        cv::Mat InnerGBHandler(int method, ImageOperaParam* param, cv::Mat& srcMat) override;
    };
}

#endif // BOPENCVHANDLE_H
