#ifndef IMAGESPLIT_H
#define IMAGESPLIT_H

#include <QObject>
#include <opencv2/opencv.hpp>

namespace onechchy {
    class ImageSplit : public QObject
    {
        Q_OBJECT
    public:
        explicit ImageSplit(QObject *parent = nullptr);

        cv::Mat kmeans(const cv::Mat& srcMat, int clusterCount = 2);

    signals:

    public slots:
    };
}

#endif // IMAGESPLIT_H
