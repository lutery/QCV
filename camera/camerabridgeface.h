#ifndef CAMERABRIDGEFACE_H
#define CAMERABRIDGEFACE_H

#include <QObject>
#include <mutex>
#include <QString>

namespace onechchy {

    class CameraBridgeFace : public QObject
    {
        Q_OBJECT

    public:
        static CameraBridgeFace* getInstance();

    protected:
        explicit CameraBridgeFace(QObject *parent = nullptr);

    signals:
        void curFps(QString);
        void curPixelFormat(QString);
        void curFaceCount(int);
        void startFaceIdentify(bool, QString);

    public slots:

    private:
        static CameraBridgeFace* mpSInstance;
        static std::mutex sMutex;
    };

}

#endif // CAMERABRIDGEFACE_H
