#include "transformimage.h"
#include <vector>
#include <math.h>
#include "imageutil.h"

namespace onechchy {
    TransformImage::TransformImage(QObject *parent) : QObject(parent)
    {

    }

    /**
     * @brief TransformImage::inclineDFT 适用于纯色背景（例如白色），一段文字、身份证扫描图等图像的纠偏
     * @param p
     * @return
     */
    cv::Mat TransformImage::inclineDFT(const cv::Mat&& p)
    {
        if (p.empty())
        {
            // ToDo 抛出异常
            return cv::Mat();
        }

        cv::Mat grayp = onechchy::convertGray(p);

        cv::Point center(grayp.cols / 2, grayp.rows / 2);

        cv::Mat padded;
        int opWidth = cv::getOptimalDFTSize(grayp.rows);
        int opHeight = cv::getOptimalDFTSize(grayp.cols);

        cv::copyMakeBorder(grayp, padded, 0, opWidth - grayp.rows, 0, opHeight - grayp.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

        cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
        cv::Mat comImg;
        cv::merge(planes, 2, comImg);

        cv::dft(comImg, comImg);

        cv::split(comImg, planes);
        cv::magnitude(planes[0], planes[1], planes[0]);

        cv::Mat magMat = planes[0];
        magMat += cv::Scalar::all(1);
        cv::log(magMat, magMat);

        magMat = magMat(cv::Rect(0, 0, magMat.cols & -2, magMat.rows & -2));

        int cx = magMat.cols / 2;
        int cy = magMat.rows / 2;

        cv::Mat q0(magMat, cv::Rect(0, 0, cx, cy));
        cv::Mat q1(magMat, cv::Rect(0, cy, cx, cy));
        cv::Mat q2(magMat, cv::Rect(cx, cy, cx, cy));
        cv::Mat q3(magMat, cv::Rect(cx, 0, cx, cy));

        cv::Mat tmp;
        q0.copyTo(tmp);
        q2.copyTo(q0);
        tmp.copyTo(q2);

        q1.copyTo(tmp);
        q3.copyTo(q1);
        tmp.copyTo(q3);

        cv::normalize(magMat, magMat, 0, 1, cv::NORM_MINMAX);
        cv::Mat magImg(magMat.size(), CV_8UC1);
        magMat.convertTo(magImg, CV_8UC1, 255, 0);

        cv::threshold(magImg, magImg, GRAY_THRESH, 255, cv::THRESH_BINARY);

        std::vector<cv::Vec2f> lines;
        float pi180 = (float)CV_PI / 180;
        cv::Mat linImg(magImg.size(), CV_8UC3);
        cv::HoughLines(magImg, lines, 1, pi180, HOUGH_VOTE, 0, 0);
        int numLines = lines.size();

//        for (int l = 0; l < numLines; ++l)
//        {
//            float rho = lines[l][0], theta = lines[l][1];
//            cv::Point pt1, pt2;
//            double a = std::cos(theta), b = std::sin(theta);
//            double x0 = a * rho, y0 = b * rho;
//            pt1.x = cvRound(x0 + 1000*(-b));
//            pt1.y = cvRound(y0 + 1000*(a));
//            pt2.x = cvRound(x0 - 1000*(-b));
//            pt2.y = cvRound(y0 - 1000*(a));
//            line(linImg,pt1,pt2,Scalar(255,0,0),3,8,0);
//        }

        float angel=0;
        float piThresh = (float)CV_PI/90;
        float pi2 = CV_PI/2;
        for(int l=0; l<numLines; l++)
        {
            float theta = lines[l][1];
            if(abs(theta) < piThresh || abs(theta-pi2) < piThresh)
                continue;
            else{
                angel = theta;
                break;
            }
        }

        angel = angel<pi2 ? angel : angel-CV_PI;
        if(angel != pi2){
            float angelT = grayp.rows*tan(angel)/grayp.cols;
            angel = atan(angelT);
        }
        float angelD = angel*180/(float)CV_PI;

        //Rotate the image to recover
        cv::Mat rotMat = cv::getRotationMatrix2D(center,angelD,1.0);
        cv::Mat dstImg = cv::Mat::ones(grayp.size(),CV_8UC3);
        cv::warpAffine(grayp,dstImg,rotMat,grayp.size(),1,0,cv::Scalar(255,255,255));

        return dstImg;
    }

    cv::Mat TransformImage::resizeImg(const cv::Mat &&src, int dstWidth, int dstHeight)
    {
        cv::Mat dstMat;

        if (dstWidth > 0 && dstHeight > 0)
        {
            cv::resize(src, dstMat, cv::Size(dstWidth, dstHeight));
        }
        else
        {
            dstMat = src;
        }

        return dstMat;
    }
}
