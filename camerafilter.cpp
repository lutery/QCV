#include "camerafilter.h"
#include "camerafilterrunnable.h"

namespace onechchy {

    CameraFilter::CameraFilter(QObject *parent) : QAbstractVideoFilter(parent)
    {

    }

    CameraFilter::~CameraFilter()
    {

    }

    /**
     * @brief CameraFilter::createFilterRunnable 创建过滤器运行对象
     * @return
     */
    QVideoFilterRunnable* CameraFilter::createFilterRunnable()
    {
        return new CameraFilterRunnable(this);
    }
}
