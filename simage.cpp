#include "transformimage.h"
#include "itrimingborder.h"
#include "simage.h"
#include "imageutil.h"

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

    void SImage::setTrimBorder(ITrimingBorder* value)
    {
        mpTrimBorder = std::unique_ptr<ITrimingBorder>(value);
    }
}
