#include "imageoperaparam.h"

namespace onechchy {
    ImageOperaParam::ImageOperaParam(QObject *parent) : QObject(parent)
    {

    }

    int ImageOperaParam::trimBorder() const
    {
        return mTrimBorder;
    }

    void ImageOperaParam::setTrimBorder(int trimBorder)
    {
        mTrimBorder = trimBorder;
    }

    long ImageOperaParam::bgColor() const
    {
        return mBgColor;
    }

    void ImageOperaParam::setBgColor(long bgColor)
    {
        mBgColor = bgColor;
    }
}
