#include "math_integral.h"
 
#define CHARS_NEEDED 5 //adding chars 'x','^', '(' ,')','/' 

char* indef_integral(char* function) // polynomials only that have exponents between 2 and 8
{
    char* indef_integral_str = NULL; // Indefinite Integral
    char* exponent = NULL; // Exponent of the function
    int function_len = 0; // Lenght of function str
    int exponent_len = 0; // Lenght of expoent str 
    int exponent_i = 0,function_i = 0,integral_i = 0; // exponent, function and integral Iterators

    function_len = my_strlen(function); // Getting string lenght 

    for(exponent_i = -1,function_i = 0; function_i < function_len; function_i++) // Getting the Exponent from the function
    {
        if(exponent_i >= 0) // Extracting Exponent from the function
        {
            exponent[exponent_i] = function[function_i];
            exponent_i++;
        }

        if(function[function_i] == '^') //Setting the size of the "exponent" str
        {
            exponent_i++;
            exponent = (char*)malloc((function_len-function_i)*sizeof(char));
        }
    }
    exponent[exponent_i] = '\0'; // Setting end of "exponent" str
    
    exponent_len = my_strlen(exponent); // Getting string lenght
    
    if(exponent_len == str_count_char(exponent,'9')) // if it's true, we need one more byte because the next number string will have lenght "exponent_len + 1"
    {
        indef_integral_str = (char*)malloc(sizeof(char) * (2*exponent_len + CHARS_NEEDED + 3));
    }
    else indef_integral_str = (char*)malloc(sizeof(char) * (2*exponent_len + CHARS_NEEDED + 1));

    // setting up polinomial integration string 
    indef_integral_str[integral_i++] ='(';
    indef_integral_str[integral_i++] ='x';
    indef_integral_str[integral_i++] ='^';

    // adding +1 to the exponent

    if(exponent_len == str_count_char(exponent,'9'))
    {
        indef_integral_str[integral_i++] = '1';
        for(int i = 0; i < exponent_len; i++)indef_integral_str[integral_i++] = '0';
    }
    else
    {
        if(str_find_char(exponent,'9') == -1) // there isn't any '9' on the string
        {
            for(int i = 0; i < exponent_len; i++)
            {
                if(i == exponent_len -1)
                {
                    indef_integral_str[integral_i + i] = exponent[i] + 1;
                    integral_i += i + 1;
                }
                else
                {
                    indef_integral_str[integral_i + i] = exponent[i];
                }
            }
        }
        else
        {

        }
    }

    // setting up polinomial integration string 
    indef_integral_str[integral_i++] =')';
    indef_integral_str[integral_i++] ='/';

    if(exponent_len == str_count_char(exponent,'9'))
    {
        indef_integral_str[integral_i++] = '1';
        for(int i = 0; i < exponent_len; i++)indef_integral_str[integral_i++] = '0';
    }
    else
    {
        if(str_find_char(exponent,'9') == -1) // there isn't any '9' on the string
        {
            for(int i = 0; i < exponent_len; i++)
            {
                if(i == exponent_len -1)
                {
                    indef_integral_str[integral_i + i] = exponent[i] + 1;
                    integral_i += i + 1;
                }
                else
                {
                    indef_integral_str[integral_i + i] = exponent[i];
                }
            }
        }
        else
        {

        }
    }
    
    // ending the string
    indef_integral_str[integral_i++] = '\0';

    if (exponent != NULL)free(exponent);

    return indef_integral_str;
}

float def_integral(char* function, float sup_lim, float inf_lim) // polynomials only that have exponents between 2 and 8
{
    float def_integral_value;
    int exponent_value;
    float inf_n = 1, sup_n = 1; // Inferior Number and Superior Number, Numbers that we get after applying the inferior and superior limits
    int j,i; // Iterators
    char* indef_integral_str = NULL; // Integral Indefinite string
    char* exponent = NULL; // Exponent of the function

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


    exponent_value = exponent[0]-'0';

    for(i = 0; i < exponent_value;i++)
    {
        inf_n*=inf_lim;
        sup_n*=sup_lim;
    }
    def_integral_value = (sup_n-inf_n)/exponent_value;

    free(indef_integral_str);
    if (exponent != NULL)free(exponent);

    return def_integral_value;
}

int main(int argc, char** argv)
{
    char* function;
    float inf_lim ,sup_lim;
    
    if(argc <= 1)
    {
        function = "x^99";
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
        sup_lim = my_atof(argv[2]);
        inf_lim = 0;
    }
    if(argc >= 4)
    {
        function = argv[1];
        sup_lim = my_atof(argv[2]);
        inf_lim = my_atof(argv[3]);
    }
    
    char* indef_integral_str = indef_integral(function); //Getting the Indefinite Integral (retuns a malloced string)
    //float def_integral_value = def_integral(function,sup_lim,inf_lim);
    printf("The Indefinite Integral of %s is %s\n", function , indef_integral_str);
    //printf("The Definite Integral of %s from %.2f to %.2f is %.2f\n", function , inf_lim, sup_lim, def_integral_value);
    free(indef_integral_str);
    
    return 0;
}