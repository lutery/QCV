#include "btriangleopencvhandle.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy {
    BTriangleOpenCVHandle::BTriangleOpenCVHandle()
    {

    }

    BTriangleOpenCVHandle::~BTriangleOpenCVHandle()
    {

    }

    bool BTriangleOpenCVHandle::canHanlde(int method)
    {
        qDebug() << "BOSTUOpenCVHandle canHandle process";
        return method == (int)SImageService::GBMethodType::TriangleOpenCV;
    }

    cv::Mat BTriangleOpenCVHandle::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        cv::Mat dstMat;

        if (srcMat.empty())
        {
            return dstMat;
        }

        int threshold = cv::threshold(srcMat, dstMat, 0, 255, cv::THRESH_TRIANGLE);

        return dstMat;
    }
}
