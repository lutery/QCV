#ifndef IMAGEOPERAPARAM_H
#define IMAGEOPERAPARAM_H

#include <QObject>
#include <QColor>

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

        int trimBorder() const;
        Q_INVOKABLE void setTrimBorder(int trimBorder);

        QColor bgColor() const;
        Q_INVOKABLE void setBgColor(QColor bgColor);

        int clusterCount() const;
        Q_INVOKABLE void setClusterCount(int clusterCount);

        int imageSplitType() const;
        Q_INVOKABLE void setImageSplitType(int imageSplitType);

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
    };
}

#endif // IMAGEOPERAPARAM_H
