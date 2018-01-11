#include "transformimage.h"
#include "simage.h"

namespace onechchy {
    SImage::SImage(QObject *parent) : QObject(parent)
    {

    }

    void SImage::setTransImg(TransformImage* value)
    {
        mpTransImg = std::unique_ptr<TransformImage>(value);
    }
}
