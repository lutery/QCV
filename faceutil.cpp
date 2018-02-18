#include "faceutil.h"
#include "FaceDected.h"
#include <QDebug>
#include <vector>

namespace FaceIdentify {

    void readCSVData(const std::string & filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator)
    {
        std::ifstream file(filename.c_str(), std::ifstream::in);
        if (!file)
        {
            std::string error_message = "No valid input file was given, please check the given filename.";
            CV_Error(CV_StsBadArg, error_message);
        }
        std::string line, path, classlabel;
        while (getline(file, line))
        {
            std::stringstream liness(line);
            getline(liness, path, separator);
            getline(liness, classlabel);
            if (!path.empty() && !classlabel.empty())
            {
                cv::Mat image = cv::imread(path, 0);

                if (!image.empty())
                {
                    images.push_back(image);
                    labels.push_back(atoi(classlabel.c_str()));
                }
            }
        }
    }

    void resizeData(std::vector<cv::Mat>& images, const cv::Size& size)
    {
        for (auto& image : images)
        {
            if (image.size() != size)
            {
                cv::resize(image, image, size);
            }
        }
    }

    void FaceDectedHelper(cv::Mat &mat)
    {
        static FaceDected faceDected;

        auto FaceRIOs = faceDected.dectedROI(mat);

        qDebug() << "Face RIOs size = " << FaceRIOs.size();

        for (const auto& faceRIO : FaceRIOs)
        {
            cv::rectangle(mat, faceRIO, cv::Scalar(0, 0, 255), 10);
        }
    }

    std::vector<cv::Rect> FaceRectHelper(cv::Mat &mat)
    {
        static FaceDected faceDected;

        auto FaceRIOs = faceDected.dectedROI(mat);

        qDebug() << "FaceRIOs size " << FaceRIOs.size();

        return FaceRIOs;
    }
}
