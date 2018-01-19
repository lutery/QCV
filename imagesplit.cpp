#include "imagesplit.h"
#include <QDebug>

namespace onechchy {
    ImageSplit::ImageSplit(QObject *parent) : QObject(parent)
    {

    }

    cv::Mat ImageSplit::kmeans(const cv::Mat &srcMat, int clusterCount)
    {
        qDebug() << "channels is " << srcMat.channels();
        int srcChannels = srcMat.channels();

        //生成一维采样点,包括所有图像像素点,注意采样点格式为32bit浮点数。
        cv::Mat samples(srcMat.cols*srcMat.rows, 1, CV_32FC3);
//        cv::Mat samples;
//        srcMat.convertTo(samples, CV_32FC3);
        //标记矩阵，32位整形
        cv::Mat labels(srcMat.cols*srcMat.rows, 1, CV_32SC1);
        if (srcChannels == 3 || srcChannels == 4)
        {
            {
                const uchar* p = nullptr;

                for(int i=0, k = 0; i < srcMat.rows; i++)
                {
                    p = srcMat.ptr<uchar>(i);
                    for(int j=0; j< srcMat.cols; j++)
                    {
                        samples.at<cv::Vec3f>(k,0)[0] = float(p[j*srcChannels]);
                        samples.at<cv::Vec3f>(k,0)[1] = float(p[j*srcChannels+1]);
                        samples.at<cv::Vec3f>(k,0)[2] = float(p[j*srcChannels+2]);
                        k++;
                    }
                }
            }
        }
        else if (srcChannels == 1)
        {
            {
                const uchar* p = nullptr;

                for(int i=0, k = 0; i < srcMat.rows; i++)
                {
                    p = srcMat.ptr<uchar>(i);
                    for(int j=0; j< srcMat.cols; j++)
                    {
                        samples.at<cv::Vec3f>(k,0)[0] = float(p[j*srcChannels]);
                        samples.at<cv::Vec3f>(k,0)[1] = float(p[j*srcChannels]);
                        samples.at<cv::Vec3f>(k,0)[2] = float(p[j*srcChannels]);
                        k++;
                    }
                }
            }
        }
        else
        {
            return cv::Mat();
        }

//         cv::imwrite("D:\\Test\\samples.bmp", samples);

        cv::Mat centers(clusterCount, 1, samples.type());
        cv::kmeans(samples, clusterCount, labels,
                   cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
                   3, cv::KMEANS_PP_CENTERS, centers);
        //我们已知有3个聚类，用不同的灰度层表示。
        cv::Mat img1(srcMat.rows, srcMat.cols, CV_8UC1);
//        cv::imwrite("D:\\Test\\srcMat.jpg", srcMat);
        float step = 255 / (clusterCount - 1);

        uchar* p = nullptr;
        for(int i=0, k = 0; i < img1.rows; ++i)
        {
            p = img1.ptr<uchar>(i);
            for(int j=0; j< img1.cols; ++j)
            {
                int tt = labels.at<int>(k, 0);
                k++;
                p[j] = 255 - tt*step;
            }
        }

         cv::imwrite("D:\\Test\\img1.jpg", img1);

        return img1;
    }
}
