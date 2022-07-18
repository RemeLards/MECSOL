#include "trabmecsol.h"

int main(int argc, char** argv)
{
    BAR barra;
    APOIO_L apoio_livre;
    ENGST engaste;

    barra.size = 1;

    double force_distribution_pos = 0;
    double inf_lim = 0;
    double sup_lim = 0;
    if(((sup_lim-inf_lim) + force_distribution_pos) - barra.size >= 0)
    {

    }
    else
    {
        sup_lim+= ((sup_lim-inf_lim) + force_distribution_pos) - barra.size;
    }

    return 0;
}