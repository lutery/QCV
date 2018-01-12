#ifndef IMAGESHOWRENDERER_H
#define IMAGESHOWRENDERER_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>
#include <QOpenGLTexture>
#include <QMutex>
#include <QImage>
#include <memory>

namespace onechchy {
    class ImageShowRenderer : public QObject, protected QOpenGLFunctions
    {
        Q_OBJECT
    public:
        explicit ImageShowRenderer(QObject *parent = nullptr);
        virtual ~ImageShowRenderer();

        void setViewportSize(const QSize& size);
        void setWindow(QQuickWindow* pWin);
        void setCurImage(std::shared_ptr<QImage> pImage);
        QImage getCurImage();

    signals:

    public slots:
        void sltInit();
        void sltPaint();

    protected:
        std::shared_ptr<QImage> mpCurImage = nullptr;
        QMutex mMutex;
        QOpenGLTexture* mCurTexture = nullptr;
        QSize mViewportSize;
        QQuickWindow* mpWindow = nullptr;
        QOpenGLShaderProgram* mProgram = nullptr;
    };
}

#endif // IMAGESHOWRENDERER_H
