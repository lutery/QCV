#include "imageoperaparam.h"

namespace onechchy {
    ImageOperaParam::ImageOperaParam(QObject *parent) : QObject(parent)
    {

    }

    ImageOperaParam::~ImageOperaParam()
    {

    }

    int ImageOperaParam::trimType() const
    {
        return mParam.commonParam.methodType;
    }

    void ImageOperaParam::setTrimType(int trimType)
    {
        mParam.commonParam.methodType = trimType;
    }

    int ImageOperaParam::trimBorder() const
    {
        return mParam.trimParam.trimBorder;
    }

    void ImageOperaParam::setTrimBorder(int trimBorder)
    {
        mParam.trimParam.trimBorder = trimBorder;
    }

    QColor ImageOperaParam::bgColor() const
    {
        return mParam.trimParam.bgColor;
    }

    void ImageOperaParam::setBgColor(QColor bgColor)
    {
        mParam.trimParam.bgColor = bgColor;
    }
    
    int ImageOperaParam::clusterCount() const
    {
        return mParam.splitParam.clusterCount;
    }
    
    void ImageOperaParam::setClusterCount(int clusterCount)
    {
        mParam.splitParam.clusterCount = clusterCount;
    }
    
    int ImageOperaParam::imageSplitType() const
    {
        return mParam.commonParam.methodType;
    }
    
    void ImageOperaParam::setImageSplitType(int imageSplitType)
    {
        mParam.commonParam.methodType = imageSplitType;
    }
    
    QString ImageOperaParam::selectPath() const
    {
        return mSaveOpenPath;
    }
    
    void ImageOperaParam::setSelectPath(const QString &selectPath)
    {
        mSaveOpenPath = selectPath;
    }

    int ImageOperaParam::gbMethod() const
    {
        return mParam.jsonParam.methodType;
    }

    void ImageOperaParam::setGBMethod(const int method)
    {
        mParam.jsonParam.methodType = method;
    }

    int ImageOperaParam::gbParam() const
    {
        return mParam.commonParam.intTwo;
    }

    void ImageOperaParam::setGBParam(const int param)
    {
        mParam.commonParam.intTwo = param;
    }

    int ImageOperaParam::rotateMethod() const
    {
        return mParam.commonParam.methodType;
    }

    void ImageOperaParam::setRotateMethod(const int method)
    {
        mParam.commonParam.methodType = method;
    }

    int ImageOperaParam::rotateParam() const
    {
        return mParam.rotateParam.rotateAngle;
    }

    void ImageOperaParam::setRotateParam(const int param)
    {
        mParam.rotateParam.rotateAngle = param;
    }

    int ImageOperaParam::widthParam() const
    {
        return mParam.transformParam.width;
    }

    void ImageOperaParam::setWidthParam(const int width)
    {
        mParam.transformParam.width = width;
    }

    int ImageOperaParam::heightParam() const
    {
        return mParam.transformParam.height;
    }

    void ImageOperaParam::setHeightParam(const int height)
    {
        mParam.transformParam.height = height;
    }

    int ImageOperaParam::transformType() const
    {
        return mParam.commonParam.methodType;
    }

    void ImageOperaParam::setTransformType(const int transformType)
    {
        mParam.commonParam.methodType = transformType;
    }

    int ImageOperaParam::remapType() const
    {
        return mParam.commonParam.methodType;
    }

    void ImageOperaParam::setRemapType(const int remapType)
    {
        mParam.commonParam.methodType = remapType;
    }

    float ImageOperaParam::waveRange() const
    {
        return mParam.remapParam.range;
    }

    void ImageOperaParam::setWaveRange(const float range)
    {
        mParam.remapParam.range = range;
    }

    float ImageOperaParam::waveFreq() const
    {
        return mParam.remapParam.freq;
    }

    void ImageOperaParam::setWaveFreq(const float freq)
    {
        mParam.remapParam.freq = (freq == 0 ? 1 : freq);
    }

    QColor ImageOperaParam::detectColor() const
    {
        return mParam.detectParam.color;
    }

    void ImageOperaParam::setDetectColor(const QColor color)
    {
        mParam.detectParam.color = color;
    }

    int ImageOperaParam::detectType() const
    {
        return mParam.commonParam.methodType;
    }

    // ToDo 整合所有的设置type方法
    void ImageOperaParam::setDetectType(const int type)
    {
        mParam.commonParam.methodType = type;
    }

    int ImageOperaParam::borderType() const
    {
        return mParam.dilateParam.borderType;
    }

    void ImageOperaParam::setBorderType(int boderType)
    {
        mParam.dilateParam.borderType = boderType;
    }

    int ImageOperaParam::borderWidth() const
    {
        return mParam.dilateParam.width;
    }

    void ImageOperaParam::setBorderWidth(int width)
    {
        mParam.dilateParam.width = width;
    }

    int ImageOperaParam::borderHeight() const
    {
        return mParam.dilateParam.height;
    }

    void ImageOperaParam::setBorderHeight(int height)
    {
        mParam.dilateParam.height = height;
    }

    unsigned char ImageOperaParam::bayerParam() const
    {
        return mParam.commonParam.intTwo;
    }

    void ImageOperaParam::setBayerParam(unsigned char bayer)
    {
        mParam.commonParam.intTwo = bayer;
    }

    QString ImageOperaParam::jsonParam() const
    {
        return mParam.jsonParam.param;
    }

    void ImageOperaParam::setJsonParam(QString jsonParam)
    {
        mParam.jsonParam.param = jsonParam;
    }
}
