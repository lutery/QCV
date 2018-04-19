#ifndef IFACERECOGNITION_H
#define IFACERECOGNITION_H

#include <QList>
#include "faceinfo.h"

namespace FaceIdentify {

    class IFaceRecognition
    {
    public:
        virtual QStringList scanFaceInfos() = 0;
    };

}

#endif // IFACERECOGNITION_H
