#ifndef KIMAGE_FWD_H
#define KIMAGE_FWD_H

enum TOOL {
    NONE, RESIZE, RECTANGLE, MOVE, ELLIPSE, PATH
};

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
    ~Seam();
    int energy;
    int min, max;
    int *next;
};

#endif // KIMAGE_FWD_H
