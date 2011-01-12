#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QFrame>

#include "kimage.h"

class Histogram : public QFrame
{
protected:
    KImage *image;
    int red[256];
    int green[256];
    int blue[256];
    int redCumul[256];
    int greenCumul[256];
    int blueCumul[256];
    int y[256];
    int u[256];
    int v[256];
    bool yuv;
    int MAX_R, MAX_G, MAX_B;
    int MAX_Y, MAX_U, MAX_V;
    int VERTICAL_SCALE;
    int min, max;

public:
    Histogram(KImage*, bool yuv);
    void createRGB(KImage *);
    void createYUV(KImage *);
    void paintEvent(QPaintEvent *);
    int normalize(int v);
    KImage* normalize();
    int equalize(int v);
    KImage* equalize();
};

#endif // HISTOGRAM_H
