#ifndef SIMAGESERVICE_H
#define SIMAGESERVICE_H

#include <QObject>
#include <memory>
#include <QString>
#include <QImage>
#include "imageoperaparam.h"

namespace onechchy {
    class SImage;
    class TransformImage;
//    class ImageOperaParam;

    class SImageService : public QObject
    {
        Q_OBJECT
        Q_ENUMS(ImageOpera)

        Q_PROPERTY(ImageOperaParam *operaParam READ operaParam WRITE setOperaParam)

    public:
        explicit SImageService(QObject *parent = nullptr);

        enum ImageOpera
        {
            AutoRectifying = 0,
            TrimBorder = 1
        };

        ImageOperaParam *operaParam() const;
        void setOperaParam(ImageOperaParam *operaParam);

    signals:
        void updateImg(QImage image);

    public slots:
        void sltImageOpera(ImageOpera opera, QImage image);

    private:
        std::unique_ptr<SImage> mpSImage = nullptr;
        ImageOperaParam* mOperaParam = nullptr;

        void rectifyingOpera(QImage& image);
        void trimBorderOpera(QImage& image);
    };
}

#endif // SIMAGESERVICE_H
