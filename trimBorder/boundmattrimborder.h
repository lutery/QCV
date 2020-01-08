#ifndef BOUNDMATTRIMBORDER_H
#define BOUNDMATTRIMBORDER_H

#include "itrimingborder.h"

namespace onechchy {

    /**
     * @brief The BoundMatTrimBorder class 使用opencv矩形查询算法进行边界的查询
     * 效果不好，会对部分边界无黑边以及噪点给干扰
     */
    class BoundMatTrimBorder : public ITrimingBorder
    {
    public:
        BoundMatTrimBorder();

        cv::Mat trimBorder(const cv::Mat& srcMat, int border, QColor bgColor) override;

    };

}
#endif // BOUNDMATTRIMBORDER_H
