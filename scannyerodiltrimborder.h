#ifndef SCANNYERODILTRIMBORDER_H
#define SCANNYERODILTRIMBORDER_H

#include "simpletrimborder.h".h"

namespace onechchy {

    /**
     * @brief The SCannyErodeTrimBorder class 在使用腐蚀膨胀的基础上使用Canny算法
     */
    class ScannyEroDilTrimBorder : public SimpleTrimBorder
    {
    public:
        ScannyEroDilTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    protected:
        cv::Mat mcErodeElement;
    };

}

#endif // SCANNYERODILTRIMBORDER_H
