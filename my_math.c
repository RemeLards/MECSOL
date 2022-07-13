#include "my_math.h"
 
#define CHARS_NEEDED 5 //adding chars 'x','^', '(' ,')','/' 

char* exponent_str(char* function)
{
    int function_len = my_strlen(function); // Getting function string length
    int exponent_len = -1; // Getting exponent string length
    int func_i = 0, expo_i = 0; // Iterators 
    char* exponent = NULL; // Exponent string 


    for(func_i = 0; function[func_i]; func_i++) //Setting the size of the "exponent" str
    {
        if(exponent_len >= 0)
        {
            if(!((function[func_i]>= '0' && function[func_i]<= '9') || function[func_i]== '.'))break; //if there isn't any integer or float 
            else exponent_len++;
        }
        if(function[func_i] == '^')exponent_len++;
    }

    if(exponent_len > 0) //if there's a exponent
    {
        exponent = (char*)malloc(sizeof(char) *(exponent_len+1)); // +1 because of the '\0' char

        if(exponent != NULL) // if exponent was allocated
        {
            for(expo_i = 0;expo_i < exponent_len; expo_i++)exponent[expo_i] = function[(func_i-exponent_len) +expo_i];

            exponent[expo_i] = '\0'; // Setting end of "exponent" str
        }  
    }

    return exponent; //if there's a exponent it returns a allocated str, else it will return "NULL"
}

int exponent_value(char* function)
{
    char* exponent = exponent_str(function); // gets exponent string
    int exponent_value = -1; // default exponent value

    if(exponent != NULL) // if there is a exponent
    {
        exponent_value = my_atoi(exponent);
        free(exponent);
    }
    else
    {
        if(str_count_char(function,'x') == 1 && str_count_char(function,'^') == 0)exponent_value = 1; // it means the function is "C * x" , so the its exponent is 1
        if(str_count_char(function,'x') == 0 && str_count_char(function,'^') == 0)exponent_value = 0; // it means the function is "C"
    }

    return exponent_value;
}

char* mult_const_str(char* function)
{
    int mult_const_len = 0;
    char* mult_const = NULL;
    int const_i = 0; 

    //while the string is an integer or a float point, it'll count its length
    for(mult_const_len = 0; (function[mult_const_len]>= '0' && function[mult_const_len]<= '9') || function[mult_const_len]== '.'; mult_const_len++);

    if(mult_const_len > 0)
    {
        //allocates the string of the constant
        mult_const = (char*)malloc(sizeof(char) *(mult_const_len+1));

        if(mult_const != NULL)
        {

            //copies the constant string
            for(const_i = 0; const_i < mult_const_len; const_i++)mult_const[const_i] = function[const_i];
            
            //finalizing str
            mult_const[const_i] = '\0';

        }
    } 

    return  mult_const; //if there's a constant it returns a allocated str, else it will return "NULL"
}

double mult_const_value(char* function)
{
    char* mult_const = mult_const_str(function); // getting constant multiplying the function 
    double mult_const_value = 1; // default multiplier value

    if(mult_const != NULL) // if there is a multiplier
    {
        mult_const_value = my_atof(mult_const);
        free(mult_const);
    }

    return mult_const_value;    
}

char* div_const_str(char* function)
{
    int div_const_len = -1;
    char* div_const = NULL;
    int func_i = 0,const_i = 0;
    
    for(func_i = 0; function[func_i] != '\0'; func_i++) //gets number length after the 'x' expression
    {
        if(div_const_len >= 0)
        {
            if(!((function[func_i] >= '0' && function[func_i]<= '9') || function[func_i]== '.'))break; //if there isn't any integer or float 
            else div_const_len++;
        }
        if(function[func_i] == '/')div_const_len++;
    }

    
    if(div_const_len > 0)
    {
        //allocates the string of the constant
        div_const = (char*)malloc(sizeof(char) *(div_const_len+1));

        if(div_const != NULL)
        {
            //copies the constant string
            for(const_i = 0; const_i < div_const_len; const_i++)div_const[const_i] = function[(func_i - div_const_len) + const_i];

            //finalizing str
            div_const[const_i] = '\0';
        
        }
    }

    return div_const; //if there's a constant diving the function it returns a allocated str, else it will return "NULL"
}

double div_const_value(char* function)
{
    char* div_const = div_const_str(function); // getting number diving the function
    double div_const_value = 1; // default value

    if(div_const != NULL) // if there's a number dividing the function
    {
        div_const_value = my_atof(div_const);
        free(div_const);
    }
    
    return div_const_value;
}

