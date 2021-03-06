#include "transformimage.h"
#include "trimBorder/itrimingborder.h"
#include "simage.h"
#include "imageutil.h"
#include "imagesplit.h"
#include "simageservice.h"
#include "imageoperaparam.h"
#include "grayBinary/gopencvhandle.h"
#include "grayBinary/bopencvhandle.h"
#include "grayBinary/bostuopencvhandle.h"
#include "grayBinary/btriangleopencvhandle.h"
#include "grayBinary/gthirdhandle.h"
#include "grayBinary/ditherhandler.h"
#include "grayBinary/badaptiveopencvhandle.h"
#include "transform/reiszenearopencv.h"
#include "transform/resizelinearopencv.h"
#include "transform/resizecubicopencv.h"
#include "colordetector.h"
#include <QDebug>

namespace onechchy {
    SImage::SImage(QObject *parent) : QObject(parent)
    {
        auto pGCVHandle = new GOpenCVHandle();
//        auto pBCVHandle = new BOpenCVHandle();
//        auto pOSTUHandle = new BOSTUOpenCVHandle();
//        auto pGThirdHandle = new GThirdHandle();
//        auto pTriangleHandle = new BTriangleOpenCVHandle();
//        auto pBayerDiather = new BayerHandler();
//        auto pAdapHandler = new BAdaptiveOpenCVHandle();

        this->mpGBHandle = std::unique_ptr<VGBHandle>(pGCVHandle);
        pGCVHandle->setMpNext(new BOpenCVHandle())
                ->setMpNext(new BOSTUOpenCVHandle())
                ->setMpNext(new GThirdHandle())
                ->setMpNext(new BTriangleOpenCVHandle())
                ->setMpNext(new BayerHandler())
                ->setMpNext(new BAdaptiveOpenCVHandle());
//        pBCVHandle->setMpNext(pOSTUHandle);
//        pOSTUHandle->setMpNext(pTriangleHandle);
//        pTriangleHandle->setMpNext(pGThirdHandle);
//        pGThirdHandle->setMpNext(pBayerDiather);
//        pBayerDiather->setMpNext(pAdapHandler);

        mapTransform[(int)SImageService::TransformType::Resize_NEAREST_OpenCV] = std::unique_ptr<ITransformImg>(new ReiszeNearOpencv());
        mapTransform[(int)SImageService::TransformType::Resize_LINEAR_OpenCV] = std::unique_ptr<ITransformImg>(new ResizeLinearOpencv());
        mapTransform[(int)SImageService::TransformType::Resize_CUBIC_OpenCV] = std::unique_ptr<ITransformImg>(new ResizeCubicOpencv());

        mapColorDected[(int)SImageService::DetectType::Color_Simple] = std::unique_ptr<IColorDetector>(new SimpleDectector());
    }

    void SImage::setTransImg(TransformImage* value)
    {
        mpTransImg = std::unique_ptr<TransformImage>(value);
    }

    QImage SImage::autoRotate(QImage& image)
    {
        cv::Mat mat = mpTransImg->inclineDFT(onechchy::QImage2cvMat(image));

        return onechchy::cvMat2QImage(mat);
    }

    QImage SImage::trimBorder(QImage& image, int trimType, QColor bgColor)
    {
        cv::Mat mat = this->mpTrimBorder->trimBorder(onechchy::QImage2cvMat(image), trimType, bgColor);

        return onechchy::cvMat2QImage(mat);
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
            mat = this->mpImageSplit->kmeans(onechchy::QImage2cvMat(image), clusterCount);
            break;
        }

        return onechchy::cvMat2QImage(mat);
    }

    QImage SImage::grayBinary(QImage& image, ImageOperaParam *param)
    {
        qDebug() << "process grayBinary method is " << param->gbMethod();
        cv::Mat mat;

        mat = this->mpGBHandle->GBHanlde(param->gbMethod(), param, onechchy::QImage2cvMat(image));

//        cv::imwrite("F:/Test/mat.png", mat);
        return onechchy::cvMat2QImage(mat);
    }

    QImage SImage::transformImg(QImage &image, ImageOperaParam *param)
    {
        qDebug() << "process transform method is " << param->transformType();
        cv::Mat mat;

        if (this->mapTransform.count(param->transformType()) > 0)
        {
            mat = this->mapTransform[param->transformType()]->transform(onechchy::QImage2cvMat(image), param);
        }

        return onechchy::cvMat2QImage(mat);
    }

    QImage SImage::remapImg(QImage &image, ImageOperaParam *param)
    {
        switch ((SImageService::RemapType)param->remapType())
        {
        case SImageService::RemapType::Remap_wave:
            return this->remapWave(image, param);
            break;

        default:
            qDebug() << "unknow remap type is " << param->remapType();
            break;
        }

        return image;
    }

    QImage SImage::colorDected(QImage &image, ImageOperaParam *param)
    {
        cv::Mat mat;

        if (mapColorDected.count(param->detectType()) > 0)
        {
            cv::Vec3b dstColor(param->detectColor().red(), param->detectColor().green(), param->detectColor().blue());
            mat = this->mapColorDected[param->detectType()]->detector(onechchy::QImage2cvMat(image), dstColor);
        }

        return onechchy::cvMat2QImage(mat);
    }

    QImage SImage::remapWave(QImage &image, ImageOperaParam *param)
    {
        cv::Mat srcImg = onechchy::QImage2cvMat(image);
        cv::Mat srcX(srcImg.rows, srcImg.cols, CV_32F);
        cv::Mat srcY(srcImg.rows, srcImg.cols, CV_32F);

        for (int i = 0; i < srcImg.rows; ++i)
        {
            for (int j = 0; j < srcImg.cols; ++j)
            {
                srcX.at<float>(i, j) = j;
                // ToDo 这里需要避免waveFreq为0
                srcY.at<float>(i, j) = i + param->waveRange() * sin(j / param->waveFreq());
            }
        }

        cv::Mat dstImg(srcImg.rows, srcImg.cols, srcImg.type());
        cv::remap(srcImg, dstImg, srcX, srcY, cv::INTER_LINEAR);

        return onechchy::cvMat2QImage(dstImg);
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
