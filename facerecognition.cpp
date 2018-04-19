#include "facerecognition.h"
#include <QDir>
#include "faceservice.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace FaceIdentify {

    QString FaceRecognition::sFaceInfoDir = "FaceInfo/FaceImg";
    QString FaceRecognition::sFaceInfoJson = FaceRecognition::sFaceInfoDir + "/facelabel.json";
    QString FaceRecognition::sFaceConfig = FaceRecognition::sFaceInfoDir + "/faceConfig.json";

    FaceRecognition::FaceRecognition(QObject *parent) : QObject(parent)
    {
        QDir dir(FaceRecognition::sFaceInfoDir);
        if (!dir.exists())
        {
            // 如果目录不存在则直接创建目录
            dir.mkpath(FaceRecognition::sFaceInfoDir);
        }

        {
            QFile file(FaceRecognition::sFaceConfig);

            if (!file.exists())
            {
                // 如果文件不存在，将内嵌的json文件释放到指定的目录
    //            file.open(QIODevice::WriteOnly | QIODevice::Text);
    //            file.close();

                QFile qrcFile(":/image/resource/assets/faceConfig.json");

                if (qrcFile.exists())
                {
                    qrcFile.open(QIODevice::ReadOnly);

                    QByteArray qrcBytes = qrcFile.readAll();

                    file.open(QIODevice::WriteOnly);

                    file.write(qrcBytes);
                    file.flush();
                    file.close();
                }
            }

            file.open(QIODevice::ReadOnly);
            QByteArray faceConfig = file.readAll();

            QJsonParseError jsonError;
            QJsonDocument faceJson = QJsonDocument::fromJson(faceConfig, &jsonError);

            if (jsonError.error == QJsonParseError::NoError && faceJson.isObject())
            {
                if (faceJson.isObject())
                {
                    QJsonObject rootObj = faceJson.object();

                    if (rootObj.contains("normalsize"))
                    {
                        QJsonObject normalsize = rootObj.value("normalsize").toObject();

                        int width = normalsize.value("width").toInt();
                        int height = normalsize.value("height").toInt();

                        mNormalWidth = width;
                        mNormalHeight = height;
                    }
                }
            }
        }


        {
            QFile file(FaceRecognition::sFaceInfoJson);

            if (!file.exists())
            {
                // 如果文件不存在，将内嵌的json文件释放到指定的目录
    //            file.open(QIODevice::WriteOnly | QIODevice::Text);
    //            file.close();

                QFile qrcFile(":/image/resource/assets/faceInfos.json");

                if (qrcFile.exists())
                {
                    qrcFile.open(QIODevice::ReadOnly);

                    QByteArray qrcBytes = qrcFile.readAll();

                    file.open(QIODevice::WriteOnly);

                    file.write(qrcBytes);
                    file.flush();
                    file.close();
                }
            }

            file.open(QIODevice::ReadOnly);
            QByteArray faceConfig = file.readAll();

            QJsonParseError jsonError;
            QJsonDocument faceJson = QJsonDocument::fromJson(faceConfig, &jsonError);

            if (jsonError.error == QJsonParseError::NoError && faceJson.isObject())
            {
                if (faceJson.isObject())
                {
                    QJsonObject rootObj = faceJson.object();

                    if (rootObj.contains("faces"))
                    {
                        QJsonArray facesObj = rootObj.value("faces").toArray();

                        for (int i = 0; i < facesObj.size(); ++i)
                        {
                            QJsonObject faceObj = facesObj[i].toObject();

                            QString faceName = faceObj.value("faceName").toString();
                            int faceLabel = faceObj.value("faceName").toInt();

                            QPair<QString, int> facePair(faceName, faceLabel);

                            mFaceInfos.append(facePair);
                        }
                    }
                }
            }
        }
    }

    QStringList FaceRecognition::scanFaceInfos()
    {
        QStringList faceNames;

        for (QPair<QString, int> facePair : mFaceInfos)
        {
            faceNames.append(facePair.first);
        }

        return faceNames;
    }

    void FaceRecognition::normalizeData(cv::Mat &faceImg)
    {
        cv::Size standard(mNormalWidth, mNormalHeight);
        cv::Mat resizeFace;
        cv::resize(faceImg, resizeFace, standard, 0, 0, CV_INTER_AREA);

        cv::normalize(resizeFace,resizeFace,0, 255, cv::NORM_MINMAX, CV_8UC1);
    }

    void FaceRecognition::normalizeDatas(QVector<cv::Mat> &faceImgs)
    {
        for (auto& faceImg : faceImgs)
        {
            this->normalizeData(faceImg);
        }
    }
}
