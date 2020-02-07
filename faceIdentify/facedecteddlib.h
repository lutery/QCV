#ifndef FACEDECTEDDLIB_H
#define FACEDECTEDDLIB_H

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include "ifacedected.h"

namespace FaceIdentifion {

    class FaceDectedDlib : public IFaceDected
    {
    public:
        FaceDectedDlib();
        virtual ~FaceDectedDlib();

        // IFaceDected interface
    public:
        std::vector<cv::Rect> dectedROI(const cv::Mat &) override;
        std::vector<cv::Mat> dectedMat(const cv::Mat &) override;
        std::vector<cv::Mat> acquireFace(const std::vector<cv::Rect> &faceROIs, const cv::Mat &srcMat) override;

    private:
        dlib::frontal_face_detector mDetector;
    };

}

#endif // FACEDECTEDDLIB_H
