#include "gopencvhandle.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy {
    GOpenCVHandle::GOpenCVHandle()
    {

    }

    GOpenCVHandle::~GOpenCVHandle()
    {

    }

    bool GOpenCVHandle::canHanlde(int method)
    {
        qDebug() << "BOSTUOpenCVHandle canHandle process";
        return method == (int)SImageService::GBMethodType::GeneralGrayOpenCV;
    }

    cv::Mat GOpenCVHandle::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        cv::Mat dstMat;

        if (srcMat.channels() == 4)
        {
            cv::cvtColor(srcMat, dstMat, cv::COLOR_BGRA2GRAY);
        }
        else if (srcMat.channels() == 3)
        {
            cv::cvtColor(srcMat, dstMat, cv::COLOR_BGR2GRAY);
        }

        return dstMat;
    }
}
