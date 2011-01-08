#ifndef KIMAGE_H
#define KIMAGE_H

#include <QImage>
#include <QRgb>

#define C_RED 0.299
#define C_GREEN 0.587
#define C_BLUE 0.114

class KRGB {
public:
    int red;
    int green;
    int blue;

public:
    KRGB();
    KRGB(int red, int green, int blue);
    void toGray();
    KRGB *copyToYUV();
    KRGB copy();
    friend class KImage;
};

class KImage
{
protected:
    KImage *previousImage;
    KImage *nextImage;
    bool saved;
    QString filename;

public:
    int width;
    int height;
    KRGB **matrix;

    KImage(QString);
    KImage(int, int, QString);
    ~KImage();
    QImage toQImage();
    QString getFilename();
    void setFilename(QString);
    KImage* toGrayScale();
    KImage* copy();
    KImage* getPrevious();
    KImage* getNext();
    void setNext(KImage*);
    void removePrevious();
    void removeNext();
    bool isSaved();
    void setSaved(bool);
    void setNextUnsaved();

    friend class KRGB;
};

#endif // KIMAGE_H
