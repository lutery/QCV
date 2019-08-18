#ifndef IFACESERVICE_H
#define IFACESERVICE_H

namespace FaceIdentifion {

    class IFaceService
    {
    public:
        virtual void switchFaceDectedMethod(int methodId) = 0;
    };

}

#endif // IFACESERVICE_H
