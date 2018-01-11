#ifndef IMAGESHOWITEM_H
#define IMAGESHOWITEM_H

#include <QQuickItem>

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

    public slots:
        void sync();
        void cleanup();
        void sltQImage(std::shared_ptr<QImage>);
        void sltUpdate();

    private slots:
        void handleWindowChanged(QQuickWindow* win);

    private:
    //    std::shared_ptr<QImage> mpCurImage = nullptr;
        ImageShowRenderer* mpRender = nullptr;
    };
}

#endif // IMAGESHOWITEM_H
