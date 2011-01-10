#include "kfiltre.h"

KFiltre::~KFiltre()
{
    for (int i = 0; i < this->taille; ++i) delete[] this->matrix[i];
    delete [] this->matrix;
}

KFiltre::KFiltre(FILTER filtre) : diviseur(1)
{
    switch (filtre)
    {
    case BLUR :
        taille = 3;
        diviseur = 9;
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 1;
            }
        }
        break;

    case EDGE_V :
        taille = 3;
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 0;
            }
        }

        matrix[1][0] = -1;
        matrix[1][1] = 2;
        break;

    case EDGE_H :
        taille = 3;
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 0;
            }
        }

        matrix[0][1] = -1;
        matrix[1][1] = 2;
        break;

    case PAINT :
        taille = 3;
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 0;
            }
        }

        matrix[0][0] = -2;
        matrix[1][0] = -1;
        matrix[0][1] = -1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 2;
        break;

    case LAPLACIEN :
        taille = 3;
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 1;
            }
        }

        matrix[1][1] = -8;
        break;
    }
}
