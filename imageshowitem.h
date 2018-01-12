#ifndef IMAGESHOWITEM_H
#define IMAGESHOWITEM_H

#include <QQuickItem>
#include <QString>
#include <QImage>
//#include "simageservice.h"

class QQuickWindow;
class QOpenGLTexture;

namespace onechchy {
    class ImageShowRenderer;

    class ImageShowItem : public QQuickItem
    {
        Q_OBJECT

    public:
        ImageShowItem();
        virtual ~ImageShowItem();

    signals:
//        void imageOpera(SImageService::ImageOpera, QImage);

    public slots:
        void sync();
        void cleanup();
        void sltQImage(std::shared_ptr<QImage>);
        void sltQImage(QImage);
        void sltQImage(QString imagePath);
        void sltUpdate();
        QImage copyImage();

    private slots:
        void handleWindowChanged(QQuickWindow* win);

    private:
    //    std::shared_ptr<QImage> mpCurImage = nullptr;
        ImageShowRenderer* mpRender = nullptr;
        QString mImagePath;
    };
}

#endif // IMAGESHOWITEM_H
