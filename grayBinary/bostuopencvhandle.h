#ifndef BOSTUOPENCVHANDLE_H
#define BOSTUOPENCVHANDLE_H

#include "vgbhandle.h"

namespace onechchy {
    class BOSTUOpenCVHandle : public VGBHandle
    {
    public:
        BOSTUOpenCVHandle();
        virtual ~BOSTUOpenCVHandle();

    private:
        bool canHanlde(int method) override;
        cv::Mat InnerGBHandler(int method, ImageOperaParam* param, cv::Mat& srcMat) override;
    };
}

#endif // BOSTUOPENCVHANDLE_H
