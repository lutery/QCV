#include "badaptiveopencvhandle.h"
#include "simageservice.h"
#include <QDebug>

namespace onechchy
{
    BAdaptiveOpenCVHandle::BAdaptiveOpenCVHandle()
    {

    }

    BAdaptiveOpenCVHandle::~BAdaptiveOpenCVHandle()
    {

    }

    bool BAdaptiveOpenCVHandle::canHanlde(int method)
    {
        return (int)SImageService::GBMethodType::AdapOpenCV == method;
    }

    cv::Mat BAdaptiveOpenCVHandle::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        if (srcMat.empty())
        {
            return srcMat;
        }

        QString jsonParam = param->jsonParam();
        QJsonParseError err_rpt;
        QJsonDocument root_doc = QJsonDocument::fromJson(jsonParam.toUtf8(), &err_rpt);

        if (err_rpt.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON格式错误";
            return srcMat;
        }

        /*
         * {
         * "maxValue":255,
         * "method":generate/gaussian
         * "type":CV_THRESH_BINARY/CV_THRESH_BINARY_INV
         * "blockSize":3
         * "delta":30
         * }
         */

        double maxValue = root_doc.object().value("maxValue").toDouble();
        int bmethod = root_doc.object().value("method").toInt();
        int type = root_doc.object().value("type").toInt();
        int blockSize = root_doc.object().value("blockSize").toInt();
        double delta = root_doc.object().value("delta").toDouble();

        if (bmethod < cv::ADAPTIVE_THRESH_MEAN_C)
        {
            bmethod = cv::ADAPTIVE_THRESH_MEAN_C;
        }
        else if (bmethod > cv::ADAPTIVE_THRESH_GAUSSIAN_C)
        {
            bmethod = cv::ADAPTIVE_THRESH_GAUSSIAN_C;
        }

        if (type < cv::THRESH_BINARY)
        {
            type = cv::THRESH_BINARY;
        }
        else if (type > cv::THRESH_BINARY_INV)
        {
            type = cv::THRESH_BINARY_INV;
        }

        if (blockSize < 3)
        {
            blockSize = 3;
        }
        else if (blockSize % 2 == 0)
        {
            blockSize += 1;
        }

        cv::Mat dstMat;
        cv::adaptiveThreshold(srcMat, dstMat, maxValue, bmethod, type, blockSize, delta);

        return dstMat;
    }


}
