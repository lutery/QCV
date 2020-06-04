#include "morphology.h"

namespace onechchy
{
    IMorphology::IMorphology()
    {

    }

    DilateOpenCV::DilateOpenCV():IMorphology()
    {

    }

    cv::Mat DilateOpenCV::handler(const cv::Mat &srcMat, MorphologyParam param)
    {
        cv::Mat kernel = cv::getStructuringElement(param.shapes(), param.size());
        cv::Mat dstMat;
        cv::dilate(srcMat, dstMat, kernel);

        return dstMat;
    }

    cv::MorphShapes MorphologyParam::shapes() const
    {
        return mShapes;
    }

    void MorphologyParam::setShapes(const cv::MorphShapes &shapes)
    {
        mShapes = shapes;
    }

    cv::Size MorphologyParam::size() const
    {
        return mSize;
    }

    void MorphologyParam::setSize(const cv::Size &size)
    {
        mSize = size;
    }

    cv::Mat ErodeOpenCV::handler(const cv::Mat &srcMat, MorphologyParam param)
    {
        cv::Mat kernel = cv::getStructuringElement(param.shapes(), param.size());
        cv::Mat dstMat;
        cv::erode(srcMat, dstMat, kernel);

        return dstMat;
    }

}

