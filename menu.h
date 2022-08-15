#ifndef _MENU
#define _MENU

#include "trabmecsol.h"

//Tipos de Apoios
enum APOIOS
{
    APOIO_SIMPLES = 1,
    ENGASTE,
    LIVRE,
};

//Tipos de Vigas
enum VIGAS
{
    CIRCULAR = 1,
    RETANGULAR,
    TRIANGULAR,
    TIPO_U,
    TIPO_H,
    TIPO_I,
    TIPO_T,
};

//Acoes Externas
enum ACOES_EXTERNAS
{
    FORCA = 1,
    MOMENTO,
    DISTRIBUICAO_DE_CARGA,
    RESULTADO,
};

void printTela_1();
void printTela_2();
void printEng_Eng_validation();
void print_Apoios_validation(char** tiposApoios, int apoio1, int apoio2, double pos_apoio1, double pos_apoio2);
void print_posApoio2_validation();
void printTela_3();
void print_UserOp_validation();


#endif