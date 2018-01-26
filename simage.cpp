#include "transformimage.h"
#include "itrimingborder.h"
#include "simage.h"
#include "imageutil.h"
#include "imagesplit.h"
#include "simageservice.h"

namespace onechchy {
    SImage::SImage(QObject *parent) : QObject(parent)
    {

    }

    void SImage::setTransImg(TransformImage* value)
    {
        mpTransImg = std::unique_ptr<TransformImage>(value);
    }

    QImage SImage::autoRotate(QImage& image)
    {
        cv::Mat mat = mpTransImg->inclineDFT(ImageUtil::QImage2cvMat(image));

        return ImageUtil::cvMat2QImage(mat);
    }

    QImage SImage::trimBorder(QImage& image, int trimType, QColor bgColor)
    {
        cv::Mat mat = this->mpTrimBorder->trimBorder(ImageUtil::QImage2cvMat(image), trimType, bgColor);

        return ImageUtil::cvMat2QImage(mat);
    }

    QImage SImage::imageSplit(QImage& image, int imgSplitType, int clusterCount)
    {
        cv::Mat mat;

        switch (imgSplitType) {
        case SImageService::GMM:
            break;

        case SImageService::Watershed:
            break;

        case SImageService::GrabCut:
            break;

        default:
        case SImageService::KMeans:
            mat = this->mpImageSplit->kmeans(ImageUtil::QImage2cvMat(image), clusterCount);
            break;
        }

        return ImageUtil::cvMat2QImage(mat);
    }

    void SImage::setImageSplit(ImageSplit* value)
    {
        mpImageSplit = std::unique_ptr<ImageSplit>(value);
    }

    void SImage::setTrimBorder(ITrimingBorder* value)
    {
        mpTrimBorder = std::unique_ptr<ITrimingBorder>(value);
    }
}
