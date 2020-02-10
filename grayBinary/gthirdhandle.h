#ifndef GTHIRDHANDLE_H
#define GTHIRDHANDLE_H

#include "vgbhandle.h"

namespace onechchy {
    class GThirdHandle : public VGBHandle
    {
    public:
        explicit GThirdHandle();

    signals:

    private:
        bool canHanlde(int method) override;
        cv::Mat InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat) override;

        void bgra2gray(cv::Mat& srcMat, cv::Mat& dstMat, onechchy::ImageOperaParam *param);
        void bgr2gray(cv::Mat& srcMat, cv::Mat& dstMat, onechchy::ImageOperaParam *param);
    };
}

#endif // GTHIRDHANDLE_H
