#include "math_integral.h"

#define CHARS_NEEDED 6

char* indef_integral(char* function) // polynomials only that have exponents between 2 and 8
{
    char* indef_integral_str; // Indefinite Integral
    char* exponent; // Exponent of the function
    int function_len; // Lenght of function str
    int exponent_len; // Lenght of expoent str 
    int j,i; // Iterators

    function_len = my_strlen(function); // Getting string lenght 

    for(j = -1,i = 0; i < function_len; i++) // Getting the Exponent from the function
    {
        if(j >= 0) // Extracting Exponent from the function
        {
            exponent[j] = function[i];
            j++;
        }

        if(function[i] == '^') //Setting the size of the "exponent" str
        {
            j++;
            exponent = (char*)malloc((function_len-i)*sizeof(char));
        }
    }
    exponent[j] = '\0'; // Setting end of "exponent" str
    
    exponent_len = my_strlen(exponent); // Getting string lenght
    indef_integral_str = (char*)malloc(exponent_len * sizeof(char) + CHARS_NEEDED) + 1;// adding chars 'x','^', '(' ,')','/','number' (if number is in 2-8 range)

    indef_integral_str[0] = '(';
    indef_integral_str[1] = 'x';
    indef_integral_str[2] = '^';
    indef_integral_str[3] = exponent[0] + 1;
    indef_integral_str[4] = ')';
    indef_integral_str[5] = '/';
    indef_integral_str[6] = exponent[0] + 1;
    indef_integral_str[7] = '\0';

    free(exponent);

    return indef_integral_str;
}

float def_integral(char* function, float sup_lim, float inf_lim) // polynomials only that have exponents between 2 and 8
{
    float def_integral_value;
    int exponent_value;
    float inf_n = 1, sup_n = 1; // Inferior Number and Superior Number, Numbers that we get after applying the inferior and superior limits
    int j,i; // Iterators
    char* indef_integral_str; // Integral Indefinite string
    char* exponent; // Exponent of the function

    indef_integral_str = indef_integral(function); // Getting the Indefinite Integral (retuns a malloced string)


    for(j = -1,i = 0; indef_integral_str[i] != ')'; i++) // Getting the Exponent from the function
    {
        if(j >= 0) // Extracting Exponent from the function
        {
            exponent[j] = indef_integral_str[i];
            j++;
        }

        if(indef_integral_str[i] == '^') //Setting the size of the "exponent" str
        {
            j++;
            exponent = (char*)malloc(2*sizeof(char));
        }
    }
    exponent[j] = '\0';
    free(indef_integral_str);


    exponent_value = exponent[0]-'0';
    free(exponent);

    for(i = 0; i < exponent_value;i++)
    {
        inf_n*=inf_lim;
        sup_n*=sup_lim;
    }
    def_integral_value = (sup_n-inf_n)/exponent_value;

    return def_integral_value;
}

int main(int argc, char** argv)
{
    char* function;
    float inf_lim ,sup_lim;
    
    if(argc <= 1)
    {
        function = "x^8";
        sup_lim = 2.546;
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
        sup_lim = atof(argv[2]);
        inf_lim = 0;
    }
    if(argc >= 4)
    {
        function = argv[1];
        sup_lim = atof(argv[2]);
        inf_lim = atof(argv[3]);
    }
    
    char* indef_integral_str = indef_integral(function); //Getting the Indefinite Integral (retuns a malloced string)
    float def_integral_value = def_integral(function,sup_lim,inf_lim);
    printf("The Indefinite Integral of %s is %s\n", function , indef_integral_str);
    printf("The Definite Integral of %s from %.2f to %.2f is %.2f\n", function , inf_lim, sup_lim, def_integral_value);
    free(indef_integral_str);
    
    return 0;
}