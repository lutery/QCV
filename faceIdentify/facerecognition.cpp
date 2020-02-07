#include "facerecognition.h"
#include <QDir>
#include "faceservice.h"
#include "faceutil.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
//#include <range/v3/core.hpp>
//#include <range/v3/algorithm/copy.hpp>
//#include <range/v3/algorithm/move.hpp>
//#include <range/v3/utility/copy.hpp>
//#include <range/v3/utility/iterator.hpp>
//#include <range/v3/view/bounded.hpp>
//#include <range/v3/view/for_each.hpp>
//#include <range/v3/view/iota.hpp>
//#include <range/v3/view/map.hpp>
//#include <range/v3/view/move.hpp>
//#include <range/v3/view/stride.hpp>
//#include <range/v3/view/take_while.hpp>
//#include <range/v3/view/zip.hpp>
//#include <range/v3/view/zip_with.hpp>

namespace FaceIdentifion {

    // 面部路径
    QString FaceRecognition::sFaceInfoDir = "FaceInfo/FaceImg";
    // 面部标识文件
    QString FaceRecognition::sFaceInfoJson = FaceRecognition::sFaceInfoDir + "/facelabel.json";
    // 面部配置文件
    QString FaceRecognition::sFaceConfig = FaceRecognition::sFaceInfoDir + "/faceConfig.json";

    /**
     * @brief FaceRecognition::FaceRecognition
     * @param parent
     */
    FaceRecognition::FaceRecognition(QObject *parent) : QObject(parent), mpFaceIDentify(new FaceIdentify())
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

    /**
     * @brief FaceRecognition::scanFaceInfos 获取所有的人脸标识名字
     * @return
     */
    QStringList FaceRecognition::scanFaceInfos()
    {
        QStringList faceNames;

        for (QPair<QString, int> facePair : mFaceInfos)
        {
            faceNames.append(facePair.first);
        }

        return faceNames;
    }

    /**
     * @brief FaceRecognition::RecordFace 训练面部特征
     * @param faceId 该人脸的名字
     * @param faceMat 该人脸的矩阵信息
     */
    void FaceRecognition::RecordFace(std::vector<QString> faceId, std::vector<cv::Mat> faceMat)
    {
        int faceValue = 0;

        // 由于opencv面部标识是整形，所以这里将字符串转换为整形
        std::vector<int> faceIdInt;
        for (auto& face : faceId)
        {
            faceIdInt.push_back(FaceIdentifion::string2int(face));
        }

        // 训练
        mpFaceIDentify->trainEigenModel(faceMat, faceIdInt);

        // 将面部信息的名字和标识整形存储到内存中
//        auto testzip = ranges::view::zip(faceId, faceIdInt);
//        for (const auto& [faceName, face] : ranges::view::zip(faceId, faceIdInt))
        for (int i = 0, count = faceId.size(); i < count; ++i)
        {
            auto faceName = faceId[i];
            auto face = faceIdInt[i];
            bool bFind = false;
            QVector<QPair<QString, int>>::iterator iter = mFaceInfos.begin();

            for (; iter != mFaceInfos.end(); ++iter)
            {
                if (iter->second == face)
                {
                    bFind = true;
                    break;
                }
            }

            if (!bFind)
            {
                mFaceInfos.push_back(QPair<QString, int>(faceName, face));
            }
        }
    }

    /**
     * @brief FaceRecognition::save 保存面部识别信息到本地
     */
    void FaceRecognition::save()
    {
        mpFaceIDentify->saveModel();

        auto iter = mFaceInfos.begin();

        QJsonObject rootObj;

        QJsonArray facesArray;

        for (; iter != mFaceInfos.end(); ++iter)
        {
            QJsonObject objectJson;

            QString faceName = iter->first;
            int faceId = iter->second;

            objectJson.insert("faceName", faceName);
            objectJson.insert("faceLabel", faceId);

            facesArray.append(objectJson);
        }

        rootObj.insert("faces", facesArray);

        QJsonDocument saveDoc(rootObj);
        QFile saveFile(FaceRecognition::sFaceInfoJson);

        if (saveFile.open(QIODevice::WriteOnly))
        {
            saveFile.write(saveDoc.toJson());
        }
    }

    /**
     * @brief FaceRecognition::normalizeData 标准化面部数据的尺寸
     * @param faceImg 面部数据
     */
    void FaceRecognition::normalizeData(cv::Mat &faceImg)
    {
        cv::Size standard(mNormalWidth, mNormalHeight);
        cv::Mat resizeFace;
//        cv::resize(faceImg, resizeFace, standard, 0, 0, CV_INTER_AREA);
        cv::resize(faceImg, resizeFace, standard, 0, 0, cv::INTER_AREA);

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
