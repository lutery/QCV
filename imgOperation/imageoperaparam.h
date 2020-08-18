#ifndef IMAGEOPERAPARAM_H
#define IMAGEOPERAPARAM_H

#include <QObject>
#include <QColor>
#include <QString>
#include <string>

namespace onechchy {

    // 图像处理参数联合体
    union ParamUnion{
        ParamUnion(){}
        ~ParamUnion(){}

        // 切边参数
        struct{
            // 切哪个方向的边
            int trimBorder = 0x00;
            // 切边的方法
//            int trimType = 0;
            // 背景颜色
            QColor bgColor;
        } trimParam;

        struct{
            int clusterCount = 2;
//            int imageSplitType = 0x01;
        } splitParam;

        struct{
            QString selectPath;
        }saveParam;

        // 通用参数 双整形
        struct{
            int intOne = 0;
            int intTwo = 0;
            int methodType = 0;
        }commonParam;

        // 图形旋转参数
        struct{
//            int rotateType = -1;
            int rotateAngle = 0;
        }rotateParam;

        // 图形变换参数
        struct{
            int width = 0;
            int height = 0;
//            int type = 0;
        }transformParam;

        // 重采样参数
        struct{
//           int type = 0;
           float range = 0.0f;
           float freq = 0.0f;
        }remapParam;

        // 颜色检测参数
        struct {
            QColor color;
        }detectParam;

        struct{
            int borderType;
            int width;
            int height;
        }dilateParam;
    };

    /**
     * @brief The ImageOperaParam class
     * 图像操作参数
     */
    class ImageOperaParam : public QObject
    {
        Q_OBJECT
    public:
        explicit ImageOperaParam(QObject *parent = nullptr);
        virtual ~ImageOperaParam();

        int trimType() const;
        Q_INVOKABLE void setTrimType(int trimType);

        int trimBorder() const;
        Q_INVOKABLE void setTrimBorder(int trimBorder);

        QColor bgColor() const;
        Q_INVOKABLE void setBgColor(QColor bgColor);

        int clusterCount() const;
        Q_INVOKABLE void setClusterCount(int clusterCount);

        int imageSplitType() const;
        Q_INVOKABLE void setImageSplitType(int imageSplitType);

        QString selectPath() const;
        Q_INVOKABLE void setSelectPath(const QString &selectPath);

        int gbMethod() const;
        Q_INVOKABLE void setGBMethod(const int method);

        int gbParam() const;
        Q_INVOKABLE void setGBParam(const int param);

        int rotateMethod() const;
        Q_INVOKABLE void setRotateMethod(const int method);

        int rotateParam() const;
        Q_INVOKABLE void setRotateParam(const int param);

        int widthParam() const;
        Q_INVOKABLE void setWidthParam(const int width);

        int heightParam() const;
        Q_INVOKABLE void setHeightParam(const int height);

        int transformType() const;
        Q_INVOKABLE void setTransformType(const int resizeType);

        // 重采样
        int remapType() const;
        Q_INVOKABLE void setRemapType(const int remapType);

        float waveRange() const;
        Q_INVOKABLE void setWaveRange(const float range);

        float waveFreq() const;
        Q_INVOKABLE void setWaveFreq(const float freq);
        //

        // 颜色检测
        QColor detectColor() const;
        Q_INVOKABLE void setDetectColor(const QColor color);

        int detectType() const;
        Q_INVOKABLE void setDetectType(const int type);
        //

        int borderType() const;
        Q_INVOKABLE void setBorderType(int boderType);

        int borderWidth() const;
        Q_INVOKABLE void setBorderWidth(int width);

        int borderHeight() const;
        Q_INVOKABLE void setBorderHeight(int height);

        // 抖色参数
        unsigned char bayerParam() const;
        Q_INVOKABLE void setBayerParam(unsigned char bayer);

    signals:

    public slots:

    private:
        ParamUnion mParam;
        QString mSaveOpenPath;

        // 需要切的边
//        int mTrimBorder = 0x00;
        // 背景颜色 QColor类型与qml中color类型相同固在qml中可以使用字符串进行初始化
//        QColor mBgColor;
        // 图像分割需要分割的分数
//        int mClusterCount = 2;
//        图像分割类型
//        int mImageSplitType = 0x01;
//        QString mSelectPath = "";
//        int mIntOne = 0;
//        int mIntTwo = 0;
    };
}

#endif // IMAGEOPERAPARAM_H
