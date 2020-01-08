#ifndef SCANNYERODETRIMBORDER_H
#define SCANNYERODETRIMBORDER_H

#include "simpletrimborder.h"

namespace onechchy {

    /**
     * @brief The SCannyErodeTrimBorder class 在使用腐蚀的基础上使用Canny算法
     */
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
