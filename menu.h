#ifndef _MENU
#define _MENU

#include "trabmecsol.h"

//Menu
#define APOIO_SIMPLES 1
#define ENGASTE 2
#define LIVRE 3

//Tipos de vigas
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
#define FORCA 1
#define MOMENTO 2
#define DISTRIBUICAO_DE_CARGA 3
#define RESULTADO 4

void printTela_1();
void printTela_2();
void printEng_Eng_validation();
void print_Apoios_validation(char** tiposApoios, int apoio1, int apoio2, double pos_apoio1, double pos_apoio2);
void print_posApoio2_validation();
void printTela_3();
void print_UserOp_validation();


#endif