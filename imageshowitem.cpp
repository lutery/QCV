#include "imageshowitem.h"
#include "imageshowrenderer.h"
#include <QQuickWindow>
#include <QImage>

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

    void ImageShowItem::sltQImage(QImage image)
    {
        std::shared_ptr<QImage> pImage(new QImage(image));

        if (mpRender != nullptr)
        {
            mpRender->setCurImage(pImage);
            if (window())
            {
                qDebug() << "window() update";
                window()->update();
            }
        }
    }

    void ImageShowItem::sltQImage(QString imagePath)
    {
        mImagePath = imagePath;

        QImage* pImg = new QImage();
        if (pImg->load(imagePath))
        {
            this->sltQImage(std::shared_ptr<QImage>(pImg));
        }
        else
        {
            delete pImg;
        }
    }

    void ImageShowItem::sltUpdate()
    {

    }

    QImage ImageShowItem::copyImage()
    {
        if (mpRender != nullptr)
        {
            return mpRender->getCurImage();
        }

        return QImage();
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
