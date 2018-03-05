#include "imageutil.h"
#include <QDebug>

namespace onechchy {
//    ImageUtil::ImageUtil(QObject *parent) : QObject(parent)
//    {

//    }

//    int ImageUtil::rgb2gray(int red, int green, int black)
//    {
//        return (red*38 + green*75 + black*15) >> 7;
//    }

//    cv::Mat ImageUtil::convertGray(const cv::Mat& mat)
//    {
//        if(mat.type() == CV_8UC1)
//        {
//            return mat;
//        }
//        // 8-bits unsigned, NO. OF CHANNELS = 3
//        else if(mat.type() == CV_8UC3)
//        {
//            cv::Mat grayMat;

//            cv::cvtColor(mat, grayMat, CV_BGR2GRAY);

//            return grayMat;
//        }
//        else if(mat.type() == CV_8UC4)
//        {
//            cv::Mat grayMat;

//            cv::cvtColor(mat, grayMat, CV_BGRA2GRAY);

//            return grayMat;
//        }
//        else
//        {
//            //ToDo 抛出异常
//            qDebug() << "ERROR: Mat could not be converted to gray.";
//            return cv::Mat();
//        }
//    }

//    QImage ImageUtil::cvMat2QImage(const cv::Mat &mat)
//    {
//        // 8-bits unsigned, NO. OF CHANNELS = 1
//            if(mat.type() == CV_8UC1)
//            {
//                QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
//                // Set the color table (used to translate colour indexes to qRgb values)
//                image.setColorCount(256);
//                for(int i = 0; i < 256; i++)
//                {
//                    image.setColor(i, qRgb(i, i, i));
//                }
//                // Copy input Mat
//                uchar *pSrc = mat.data;
//                for(int row = 0; row < mat.rows; row ++)
//                {
//                    uchar *pDest = image.scanLine(row);
//                    memcpy(pDest, pSrc, mat.cols);
//                    pSrc += mat.step;
//                }
//                return image;
//            }
//            // 8-bits unsigned, NO. OF CHANNELS = 3
//            else if(mat.type() == CV_8UC3)
//            {
//                // Copy input Mat
//                const uchar *pSrc = (const uchar*)mat.data;
//                // Create QImage with same dimensions as input Mat
//                QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
//                return image.rgbSwapped();
//            }
//            else if(mat.type() == CV_8UC4)
//            {
//                qDebug() << "CV_8UC4";
//                // Copy input Mat
//                const uchar *pSrc = (const uchar*)mat.data;
//                // Create QImage with same dimensions as input Mat
//                QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
//                return image.copy();
//            }
//            else
//            {
//                //ToDo 抛出异常
//                qDebug() << "ERROR: Mat could not be converted to QImage.";
//                return QImage();
//            }
//    }

//    cv::Mat ImageUtil::QImage2cvMat(const QImage &image)
//    {
//        cv::Mat mat;
//           qDebug() << image.format();
//           switch(image.format())
//           {
//           case QImage::Format_ARGB32:
//           case QImage::Format_RGB32:
//           case QImage::Format_ARGB32_Premultiplied:
//               mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
//               break;
//           case QImage::Format_RGB888:
//               mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
//               cv::cvtColor(mat, mat, CV_BGR2RGB);
//               break;
//           case QImage::Format_Indexed8:
//               mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
//               break;
//           }
//           return mat;
//    }

    QImage cvMat2QImage(const cv::Mat &mat)
    {
        // 8-bits unsigned, NO. OF CHANNELS = 1
            if(mat.type() == CV_8UC1)
            {
                QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
                // Set the color table (used to translate colour indexes to qRgb values)
                image.setColorCount(256);
                for(int i = 0; i < 256; i++)
                {
                    image.setColor(i, qRgb(i, i, i));
                }
                // Copy input Mat
                uchar *pSrc = mat.data;
                for(int row = 0; row < mat.rows; row ++)
                {
                    uchar *pDest = image.scanLine(row);
                    memcpy(pDest, pSrc, mat.cols);
                    pSrc += mat.step;
                }
                return image;
            }
            // 8-bits unsigned, NO. OF CHANNELS = 3
            else if(mat.type() == CV_8UC3)
            {
                // Copy input Mat
                const uchar *pSrc = (const uchar*)mat.data;
                // Create QImage with same dimensions as input Mat
                QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
                return image.rgbSwapped();
            }
            else if(mat.type() == CV_8UC4)
            {
                qDebug() << "CV_8UC4";
                // Copy input Mat
                const uchar *pSrc = (const uchar*)mat.data;
                // Create QImage with same dimensions as input Mat
                QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
                return image.copy();
            }
            else
            {
                //ToDo 抛出异常
                qDebug() << "ERROR: Mat could not be converted to QImage.";
                return QImage();
            }
    }

