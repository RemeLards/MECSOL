#include "my_math.h"
#include <stdio.h>
 
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
    int mult_const_len = 0; // default multiplicative constant str length
    char* mult_const = NULL; // mltiplicative constant str 
    int const_i = 0; // constant iterator

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
    int div_const_len = -1; // default dividing constant str length
    char* div_const = NULL; // dividing constant str 
    int func_i = 0,const_i = 0; // iterators (function iterator, constant iterator)
    
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

    if(exponent > 0) // calculating definite integral (only works with positive integer)
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

char** function_divider(char* all_functions)
{
    int functions_count = 1; // counts how many functions the string has
    int first_char_is_sign = 0; // checks if the first char is a sign
    int i = 0, j = 0; // iterators
    int past_i_value = 0; // store the past value of "i" iterator 
    char** function_list = NULL; // vector containing all functions
    char* single_function = NULL; // single function string
    int* function_lens = NULL; // vector containing all functions lenghts

    if(all_functions != NULL)
    {
        if(all_functions[0] == '+' || all_functions[0] == '-') // checks if the first char of the function it´s a sign, it´s needed for the for loop
        {
            i++;
            first_char_is_sign++;
        }

        // counts how many functions the function has 
        // for example the function "x^2 + x + 5" it's a sum of 3 functions, "x^2", "x" and "5" 
        for(i; all_functions[i] != '\0'; i++)if((all_functions[i] == '+' || all_functions[i] == '-')) functions_count++; 

        function_lens = (int*)malloc(sizeof(int) * functions_count); //stores the lenght of each individual function

        if(function_lens != NULL) // if we could allocate the int pointer
        {
        
            function_list = (char**)malloc(sizeof(char*) * functions_count); //it stores the ammount of functions that we will allocate in it

            if(function_list != NULL) //if we could allocate the list of strings
            {
                // setting up iterators values before entering the for loop
                i = 0;
                
                for(i; i < functions_count; i++)function_list[i] = NULL; // initialize each pointers in "function_list" as NULL      

                // setting up iterators values before entering the for loop
                j = 0;
                i = 0;
                if(first_char_is_sign == 1)i++;
                past_i_value = 0;


                for(i;all_functions[i] != '\0'; i++) // counts each function length based on signs and '\0' chars
                {
                    if(all_functions[i] == '+' || all_functions[i] == '-')
                    {
                        function_lens[j] = i - past_i_value; // calculates  the function length 
                        j++;  // goes to the next "function_lens" pos 
                        past_i_value = i;  //saves the "i" value from the for loop;
                    }   
                }
                function_lens[j] = i - past_i_value; //last function lenght value;

                // setting up iterators values before entering the for loop
                j = 0;
                i = 0;
                past_i_value = 0;

                for(j; j < functions_count; j++) // storing each individual function string
                {
                    single_function = malloc(sizeof(char) *(function_lens[j] + 1)); // +1 because of the '\0' char

                    if(single_function != NULL) // if the string was allocated
                    {
                        for(i; i < function_lens[j] + past_i_value; i++)
                        {
                            single_function[i-past_i_value] = all_functions[i]; // copies the function with it's sign 
                        }
                        single_function[i-past_i_value] = '\0'; // terminates the function string

                        function_list[j] = single_function; // stores the function string

                        past_i_value = i; // saves the "i" value from the for loop;
                    }
                    
                    else //some string couldn't be allocated for some reason (error or memory insufficient)
                    {
                        // setting up iterators values before entering the for loop
                        i = 0;
                        
                        for(i; i < functions_count; i++)
                        {
                            if(function_list[i] != NULL) free(function_list[i]); // freeing all strings allocated
                        }
                        
                        free(function_list); // freeing the string pointer to indicate that something went wrong

                        break;
                    }
                }

            }
        }

    }

    if(function_lens != NULL)free(function_lens); // frees the pointer if it isn't NULL

    return function_list;

}