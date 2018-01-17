#ifndef ITRIMMINGBORDER_H
#define ITRIMMINGBORDER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <QColor>

namespace onechchy {
    /**
     * @brief The ITrimmingBorder class 切边接口，用于实现不同类型的切边方法
     */
    class ITrimingBorder : public QObject
    {
        Q_OBJECT

    public:
        explicit ITrimingBorder(QObject *parent = nullptr);

        virtual cv::Mat trimBorder(const cv::Mat&, int, QColor) = 0;

    signals:

    public slots:
    };
}

#endif // ITRIMMINGBORDER_H
