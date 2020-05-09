#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/opencv.hpp>

namespace onechchy {
    class IColorDetector
    {
    public:
        explicit IColorDetector(){}

    public:
        virtual cv::Mat detector(cv::Mat& srcMat, cv::Vec3b &dstColor) = 0;
        virtual int getDistanceToTargetColor(const cv::Vec3b& color, const cv::Vec3b& detectColor) = 0;

        int getMaxDist() const;
        void setMaxDist(int maxDist);

    protected:
        int mMaxDist = 100;
    };

    class SimpleDectector : public IColorDetector
    {
    private:
        // IColorDetector interface
    public:
        cv::Mat detector(cv::Mat &srcMat, cv::Vec3b &dstColor) override;

        // IColorDetector interface
    public:
        int getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor) override;
    };

    class NormDectector : public IColorDetector
    {
    private:
        // IColorDetector interface
    public:
        cv::Mat detector(cv::Mat &srcMat, cv::Vec3b &dstColor) override;

        // IColorDetector interface
    public:
        int getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor) override;
    };

    class AbsdiffDectector : public IColorDetector
    {
    private:
        // IColorDetector interface
    public:
        cv::Mat detector(cv::Mat &srcMat, cv::Vec3b &dstColor) override;

        // IColorDetector interface
    public:
        int getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor) override;
    };

    class FloodDectector : public IColorDetector
    {
    private:
        // IColorDetector interface
    public:
        cv::Mat detector(cv::Mat &srcMat, cv::Vec3b &dstColor) override;

        // IColorDetector interface
    public:
        int getDistanceToTargetColor(const cv::Vec3b &color, const cv::Vec3b &detectColor) override;
    };
}

#endif // COLORDETECTOR_H
