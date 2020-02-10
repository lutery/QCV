#include "simageservice.h"
#include "imgOperation/simage.h"
#include "imgOperation/transformimage.h"
#include "trimBorder/simpletrimborder.h"
#include "trimBorder/boundmattrimborder.h"
#include "imgOperation/imagesplit.h"
#include "trimBorder/simplecannytrimborder.h"
#include "trimBorder/scannyerodetrimborder.h"
#include "trimBorder/scannyerodiltrimborder.h"
#include "trimBorder/partitiontrimborder.h"
#include "imgOperation/util.h"
#include <QDebug>

namespace onechchy {
    SImageService::SImageService(QObject *parent) : QObject(parent)
    {
        mpSImage = std::unique_ptr<onechchy::SImage>(new SImage());
        mpSImage->setTransImg(new TransformImage());
        mpSImage->setImageSplit(new ImageSplit());
        mpSImage->setTrimBorder(new SimpleTrimBorder());

        mUnDoImg.clear();
        mReDoImg.clear();
    }

    /**
     * @brief SImageService::sltImageOpera 图像操作方法
     * @param opera 操作类型
     * @param image 被操作的图像
     * 以后如果switch case太多，可以采用广播模式进行图像的处理
     */
    void SImageService::sltImageOpera(SImageService::ImageOpera opera, QImage image)
    {
        qDebug() << "sltImageOpera process";

        mUnDoImg.push_back(image);
        mReDoImg.clear();

        switch (opera) {
        case ImageOpera::Rotate:
            this->rectifyingOpera(image);
            break;

        case ImageOpera::TrimBorder:
            this->trimBorderOpera(image);
            break;

        case ImageOpera::ImageSplit:
            this->imageSplitOpera(image);
            break;

        case ImageOpera::Save:
            this->saveImage(image);
            break;

        case ImageOpera::GrayBinary:
            this->grayBinary(image);
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

    void SImageService::undo()
    {
        if (mUnDoImg.size() > 0)
        {
            mReDoImg.push(mCurImg);
            mCurImg = mUnDoImg.pop();
            this->updateImg(mCurImg);
        }
    }

    void SImageService::redo()
    {
        if (mReDoImg.size() > 0)
        {
            mUnDoImg.push(mCurImg);
            mCurImg = mReDoImg.pop();
            this->updateImg(mCurImg);
        }
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
            if (!resultImg.isNull())
            {
                mCurImg = resultImg;
                this->updateImg(resultImg);
            }
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

            int trimType = mOperaParam->trimType();

            switch (trimType) {
            case (SImageService::TrimType::PartitionSCanny):
                mpSImage->setTrimBorder(new PartitionTrimBorder());
                break;

            case (SImageService::TrimType::Count):

                break;

            case (SImageService::TrimType::Map):
                break;

            case (SImageService::TrimType::BoundMat):
                mpSImage->setTrimBorder(new BoundMatTrimBorder());
                break;

            case (SImageService::TrimType::SimpleCanny):
                mpSImage->setTrimBorder(new SimpleCannyTrimBorder());
                break;

            case (SImageService::TrimType::SCannyErode):
                mpSImage->setTrimBorder(new SCannyErodeTrimBorder());
                break;

            case (SImageService::TrimType::SCannyEroDil):
                mpSImage->setTrimBorder(new ScannyEroDilTrimBorder());
                break;

            case (SImageService::TrimType::Simple):
            default:
                break;
            }

//            onechchy::tick();
//            QImage resultImg = mpSImage->trimBorder(image, mOperaParam->trimBorder(), mOperaParam->bgColor());
//            int timeCount = onechchy::clock<std::chrono::microseconds>();

            auto [timeCount, resultImg] = onechchy::cfunClock<std::chrono::milliseconds>(&SImage::trimBorder, mpSImage.get(), image, mOperaParam->trimBorder(), mOperaParam->bgColor());

            qDebug() << "time Count " << timeCount;
            if (!resultImg.isNull())
            {
                mCurImg = resultImg;
                this->updateImg(resultImg);
            }
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

        QImage resultImg = mpSImage->imageSplit(image, mOperaParam->imageSplitType(), clusterCount);
        if (!resultImg.isNull())
        {
            mCurImg = resultImg;
            this->updateImg(resultImg);
        }
    }

    void SImageService::saveImage(QImage &image)
    {
        if (mOperaParam != nullptr)
        {
            QString savePath = mOperaParam->selectPath();
            image.save(savePath);
        }
    }

    void SImageService::grayBinary(QImage &image)
    {
        qDebug() << "grayBinary";
        if (mOperaParam != nullptr)
        {
            qDebug() << "mOperaParam";

            QImage resultImg = mpSImage->grayBinary(image, mOperaParam);

            if (!resultImg.isNull())
            {
                mCurImg = resultImg;
                this->updateImg(resultImg);
            }
        }
    }
}
