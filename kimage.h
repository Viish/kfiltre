#ifndef KIMAGE_H
#define KIMAGE_H

#include <QImage>

#include "kimage_fwd.h"

enum TOOL {
    NONE, RESIZE, RECTANGLE, MOVE, ELLIPSE, PATH
};

class KImage
{
protected:
    KImage *previousImage;
    KImage *nextImage;
    QString filename;
    bool saved;
    int **energy;

    KImage& operator=(const KImage&);

public:
    Pixel **matrix;
    int realWidth;
    int realHeight;
    int width;
    int height;
    int nextVSeam, nextHSeam;
    Seam *pathX, *pathY;

    KImage();
    KImage(const KImage&);
    KImage(QString);
    KImage(int, int, QString = "");
    ~KImage();

    void deleteMatrix();
    void deleteSeamCarving();
    QImage toQImage();
    void loadImage(const QImage&);
    void reload();
    void copy(const KImage&);

    QString getFilename();
    void setFilename(QString);
    Pixel getPixel(int x, int y) const;
    Pixel getYUVPixel(int x, int y) const;

    KImage* toGrayScale();
    KImage* toGrayScale(Path*);
    KImage* toGrayScale(int, int, int, int, TOOL, Path* = NULL);
    KImage* copy();
    KImage* getPrevious();
    KImage* getNext();
    KImage* rotateClockwise();
    KImage* rotateCounterClockwise();
    KImage* applyFilter(const KFiltre&);
    KImage* applyFilter(const KFiltre&, Path*);
    KImage* applyFilter(const KFiltre&, int, int, int, int, TOOL, Path* = NULL);
    KImage* resize(int, int, bool scale = false);
    KImage* fusion(KImage* image, int factor);
    KImage* applyNegative();
    KImage* applyNegative(Path*);
    KImage* applyNegative(int, int, int, int, TOOL, Path* = NULL);
    KImage* applyMedianSmoothing();
    KImage* applyMedianSmoothing(Path*);
    KImage* applyMedianSmoothing(int, int, int, int, TOOL, Path* = NULL);
    KImage* verticalMirror();
    KImage* horizontalMirror();

    void fusion(const KImage &image, KImage &target, int factor);
    void sortArray(unsigned char*, int = 9);
    void setNext(KImage*);
    void removePrevious();
    void removeNext();
    bool isSaved();
    void setSaved(bool);
    void setNextUnsaved();
    bool isInsideEllipse(int, int, int, int, int, int);
    bool isInsidePath(int, int, Path*);
    double angle2D(double, double, double, double);

    KImage* seamCarving(int, int, KResizeDialog* = NULL);
    void initSeamCarving();
    void initEnergy();
    void initVerticalPaths();
    void initHorizontalPaths();

    void recalculateEnergy(int minx, int maxx, int miny, int maxy);
    void generateVerticalPaths(int, int);
    void generateHorizontalPaths(int, int);
    void generateVerticalPath(int);
    void generateHorizontalPath(int);
    void removeVerticalPath(int);
    void removeHorizontalPath(int);
    int gradient(int x, int y);

};

#endif // KIMAGE_H
