#ifndef SCANNYERODETRIMBORDER_H
#define SCANNYERODETRIMBORDER_H

#include "simpletrimborder.h".h"

namespace onechchy {

    class SCannyErodeTrimBorder : public SimpleTrimBorder
    {
    public:
        SCannyErodeTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    private:
        cv::Mat mcErodeElement;
    };

}

#endif // SCANNYERODETRIMBORDER_H