    cv::Mat QImage2cvMat(const QImage &image)
    {
        cv::Mat mat;
        qDebug() << image.format();
        switch(image.format())
        {
        case QImage::Format_ARGB32:
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32_Premultiplied:
            mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
            break;
        case QImage::Format_RGB888:
            mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
            cv::cvtColor(mat, mat, CV_BGR2RGB);
            break;
        case QImage::Format_Indexed8:
        case QImage::Format_Grayscale8:
            mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
            break;
        }
        return mat;
    }

    int rgb2gray(int red, int green, int black)
    {
        return (red*38 + green*75 + black*15) >> 7;
    }

    cv::Mat convertGray(const cv::Mat& mat)
    {
        if(mat.type() == CV_8UC1)
        {
            return mat;
        }
        // 8-bits unsigned, NO. OF CHANNELS = 3
        else if(mat.type() == CV_8UC3)
        {
            cv::Mat grayMat;

            cv::cvtColor(mat, grayMat, CV_BGR2GRAY);

            return grayMat;
        }
        else if(mat.type() == CV_8UC4)
        {
            cv::Mat grayMat;

            cv::cvtColor(mat, grayMat, CV_BGRA2GRAY);

            return grayMat;
        }
        else
        {
            //ToDo 抛出异常
            qDebug() << "ERROR: Mat could not be converted to gray.";
            return cv::Mat();
        }
    }

    QVideoFrame cvMat2QVideoFrame(const cv::Mat &mat)
    {
        // 8-bits unsigned, NO. OF CHANNELS = 1
        if(mat.type() == CV_8UC1)
        {
            QVideoFrame frame(mat.step * mat.rows, QSize(mat.cols, mat.rows), mat.step, QVideoFrame::Format_Y8);

            if (frame.map(QAbstractVideoBuffer::WriteOnly))
            {
                // Copy input Mat
                uchar *pSrc = mat.data;
                for(int row = 0; row < mat.rows; row ++)
                {
                    uchar *pDest = frame.bits(row);
                    memcpy(pDest, pSrc, mat.cols);
                    pSrc += mat.step;
                }

                frame.unmap();
            }

            return frame;
        }
        // 8-bits unsigned, NO. OF CHANNELS = 3
        else if(mat.type() == CV_8UC3)
        {
            QVideoFrame frame(mat.step * mat.rows, QSize(mat.cols, mat.rows), mat.step, QVideoFrame::Format_RGB24);

            if (frame.map(QAbstractVideoBuffer::WriteOnly))
            {
                // Copy input Mat
                uchar *pSrc = mat.data;
                for(int row = 0; row < mat.rows; row++)
                {
                    uchar *pDest = frame.bits(row);
                    memcpy(pDest, pSrc, mat.cols * 3);
                    pSrc += mat.step;
                }


                frame.unmap();
            }

            return frame;
        }
        else if(mat.type() == CV_8UC4)
        {
            qDebug() << "CV_8UC4";
            QVideoFrame frame(mat.step * mat.rows, QSize(mat.cols, mat.rows), mat.step, QVideoFrame::Format_RGB32);

            if (frame.map(QAbstractVideoBuffer::WriteOnly))
            {
                // Copy input Mat
                uchar *pSrc = mat.data;
                for(int row = 0; row < mat.rows; row++)
                {
                    uchar *pDest = frame.bits(row);
                    memcpy(pDest, pSrc, mat.cols * 4);
                    pSrc += mat.step;
                }


                frame.unmap();
            }

            return frame;
        }
        else
        {
            //ToDo 抛出异常
            qDebug() << "ERROR: Mat could not be converted to QImage.";
            return QVideoFrame();
        }
    }

