#include "math_integral.h"
 
#define CHARS_NEEDED 5 //adding chars 'x','^', '(' ,')','/' 

char* indef_integral(char* function) // polynomials only that have exponents between 2 and 8
{
    char* indef_integral_str = NULL; // Indefinite Integral
    char* exponent = NULL; // Exponent of the function
    int function_len = 0; // Lenght of function str
    int exponent_len = 0; // Lenght of expoent str
    int exponent_n = 0; // Exponent 
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

    if(exponent != NULL)
    {
        exponent[exponent_i] = '\0'; // Setting end of "exponent" str
        
        exponent_len = my_strlen(exponent); // Getting string lenght
        
        if(exponent_len == str_count_char(exponent,'9')) // if it's true, we need one more byte because the next number string will have lenght "exponent_len + 1"
        {
            indef_integral_str = (char*)malloc(sizeof(char) * (2*(++exponent_len) + CHARS_NEEDED + 1));
        }
        else indef_integral_str = (char*)malloc(sizeof(char) * (2*exponent_len + CHARS_NEEDED + 1));

        // setting up polinomial integration string 
        indef_integral_str[integral_i++] ='(';
        indef_integral_str[integral_i++] ='x';
        indef_integral_str[integral_i++] ='^';

        // adding +1 to the exponent
        exponent_n = my_atoi(exponent) + 1;
        free(exponent); // Don't need "old" exponent
        exponent = my_itoa(exponent_n); // getting new exponent

        // copying the new exponent to the indefinite integral 
        for(int i = 0; i < exponent_len; integral_i++, i++)indef_integral_str[integral_i] = exponent[i]; 

        // setting up polinomial integration string 
        indef_integral_str[integral_i++] =')';
        indef_integral_str[integral_i++] ='/';

        // dividing the polinomial by the new exponent
        for(int i = 0; i < exponent_len; integral_i++, i++)indef_integral_str[integral_i] = exponent[i]; 
        
        // ending the string
        indef_integral_str[integral_i] = '\0';

        free(exponent); // freeing malloced str that won't return;


        return indef_integral_str;
    }
    
    return NULL; // if couldn't find any exponent
}

float def_integral(char* function, float inf_lim, float sup_lim) // polynomials only that have exponents between 2 and 8
{
    float def_integral_value;
    int exponent_n = 0; // exponent number
    float inf_n = 1, sup_n = 1; // Inferior Number and Superior Number, Numbers that we get after applying the inferior and superior limits
    int exponent_i = 0,integral_i = 0; // exponent and integral Iterators 
    char* indef_integral_str = NULL; // Integral Indefinite string
    char* exponent = NULL; // Exponent of the function
    int exponent_len = 0,indef_integral_str_len = 0;

    indef_integral_str = indef_integral(function); // Getting the Indefinite Integral (retuns a malloced string)
    indef_integral_str_len = my_strlen(indef_integral_str); // Size of indefinite integral str
    exponent_len = (indef_integral_str_len - CHARS_NEEDED - 1)/2; // lenght of exponent number

    for(exponent_i = -1,integral_i = 0; indef_integral_str[integral_i] != ')'; integral_i++) // Getting the Exponent from the function
    {
        if(exponent_i >= 0) // Extracting Exponent from the function
        {
            exponent[exponent_i] = indef_integral_str[integral_i];
            exponent_i++;
        }

        if(indef_integral_str[integral_i] == '^') //Setting the size of the "exponent" str
        {
            exponent_i++;
            exponent = (char*)malloc((exponent_len+1)*sizeof(char)); // +1 because of the '\0' char
        }
    }


    if(exponent != NULL && indef_integral_str != NULL)
    {
        exponent[exponent_i] = '\0';

        exponent_n = my_atoi(exponent);

        for(int i = 0; i < exponent_n;i++)
        {
            inf_n*=inf_lim;
            sup_n*=sup_lim;
        }
        def_integral_value = (sup_n-inf_n)/exponent_n; 

        free(indef_integral_str);
        free(exponent);

        return def_integral_value;
    }

    if(exponent == NULL && indef_integral_str != NULL)free(indef_integral_str);
    if(exponent != NULL && indef_integral_str == NULL)free(exponent);

    return 0;
}