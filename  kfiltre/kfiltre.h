#ifndef KFILTRE_H
#define KFILTRE_H

enum FILTER {
    BLUR, EDGE_H, EDGE_V, PAINT, LAPLACIEN
};

class KFiltre
{
public:
    KFiltre(FILTER);
    ~KFiltre();
    int **matrix;
    int taille;
    int diviseur;
};

#endif // KFILTRE_H
