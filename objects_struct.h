#ifndef _OBJECTS_STRUCT
#define _OBJECTS_STRUCT

typedef struct barra
{
    double size;
    double force_y;
    double force_x;
    double moment_y;
    double moment_x;
}BAR;

typedef struct apoio_livre
{
   double force_y;
   double moment_y;
}APOIO_L;

typedef struct engaste
{
    double force_y;
    double force_x;
    double moment_y;
    double moment_x;
    
}ENGST;



#endif