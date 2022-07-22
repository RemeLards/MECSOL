#include <stdio.h>
#include "my_math.h"

int main()
{
    char* functions = "x^2";
    char* integral_ncost = indef_integral_ncosnt(functions);

    printf("integral function : %s\n",integral_ncost);



    if(integral_ncost!=NULL)free(integral_ncost);

    return 0;


}