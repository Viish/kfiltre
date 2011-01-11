#ifndef KIMAGE_H
#define KIMAGE_H

#include <QImage>
#include <QRgb>
#include "kfiltre.h"

#define C_RED 0.299
#define C_GREEN 0.587
#define C_BLUE 0.114

class Point
{
public :
    Point(int, int);
    Point();
    int x, y;
    int pathEnergy;
};

class KRGB {
public:
    int red;
    int green;
    int blue;
    int energy;

public:
    KRGB();
    KRGB(int red, int green, int blue, int energy = 0);
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
    QString filename;
    bool saved;

public:
    int width;
    int height;
    KRGB **matrix;
    Point **entryPointsX, **entryPointsY;
    bool isEnergyDirty;

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
    KImage* applyFilter(KFiltre *, bool setDirty = true);
    KImage* resize(int, int, bool scale = false);
    KImage* fusion(KImage* image, int factor);

    void setNext(KImage*);
    void removePrevious();
    void removeNext();
    bool isSaved();
    void setSaved(bool);
    void setNextUnsaved();

    void calculateEnergy();
    Point* generateLowCostVerticalPath(int x);
    Point* generateLowCostHorizontalPath(int x);
    int getLowCostEntryPointX();
    int getLowCostEntryPointY();
    Point** generateEntryPointsX();
    Point** generateEntryPointsY();
    int getVerticalPathEnergy(Point* path);
    int getHorizontalPathEnergy(Point* path);
    KImage* removeVerticalPath(Point* path);
    KImage* removeHorizontalPath(Point* path);
    KImage* seamCarving(int, int);

    friend class KRGB;

private :
    KRGB** getPixels(int, int, int);
};

#endif // KIMAGE_H
