#include "trabmecsol.h"

int main(int argc, char** argv)
{
    //***************************************************************************TESTING INTEGRALS***************************************************************************
    //Uncomment to test it

    /* char* function;
    float inf_lim ,sup_lim;
    if(argc <= 1)
    {
        function = "2";
        sup_lim = 1;
        inf_lim = 0;
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
    
    char* indef_integral_str = indef_integral_ncosnt(function); //Getting the Indefinite Integral without constants included (retuns a allocated string)
    float def_integral = def_integral_value(function,inf_lim,sup_lim);
    printf("The Indefinite Integral (without constants included) of %s is %s\n", function , indef_integral_str);
    printf("The Definite Integral of %s from %.2f to %.2f is %.2f\n", function , inf_lim, sup_lim, def_integral);
    free(indef_integral_str);*/

    //***************************************************************************TESTING FUNCTION DIVIDER***************************************************************************
    //Uncomment to test it

     /*                               
    char* all_functions = "+x^1111+1"; // any function (without spaces between chars)
    int i = 0; // iterator
    int first_char_is_sign = 0; // checks if the first char is a sign
    int functions_count = 1; // simulating that the string that we put is a function, so it has atleast one function

    printf("all_functions : %s\n",all_functions); 

    if(all_functions[0] == '+' || all_functions[0] == '-') // checks if the first char of the function it´s a sign, it´s needed for the for loop
    {
        i++;
        first_char_is_sign++;
    }

    // counts how many functions the function has 
    // for example the function "x^2 + x + 5" it's a sum of 3 functions, "x^2", "x" and "5" 
    for(i; all_functions[i] != '\0'; i++)if((all_functions[i] == '+' || all_functions[i] == '-')) functions_count++; 

    char** f_list = function_divider(all_functions);

    if(f_list != NULL) // if "f_list" isn't NULL, that means that the function could allocate every function, that's why it isn't needed to check if each string is NULL
    {
        for(int j = 0; j < functions_count; j++)
        {
            printf("function number %d : %s\n",j+1,f_list[j]);
        }

        for(int j = 0; j < functions_count; j++)
        {
            free(f_list[j]);
        }
    }

    free(f_list);*/

    char* function_incremented = x_power_increment("4x");
    printf("%s\n",function_incremented);
    free(function_incremented);
    
    
    return 0;
}