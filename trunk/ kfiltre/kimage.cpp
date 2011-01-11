#include <QImage>
#include <QRgb>

#include <iostream>
#include "kimage.h"
#include <math.h>

KRGB::KRGB() :
        red(0),
        green(0),
        blue(0),
        energy(0)
{}

KRGB::KRGB(int red, int green, int blue, int energy) :
        red(red),
        green(green),
        blue(blue),
        energy(energy)
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
    KRGB *pixelYUV = new KRGB(y, u, v, energy);
    return pixelYUV;
}

KRGB KRGB::copy()
{
    KRGB pixel(red, green, blue, energy);
    return pixel;
}

KImage::KImage(QString filename) :
        previousImage(NULL),
        nextImage(NULL),
        filename(filename),
        saved(true),
        isEnergyDirty(true)
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
        }
    }
}

KImage::KImage(int width, int height, QString filename) :
        previousImage(NULL),
        nextImage(NULL),
        filename(filename),
        saved(false),
        width(width), height(height),
        isEnergyDirty(true)
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
    fusionnedImage->isEnergyDirty = true;

    KImage *image2 = image->resize(fusionnedImage->width, fusionnedImage->height);

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            fusionnedImage->matrix[i][j].red = (factor * fusionnedImage->matrix[i][j].red + (100 - factor) * image2->matrix[i][j].red) / 100;
            fusionnedImage->matrix[i][j].green = (factor * fusionnedImage->matrix[i][j].green + (100 - factor) * image2->matrix[i][j].green) / 100;
            fusionnedImage->matrix[i][j].blue = (factor * fusionnedImage->matrix[i][j].blue + (100 - factor) * image2->matrix[i][j].blue) / 100;
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
    resizedImage->isEnergyDirty = true;

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

    grayScale->entryPointsX = this->entryPointsX;
    grayScale->entryPointsY = this->entryPointsY;

    return grayScale;
}

KImage* KImage::copy()
{
    KImage *copy = new KImage(this->width, this->height, this->filename);
    copy->entryPointsX = this->entryPointsX;
    copy->entryPointsY = this->entryPointsY;
    copy->isEnergyDirty = this->isEnergyDirty;

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

KImage* KImage::applyFilter(KFiltre *filtre, bool setDirty)
{
    KImage* filteredImage = this->copy();
    if (setDirty) filteredImage->isEnergyDirty = true;

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

Point::Point(int x, int y) : x(x), y(y) {}
Point::Point() : x(-1), y(-1) {}

void KImage::calculateEnergy()
{
    KFiltre *filtreX = new KFiltre(PREWITT_X);
    KFiltre *filtreY = new KFiltre(PREWITT_Y);

    KImage *tempX = this->applyFilter(filtreX, false);
    KImage *tempY = this->applyFilter(filtreY, false);

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            this->matrix[i][j].energy = abs(tempX->matrix[i][j].red) + abs(tempY->matrix[i][j].red);
        }
    }

    delete tempX;
    delete tempY;

    this->entryPointsX = this->generateEntryPointsX();
    this->entryPointsY = this->generateEntryPointsY();
}

Point** KImage::generateEntryPointsX()
{
    Point **entryPointsX = new Point*[this->width];
    for (int x = 0; x < this->width; x++)
    {
        Point *p = new Point(x, 0);
        entryPointsX[x] = p;
        entryPointsX[x]->pathEnergy = this->getVerticalPathEnergy(this->generateLowCostVerticalPath(x));
    }

    return entryPointsX;
}

Point** KImage::generateEntryPointsY()
{
    Point **entryPointsY = new Point*[this->height];
    for (int y = 0; y < this->height; y++)
    {
        Point *p = new Point(0, y);
        entryPointsY[y] = p;
        entryPointsY[y]->pathEnergy = this->getHorizontalPathEnergy(this->generateLowCostHorizontalPath(y));
    }

    return entryPointsY;
}

int KImage::getVerticalPathEnergy(Point* path)
{
    int energy = 0;

    for (int x = 0; x < this->height; x++)
    {
        energy += this->matrix[path[x].x][path[x].y].energy;
    }

    return energy;
}

