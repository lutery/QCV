#include "bopencvhandle.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy{
    BOpenCVHandle::BOpenCVHandle()
    {

    }

    BOpenCVHandle::~BOpenCVHandle()
    {

    }

    bool BOpenCVHandle::canHanlde(int method)
    {
        qDebug() << "BOpenCVHandle canHandle process";
        return method == (int)SImageService::GBMethodType::CustomBinaryOpenCV;
    }

    cv::Mat BOpenCVHandle::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        cv::Mat dstMat;

        if (srcMat.empty())
        {
            return dstMat;
        }

        QString jsonParam = param->jsonParam();
        QJsonParseError err_rpt;
        QJsonDocument root_doc = QJsonDocument::fromJson(jsonParam.toUtf8(), &err_rpt);

        if (err_rpt.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON格式错误";
            return dstMat;
        }

        int threshold = root_doc.object().value("value").toInt();

        if (threshold < 0)
        {
            threshold = 1;
        }
        else if (threshold > 255)
        {
            threshold = 254;
        }

        cv::threshold(srcMat, dstMat, threshold, 255, cv::THRESH_BINARY);

        return dstMat;
    }
}
