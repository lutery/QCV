#ifndef IMAGEOPERAPARAM_H
#define IMAGEOPERAPARAM_H

#include <QObject>
#include <QColor>
#include <QString>

namespace onechchy {
    /**
     * @brief The ImageOperaParam class
     * 图像操作参数
     */
    class ImageOperaParam : public QObject
    {
        Q_OBJECT
    public:
        explicit ImageOperaParam(QObject *parent = nullptr);

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

    signals:

    public slots:

    private:
        // 需要切的边
        int mTrimBorder = 0x00;
        // 背景颜色 QColor类型与qml中color类型相同固在qml中可以使用字符串进行初始化
        QColor mBgColor;
        // 图像分割需要分割的分数
        int mClusterCount = 2;
//        图像分割类型
        int mImageSplitType = 0x01;
        QString mSelectPath = "";
        int mIntOne = 0;
        int mIntTwo = 0;
    };
}

#endif // IMAGEOPERAPARAM_H
