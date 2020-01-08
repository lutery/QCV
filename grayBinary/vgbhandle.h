#ifndef VGBHANDLE_H
#define VGBHANDLE_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "imgOperation/imageoperaparam.h"

namespace onechchy {

    class VGBHandle
    {
    public:
        VGBHandle();
        virtual ~VGBHandle();

        cv::Mat GBHanlde(int method, ImageOperaParam* param, cv::Mat&& srcMat);
        cv::Mat GBHanlde(int method, ImageOperaParam *param, cv::Mat& srcMat);

        VGBHandle* getMpNext() const;
        void setMpNext(VGBHandle* value);

    private:
        virtual bool canHanlde(int method) = 0;
        virtual cv::Mat InnerGBHandler(int method, ImageOperaParam* param, cv::Mat& srcMat) = 0;

        std::shared_ptr<VGBHandle> mpNext = nullptr;
    };
}

#endif // VGBHANDLE_H
