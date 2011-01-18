#include "kfiltre.h"

KFiltre::KFiltre(int** matrix, int taille, int diviseur) :
        matrix(matrix), taille(taille), diviseur(diviseur)
{ }

KFiltre::KFiltre(FILTER filtre) :
        matrix(0), taille(3), diviseur(1)
{
    switch (filtre)
    {
    case BLUR :
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

    case EDGE :
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 0;
            }
        }

        matrix[1][0] = 1;
        matrix[0][1] = 1;
        matrix[1][1] = -4;
        matrix[1][2] = 1;
        matrix[2][1] = 1;
        break;

    case LAPLACIEN :
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

    case PREWITT_Y :
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 0;
            }
        }

        matrix[0][0] = -1;
        matrix[0][1] = -1;
        matrix[0][2] = -1;
        matrix[2][0] = 1;
        matrix[2][1] = 1;
        matrix[2][2] = 1;
        break;

    case PREWITT_X :
        matrix = new int*[taille];

        for (int i = 0; i < taille; i++)
        {
            matrix[i] = new int[taille];
            for (int j = 0; j < taille; j++)
            {
                matrix[i][j] = 0;
            }
        }

        matrix[0][0] = -1;
        matrix[1][0] = -1;
        matrix[2][0] = -1;
        matrix[0][2] = 1;
        matrix[1][2] = 1;
        matrix[2][2] = 1;
        break;
    }
}

KFiltre::~KFiltre()
{
    for (int i = 0; i < this->taille; ++i) delete[] this->matrix[i];
    delete [] this->matrix;
}
