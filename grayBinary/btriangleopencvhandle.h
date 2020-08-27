#ifndef BTRIANGLEOPENCVHANDLE_H
#define BTRIANGLEOPENCVHANDLE_H

#include "vgbhandle.h"

namespace onechchy
{
    class BTriangleOpenCVHandle : public VGBHandle
    {
    public:
        BTriangleOpenCVHandle();
        ~BTriangleOpenCVHandle();

    private:
        bool canHanlde(int method) override;
        cv::Mat InnerGBHandler(int method, ImageOperaParam* param, cv::Mat& srcMat) override;
    };
}

#endif // BTRIANGLEOPENCVHANDLE_H
