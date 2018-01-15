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

        case ImageOpera::TrimBorder:
            this->trimBorderOpera(image);
            break;
        default:
            break;
        }
    }

    ImageOperaParam *SImageService::operaParam() const
    {
        return mOperaParam;
    }

    void SImageService::setOperaParam(ImageOperaParam *operaParam)
    {
        mOperaParam = operaParam;
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

    void SImageService::trimBorderOpera(QImage &image)
    {
        qDebug() << "trimBorderOpera";

        if (mOperaParam != nullptr)
        {
            qDebug() << mOperaParam->bgColor();
            qDebug() << mOperaParam->trimBorder();
        }
    }
}
