#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include <opencv2/opencv.hpp>

namespace onechchy
{

    class MorphologyParam
    {
    public:
        cv::MorphShapes shapes() const;
        void setShapes(const cv::MorphShapes &shapes);

        cv::Size size() const;
        void setSize(const cv::Size &size);

    private:
        cv::MorphShapes mShapes;
        cv::Size mSize;
    };

    class IMorphology
    {
    protected:
        IMorphology();

    public:
        virtual cv::Mat handler(const cv::Mat& srcMat, MorphologyParam param) = 0;
    };

    class DilateOpenCV : IMorphology
    {
    public:
        DilateOpenCV();

        // IMorphology interface
    public:
        cv::Mat handler(const cv::Mat &srcMat, MorphologyParam param) override;
    };

    class ErodeOpenCV: IMorphology
    {
    public:
        ErodeOpenCV();

        // IMorphology interface
    public:
        cv::Mat handler(const cv::Mat &srcMat, MorphologyParam param) override;
    };
}

#endif // MORPHOLOGY_H
