#include "facerecognitiondaemon.h"
#include "faceutil.h"
#include <QMutexLocker>

namespace onechchy {

    void FaceRecognitionDaemon::run()
    {
        while (!mbExit)
        {
            QMutexLocker locker(&mLock);
            std::vector<QString> faceIds;
            QVector<cv::Mat> faces;

            auto _iterator = mFacesIds.begin();

            if (_iterator == mFacesIds.begin())
            {
                continue;
            }

            for (;_iterator != mFacesIds.constEnd(); ++_iterator)
            {
                if (_iterator.value().size() > 30)
                {
//                    faceIds.push_back(_iterator.key());
//                    faces.insert(faces.end(), _iterator.value().begin(), _iterator.value().end());

                    for (int i = 0; i < _iterator.value().size(); ++i)
                    {
                        faceIds.push_back(_iterator.key());
                        faces.push_back(_iterator.value()[i]);
                    }
                }
            }

            for (const auto& faceId : faceIds)
            {
                mFacesIds.remove(faceId);
            }

            if (faceIds.size() > 0)
            {
                FaceIdentifion::FaceIDentifyHelper(faceIds, faces);
            }
        }
    }

    FaceRecognitionDaemon::FaceRecognitionDaemon(QObject *parent) : QThread(parent)
    {

    }

    FaceRecognitionDaemon::~FaceRecognitionDaemon()
    {

    }

    void FaceRecognitionDaemon::pushFaces(QString faceId, QVector<cv::Mat> faces)
    {
        QMutexLocker locker(&mLock);

        if (mFacesIds.contains(faceId))
        {
            mFacesIds[faceId].append(faces);
        }
        else
        {
            mFacesIds[faceId] = faces;
        }
    }

    void FaceRecognitionDaemon::quit()
    {
        QThread::quit();

        mbExit = true;
    }

}
