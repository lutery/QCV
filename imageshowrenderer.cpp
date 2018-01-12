#include "imageshowrenderer.h"

namespace onechchy {
    ImageShowRenderer::ImageShowRenderer(QObject *parent) : QObject(parent)
    {

    }

    ImageShowRenderer::~ImageShowRenderer()
    {
        if (mProgram != nullptr)
        {
            delete mProgram;
            mProgram = nullptr;
        }

        QMutexLocker locker(&mMutex);
        if (mCurTexture != nullptr)
        {
            delete mCurTexture;
            mCurTexture = nullptr;
        }
    }

    void ImageShowRenderer::setViewportSize(const QSize &size)
    {
        mViewportSize = size;
    }

    void ImageShowRenderer::setWindow(QQuickWindow *pWin)
    {
        mpWindow = pWin;
    }

    void ImageShowRenderer::setCurImage(std::shared_ptr<QImage> pImage)
    {
        QMutexLocker locker(&mMutex);
        mpCurImage = pImage;
    }

    void ImageShowRenderer::sltInit()
    {
        this->initializeOpenGLFunctions();

    //    mCurTexture = new QOpenGLTexture(QImage(":/images/Image/Zero0.jpg"));
        mpCurImage = std::shared_ptr<QImage>(new QImage(":/image/resource/image/RGB24.bmp"));

        mProgram = new QOpenGLShaderProgram();
        mProgram->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                                     "attribute highp vec4 vertices;"
                                                     "attribute vec2 coord_texture;"
                                                     "varying highp vec2 coords;"
                                                     "void main() {"
                                                     "    gl_Position = vertices;"
                                                     "    coords = coord_texture;"
                                                     "}");

         mProgram->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                     "uniform sampler2D texture0;"
                                                     "varying highp vec2 coords;"
                                                     "void main() {"
                                                     "    "
                                                     "    gl_FragColor = texture2D(texture0, coords);"
                                                     "}");

        mProgram->bindAttributeLocation("vertices", 0);
        mProgram->bindAttributeLocation("coord_texture", 1);
        mProgram->link();
        mProgram->setUniformValue("texture0", 0);
    }

    void ImageShowRenderer::sltPaint()
    {
        mProgram->bind();

        mProgram->enableAttributeArray(0);
        mProgram->enableAttributeArray(1);

        static float values[] = {
            -1, -1,
            1, -1,
            -1, 1,
            1, 1
        };

        static float coords[] = {
            0, 1,
            1, 1,
            0, 0,
            1, 0,
        };

        mProgram->setAttributeArray(0, GL_FLOAT, values, 2);
        mProgram->setAttributeArray(1, GL_FLOAT, coords, 2);


        glViewport(0, 0, mViewportSize.width(), mViewportSize.height());

        glDisable(GL_DEPTH_TEST);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        QMutexLocker locker(&mMutex);
        qDebug() << "--------------------------------";
        if (mpCurImage != nullptr){
            qDebug() << "+++++++++++++++++++++++++++++++";
            if (mCurTexture != nullptr)
            {
                delete mCurTexture;
                mCurTexture = nullptr;
            }

            mCurTexture = new QOpenGLTexture(*mpCurImage);
        }

        mCurTexture->bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        mProgram->disableAttributeArray(1);
        mProgram->disableAttributeArray(0);
        mProgram->release();

        mpWindow->resetOpenGLState();
    }
    
    QImage ImageShowRenderer::getCurImage()
    {
        return *mpCurImage;
    }
}
