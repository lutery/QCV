#ifndef GOPENCVHANDLE_H
#define GOPENCVHANDLE_H

#include "vgbhandle.h"

namespace onechchy {
    class GOpenCVHandle : public VGBHandle
    {
    public:
        GOpenCVHandle();
        virtual ~GOpenCVHandle();

    private:
        bool canHanlde(int method) override;
        cv::Mat InnerGBHandler(int method, ImageOperaParam* param, cv::Mat& srcMat) override;
    };
}

#endif // GOPENCVHANDLE_H
