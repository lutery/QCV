#include "camerafilter.h"
#include "camerafilterrunnable.h"

namespace onechchy {

    CameraFilter::CameraFilter(QObject *parent) : QAbstractVideoFilter(parent)
    {

    }

    CameraFilter::~CameraFilter()
    {

    }

    QVideoFilterRunnable* CameraFilter::createFilterRunnable()
    {
        return new CameraFilterRunnable(this);
    }
}
