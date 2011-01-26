#include <cmath>
#include <QImage>
#include <QRgb>
#include <iostream>

#include "kfiltre.h"
#include "kimage.h"
#include "kresizedialog.h"

#define C_RED 0.299
#define C_GREEN 0.587
#define C_BLUE 0.114

KImage::KImage() :
        previousImage(NULL),
        nextImage(NULL),
        filename(""),
        saved(false),
        energy(NULL),
        matrix(NULL),
        realWidth(0),
        realHeight(0),
        width(0),
        height(0),
        nextVSeam(-1),
        nextHSeam(-1),
        pathX(NULL),
        pathY(NULL)
{ }

KImage::KImage(const KImage& image) :
        previousImage(NULL),
        nextImage(NULL),
        filename(image.filename),
        saved(false),
        energy(NULL),
        matrix(NULL),
        realWidth(image.width),
        realHeight(image.height),
        width(image.width),
        height(image.height),
        nextVSeam(-1),
        nextHSeam(-1),
        pathX(NULL),
        pathY(NULL)
{
    this->copy(image);
}

KImage::KImage(QString filename) :
        previousImage(NULL),
        nextImage(NULL),
        filename(filename),
        saved(true),
        energy(NULL),
        realWidth(0),
        realHeight(0),
        width(0),
        height(0),
        nextVSeam(-1),
        nextHSeam(-1),
        pathX(NULL),
        pathY(NULL)
{
    QImage input(filename);
    this->loadImage(input);
}

KImage::KImage(int width, int height, QString filename) :
        previousImage(NULL),
        nextImage(NULL),
        filename(filename),
        saved(false),
        energy(NULL),
        matrix(NULL),
        realWidth(width),
        realHeight(height),
        width(width),
        height(height),
        nextVSeam(-1),
        nextHSeam(-1),
        pathX(NULL),
        pathY(NULL)
{
    this->matrix = new Pixel*[this->realWidth];

    for (int i = 0; i < this->realWidth; i++)
    {
        this->matrix[i] = new Pixel[this->realHeight];
        for (int j = 0; j < this->realHeight; j++)
        {
            this->matrix[i][j].red = 0;
            this->matrix[i][j].green = 0;
            this->matrix[i][j].blue = 0;
            this->matrix[i][j].alpha = 0;
        }
    }
}

KImage::~KImage()
{
    this->deleteMatrix();
    this->deleteSeamCarving();
}

KImage& KImage::operator=(const KImage& image)
{
    if (this->width < image.width || this->height < image.height)
    {
        this->deleteMatrix();
        this->copy(image);
    }
    else
    {
        this->width = image.width;
        this->height = image.height;
        this->filename = image.filename;

        for (int i = 0; i < this->width; ++i)
        {
            for (int j = 0; j < this->height; ++j)
            {
                this->matrix[i][j] = image.matrix[i][j];
            }
        }
    }
    return *this;
}

void KImage::copy(const KImage& image)
{
    this->matrix = new Pixel*[this->realWidth];

    for (int i = 0; i < this->realWidth; i++)
    {
        this->matrix[i] = new Pixel[this->realHeight];
        for (int j = 0; j < this->realHeight; j++)
        {
            this->matrix[i][j] = image.matrix[i][j];
        }
    }
}

QImage KImage::toQImage()
{
    QImage result(this->width, this->height, QImage::Format_ARGB32);
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            result.setPixel(i, j, qRgba(this->matrix[i][j].red, this->matrix[i][j].green, this->matrix[i][j].blue, this->matrix[i][j].alpha));
        }
    }
    return result;
}

void KImage::loadImage(const QImage &input)
{
    this->realWidth = this->width = input.width();
    this->realHeight = this->height = input.height();
    this->matrix = new Pixel*[this->realWidth];

    for (int i = 0; i < this->realWidth; i++)
    {
        this->matrix[i] = new Pixel[this->realHeight];
        for (int j = 0; j < this->realHeight; j++)
        {
            QRgb pixel = input.pixel(i, j);
            this->matrix[i][j].red = (unsigned char)qRed(pixel);
            this->matrix[i][j].green = (unsigned char)qGreen(pixel);
            this->matrix[i][j].blue = (unsigned char)qBlue(pixel);
            this->matrix[i][j].alpha = (unsigned char)qAlpha(pixel);
        }
    }
}

void KImage::deleteMatrix()
{
    for (int i = 0; i < this->realWidth; ++i) delete[] this->matrix[i];
    delete [] this->matrix;
}

