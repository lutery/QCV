#include "vgbhandle.h"
#include "imgOperation/imageoperaparam.h"

namespace onechchy {
    VGBHandle::VGBHandle()
    {

    }

    VGBHandle::~VGBHandle()
    {

    }

    cv::Mat VGBHandle::GBHanlde(int method, ImageOperaParam *param, cv::Mat&& srcMat)
    {
        if (this->canHanlde(method))
        {
            return this->InnerGBHandler(method, param, srcMat);
        }
        else if (this->mpNext != nullptr)
        {
            return this->mpNext->GBHanlde(method, param, srcMat);
        }
        else
        {
            return cv::Mat();
        }
    }

    cv::Mat VGBHandle::GBHanlde(int method, ImageOperaParam *param, cv::Mat& srcMat)
    {
        if (this->canHanlde(method))
        {
            return this->InnerGBHandler(method, param, srcMat);
        }
        else if (this->mpNext != nullptr)
        {
            return this->mpNext->GBHanlde(method, param, srcMat);
        }
        else
        {
            return cv::Mat();
        }
    }

    VGBHandle *VGBHandle::getMpNext() const
    {
        return mpNext.get();
    }

    VGBHandle* VGBHandle::setMpNext(VGBHandle *value)
    {
        mpNext = std::shared_ptr<VGBHandle>(value);

        return mpNext.get();
    }
}
