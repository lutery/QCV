#ifndef RESIZECUBICOPENCV_H
#define RESIZECUBICOPENCV_H

#include "itransformimg.h"

namespace onechchy {
    class ResizeCubicOpencv : public ITransformImg
    {
    public:
        explicit ResizeCubicOpencv(QObject *parent = nullptr);

    signals:


        // ITransformImg interface
    public:
        cv::Mat transform(const cv::Mat &, ImageOperaParam *imgOprParam) override;
    };
}

#endif // RESIZECUBICOPENCV_H