char* indef_integral_ncosnt(char* function) // positive integer polynomials only 
{
    char* indef_integral_str = NULL; // Indefinite Integral
    char* exponent = NULL; // Exponent of the function
    int exponent_len = 0; // length of expoent str
    int exponent_value = 0; // Exponent value
    int integral_i = 0; // exponent, function and integral Iterators

    exponent = exponent_str(function); // gets exponent string

    if(exponent != NULL)
    {   
        exponent_len = my_strlen(exponent); // Getting string length


        // if it's true, one more byte is needed because the next number string will have length "exponent_len + 1"
        // and the integral will be divided by the same number, that's why is multiplied by 2 
        if(exponent_len == str_count_char(exponent,'9')) indef_integral_str = (char*)malloc(sizeof(char) * (2*(++exponent_len) + CHARS_NEEDED + 1));
    
        else indef_integral_str = (char*)malloc(sizeof(char) * (2*exponent_len + CHARS_NEEDED + 1));

        // setting up polinomial integration string 
        indef_integral_str[integral_i++] ='(';
        indef_integral_str[integral_i++] ='x';
        indef_integral_str[integral_i++] ='^';

        // adding +1 to the exponent
        exponent_value = my_atoi(exponent) + 1;
        free(exponent); // Don't need "old" exponent
        exponent = my_itoa(exponent_value); // getting new exponent

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
    }
    else
    {
        //if the function is "C*x"

        if(str_count_char(function,'x') == 1 && str_count_char(function,'^') == 0)
        {
            exponent_len = 1;
            indef_integral_str = (char*)malloc(sizeof(char) * (2*exponent_len + CHARS_NEEDED + 1));
            char* integral_of_x = "(x^2)/2";

            // setting up polinomial integration string 
            for(integral_i = 0; integral_i < (2*exponent_len + CHARS_NEEDED); integral_i++)indef_integral_str[integral_i] = integral_of_x[integral_i];
            indef_integral_str[integral_i] ='\0';

        }

        //if the function is "C"

        if(str_count_char(function,'x') == 0 && str_count_char(function,'^') == 0)
        {
            exponent_len = 0;
            indef_integral_str = (char*)malloc(sizeof(char) * (1 + 1));// for the 'x' and for the '\0'
            indef_integral_str[integral_i++] ='x';
            indef_integral_str[integral_i] ='\0';      
        }
    }

    return indef_integral_str;
}

double def_integral_value(char* function, float inf_lim, float sup_lim) // positive integer polynomials only 
{
    int exponent = 0; // exponent number
    double inf_value = 1, sup_value = 1; // Inferior Number and Superior Number, Numbers that we get after applying the inferior and superior limits
    double def_integral = 0, constant = 0; // integral value
    char* indef_integral_str = NULL; // Integral Indefinite string

    //Calculating Constants Value

    constant = (mult_const_value(function)/div_const_value(function));

    // Calculating Integral

    indef_integral_str = indef_integral_ncosnt(function); // Getting the Indefinite Integral (retuns a allocated string)
    exponent = exponent_value(indef_integral_str); // Getting exponent value of the Indefinite Integral
    if(indef_integral_str != NULL)free(indef_integral_str); // Dont need the Indefinite Integral

    if(exponent > 0) // only works with positive integer
    {
        for(int i = 0; i < exponent;i++)
        {
            inf_value*=inf_lim;
            sup_value*=sup_lim;
        }
        def_integral = constant*((sup_value-inf_value)/exponent); 
    }

    return def_integral;
}

char** function_list(char* function)
{
    int function_list_len = 1; // counts how many functions the string has
    int first_char_is_sing = 0;
    int i = 0, j = 0;
    char** function_list = NULL;

    if(function != NULL)
    {
        if(function[0] == '+' || function[0] == '-')
        {
            i++;
            first_char_is_sing++;
        }

        for(i; function[i] != '\0'; i++)if((function[i] == '+' || function[i] == '-')) function_list_len++;
        
        function_list = (char*)malloc(sizeof(char*) * function_list_len);

        
        for(j; j < function_list_len; j++)
        {
            for(i; function[i] != '\0'; i++)
            {
                function_list[j][i] = function[i];
                if(function[i+1] == '+' || function[i+1] == '-')break;

            }
            i+= 2;
            function_list[j][i] = '\0';
        }

    }

    return function_list;

}