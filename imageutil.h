#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>

namespace onechchy {
    class ImageUtil : public QObject
    {
        Q_OBJECT
    public:
        explicit ImageUtil(QObject *parent = nullptr);

        static cv::Mat convertGray(const cv::Mat&);
        static QImage cvMat2QImage(const cv::Mat& mat);
        static cv::Mat QImage2cvMat(const QImage& image );
    signals:

    public slots:
    };
}

#endif // IMAGEUTIL_H
