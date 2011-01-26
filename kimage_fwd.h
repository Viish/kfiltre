#ifndef KIMAGE_FWD_H
#define KIMAGE_FWD_H

struct Pixel {
    unsigned char red, green, blue, alpha;
};

struct Point
{
    Point(int, int);
    Point();
    int x, y;
    int pathEnergy;
};

struct Path {
    Path(int, int, Path* = NULL);
    Point point;
    Path *next;
};

struct Seam {
    Seam(int);
    Seam();
    int energy;
    int min, max;
    int *next;
};

struct EnergyMap {
    EnergyMap();
    int energy;
};

class KResizeDialog;
class KFiltre;

#endif // KIMAGE_FWD_H
