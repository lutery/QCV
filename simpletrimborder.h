#ifndef SIMPLETRIMBORDER_H
#define SIMPLETRIMBORDER_H

#include "itrimingborder.h"

namespace onechchy {
    /**
     * @brief The SimpleTrimBorder class 简答切边函数，该类认定图形的背景是没有噪点的纯色，
     */
    class SimpleTrimBorder : public ITrimingBorder
    {
        Q_OBJECT
    public:
        explicit SimpleTrimBorder(QObject *parent = nullptr);

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    private:
        // 阈值抖动
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
