#include <QPainter>
#include <QDesktopWidget>

#include "kimage.h"
#include "histogram.h"

#define VERTICAL_MARGIN 2
#define HORIZONTAL_MARGIN 2
#define HORIZONTAL_SPACING 1

Histogram::Histogram(KImage *image, bool yuv) : image(image), yuv(yuv)
{
    if (yuv) { createYUV(image); }
    else { createRGB(image); }
}

void Histogram::createRGB(KImage *image)
{
    MAX_R = MAX_G = MAX_B = 0;
    for (int i = 0; i < 256; ++i)
    {
        red[i] = green[i] = blue[i] = 0;
    }

    min = 255; max = 0;
    for (int i = 0; i < image->width; ++i)
    {
        for (int j = 0; j < image->height; ++j)
        {
            Pixel pixel = image->getPixel(i,j);

            if ((pixel.red + pixel.green + pixel.blue) / 3 < min)
                min = pixel.red;
            if ((pixel.red + pixel.green + pixel.blue) / 3  > max)
                max = pixel.red;

            this->red[pixel.red]++; if (this->red[pixel.red] > this->MAX_R) { this->MAX_R = this->red[pixel.red]; }
            this->green[pixel.green]++; if (this->green[pixel.green] > this->MAX_G) { this->MAX_G = this->green[pixel.green]; }
            this->blue[pixel.blue]++; if (this->blue[pixel.blue] > this->MAX_B) { this->MAX_B = this->blue[pixel.blue]; }
        }
    }

    redCumul[0] = red[0];
    greenCumul[0] = green[0];
    blueCumul[0] = blue[0];
    for(int i = 1; i < 256; i++)
    {
        redCumul[i] = redCumul[i - 1] + red[i];
        greenCumul[i] = greenCumul[i - 1] + green[i];
        blueCumul[i] = blueCumul[i - 1] + blue[i];
    }

    QDesktopWidget desk;
    QRect rect = desk.screenGeometry();
    this->VERTICAL_SCALE = 1;
    while ((MAX_R + MAX_G + MAX_B) / VERTICAL_SCALE + (2 * VERTICAL_MARGIN) >= rect.height())
    {
        this->VERTICAL_SCALE = this->VERTICAL_SCALE * 2;
    }

    this->setWindowTitle("RGB Histogram");

    this->setGeometry(10, 10, int(255 * HORIZONTAL_SPACING) + HORIZONTAL_MARGIN * 2, (MAX_R + MAX_G + MAX_B) / VERTICAL_SCALE + VERTICAL_MARGIN * 2);
}

void Histogram::createYUV(KImage *image)
{
    MAX_Y = MAX_U = MAX_V = 0;
    for (int i = 0; i < 256; ++i)
    {
        y[i] = u[i] = v[i] = 0;
    }
    for (int i = 0; i < image->width; ++i)
    {
        for (int j = 0; j < image->height; ++j)
        {
            Pixel pixel = image->getYUVPixel(i,j);

            this->y[pixel.red]++; if (this->y[pixel.red] > this->MAX_Y) { this->MAX_Y = this->y[pixel.red]; }
            this->u[pixel.green]++; if (this->u[pixel.green] > this->MAX_U) { this->MAX_U = this->u[pixel.green]; }
            this->v[pixel.blue]++; if (this->v[pixel.blue] > this->MAX_V) { this->MAX_V = this->v[pixel.blue]; }
        }
    }

    QDesktopWidget desk;
    QRect rect = desk.screenGeometry();
    this->VERTICAL_SCALE = 1;
    while ((MAX_Y + MAX_U + MAX_V) / VERTICAL_SCALE + (2 * VERTICAL_MARGIN) >= rect.height())
    {
        this->VERTICAL_SCALE = this->VERTICAL_SCALE * 2;
    }

    this->setWindowTitle("YUV Histogram");

    this->setGeometry(10, 10, int(255 * HORIZONTAL_SPACING) + HORIZONTAL_MARGIN * 2, (MAX_Y + MAX_U + MAX_V) / VERTICAL_SCALE + VERTICAL_MARGIN * 2);
}

KImage* Histogram::normalize()
{
    KImage *normalizedImage = new KImage(image->width, image->height, image->getFilename());

    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            normalizedImage->matrix[i][j].red = normalize(image->matrix[i][j].red);
            normalizedImage->matrix[i][j].green = normalize(image->matrix[i][j].green);
            normalizedImage->matrix[i][j].blue = normalize(image->matrix[i][j].blue);
            normalizedImage->matrix[i][j].alpha = image->matrix[i][j].alpha;
        }
    }

    return normalizedImage;
}

