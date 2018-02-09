#ifndef CAMERAFILTER_H
#define CAMERAFILTER_H

#include <QVideoFilterRunnable>

namespace onechchy {

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
