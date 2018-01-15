#ifndef ITRIMMINGBORDER_H
#define ITRIMMINGBORDER_H

#include <QObject>
#include <opencv2/opencv.hpp>

namespace onechchy {
    class ITrimmingBorder : public QObject
    {
        Q_OBJECT
        Q_ENUMS(Border)
    public:
        explicit ITrimmingBorder(QObject *parent = nullptr);

        enum Border{
            left = 0x01,
            top = 0x02,
            right = 0x04,
            bottom = 0x08
        };

        virtual cv::Mat trimBorder(cv::Mat, int) = 0;

    signals:

    public slots:
    };
}

#endif // ITRIMMINGBORDER_H
