#include "simageservice.h"
#include "simage.h"
#include "transformimage.h"
#include <QDebug>

namespace onechchy {
    SImageService::SImageService(QObject *parent) : QObject(parent)
    {
        mpSImage = std::unique_ptr<onechchy::SImage>(new SImage());
        mpSImage->setTransImg(new TransformImage());
    }

    void SImageService::sltImageOpera(SImageService::ImageOpera opera, QImage image)
    {
        switch (opera) {
        case ImageOpera::AutoRectifying:
            this->rectifyingOpera(image);
            break;
        default:
            break;
        }
    }

    void SImageService::rectifyingOpera(QImage &image)
    {
        if (!image.isNull())
        {
            QImage resultImg = mpSImage->autoRotate(image);
            this->updateImg(resultImg);
        }
        else
        {
            qDebug() << "invalid image";
        }
    }
}
