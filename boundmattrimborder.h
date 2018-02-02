#ifndef BOUNDMATTRIMBORDER_H
#define BOUNDMATTRIMBORDER_H

#include "itrimingborder.h"

namespace onechchy {

    class BoundMatTrimBorder : public ITrimingBorder
    {
    public:
        BoundMatTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    };

}
#endif // BOUNDMATTRIMBORDER_H
