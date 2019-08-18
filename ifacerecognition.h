#ifndef IFACERECOGNITION_H
#define IFACERECOGNITION_H

#include <QList>
#include <opencv2/opencv.hpp>
#include "faceinfo.h"

namespace FaceIdentifion {

    class IFaceRecognition
    {
    public:
        virtual QStringList scanFaceInfos() = 0;
        virtual void RecordFace(std::vector<QString> faceId, std::vector<cv::Mat> faceMat) = 0;
        virtual void save() = 0;
    };

}

#endif // IFACERECOGNITION_H