void KImage::reload()
{
    QImage input(this->filename);
    if (this->width < input.width() || this->height < input.height())
    {
        this->deleteMatrix();
        this->loadImage(input);
    }
    else
    {
        this->width = input.width();
        this->height = input.height();

        for (int i = 0; i < this->width; i++)
        {
            for (int j = 0; j < this->height; j++)
            {
                QRgb pixel = input.pixel(i, j);
                this->matrix[i][j].red = (unsigned char)qRed(pixel);
                this->matrix[i][j].green = (unsigned char)qGreen(pixel);
                this->matrix[i][j].blue = (unsigned char)qBlue(pixel);
                this->matrix[i][j].alpha = (unsigned char)qAlpha(pixel);
            }
        }
    }
}

Pixel KImage::getPixel(int x, int y) const
{
    return this->matrix[x][y];
}

Pixel KImage::getYUVPixel(int x, int y) const
{
    Pixel yuv;
    yuv.red = 0.299 * this->matrix[x][y].red + 0.587 * this->matrix[x][y].green + 0.114 * this->matrix[x][y].blue;
    yuv.green = 0.436 * (this->matrix[x][y].blue - yuv.red) / (1 - 0.114);
    yuv.blue = 0.615 * (this->matrix[x][y].red - yuv.red) / (1 - 0.299);

    return yuv;
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
    KImage* target = new KImage(this->width, this->height, this->filename);
    KImage *fusion = image->resize(this->width, this->height);

    this->fusion(*fusion, *target, factor);
    delete fusion;

    return target;
}

void KImage::fusion(const KImage &image, KImage &target, int factor)
{
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            target.matrix[i][j].red = (factor * this->matrix[i][j].red + (100 - factor) * image.matrix[i][j].red) / 100;
            target.matrix[i][j].green = (factor * this->matrix[i][j].green + (100 - factor) * image.matrix[i][j].green) / 100;
            target.matrix[i][j].blue = (factor * this->matrix[i][j].blue + (100 - factor) * image.matrix[i][j].blue) / 100;
            target.matrix[i][j].alpha = (factor * this->matrix[i][j].alpha + (100 - factor) * image.matrix[i][j].alpha) / 100;
        }
    }
}

KImage* KImage::resize(int width, int height, bool scale)
{
    if (scale)
    {
        if (this->width * height < this->height * width)
        {
            width = height * this->width / this->height;
        }
        else
        {
            height = width * this->height / this->width;
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

            resizedImage->matrix[x][y] = matrix[x0][y0];
        }
    }

    return resizedImage;
}

KImage* KImage::toGrayScale(int x1, int y1, int x2, int y2, TOOL shape, Path *path)
{
    KImage* grayScale = this->copy();

    for (int i = x1; i < x2; ++i)
    {
        for (int j = y1; j < y2; ++j)
        {
            if (shape == RECTANGLE || (shape == ELLIPSE and isInsideEllipse(i, j, x1, y1, x2, y2)) || (shape == PATH and isInsidePath(i, j, path)))
                grayScale->matrix[i][j].red =
                                    grayScale->matrix[i][j].blue =
                                    grayScale->matrix[i][j].green =
                                    grayScale->matrix[i][j].red * C_RED + grayScale->matrix[i][j].blue * C_BLUE + grayScale->matrix[i][j].green * C_GREEN;
        }
    }

    return grayScale;
}

KImage* KImage::toGrayScale()
{
    return this->toGrayScale(0, 0, this->width, this->height, RECTANGLE);
}

KImage* KImage::toGrayScale(Path *path)
{
    return this->toGrayScale(0, 0, this->width, this->height, PATH, path);
}

KImage* KImage::applyNegative()
{
    return this->applyNegative(0, 0, this->width, this->height, RECTANGLE);
}

KImage* KImage::applyNegative(Path *path)
{
    return this->applyNegative(0, 0, this->width, this->height, PATH, path);
}

KImage* KImage::applyNegative(int x1, int y1, int x2, int y2, TOOL shape, Path *path)
{
    KImage *negative = this->copy();

    for (int i = x1; i < x2; i++)
    {
        for (int j = y1; j < y2; j++)
        {
            if (shape == RECTANGLE || (shape == ELLIPSE and isInsideEllipse(i, j, x1, y1, x2, y2)) || (shape == PATH and isInsidePath(i, j, path)))
            {
                negative->matrix[i][j].red = 255 - this->matrix[i][j].red;
                negative->matrix[i][j].green = 255 - this->matrix[i][j].green;
                negative->matrix[i][j].blue = 255 - this->matrix[i][j].blue;
            }
        }
    }

    return negative;
}

