#ifndef SCANNYERODILTRIMBORDER_H
#define SCANNYERODILTRIMBORDER_H

#include "simpletrimborder.h".h"

namespace onechchy {

    class ScannyEroDilTrimBorder : public SimpleTrimBorder
    {
    public:
        ScannyEroDilTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    private:
        cv::Mat mcErodeElement;
    };

}

#endif // SCANNYERODILTRIMBORDER_H
