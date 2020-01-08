#ifndef TRANSFORMIMAGE_H
#define TRANSFORMIMAGE_H

#include <QObject>
#include <opencv2/opencv.hpp>

namespace onechchy {
    /**
     * @brief The TransformImage class 移动图像操作
     */
    class TransformImage : public QObject
    {
        Q_OBJECT
    public:
        static const int GRAY_THRESH = 150;
        static const int HOUGH_VOTE = 100;

    public:
        explicit TransformImage(QObject *parent = nullptr);

        cv::Mat inclineDFT(const cv::Mat&& p);

    signals:

    public slots:

    private:

    };
}

#endif // TRANSFORMIMAGE_H
