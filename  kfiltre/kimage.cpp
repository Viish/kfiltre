#include <QImage>
#include <QRgb>

#include <iostream>
#include "kimage.h"

KRGB::KRGB() :
        red(0),
        green(0),
        blue(0)
{}

KRGB::KRGB(int red, int green, int blue) :
        red(red),
        green(green),
        blue(blue)
{}

void KRGB::toGray()
{
    this->red = this->blue = this->green = this->red * C_RED + this->blue * C_BLUE + this->green * C_GREEN;
}

KRGB* KRGB::copyToYUV()
{
    int y, u, v;
    y = 0.299 * this->red + 0.587 * this->green + 0.114 * this->blue;
    u = 0.436 * (this->blue - y) / (1 - 0.114);
    v = 0.615 * (this->red - y) / (1 - 0.299);
    KRGB *pixelYUV = new KRGB(y, u, v);
    return pixelYUV;
}

KRGB KRGB::copy()
{
    KRGB pixel(red, green, blue);
    return pixel;
}

KImage::KImage(QString filename) :
        previousImage(NULL),
        nextImage(NULL),
        filename(filename),
        saved(true)
{
    QImage input(filename);
    this->width = input.width();
    this->height = input.height();
    this->matrix = new KRGB*[this->width];

    for (int i = 0; i < this->width; i++)
    {
        this->matrix[i] = new KRGB[this->height];
        for (int j = 0; j < this->height; j++)
        {
            QRgb pixel = input.pixel(i, j);
            KRGB newpixel(qRed(pixel), qGreen(pixel), qBlue(pixel));
            this->matrix[i][j] = newpixel;
            //std::cout << "matrix[" << i << ","<< j << "]" << newpixel.blue << std::endl;
        }
    }
}

KImage::KImage(int width, int height, QString filename) :
        previousImage(NULL),
        nextImage(NULL),
        width(width), height(height),
        filename(filename),
        saved(false)
{
    this->matrix = new KRGB*[this->width];

    for (int i = 0; i < this->width; i++)
    {
        this->matrix[i] = new KRGB[this->height];
        for (int j = 0; j < this->height; j++)
        {
            KRGB newpixel(0, 0, 0);
            this->matrix[i][j] = newpixel;
        }
    }
}

KImage::~KImage()
{
    for (int i = 0; i < this->width; ++i) delete[] this->matrix[i];
    delete [] this->matrix;
}

QImage KImage::toQImage()
{
    QImage result(this->width, this->height, QImage::Format_RGB32);
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            result.setPixel(i, j, qRgb((this->matrix[i][j].red), (this->matrix[i][j].green), (this->matrix[i][j].blue)));
        }
    }
    return result;
}

QString KImage::getFilename()
{
    return this->filename;
}

void KImage::setFilename(QString filename)
{
    this->filename = filename;
}

KImage* KImage::toGrayScale()
{
    KImage* grayScale = this->copy();
    for (int i = 0; i < grayScale->width; ++i)
    {
        for (int j = 0; j < grayScale->height; ++j)
        {
            grayScale->matrix[i][j].toGray();
        }
    }
    return grayScale;
}

KImage* KImage::copy()
{
    KImage *copy = new KImage(this->width, this->height, this->filename);
    copy->filename = this->filename;
    copy->previousImage = NULL;
    copy->nextImage = NULL;

    for (int i = 0; i < this->width; ++i)
    {
        for (int j = 0; j < this->height; ++j)
        {
            copy->matrix[i][j] = this->matrix[i][j].copy();
        }
    }

    return copy;
}

KImage* KImage::getPrevious()
{
    return this->previousImage;
}

KImage* KImage::getNext()
{
    return this->nextImage;
}

void KImage::setNext(KImage* next)
{
    std::cerr << "void KImage::setNext(KImage* next)" << std::endl;
    if (next == NULL) std::cerr << "void KImage::setNext(KImage* next) : next vaut null" << std::endl;
    if (this->nextImage != NULL)
    {
        this->removeNext();
    }
    this->nextImage = next;
    next->previousImage = this;
}

void KImage::removePrevious()
{
    KImage *q = NULL;
    KImage *p = this->previousImage;
    while (p != NULL)
    {
        q = p;
        p = p->previousImage;
        //delete q;
    }
}

void KImage::removeNext()
{
    std::cerr << "void KImage::removeNext()" << std::endl;
    KImage *q = NULL;
    KImage *p = this->nextImage;
    while (p != NULL)
    {
        q = p;
        p = p->nextImage;
        //delete q;
    }
}

bool KImage::isSaved()
{
    return this->saved;
}

void KImage::setSaved(bool saved)
{
    this->saved = saved;
}

void KImage::setNextUnsaved()
{
    this->setSaved(false);
    if(this->getNext() == NULL);
    else this->getNext()->setNextUnsaved();
}
