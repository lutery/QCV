#ifndef SIMPLETRIMBORDER_H
#define SIMPLETRIMBORDER_H

#include "itrimingborder.h"

namespace onechchy {
    class SimpleTrimBorder : public ITrimingBorder
    {
        Q_OBJECT
    public:
        explicit SimpleTrimBorder(QObject *parent = nullptr);

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    private:
        const int thresholdShake = 5;

        int leftBorder(const cv::Mat& mat, const QColor& bgColor);
        int rightBorder(const cv::Mat &mat, const QColor& bgColor);
        int topBorder(const cv::Mat &mat, const QColor& bgColor);
        int bottomBorder(const cv::Mat &mat, const QColor& bgColor);

    signals:

    public slots:
    };
}

#endif // SIMPLETRIMBORDER_H