int Histogram::normalize(int v)
{
    return (((v - min) * 255) / (max - min));
}

KImage* Histogram::equalize()
{
    KImage *equalizedImage = new KImage(image->width, image->height, image->getFilename());

    for (int i = 0; i < image->width; i++)
    {
        for (int j = 0; j < image->height; j++)
        {
            equalizedImage->matrix[i][j].red = equalize(redCumul[image->matrix[i][j].red]);
            equalizedImage->matrix[i][j].green = equalize(greenCumul[image->matrix[i][j].green]);
            equalizedImage->matrix[i][j].blue = equalize(blueCumul[image->matrix[i][j].blue]);
            equalizedImage->matrix[i][j].alpha = image->matrix[i][j].alpha;
        }
    }

    return equalizedImage;
}

int Histogram::equalize(int v)
{
    return (((max - min) * v + min) / (image->width * image->height));
}

void Histogram::paintEvent(QPaintEvent *qpe)
{
    QFrame::paintEvent(qpe);
    QPainter painter(this);
    if (yuv)
    {
        painter.setWindow(0, 0, 255 * HORIZONTAL_SPACING + HORIZONTAL_MARGIN * 2, (MAX_Y + MAX_U + MAX_V) / VERTICAL_SCALE + VERTICAL_MARGIN * 2);
        painter.setBrush(Qt::white);
        painter.fillRect(0, 0, 255 * HORIZONTAL_SPACING + HORIZONTAL_MARGIN * 2, (MAX_Y + MAX_U + MAX_V) / VERTICAL_SCALE + VERTICAL_MARGIN * 2, painter.brush());

        painter.setPen(Qt::black);
        for (int i = 0; i < 256; ++i)
        {
            painter.drawLine(HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_Y) / VERTICAL_SCALE + VERTICAL_MARGIN, HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_Y - y[i]) / VERTICAL_SCALE + VERTICAL_MARGIN);
        }

        painter.setPen(Qt::red);
        for (int i = 0; i < 256; ++i)
        {
            painter.drawLine(HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_Y + MAX_U) / VERTICAL_SCALE + VERTICAL_MARGIN, HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_Y + MAX_U - u[i]) / VERTICAL_SCALE + VERTICAL_MARGIN);
        }

        painter.setPen(Qt::blue);
        for (int i = 0; i < 256; ++i)
        {
            painter.drawLine(HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_Y + MAX_U + MAX_V) / VERTICAL_SCALE + VERTICAL_MARGIN, HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_Y + MAX_U + MAX_V - v[i]) / VERTICAL_SCALE + VERTICAL_MARGIN);
        }
    }
    else
    {
        painter.setWindow(0, 0, 255 * HORIZONTAL_SPACING + HORIZONTAL_MARGIN * 2, (MAX_R + MAX_G + MAX_B) / VERTICAL_SCALE + VERTICAL_MARGIN * 2);
        painter.setBrush(Qt::white);
        painter.fillRect(0, 0, 255 * HORIZONTAL_SPACING + HORIZONTAL_MARGIN * 2, (MAX_R + MAX_G + MAX_B) / VERTICAL_SCALE + VERTICAL_MARGIN * 2, painter.brush());

        painter.setPen(Qt::red);
        for (int i = 0; i < 256; ++i)
        {
            painter.drawLine(HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_R) / VERTICAL_SCALE + VERTICAL_MARGIN, HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_R - red[i]) / VERTICAL_SCALE + VERTICAL_MARGIN);
        }

        painter.setPen(Qt::green);
        for (int i = 0; i < 256; ++i)
        {
            painter.drawLine(HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_R + MAX_G) / VERTICAL_SCALE + VERTICAL_MARGIN, HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_R + MAX_G - green[i]) / VERTICAL_SCALE + VERTICAL_MARGIN);
        }

        painter.setPen(Qt::blue);
        for (int i = 0; i < 256; ++i)
        {
            painter.drawLine(HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_R + MAX_G + MAX_B) / VERTICAL_SCALE + VERTICAL_MARGIN, HORIZONTAL_MARGIN + i * HORIZONTAL_SPACING, (MAX_R + MAX_G + MAX_B - blue[i]) / VERTICAL_SCALE + VERTICAL_MARGIN);
        }
    }
}