bool KImage::isInsideEllipse(int i, int j, int x1, int y1, int x2, int y2)
{
    int u, v, a, b, x, y;
    a = abs(x1 - x2) / 2;
    b = abs(y1 - y2) / 2;
    u = x2 - a;
    v = y2 - b;
    x = i - u;
    y = j - v;
    return pow(x, 2) / pow(a, 2) + pow(y, 2) / pow(b, 2) <= 1;
}

bool KImage::isInsidePath(int x, int y, Path *firstPoint)
{
    double angle = 0;
    Path *p = firstPoint;
    Point p1, p2;

    do
    {
       p1.x = p->point.x - x;
       p1.y = p->point.y - y;
       p2.x = p->next->point.x - x;
       p2.y = p->next->point.y - y;
       angle += angle2D(p1.x, p1.y, p2.x, p2.y);
       p = p->next;
    }
    while (p != firstPoint);

    if (abs(angle) < 3.14)
       return(false);
    else
       return(true);
}

double KImage::angle2D(double x1, double y1, double x2, double y2)
{
   double dtheta, theta1, theta2;

   theta1 = atan2(y1,x1);
   theta2 = atan2(y2,x2);
   dtheta = theta2 - theta1;

   while (dtheta > 3.14)
      dtheta -= 6.18;
   while (dtheta < -3.14)
      dtheta += 6.18;

   return(dtheta);
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
            copy->matrix[i][j] = this->matrix[i][j];
        }
    }

    return copy;
}

//KRGB** KImage::getPixels(int i, int j, int taille)
//{
//    KRGB** pixels = new KRGB*[taille];
//
//    for (int a = 0; a < taille; a++)
//    {
//        pixels[a] = new KRGB[taille];
//        for (int b = 0; b < taille; b++)
//        {
//            pixels[a][b] = this->matrix[i + a - 1][j + b - 1];
//        }
//    }
//
//    return pixels;
//}

KImage* KImage::rotateClockwise()
{
    KImage *rotatedImage = new KImage(this->height, this->width, this->filename);

    for (int i = 0; i < rotatedImage->width; i++)
    {
        for (int j = 0; j < rotatedImage->height; j++)
        {
            rotatedImage->matrix[i][j] = this->matrix[j][this->height - 1 - i];
        }
    }

    return rotatedImage;
}

KImage* KImage::rotateCounterClockwise()
{
    KImage *rotatedImage = new KImage(this->height, this->width, this->filename);

    for (int i = 0; i < rotatedImage->width; i++)
    {
        for (int j = 0; j < rotatedImage->height; j++)
        {
            rotatedImage->matrix[i][j] = this->matrix[this->width - 1 - j][i];
        }
    }

    return rotatedImage;
}

KImage* KImage::verticalMirror()
{
    KImage *inversedImage = new KImage(this->width, this->height, this->filename);

    for (int i = 0; i < inversedImage->width; i++)
    {
        for (int j = 0; j < inversedImage->height; j++)
        {
            inversedImage->matrix[i][j] = this->matrix[this->width - 1 - i][j];
        }
    }

    return inversedImage;
}

KImage* KImage::horizontalMirror()
{
    KImage *inversedImage = new KImage(this->width, this->height, this->filename);

    for (int i = 0; i < inversedImage->width; i++)
    {
        for (int j = 0; j < inversedImage->height; j++)
        {
            inversedImage->matrix[i][j] = this->matrix[i][this->height - 1 - j];
        }
    }

    return inversedImage;
}

KImage* KImage::applyFilter(const KFiltre &filtre)
{
    return this->applyFilter(filtre, 0, 0, this->width, this->height, RECTANGLE, NULL);
}

KImage* KImage::applyFilter(const KFiltre &filtre, Path *path)
{
    return this->applyFilter(filtre, 0, 0, this->width, this->height, PATH, path);
}

