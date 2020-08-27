#ifndef BADAPTIVEOPENCVHANDLE_H
#define BADAPTIVEOPENCVHANDLE_H

#include "vgbhandle.h"

namespace onechchy
{
    class BAdaptiveOpenCVHandle : public VGBHandle
    {
    public:
        BAdaptiveOpenCVHandle();
        virtual ~BAdaptiveOpenCVHandle();

    private:
        bool canHanlde(int method) override;
        cv::Mat InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat) override;
    };
}

#endif // BADAPTIVEOPENCVHANDLE_H
