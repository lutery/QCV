#ifndef PARTITIONTRIMBORDER_H
#define PARTITIONTRIMBORDER_H

#include "scannyerodiltrimborder.h"

namespace onechchy {

    class PartitionTrimBorder : public ScannyEroDilTrimBorder
    {
    public:
        PartitionTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    protected:
        bool leftTopPoint(const cv::Mat mat, cv::Point& point, int flag, const QColor& bgColor);
        bool rightTopPoint(const cv::Mat mat, cv::Point& point, int flag, const QColor& bgColor);
        bool leftBottomPoint(const cv::Mat mat, cv::Point& point, int flag, const QColor& bgColor);
        bool rightBottomPoint(const cv::Mat mat, cv::Point& point, int flag, const QColor& bgColor);
    };

}

#endif // PARTITIONTRIMBORDER_H
