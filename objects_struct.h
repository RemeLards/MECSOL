#ifndef _OBJECTS_STRUCT
#define _OBJECTS_STRUCT

typedef struct barra
{
    double size;
}BAR;

typedef struct apoio_simples
{
   double force_y;
   double moment_y;
   double distance;
}APOIO_S;

typedef struct engaste
{
    double force_y;
    double force_x;
    double moment_y;
    double moment_x;
    
}ENGST;



#endif