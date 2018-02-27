#include "facedecteddlib.h"
#include "faceutil.h"
#include <QDebug>

namespace FaceIdentify {

    FaceDectedDlib::FaceDectedDlib():mDetector(dlib::get_frontal_face_detector())
    {

    }

    FaceDectedDlib::~FaceDectedDlib()
    {

    }

    /**
     * @brief FaceDectedDlib::dectedROI 目前仅接受彩色图检测
     * @param srcMat
     * @return
     */
    std::vector<cv::Rect> FaceDectedDlib::dectedROI(const cv::Mat &srcMat)
    {
        std::vector<cv::Rect> faceRIOs;

        qDebug() << "srcMat channels: " << srcMat.channels();

        if (srcMat.channels() == 3)
        {
            dlib::cv_image<dlib::bgr_pixel> cvImg(srcMat);

            auto faces = mDetector(cvImg);

            faceRIOs = FaceIdentify::dlibRect2cvRect(faces);
        }
        else if (srcMat.channels() == 4)
        {

        }

        return faceRIOs;
    }

    std::vector<cv::Mat> FaceDectedDlib::dectedMat(const cv::Mat &srcMat)
    {
        std::vector<cv::Mat> faceMats;

        if (srcMat.channels() == 3)
        {
            std::vector<cv::Rect> faceRIOs = this->dectedROI(srcMat);

            for (const auto& faceRIO : faceRIOs)
            {
                cv::Mat tmp;
                srcMat(faceRIO).copyTo(tmp);
                faceMats.push_back(std::move(tmp));
            }
        }
        else if (srcMat.channels() == 4)
        {

        }

        return faceMats;
    }

    std::vector<cv::Mat> FaceDectedDlib::acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat)
    {
        std::vector<cv::Mat> faceMats;

        if (srcMat.channels() == 3)
        {
            for (const auto& faceRIO : faceROIs)
            {
                cv::Mat tmp;
                srcMat(faceRIO).copyTo(tmp);
                faceMats.push_back(std::move(tmp));
            }
        }
        else if (srcMat.channels() == 4)
        {

        }

        return faceMats;
    }

}
