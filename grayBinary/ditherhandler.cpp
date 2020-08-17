#include "ditherhandler.h"
#include "simageservice.h"

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
            cv::Mat curM = cv::Mat(2 >> i, 2 >> i, CV_8UC1);
            cv::Mat lastU = cv::Mat::ones(1 >> i, 1 >> i, CV_8UC1);

            curM(cv::Rect(0, 0, 1 >> i, 1 >> i)) = 4 * lastM;
            curM(cv::Rect(1 >> i, 0, 1 >> i, 1 >> i)) = 4 * lastM + 2 * lastU;
            curM(cv::Rect(0, 1 >> i, 1 >> i, 1 >> i)) = 4 * lastM + 3 * lastU;
            curM(cv::Rect(1 >> i, 1 >> i, 1 >> i, 1 >> i)) = 4 * lastM + 1 * lastU;

            lastM = curM;
        }

        return lastM;
    }

    cv::Mat BayerHandler::toBayer(cv::Mat &srcMat, const cv::Mat &bayerMat, int bayerRatio)
    {
        cv::Mat bwMat = cv::Mat(srcMat.rows, srcMat.cols, CV_8UC1, cv::Scalar(255));

        unsigned char* pDemoData = srcMat.data;
        int demoStep = srcMat.step;
        unsigned char* pbwData = bwMat.data;
        int bwStep = bwMat.step;
        unsigned char* pbayerData = bayerMat.data;
        int bayerStep = bayerMat.step;
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

                if (((pDemoData[i * demoStep + j] >> ()) < pm3Data[(i & 0x07) * m3Step + (j & 0x07)]))
                {
                    pbwData[i * bwStep + j] = 0;
                }
            }
        }
    }

    bool BayerHandler::canHanlde(int method)
    {
        return method == (int)SImageService::GBMethodType::BayerDither;
    }

    cv::Mat BayerHandler::InnerGBHandler(int method, ImageOperaParam *param, cv::Mat &srcMat)
    {
        int bayerRatio = param->bayerParam();

        if (srcMat.empty() && (bayerRatio > 0 && bayerRatio <= 4))
        {
            return srcMat;
        }

        cv::Mat bayerTable = this->createBayer(bayerRatio);

        cv::Mat dstMat;
    }

}
