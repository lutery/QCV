#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>

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
    int rgb2gray(int red, int green, int black);
    cv::Mat convertGray(const cv::Mat&);
}

#endif // IMAGEUTIL_H
