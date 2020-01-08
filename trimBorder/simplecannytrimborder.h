#ifndef SIMPLECANNYTRIMBORDER_H
#define SIMPLECANNYTRIMBORDER_H

#include "simpletrimborder.h"

namespace onechchy {

    /**
     * @brief The SimpleCannyTrimBorder class 使用canny进行边界的查找
     */
    class SimpleCannyTrimBorder : public SimpleTrimBorder
    {
    public:
        SimpleCannyTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;
    };

}

#endif // SIMPLECANNYTRIMBORDER_H
