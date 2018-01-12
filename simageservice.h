#ifndef SIMAGESERVICE_H
#define SIMAGESERVICE_H

#include <QObject>
#include <memory>
#include <QString>
#include <QImage>

namespace onechchy {
    class SImage;
    class TransformImage;

    class SImageService : public QObject
    {
        Q_OBJECT
        Q_ENUMS(ImageOpera)

    public:
        explicit SImageService(QObject *parent = nullptr);

        enum ImageOpera
        {
            AutoRectifying = 0
        };

    signals:
        void updateImg(QImage image);

    public slots:
        void sltImageOpera(ImageOpera opera, QImage image);

    private:
        std::unique_ptr<SImage> mpSImage = nullptr;

        void rectifyingOpera(QImage& image);
    };
}

#endif // SIMAGESERVICE_H
