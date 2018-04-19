#include "faceinfo.h"

FaceInfo::FaceInfo(QObject *parent) : QObject(parent)
{

}

QString FaceInfo::recogFile() const
{
    return mRecogFile;
}

void FaceInfo::setRecogFile(const QString &recogFile)
{
    mRecogFile = recogFile;
}

QString FaceInfo::faceIcon() const
{
    return mFaceIcon;
}

void FaceInfo::setFaceIcon(const QString &faceIcon)
{
    mFaceIcon = faceIcon;
}

QString FaceInfo::faceName() const
{
    return mFaceName;
}

void FaceInfo::setFaceName(const QString &faceName)
{
    mFaceName = faceName;
}