int KImage::getHorizontalPathEnergy(Point* path)
{
    int energy = 0;

    for (int y = 0; y < this->width; y++)
    {
        energy += this->matrix[path[y].x][path[y].y].energy;
    }

    return energy;
}

Point* KImage::generateLowCostVerticalPath(int x)
{
    Point *path = new Point[this->height];
    Point p(x, 0);
    path[0] = p;

    for (int y = 1; y < this->height; y++)
    {
        Point p(x, y);
        if (x - 1 >= 0 && this->matrix[x-1][y].energy < this->matrix[p.x][p.y].energy)
            p = Point(x-1, y);
        if (x + 1 < this->width && this->matrix[x+1][y].energy < this->matrix[p.x][p.y].energy)
            p = Point(x+1, y);

        path[y] = p;
        x = p.x;
    }

    return path;
}

Point* KImage::generateLowCostHorizontalPath(int y)
{
    Point *path = new Point[this->width];
    Point p(0, y);
    path[0] = p;

    for (int x = 1; x < this->width; x++)
    {
        Point p(x, y);
        if (y - 1 >= 0 && this->matrix[x][y-1].energy < this->matrix[p.x][p.y].energy)
            p = Point(x, y-1);
        if (y + 1 < this->height && this->matrix[x][y+1].energy < this->matrix[p.x][p.y].energy)
            p = Point(x, y+1);

        path[x] = p;
        y = p.y;
    }

    return path;
}

int KImage::getLowCostEntryPointX()
{
    int x;
    int energy_min = 255*this->height;

    for (int i = 0; i < this->width; i++)
    {
        if (entryPointsX[i]->pathEnergy < energy_min)
        {
            x = i;
            energy_min = entryPointsX[i]->pathEnergy;
        }
    }

    return x;
}

int KImage::getLowCostEntryPointY()
{
    int y;
    int energy_min = 255*this->width;

    for (int i = 0; i < this->height; i++)
    {
        if (entryPointsY[i]->pathEnergy < energy_min)
        {
            y = i;
            energy_min = entryPointsY[i]->pathEnergy;
        }
    }

    return y;
}

KImage* KImage::removeVerticalPath(Point* path)
{
    KImage *image = new KImage(this->width - 1, this->height, this->filename);
    delete this->entryPointsX;
    delete this->entryPointsY;

    image->entryPointsX = this->generateEntryPointsX();
    image->entryPointsY = this->generateEntryPointsY();
    image->isEnergyDirty = false;

    for (int j = 0; j < this->height; j++)
    {
        for (int i = 0; i < image->width; i++)
        {
            if (i < path[j].x)
            {
                image->matrix[i][j] = this->matrix[i][j].copy();
            }
            else if (i >= path[j].x)
            {
                image->matrix[i][j] = this->matrix[i+1][j].copy();
            }
        }
    }

    delete path;
    return image;
}

KImage* KImage::removeHorizontalPath(Point* path)
{
    KImage *image = new KImage(this->width, this->height - 1, this->filename);
    delete this->entryPointsX;
    delete this->entryPointsY;

    image->entryPointsX = this->generateEntryPointsX();
    image->entryPointsY = this->generateEntryPointsY();
    image->isEnergyDirty = false;

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            if (j < path[i].y)
            {
                image->matrix[i][j] = this->matrix[i][j].copy();
            }
            else if (j >= path[i].y)
            {
                image->matrix[i][j] = this->matrix[i][j+1].copy();
            }
        }
    }

    delete path;
    return image;
}

KImage* KImage::seamCarving(int w, int h)
{
    if (isEnergyDirty) this->calculateEnergy();
    isEnergyDirty = false;

    KImage *image = this;
    KImage *image2 = NULL;

    while (image->width > w || image->height > h)
    {
        if (image->width > w)
        {
            Point *path = image->generateLowCostVerticalPath(image->getLowCostEntryPointX());
            image2 = image->removeVerticalPath(path);
            delete image;
            image = image2;
        }
        if (image->height > h)
        {
            Point *path = image->generateLowCostHorizontalPath(image->getLowCostEntryPointY());
            image2 = image->removeHorizontalPath(path);
            delete image;
            image = image2;
        }
    }

    return image;
}
