#include <QImage>
#include <QRgb>

#include <iostream>
#include "kimage.h"
#include <math.h>

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
        filename(filename),
        saved(false),
        width(width), height(height)
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

KImage* KImage::fusion(KImage* image, int factor)
{
    KImage* fusionnedImage = this->copy();
    image = image->resize(fusionnedImage->width, fusionnedImage->height);

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            fusionnedImage->matrix[i][j].red = (factor * fusionnedImage->matrix[i][j].red + (100 - factor) * image->matrix[i][j].red) / 100;
            fusionnedImage->matrix[i][j].green = (factor * fusionnedImage->matrix[i][j].green + (100 - factor) * image->matrix[i][j].green) / 100;
            fusionnedImage->matrix[i][j].blue = (factor * fusionnedImage->matrix[i][j].blue + (100 - factor) * image->matrix[i][j].blue) / 100;
        }
    }

    return fusionnedImage;
}

KImage* KImage::resize(int width, int height, bool scale)
{
    if (scale)
    {
        if (this->width * height < this->height * width)
        {
            width *= (int) floor((float)this->height / (float)this->width);
        }
        else
        {
            height *= (int) floor((float)this->width / (float)this->height);
        }
    }
    KImage* resizedImage = new KImage(width, height, filename);

    float xs, ys, sx, sy;
    int x0, y0;

    xs = (float) this->width / width;
    ys = (float) this->height / height;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            sx = x * xs;
            sy = y * ys;
            x0 = (int) floor(sx);
            y0 = (int) floor(sy);

            resizedImage->matrix[x][y] = matrix[x0][y0].copy();
        }
    }

    return resizedImage;
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

KRGB** KImage::getPixels(int i, int j, int taille)
{
    KRGB** pixels = new KRGB*[taille];

    for (int a = 0; a < taille; a++)
    {
        pixels[a] = new KRGB[taille];
        for (int b = 0; b < taille; b++)
        {
            pixels[a][b] = this->matrix[i + a - 1][j + b - 1];
        }
    }

    return pixels;
}

KImage* KImage::applyFilter(KFiltre *filtre)
{
    KImage* filteredImage = this->copy();
    int pixelsToSkip = (filtre->taille - 1) / 2; // Bordure où le masque n'est pas applicable

    for (int i = pixelsToSkip; i < filteredImage->width - pixelsToSkip; i++)
    {
        for (int j = pixelsToSkip; j < filteredImage->height - pixelsToSkip; j++)
        {
            KRGB** pixels = this->getPixels(i, j, filtre->taille);
            int red, green, blue;
            red = green = blue = 0;

            for(int a = 0; a < filtre->taille; a++)
            {
                for (int b = 0; b < filtre->taille; b++)
                {
                    red += pixels[a][b].red * filtre->matrix[a][b];
                    green += pixels[a][b].green * filtre->matrix[a][b];
                    blue += pixels[a][b].blue * filtre->matrix[a][b];
                }
            }

            filteredImage->matrix[i][j].red = red / filtre->diviseur;
            if (filteredImage->matrix[i][j].red < 0) filteredImage->matrix[i][j].red = 0;
            else if (filteredImage->matrix[i][j].red > 255) filteredImage->matrix[i][j].red = 255;
            filteredImage->matrix[i][j].green = green / filtre->diviseur;
            if (filteredImage->matrix[i][j].green < 0) filteredImage->matrix[i][j].green = 0;
            else if (filteredImage->matrix[i][j].green > 255) filteredImage->matrix[i][j].green = 255;
            filteredImage->matrix[i][j].blue = blue / filtre->diviseur;
            if (filteredImage->matrix[i][j].blue < 0) filteredImage->matrix[i][j].blue = 0;
            else if (filteredImage->matrix[i][j].blue > 255) filteredImage->matrix[i][j].blue = 255;
        }
    }

    delete filtre;
    return filteredImage;
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
        delete q;
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
        delete q;
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
