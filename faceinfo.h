#ifndef FACEINFO_H
#define FACEINFO_H

#include <QObject>
#include <QString>

class FaceInfo : public QObject
{
    Q_OBJECT
public:
    explicit FaceInfo(QObject *parent = nullptr);

    Q_INVOKABLE QString recogFile() const;
    void setRecogFile(const QString &recogFile);

    Q_INVOKABLE QString faceIcon() const;
    void setFaceIcon(const QString &faceIcon);

    Q_INVOKABLE QString faceName() const;
    void setFaceName(const QString &faceName);

signals:

public slots:

private:
    QString mRecogFile;
    QString mFaceIcon;
    QString mFaceName;
};

#endif // FACEINFO_H
