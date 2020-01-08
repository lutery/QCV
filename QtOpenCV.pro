QT += quick core multimedia
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += /openmp

SOURCES += \
        main.cpp \
        imageshowitem.cpp \
        imageshowrenderer.cpp \
        simageservice.cpp

HEADERS += \
    cameratodo.h \
    imageshowitem.h \
    imageshowrenderer.h \
    simageservice.h


RESOURCES += qml.qrc

LIBS += -fopenmp

CONFIG (debug, debug|release){
    win32: LIBS += -lopencv_world410d -ldlibd
    DEFINES += IDEBUG
}else{
    win32: LIBS += -lopencv_world410 -ldlib
    DEFINES += NDEBUG
}

INCLUDEPATH += \
    E:/DevelopmentKit/opencv/include \
    E:/DevelopmentKit/range-v3/include \
    F:/DevelopmentKit/dlib/inc

LIBS += \
    -LE:/DevelopmentKit/opencv/x64/vc16/lib \
    -LF:/DevelopmentKit/dlib/lib/x64

SUBDIRS += camera \
            faceIdentify \
            grayBinary \
            imgOperation \
            trimBorder

include($$PWD/camera/camera.pri)
include($$PWD/faceIdentify/faceIdentify.pri)
include($$PWD/grayBinary/grayBinary.pri)
include($$PWD/imgOperation/imgOperation.pri)
include($$PWD/trimBorder/trimBorder.pri)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
