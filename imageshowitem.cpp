#include "imageshowitem.h"
#include "imageshowrenderer.h"
#include <QQuickWindow>

namespace onechchy {
    ImageShowItem::ImageShowItem()
    {
        connect(this, &QQuickItem::windowChanged, this, &ImageShowItem::handleWindowChanged);
    }

    ImageShowItem::~ImageShowItem()
    {
        if (mpRender == nullptr)
        {
            delete mpRender;
            mpRender = nullptr;
        }
    }

    void ImageShowItem::sync()
    {
        if (mpRender == nullptr)
        {
            qDebug() << "sync mpRender create";
            mpRender = new ImageShowRenderer();
            connect(window(), &QQuickWindow::beforeRendering, mpRender, &ImageShowRenderer::sltPaint, Qt::DirectConnection);
            mpRender->sltInit();
        }

        mpRender->setViewportSize(window()->size() * window()->devicePixelRatio());
        mpRender->setWindow(window());
    }

    void ImageShowItem::cleanup()
    {
        if (mpRender != nullptr)
        {
            delete mpRender;
            mpRender = nullptr;
        }
    }

    void ImageShowItem::sltQImage(std::shared_ptr<QImage> image)
    {
        qDebug() << "sltTexture std::shared_ptr<QImage>";
        if (mpRender != nullptr)
        {
            mpRender->setCurImage(image);
            if (window())
            {
                qDebug() << "window() update";
                window()->update();
            }
        }
    }

    void ImageShowItem::sltUpdate()
    {

    }

    void ImageShowItem::handleWindowChanged(QQuickWindow *win)
    {
        if (win != nullptr)
        {
            qDebug() << "handleWindowChanged";
            connect(win, &QQuickWindow::beforeSynchronizing, this, &ImageShowItem::sync, Qt::DirectConnection);
            connect(win, &QQuickWindow::sceneGraphInvalidated, this, &ImageShowItem::cleanup, Qt::DirectConnection);
            win->setClearBeforeRendering(false);
        }
    }
}