KImage* KImage::applyFilter(const KFiltre &filtre, int x1, int y1, int x2, int y2, TOOL shape, Path *path)
{
    KImage* filteredImage = this->copy();

    int pixelsToSkip = (filtre.taille - 1) / 2; // Bordure où le masque n'est pas applicable
    if (x1 < pixelsToSkip) x1 = pixelsToSkip;
    if (x2 > filteredImage->width - pixelsToSkip) x2 = filteredImage->width - pixelsToSkip;
    if (y1 < pixelsToSkip) y1 = pixelsToSkip;
    if (y2 > filteredImage->height - pixelsToSkip) y2 = filteredImage->height - pixelsToSkip;

    for (int i = x1; i < x2; i++)
    {
        for (int j = y1; j < y2; j++)
        {
            if (shape == RECTANGLE || (shape == ELLIPSE and isInsideEllipse(i, j, x1, y1, x2, y2)) || (shape == PATH and isInsidePath(i, j, path)))
            {
                int red = 0, green = 0, blue = 0;

                for(int a = 0; a < filtre.taille; a++)
                {
                    for (int b = 0; b < filtre.taille; b++)
                    {
                        red += (int)this->matrix[i + a - 1][j + b - 1].red * (int)filtre.matrix[a][b];
                        green += (int)this->matrix[i + a - 1][j + b - 1].green * (int)filtre.matrix[a][b];
                        blue += (int)this->matrix[i + a - 1][j + b - 1].blue * (int)filtre.matrix[a][b];
                    }
                }
                red /= filtre.diviseur;
                green /= filtre.diviseur;
                blue /= filtre.diviseur;
                filteredImage->matrix[i][j].red = (red < 0 ? 0 : (red > 255 ? 255 : (unsigned char)red));
                filteredImage->matrix[i][j].green = (green < 0 ? 0 : (green > 255 ? 255 : (unsigned char)green));
                filteredImage->matrix[i][j].blue = (blue < 0 ? 0 : (blue > 255 ? 255 : (unsigned char)blue));
            }
        }
    }
    return filteredImage;
}

KImage* KImage::applyMedianSmoothing()
{
    return this->applyMedianSmoothing(0, 0, this->width, this->height, RECTANGLE);
}

KImage* KImage::applyMedianSmoothing(Path *path)
{
    return this->applyMedianSmoothing(0, 0, this->width, this->height, PATH, path);
}

KImage* KImage::applyMedianSmoothing(int x1, int y1, int x2, int y2, TOOL shape, Path *path)
{
    KImage *smoothedImage = this->copy();

    if (x1 == 0) x1 = 1;
    if (y1 == 0) y1 = 1;
    if (x2 == smoothedImage->width) x2 = smoothedImage->width - 1;
    if (y2 == smoothedImage->height) y2 = smoothedImage->height - 1;

    for (int i = x1; i < x2; i++)
    {
        for (int j = y1; j < y2; j++)
        {
            if (shape == RECTANGLE || (shape == ELLIPSE and isInsideEllipse(i, j, x1, y1, x2, y2)) || (shape == PATH and isInsidePath(i, j, path)))
            {
                unsigned char red[9], green[9], blue[9];
    
                for (int a = 0; a < 3; a++)
                {
                    for (int b = 0; b < 3; b++)
                    {
                        red[3 * a + b] = this->matrix[i + a - 1][j + b - 1].red;
                        green[3 * a + b] = this->matrix[i + a - 1][j + b - 1].green;
                        blue[3 * a + b] = this->matrix[i + a - 1][j + b - 1].blue;
                    }
                }
    
                sortArray(red); sortArray(green); sortArray(blue);
    
                smoothedImage->matrix[i][j].red = red[4];
                smoothedImage->matrix[i][j].green = green[4];
                smoothedImage->matrix[i][j].blue = blue[4];
            }
        }
    }

    return smoothedImage;
}

