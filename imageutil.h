#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QVideoFrame>

namespace onechchy {
//    class ImageUtil : public QObject
//    {
//        Q_OBJECT
//    public:
//        explicit ImageUtil(QObject *parent = nullptr);

//        static int rgb2gray(int red, int green, int black);
//        static cv::Mat convertGray(const cv::Mat&);
//        static QImage cvMat2QImage(const cv::Mat& mat);
//        static cv::Mat QImage2cvMat(const QImage& image);
//    signals:

//    public slots:
//    };

    QImage cvMat2QImage(const cv::Mat& mat);
    cv::Mat QImage2cvMat(const QImage& image);
    QVideoFrame cvMat2QVideoFrame(const cv::Mat& mat);
    cv::Mat QVideoFrame2cvMat(QVideoFrame &frame);
    int rgb2gray(int red, int green, int black);
    cv::Mat convertGray(const cv::Mat&);
    cv::Rect qRect2cvRect(const QRect &qrect);
    QRect cvRect2qRect(const cv::Rect &cvRect);
    cv::Mat cvMatAlign3(const cv::Mat& srcMat);
}

#endif // IMAGEUTIL_H
