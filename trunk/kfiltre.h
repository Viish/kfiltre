#ifndef KFILTRE_H
#define KFILTRE_H

enum FILTER {
    BLUR, EDGE_H, EDGE_V, EDGE, PAINT, LAPLACIEN, PREWITT_X, PREWITT_Y
};

class KFiltre
{
public:
    KFiltre(FILTER);
    KFiltre(int**, int, int);
    ~KFiltre();
    int **matrix;
    int taille;
    int diviseur;
};

#endif // KFILTRE_H
