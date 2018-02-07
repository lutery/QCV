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
//#include <tuple>
#include <QDebug>

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

    QGuiApplication app(argc, argv);

    qmlRegisterType<onechchy::ImageShowItem>("ImageShowItemQML", 1, 0, "ImageShowItem");
    qmlRegisterType<onechchy::SImageService>("SImageServiceQML", 1, 0, "SImageService");
    qmlRegisterType<onechchy::ImageOperaParam>("SImageOperaParamQML", 1, 0, "ImageOperaParam");

    onechchy::start();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
