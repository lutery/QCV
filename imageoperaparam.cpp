#include "imageoperaparam.h"

namespace onechchy {
    ImageOperaParam::ImageOperaParam(QObject *parent) : QObject(parent), mBgColor("0x000000")
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

    QColor ImageOperaParam::bgColor() const
    {
        return mBgColor;
    }

    void ImageOperaParam::setBgColor(QColor bgColor)
    {
        mBgColor = bgColor;
    }
    
    int ImageOperaParam::clusterCount() const
    {
        return mClusterCount;
    }
    
    void ImageOperaParam::setClusterCount(int clusterCount)
    {
        mClusterCount = clusterCount;
    }
}
