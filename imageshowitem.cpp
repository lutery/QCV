#include "imageshowitem.h"
#include "imageshowrenderer.h"
#include <QQuickWindow>
#include <QImage>

namespace onechchy {
    ImageShowItem::ImageShowItem()
    {
        // 监控控件尺寸改变信号
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

    /**
     * @brief ImageShowItem::sync 设置绘制对象与窗口控件画面同步
     */
    void ImageShowItem::sync()
    {
        if (mpRender == nullptr)
        {
            qDebug() << "sync mpRender create";
            mpRender = new ImageShowRenderer();
            // 监听控件绘制信号进行绘制操作
            connect(window(), &QQuickWindow::beforeRendering, mpRender, &ImageShowRenderer::sltPaint, Qt::DirectConnection);
            mpRender->sltInit();
        }

        mpRender->setViewportSize(window()->size() * window()->devicePixelRatio());
        mpRender->setWindow(window());
    }

    /**
     * @brief ImageShowItem::cleanup 清空
     */
    void ImageShowItem::cleanup()
    {
        if (mpRender != nullptr)
        {
            delete mpRender;
            mpRender = nullptr;
        }
    }

    /**
     * @brief ImageShowItem::sltQImage 设置需要显示的图像
     * @param image
     */
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

    /**
     * @brief ImageShowItem::copyImage 获取新的图像
     * @return
     */
    QImage ImageShowItem::copyImage()
    {
        if (mpRender != nullptr)
        {
            return mpRender->getCurImage();
        }

        return QImage();
    }

    /**
     * @brief ImageShowItem::handleWindowChanged 窗口改变槽函数，设置相关的信号与槽关联的信息
     * @param win
     */
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
