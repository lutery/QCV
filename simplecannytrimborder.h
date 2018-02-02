#ifndef SIMPLECANNYTRIMBORDER_H
#define SIMPLECANNYTRIMBORDER_H

#include "simpletrimborder.h".h"

namespace onechchy {

    class SimpleCannyTrimBorder : public SimpleTrimBorder
    {
    public:
        SimpleCannyTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;
    };

}

#endif // SIMPLECANNYTRIMBORDER_H