void KImage::sortArray(unsigned char* array, int taille)
{
    for (int j = 0; j < taille; j++)
    {
        int min = 255;
        int imin = 0;

        for (int i = j; i < taille; i++)
        {
            if (array[i] < min)
            {
                min = array[i];
                imin = i;
            }
        }

        unsigned char temp = array[j];
        array[j] = array[imin];
        array[imin] = temp;
    }
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

Seam::Seam() : energy(0) {}
Seam::Seam(int t) : energy(0)
{
    this->next = new int[t];
}
Seam::~Seam()
{
    delete [] this->next;
}

int KImage::gradient(int x, int y)
{
    int px = x - 1;
    int nx = x + 1;
    int py = y - 1;
    int ny = y + 1;

    if (px < 0)	px = this->width-1;
    if (nx >= this->width) nx = 0;
    if (py < 0)	py = this->height - 1;
    if (ny >= this->height) ny = 0;

    int Ipp = this->getYUVPixel(px,py).red;
    int Icp = this->getYUVPixel(x,py).red;
    int Inp = this->getYUVPixel(nx,py).red;
    int Ipc = this->getYUVPixel(px,y).red;
    int Inc = this->getYUVPixel(nx,y).red;
    int Ipn = this->getYUVPixel(px,ny).red;
    int Icn = this->getYUVPixel(x,ny).red;
    int Inn = this->getYUVPixel(nx,ny).red;

    int gradx = (Inc-Ipc)*2 + (Inp-Ipp) + (Inn-Ipn);
    int grady = (Icn-Icp)*2 + (Ipn-Ipp) + (Inn-Inp);
    int norme = sqrt(pow(gradx, 2) + pow(grady, 2)) / 4;

    return norme;
}

void KImage::deleteSeamCarving()
{
    if (this->energy != NULL)
    {
        for (int i=0; i < this->realWidth; ++i)
        {
            delete [] this->energy[i];
            delete [] this->pathX[i].next;
        }
        delete [] this->energy;
        delete [] this->pathX;

        for (int i = 0; i < this->realHeight; i++)
        {
            delete [] this->pathY[i].next;
        }
        delete [] this->pathY;

    }
}

void KImage::initSeamCarving()
{
    if (this->energy == NULL)
    {
        this->initEnergy();
        this->initHorizontalPaths();
        this->initVerticalPaths();
    }
}

void KImage::initEnergy()
{
    this->energy = new int*[this->realWidth];
    for (int i = 0; i < this->realWidth; i++)
    {
        this->energy[i] = new int[this->realHeight];
    }
    this->recalculateEnergy(0, this->width, 0, this->height);
}

void KImage::initVerticalPaths()
{
    this->pathX = new Seam[this->realWidth];
    for (int i = 0; i < this->realWidth; i++)
    {
        this->pathX[i].next = new int[this->realHeight];
        this->generateVerticalPath(i);
    }
}

void KImage::initHorizontalPaths()
{
    this->pathY = new Seam[this->realHeight];
    for (int i = 0; i < this->realHeight; i++)
    {
        this->pathY[i].next = new int[this->realWidth];
        this->generateHorizontalPath(i);
    }
}

void KImage::generateVerticalPath(int p)
{
    int x = p;
    int e = this->energy[p][0];
    this->pathX[p].max = 0;
    this->pathX[p].min = this->width;

    for (int y = 1; y < this->height; y++)
    {
        int nextX = 0;
        if (x - 1 >= 0 and this->energy[x-1][y] < this->energy[x][y])
            nextX = -1;
        if (x + 1 < this->width and this->energy[x+1][y] < this->energy[x + nextX][y])
            nextX = 1;

        this->pathX[p].next[y-1] = nextX;
        x += nextX;
        if (x > this->pathX[p].max) this->pathX[p].max = x;
        if (x < this->pathX[p].min) this->pathX[p].min = x;
        e += this->energy[x][y];
    }

    this->pathX[p].energy = e;
    if (this->nextVSeam < 0 || e < this->pathX[this->nextVSeam].energy)
        this->nextVSeam = p;
}

void KImage::generateHorizontalPath(int p)
{
    int y = p;
    int e = this->energy[0][p];
    this->pathY[p].max = 0;
    this->pathY[p].min = this->height;

    for (int x = 1; x < this->width; x++)
    {
        int nextY = 0;
        if (y - 1 >= 0 and this->energy[x][y-1] < this->energy[x][y])
            nextY = -1;
        if (y + 1 < this->height and this->energy[x][y+1] < this->energy[x][y + nextY])
            nextY = 1;

        this->pathY[p].next[x-1] = nextY;
        y += nextY;
        if (y > this->pathY[p].max) this->pathY[p].max = y;
        if (y < this->pathY[p].min) this->pathY[p].min = y;
        e += this->energy[x][y];
    }

    this->pathY[p].energy = e;

    if (this->nextHSeam < 0 || e < this->pathY[this->nextHSeam].energy)
        this->nextHSeam = p;
}

void KImage::recalculateEnergy(int minx, int maxx, int miny, int maxy)
{
    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            if (i >= minx and i <= maxx and j >= miny and j <= maxy)
                this->energy[i][j] = this->gradient(i, j);
        }
    }
}

