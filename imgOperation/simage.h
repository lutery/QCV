#ifndef SIMAGE_H
#define SIMAGE_H

#include <QObject>
#include <memory>
#include <QColor>
#include <map>

namespace onechchy {
    class TransformImage;
    class ITrimingBorder;
    class ImageSplit;
    class ImageOperaParam;
    class VGBHandle;
    class ITransformImg;

    /**
     * @brief The SImage class
     * 图像操作代理类，代理图像变换
     */
    class SImage : public QObject
    {
        Q_OBJECT

    public:
        explicit SImage(QObject *parent = nullptr);

        void setTransImg(TransformImage* value);
        void setTrimBorder(ITrimingBorder* value);
        void setImageSplit(ImageSplit *value);

        QImage autoRotate(QImage&);
        QImage trimBorder(QImage&,int trimType, QColor bgColor);
        QImage imageSplit(QImage&, int, int);
        QImage grayBinary(QImage&image, ImageOperaParam* param);
        QImage transformImg(QImage& image, ImageOperaParam* param);
        QImage remapImg(QImage& image, ImageOperaParam* param);


    signals:

    public slots:

    private:
        QImage remapWave(QImage& image, ImageOperaParam* param);

        // 图像变换类
        std::unique_ptr<TransformImage> mpTransImg;
        // 图像切边类
        std::unique_ptr<ITrimingBorder> mpTrimBorder;
        // 图像分割类
        std::unique_ptr<ImageSplit> mpImageSplit;
        // 图像二值化类
        std::unique_ptr<VGBHandle> mpGBHandle;
        // key value is 图像操作类enum 图像操作类
        std::map<int, std::unique_ptr<ITransformImg>> mapTransform;
    };
}

#endif // SIMAGE_H
