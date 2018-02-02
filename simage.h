#ifndef SIMAGE_H
#define SIMAGE_H

#include <QObject>
#include <memory>
#include <QColor>

namespace onechchy {
    class TransformImage;
    class ITrimingBorder;
    class ImageSplit;
    class ImageOperaParam;
    class VGBHandle;

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


    signals:

    public slots:

    private:
        std::unique_ptr<TransformImage> mpTransImg;
        std::unique_ptr<ITrimingBorder> mpTrimBorder;
        std::unique_ptr<ImageSplit> mpImageSplit;
        std::unique_ptr<VGBHandle> mpGBHandle;
    };
}

#endif // SIMAGE_H