void KImage::generateVerticalPaths(int min, int max)
{
    for (int i = 0; i < this->width; i++)
    {
        if (min > this->pathX[i].max || max < this->pathX[i].min)
        {
            if (this->nextVSeam < 0 || this->pathX[i].energy < this->pathX[this->nextVSeam].energy)
                this->nextVSeam = i;
        }
        else
            this->generateVerticalPath(i);
    }
}

void KImage::calculateVerticalPaths(int k)
{
    this->nextVSeams = new int[k];
    int emin = this->width * 255;
    int imin = 42;

    std::cout << "nextVSeam " << 0 << " : " << this->nextVSeam << std::endl;
    for (int index = 1; index < k; index++)
    {
        for (int i = 0; i < this->width; i++)
        {
            if (!isVerticalPathUsed(i, index) && this->pathX[i].energy < emin)
            {
                emin = this->pathX[i].energy;
                imin = i;
            }
        }
        this->nextVSeams[index] = imin;
        emin = this->width * 255;
        std::cout << "nextVSeam " << index << " : " << this->nextVSeams[index] << std::endl;
    }
}

bool KImage::isVerticalPathUsed(int p, int max)
{
    if (max == 0)
        return false;

    for (int i = 0; i < max; i++)
    {
        if (this->nextVSeams[i] == p)
            return true;
    }

    return false;
}

void KImage::generateHorizontalPaths(int min, int max)
{
    for (int i = 0; i < this->height; i++)
    {
        if (min > this->pathY[i].max || max < this->pathY[i].min)
        {
            if (this->nextHSeam < 0 || this->pathY[i].energy < this->pathY[this->nextHSeam].energy)
                this->nextHSeam = i;
        }
        else
            this->generateHorizontalPath(i);
    }
}

void KImage::removeVerticalPath(int p)
{
    int x = p;
    this->width--;

    for (int j = 0; j < this->height; j++)
    {
        for (int i = 0; i < this->width; i++)
        {
            if (i >= x)
            {
                this->matrix[i][j] = this->matrix[i+1][j];
            }
        }
        x += this->pathX[p].next[j];
    }

    this->recalculateEnergy(this->pathX[p].min, this->pathX[p].max, 0, this->height);
    this->generateVerticalPaths(this->pathX[p].min, this->pathX[p].max);
}

void KImage::addVerticalPaths(int t)
{
//    KImage *newImage = new KImage(this->width + t, this->height, this->filename);
//    sortArray(this->nextVSeams, t);

//    for (int j = 0; j < this->height; j++)
//    {
//        int k = 0;
//        for (int i = 0; i < this->width; i++)
//        {
//            if (i == this->pathX[this->nextVSeams[k]] + k)
//            {

//            }
//            else
//            {
//                newImage->matrix[i+k][j] = this->matrix[i][j];
//            }
//        }
//    }

    for (int k = 0; k < this->width; k++)
    {
        int p = k;
        int x = p;
        for (int j = 0; j < this->height; j++)
        {
            for (int i = 0; i < this->width; i++)
            {
                if (i == x)
                {
                    this->matrix[i][j].red = 255;
                    this->matrix[i][j].blue = 0;
                    this->matrix[i][j].green = 0;
                }
            }
            x += this->pathX[p].next[j];
        }
    }
}

void KImage::removeHorizontalPath(int p)
{
    int y = p;
    this->height--;

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
            if (j >= y)
            {
                this->matrix[i][j] = this->matrix[i][j+1];
            }
        }
        y += this->pathY[p].next[i];
    }

    this->recalculateEnergy(0, this->width, this->pathY[p].min, this->pathY[p].max);
    this->generateHorizontalPaths(this->pathY[p].min, this->pathY[p].max);
}

KImage* KImage::seamCarving(int w, int h, KResizeDialog* dialog)
{
    this->initSeamCarving();

    int total = (this->height + this->width) - (h + w);
    int value = 0;

    while (this->height > h)
    {
        this->removeHorizontalPath(this->nextHSeam);
        if(dialog != NULL)
        {
            value = (total - ((this->height + this->width) - (h + w))) * 100 / total;
            dialog->setProgressBar(value);
        }
    }

    if (this->width < w)
    {
        int k = w - this->width;
        this->calculateVerticalPaths(k);
        this->addVerticalPaths(k);
    }
    while (this->width > w)
    {
        this->removeVerticalPath(this->nextVSeam);
        if(dialog != NULL)
        {
            value = (total - ((this->height + this->width) - (h + w))) * 100 / total;
            dialog->setProgressBar(value);
        }
    }

    return this;
}
