#ifndef DITHERHANDLER_H
#define DITHERHANDLER_H

#include "vgbhandle.h"

namespace onechchy
{
    class BayerHandler: public VGBHandle
    {
    public:
        BayerHandler();
        virtual ~BayerHandler();

    private:
        cv::Mat createBayer(int n);
        cv::Mat toBayer(cv::Mat& srcMat, const cv::Mat& bayerMat, int bayerRatio);

        bool canHanlde(int method) override;
        cv::Mat InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat) override;
    };
}

#endif // DITHERHANDLER_H
