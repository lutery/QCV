#include "simageservice.h"
#include "simage.h"
#include "transformimage.h"
#include "simpletrimborder.h"
#include "imagesplit.h"
#include <QDebug>

namespace onechchy {
    SImageService::SImageService(QObject *parent) : QObject(parent)
    {
        mpSImage = std::unique_ptr<onechchy::SImage>(new SImage());
        mpSImage->setTransImg(new TransformImage());
        mpSImage->setImageSplit(new ImageSplit());
        mpSImage->setTrimBorder(new SimpleTrimBorder());
    }

    /**
     * @brief SImageService::sltImageOpera 图像操作方法
     * @param opera 操作类型
     * @param image 被操作的图像
     * 以后如果switch case太多，可以采用广播模式进行图像的处理
     */
    void SImageService::sltImageOpera(SImageService::ImageOpera opera, QImage image)
    {
        switch (opera) {
        case ImageOpera::AutoRectifying:
            this->rectifyingOpera(image);
            break;

        case ImageOpera::TrimBorder:
            this->trimBorderOpera(image);
            break;

        case ImageOpera::SplitKmeans:
            this->imageSplitOpera(image);
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

    /**
     * @brief SImageService::rectifyingOpera 图像自动纠偏，用于纯色背景的图片
     * @param image
     */
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

    /**
     * @brief SImageService::trimBorderOpera 图像切边
     * @param image
     */
    void SImageService::trimBorderOpera(QImage &image)
    {
        qDebug() << "trimBorderOpera";

        if (mOperaParam != nullptr)
        {
            qDebug() << mOperaParam->bgColor();
            qDebug() << mOperaParam->trimBorder();

            QImage resultImg = mpSImage->trimBorder(image, mOperaParam->trimBorder(), mOperaParam->bgColor());
            this->updateImg(resultImg);
        }
    }

    void SImageService::imageSplitOpera(QImage &image)
    {
        qDebug() << "imageSplitOpera";

        int clusterCount = 2;

        if (mOperaParam != nullptr)
        {
            clusterCount = mOperaParam->clusterCount() > 0 ? mOperaParam->clusterCount() : 2;
        }

        qDebug() << "clusterCount" << clusterCount;

        QImage resultImg = mpSImage->imageSplitKMeans(image, clusterCount);
        this->updateImg(resultImg);
    }
}
