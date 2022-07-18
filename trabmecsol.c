#include "trabmecsol.h"

int main(int argc, char** argv)
{
    double inf_lim = 0;
    double sup_lim = 5;
    char* function = "3x^2/5-6x/5+10"; 
    printf("inferior limit : %2.f\n",inf_lim);
    printf("superior limit : %.2f\n\n",sup_lim);
    printf("integral value : %.10f\n",def_integral_value(function,inf_lim,sup_lim));
    printf("centroid of %s is : %.5f \n",function,my_math_function_centroid(function,inf_lim,sup_lim));

    return 0;
}