    void verticalMirror(uchar* pStart, int bytePerLine, int height)
    {
        int middle = height / 2;

//        #pragma omp parallel for
        for (int y = 0; y < middle; ++y)
        {
            int mirrorY = height - y - 1;

            for (int x = 0; x < bytePerLine; ++x)
            {
                uchar temp = pStart[bytePerLine * y + x];
                pStart[bytePerLine * y + x] = pStart[bytePerLine * mirrorY + x];
                pStart[bytePerLine * mirrorY + x] = temp;
            }
        }
    }

    cv::Mat QVideoFrame2cvMat(QVideoFrame &frame)
    {
        cv::Mat mat;
//        qDebug() << frame.pixelFormat();

        if (frame.map(QAbstractVideoBuffer::ReadOnly)){
            switch(frame.pixelFormat())
            {
            case QVideoFrame::Format_ARGB32:
            case QVideoFrame::Format_RGB32:
            case QVideoFrame::Format_ARGB32_Premultiplied:
                mat = cv::Mat(frame.height(), frame.width(), CV_8UC4, (void*)((const uchar*)frame.bits()), frame.bytesPerLine());
//                verticalMirror(mat.data, mat.step, mat.rows);
                break;
            case QVideoFrame::Format_RGB24:
                mat = cv::Mat(frame.height(), frame.width(), CV_8UC3, (void*)((const uchar*)frame.bits()), frame.bytesPerLine());
                cv::cvtColor(mat, mat, CV_BGR2RGB);
//                verticalMirror(mat.data, mat.step, mat.rows);
                break;
            case QVideoFrame::Format_Y8:
                mat = cv::Mat(frame.height(), frame.width(), CV_8UC1, (void*)((const uchar*)frame.bits()), frame.bytesPerLine());
//                verticalMirror(mat.data, mat.step, mat.rows);
                break;
            }

            frame.unmap();
        }
        return mat;
    }

    cv::Mat cvMatAlign3(const cv::Mat& srcMat)
    {
        cv::Mat alignMat(srcMat.rows, srcMat.cols, CV_8UC3, cv::Scalar::all(1));

        if (srcMat.channels() == 4)
        {
            for (int i = 0; i < srcMat.rows; ++i)
            {
                uchar* palignRow = alignMat.ptr(i);
                const uchar* psrcRow = srcMat.ptr(i);

                for (int j = 0; j < srcMat.cols; ++j)
                {
                    palignRow[j * 3 + 0] = psrcRow[j * 4 + 0];
                    palignRow[j * 3 + 1] = psrcRow[j * 4 + 1];
                    palignRow[j * 3 + 2] = psrcRow[j * 4 + 2];
                }
            }
        }
        else if (srcMat.channels() == 3)
        {
            alignMat = srcMat;
        }
        else if (srcMat.channels() == 1)
        {
            for (int i = 0; i < srcMat.rows; ++i)
            {
                uchar* palignRow = alignMat.ptr(i);
                const uchar* psrcRow = srcMat.ptr(i);

                for (int j = 0; j < srcMat.cols; ++j)
                {
                    palignRow[j * 3 + 0] = psrcRow[j + 0];
                    palignRow[j * 3 + 1] = psrcRow[j + 0];
                    palignRow[j * 3 + 2] = psrcRow[j + 0];
                }
            }
        }

        verticalMirror(alignMat.data, alignMat.step, alignMat.rows);

        return alignMat;
    }

    cv::Rect qRect2cvRect(const QRect& qrect)
    {
        cv::Rect cvRect{qrect.x(), qrect.y(), qrect.width(), qrect.height()};

        return cvRect;
    }

    QRect cvRect2qRect(const cv::Rect& cvRect)
    {
        return QRect(cvRect.x, cvRect.y, cvRect.width, cvRect.height);
    }


}
