#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QImage>
#include <opencv2/opencv.hpp>
#include "imageutil.h"
#include "util.h"
#include "imageshowitem.h"
#include "simage.h"
#include "simageservice.h"
#include "imageoperaparam.h"
#include "itrimingborder.h"
#include "camerafilter.h"
#include "faceservice.h"
#include <QDebug>
#include <QList>
#include <QRect>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

//    cv::Mat mat = cv::Mat();

//    auto test = std::make_tuple(1, "a");
//    auto [i, str] = test;

//    QImage image(":/image/resource/image/zero0.png");
//    uchar* pData = image.bits();

//    cv::Mat mat = cv::imread(R"(D:\Projects\Windows\C++\Qt\QtOpenCV\resource\image\RGB32.bmp)");
//    QImage image = onechchy::ImageUtil::cvMat2QImage(mat);
//    image.save(R"(D:\tmp\qimage32.jpg)");

//    qDebug() << "i = " << i << ", str = " << str;

#ifndef _OPENMP
    qDebug() << "OpenMP not supported";
#endif

    qRegisterMetaType<QRect>("QRect");
    qRegisterMetaType<QList<QRect>>("QList<QRect>");

    QGuiApplication app(argc, argv);

    FaceIdentifion::FaceService* sFaceService = new FaceIdentifion::FaceService();

    qmlRegisterType<onechchy::ImageShowItem>("ImageShowItemQML", 1, 0, "ImageShowItem");
    qmlRegisterType<onechchy::SImageService>("SImageServiceQML", 1, 0, "SImageService");
    qmlRegisterType<onechchy::ImageOperaParam>("SImageOperaParamQML", 1, 0, "ImageOperaParam");
    qmlRegisterType<onechchy::CameraFilter>("CameraFilter", 1, 0, "CameraFilter");
//    qmlRegisterType<FaceIdentifion::FaceService>("FaceService", 1, 0, "FaceService");
    qmlRegisterSingletonType<FaceIdentifion::FaceService>("FaceService", 1, 0, "FaceService", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        FaceIdentifion::FaceService* faceService = new FaceIdentifion::FaceService();

        return faceService;
    });

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
