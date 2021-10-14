#include "mapa.h"

//////////////////////////////////////
/////////////DEFINE CORES/////////////
//////////////////////////////////////

void red ()
{
  printf("\033[1;31m");
}

void green ()
{
  printf("\033[0;32m");
}

void yellow()
{
  printf("\033[1;33m");
}

void reset ()
{
  printf("\033[0m");
}


//////////////////////////////////////
////////////FILTRA INTEIRO////////////
//////////////////////////////////////

int filtraInteiro()
{
    char triagem[100];
    double num_double = 0;
    int inteiro = 0;

    fgets(triagem, sizeof triagem, stdin);

    num_double = strtod(triagem, NULL);

    if ((num_double > 2147483647) || num_double < 0)
    {
        return -1;
    }

    inteiro = atoi(triagem);
    return inteiro;
}

