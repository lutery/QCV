#ifndef ITRANSFORMIMG_H
#define ITRANSFORMIMG_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "../imgOperation/imageoperaparam.h"

namespace onechchy {
    class ITransformImg : public QObject
    {
        Q_OBJECT
    public:
        explicit ITransformImg(QObject *parent = nullptr);

        virtual cv::Mat transform(const cv::Mat&, ImageOperaParam* imgOprParam) = 0;

    signals:

    };
}

#endif // ITRANSFORMIMG_H
