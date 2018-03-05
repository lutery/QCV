#ifndef FACESERVICE_H
#define FACESERVICE_H

#include <QObject>
#include <memory>
#include "ifaceservice.h"

namespace FaceIdentify {

    class FaceService : public QObject, public IFaceService
    {
        Q_OBJECT
        Q_ENUMS(DectedMethod)

    public:
        explicit FaceService(QObject *parent = nullptr);
        virtual ~FaceService(){}

        enum class DectedMethod
        {
            OpencvHaarcascade,
            Dlib
        };

    signals:
        void sigFps(QString curFps);
        void sigPixelFormat(QString curPF);

    public slots:

        // IFaceService interface
    public:
        Q_INVOKABLE void switchFaceDectedMethod(int methodId) override;

    private:
        std::shared_ptr<IFaceService> mpFaceServiceImpl;
    };

}

#endif // FACESERVICE_H
