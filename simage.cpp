#include "transformimage.h"
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
}
