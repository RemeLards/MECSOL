#include "math_integral.h"
#include <stdio.h>
 
#define CHARS_NEEDED 5 //adding chars 'x','^', '(' ,')','/' 

char* indef_integral(char* function) // polynomials only 2-inf+
{
    char* indef_integral_str = NULL; // Indefinite Integral
    char* exponent = NULL; // Exponent of the function
    int function_len = 0; // length of function str
    int exponent_len = -1; // length of expoent str
    int exponent_n = 0; // Exponent 
    int exponent_i = 0,function_i = 0,integral_i = 0; // exponent, function and integral Iterators

    function_len = my_strlen(function); // Getting string length 

    for(function_i = 0; function[function_i]; function_i++) //Setting the size of the "exponent" str
    {
        if(exponent_len >= 0)
        {
            if(!((function[function_i]>= '0' && function[function_i]<= '9') || function[function_i]== '.'))break; //if there isn't any integer or float 
            else exponent_len++;
        }
        if(function[function_i] == '^')exponent_len++;
    }

    if(exponent_len > 0)
    {
        exponent = (char*)malloc(sizeof(char) *(exponent_len+1));

        if(exponent != NULL)
        {
            for(exponent_i = 0;exponent_i < exponent_len; exponent_i++)exponent[exponent_i] = function[(function_i-exponent_len) + exponent_i];

            exponent[exponent_i] = '\0'; // Setting end of "exponent" str
            
            exponent_len = my_strlen(exponent); // Getting string length
            
            if(exponent_len == str_count_char(exponent,'9')) // if it's true, we need one more byte because the next number string will have length "exponent_len + 1"
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

            free(exponent); // freeing allocated str that won't return;


            return indef_integral_str;
        }
        
        return NULL; // if couldn't find any exponent
    }
    return NULL;
}

double def_integral(char* function, float inf_lim, float sup_lim) // polynomials only that have exponents between 2 and 8
{
    int i = 0, j = 0,exponent_i = 0,integral_i = 0; // Iterators
    int exponent_n = 0; // exponent number
    int exponent_len = 0,indef_integral_str_len = 0, mult_const_len = 0, div_const_len = -1; // length of the strings
    double inf_n = 1, sup_n = 1; // Inferior Number and Superior Number, Numbers that we get after applying the inferior and superior limits
    double mult_const_n = 1, div_const_n = 1; // constants values
    double def_integral_value = 0, constant_value = 0; // integral value
    char* indef_integral_str = NULL; // Integral Indefinite string
    char* exponent = NULL; // Exponent of the function 
    char* str_mult_const = NULL; // String of the constant multiplying the 'x' function
    char* str_div_const = NULL; // String of the constant dividing the 'x 'function

    //Calculating Constants

        // Multiplying Constant

    //gets number length before the 'x' expression
    for(mult_const_len  = 0; (function[mult_const_len ]>= '0' && function[mult_const_len ]<= '9') || function[mult_const_len ]== '.'; mult_const_len ++);

    if(mult_const_len  > 0)
    {
        //allocates the string of the constant
        str_mult_const = (char*)malloc(sizeof(char) *(mult_const_len+1));

        if(str_mult_const != NULL)
        {

            //copies the constant string
            for(i = 0; i < mult_const_len; i++)str_mult_const[i] = function[i];
            
            //finalizing str
            str_mult_const[i] = '\0';

            //getting multiplying constant value, if str is null const value is 1
            
            mult_const_n = my_atof(str_mult_const);
            free(str_mult_const);
        }
    }


        // Diving Constant

    //gets number length after the 'x' expression
    for(i = 0; function[i] != '\0'; i++)
    {
        printf("%c",function[i]);
        if(div_const_len >= 0)
        {
            if(!((function[i]>= '0' && function[i]<= '9') || function[i]== '.'))break; //if there isn't any integer or float 
            else div_const_len++;
        }
        if(function[i] == '/')div_const_len++;
    }
    printf("\n");

    
    if(div_const_len > 0)
    {
        //allocates the string of the constant
        str_div_const = (char*)malloc(sizeof(char) *(div_const_len+1));

        if(str_div_const != NULL)
        {
            //copies the constant string
            for(j = 0; j < div_const_len; j++)str_div_const[j] = function[(i - div_const_len) + j];

            //finalizing str
            str_div_const[j] = '\0';
            
            //getting diving constant value,  if str is null const value is 1
            
            div_const_n = my_atof(str_div_const);
            free(str_div_const);
        }
    }

        //Calculating Final Constant

    constant_value = (mult_const_n/div_const_n);


    // Calculating Integral


    indef_integral_str = indef_integral(function); // Getting the Indefinite Integral (retuns a allocated string)
    indef_integral_str_len = my_strlen(indef_integral_str); // Size of indefinite integral str
    exponent_len = (indef_integral_str_len - CHARS_NEEDED - 1)/2; // length of exponent number

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
        def_integral_value = constant_value*((sup_n-inf_n)/exponent_n); 

        free(indef_integral_str);
        free(exponent);

        return def_integral_value;
    }

    if(exponent == NULL && indef_integral_str != NULL)free(indef_integral_str);
    if(exponent != NULL && indef_integral_str == NULL)free(exponent);

    return 0;
}