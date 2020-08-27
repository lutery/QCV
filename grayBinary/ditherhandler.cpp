#include "ditherhandler.h"
#include "simageservice.h"
#include <math.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

namespace onechchy
{

    BayerHandler::BayerHandler()
    {

    }

    BayerHandler::~BayerHandler()
    {

    }

    cv::Mat BayerHandler::createBayer(int n)
    {
        cv::Mat lastM = (cv::Mat_<uchar>(2, 2) << 0, 2, 3, 1);

        for (int i = 1; i < n; i++)
        {
            cv::Mat curM = cv::Mat(2 << i, 2 << i, CV_8UC1);
            cv::Mat lastU = cv::Mat::ones(1 << i, 1 << i, CV_8UC1);

            curM(cv::Rect(0, 0, 1 << i, 1 << i)) = 4 * lastM;
            curM(cv::Rect(1 << i, 0, 1 << i, 1 << i)) = 4 * lastM + 2 * lastU;
            curM(cv::Rect(0, 1 << i, 1 << i, 1 << i)) = 4 * lastM + 3 * lastU;
            curM(cv::Rect(1 << i, 1 << i, 1 << i, 1 << i)) = 4 * lastM + 1 * lastU;

            lastM = curM;
        }

        return lastM;
    }

    cv::Mat BayerHandler::toBayer(cv::Mat &srcMat, const cv::Mat &bayerMat, int bayerRatio)
    {
        cv::Mat bwMat = cv::Mat(srcMat.rows, srcMat.cols, CV_8UC1, cv::Scalar(255));

        unsigned char* pSrcData = srcMat.data;
        int srcStep = srcMat.step;
        unsigned char* pbwData = bwMat.data;
        int bwStep = bwMat.step;
        unsigned char* pbayerData = bayerMat.data;
        int bayerStep = bayerMat.step;
        uchar posLimit = std::pow(2, bayerRatio) - 1;
        uchar grayLevel = 8 - bayerRatio * 2;
        for (int i = 0; i < srcMat.rows; ++i)
        {
            /*unsigned char* pRow = demoMat.ptr<unsigned char>(i);
            unsigned char* pbwRow = bwMat.ptr<unsigned char>(i);*/
            for (int j = 0; j < srcMat.cols; ++j)
            {
                // m3.at<unsigned char>(i & 0x07, j & 0x07) 这段代码耗时，可以得知
                // at适合少量像素的访问，大量还是得靠指针
                /*if (((pRow[j] >> 2) < m3.at<unsigned char>(i & 0x07, j & 0x07)))
                {
                    pbwRow[j] = 0;
                }*/

                // m1 2X2 0x01 2^bayerRatio - 1
                // m2 4X4 0x03
                // m3 8X8 0x07
                // m4 16X16 0x15
                if (((pSrcData[i * srcStep + j] >> grayLevel) < pbayerData[(i & posLimit) * bayerStep + (j & posLimit)]))
                {
                    pbwData[i * bwStep + j] = 0;
                }
            }
        }

        return bwMat;
    }

    bool BayerHandler::canHanlde(int method)
    {
        return method == (int)SImageService::GBMethodType::BayerDither;
    }

    cv::Mat BayerHandler::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        QString jsonParam = param->jsonParam();
        QJsonParseError err_rpt;
        QJsonDocument root_doc = QJsonDocument::fromJson(jsonParam.toUtf8(), &err_rpt);

        if (err_rpt.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON格式错误";
            return srcMat;
        }

        if (srcMat.channels() > 1)
        {
            cv::imwrite("F:/Test/mat.png", srcMat);
            qDebug() << "not gray img";
            return srcMat;
        }

        int bayerRatio = root_doc.object().value("value").toInt();

        if (srcMat.empty() && (bayerRatio > 0 && bayerRatio <= 4))
        {
            return srcMat;
        }

        cv::Mat bayerTable = this->createBayer(bayerRatio);

        cv::Mat dstMat = this->toBayer(srcMat, bayerTable, bayerRatio);

        return dstMat;
    }

}
