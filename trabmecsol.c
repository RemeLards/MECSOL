#include "trabmecsol.h"

int main(int argc, char** argv)
{
    char* function;
    float inf_lim ,sup_lim;
    if(argc <= 1)
    {
        function = "2.5(x^2)/77";
        sup_lim = 4;
        inf_lim = 1;
    }
    if(argc == 2)
    {
        function = argv[1];
        sup_lim = 1;
        inf_lim = 0;
    }
    if(argc == 3)
    {
        function = argv[1];
        inf_lim = my_atof(argv[2]);;
        sup_lim = 1;
    }
    if(argc >= 4)
    {
        function = argv[1];
        inf_lim = my_atof(argv[2]);
        sup_lim = my_atof(argv[3]);
    }
    
    char* indef_integral_str = indef_integral(function); //Getting the Indefinite Integral (retuns a allocated string)
    float def_integral_value = def_integral(function,inf_lim,sup_lim);
    printf("The Indefinite Integral of %s is %s\n", function , indef_integral_str);
    printf("The Definite Integral of %s from %.2f to %.2f is %.8f\n", function , inf_lim, sup_lim, def_integral_value);
    free(indef_integral_str);
    
    return 0;
}