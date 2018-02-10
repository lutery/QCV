#ifndef CAMERAFILTER_H
#define CAMERAFILTER_H

#include <QVideoFilterRunnable>

namespace onechchy {

    /**
     * @brief The CameraFilter class 相机帧过滤器
     */
    class CameraFilter : public QAbstractVideoFilter
    {
    public:
        CameraFilter(QObject* parent = Q_NULLPTR);
        virtual ~CameraFilter();

        // QAbstractVideoFilter interface
    public:
        QVideoFilterRunnable *createFilterRunnable() override;
    };

}

#endif // CAMERAFILTER_H
