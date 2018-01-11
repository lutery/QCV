#ifndef SIMAGE_H
#define SIMAGE_H

#include <QObject>
#include <memory>

namespace onechchy {
    class TransformImage;

    class SImage : public QObject
    {
        Q_OBJECT
    public:
        explicit SImage(QObject *parent = nullptr);

        void setTransImg(TransformImage* value);

    signals:

    public slots:

    private:
        std::unique_ptr<TransformImage> mpTransImg;
    };
}

#endif // SIMAGE_H
