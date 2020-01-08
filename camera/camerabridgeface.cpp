#include "camerabridgeface.h"

namespace onechchy {

    CameraBridgeFace* CameraBridgeFace::mpSInstance = nullptr;
    std::mutex CameraBridgeFace::sMutex;

    CameraBridgeFace *CameraBridgeFace::getInstance()
    {
        if (mpSInstance == nullptr)
        {
            std::unique_lock<std::mutex> lock(sMutex);
            if (mpSInstance == nullptr)
            {
                mpSInstance = new CameraBridgeFace();
            }
        }

        return mpSInstance;
    }

    CameraBridgeFace::CameraBridgeFace(QObject *parent) : QObject(parent)
    {

    }

}
