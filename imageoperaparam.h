#ifndef IMAGEOPERAPARAM_H
#define IMAGEOPERAPARAM_H

#include <QObject>

namespace onechchy {
    class ImageOperaParam : public QObject
    {
        Q_OBJECT
    public:
        explicit ImageOperaParam(QObject *parent = nullptr);

        int trimBorder() const;
        Q_INVOKABLE void setTrimBorder(int trimBorder);

        long bgColor() const;
        Q_INVOKABLE void setBgColor(long bgColor);

    signals:

    public slots:

    private:
        int mTrimBorder = 0x00;
        long mBgColor = 0x000000;
    };
}

#endif // IMAGEOPERAPARAM_H
