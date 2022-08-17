#include "my_math.h"

char* exponent_str(char* function)
{
    int function_len = my_strlen(function); // Getting function string length
    int exponent_len = -1; // Getting exponent string length
    int func_i = 0, expo_i = 0; // Iterators 
    char* exponent = NULL; // Exponent string 

    if(function_len > 0)
    {
        for(; function[func_i]; func_i++) //Setting the size of the "exponent" str
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
                for(;expo_i < exponent_len; expo_i++)exponent[expo_i] = function[(func_i-exponent_len) +expo_i];

                exponent[expo_i] = '\0'; // Setting end of "exponent" str
            }  
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
    int first_char_is_sign = 0;

    if(function[0] == '+' || function[0] == '-')
    {
        const_i++; //if first char is a sign, we skip it
        first_char_is_sign++;
    }

    //while the string is an integer or a float point, it'll count its length
    for(; (function[const_i]>= '0' && function[const_i]<= '9') || function[const_i]== '.'; mult_const_len++,const_i++);

    if(mult_const_len > 0)
    {
        //allocates the string of the constant
        mult_const = (char*)malloc(sizeof(char) *(mult_const_len+1));

        if(mult_const != NULL)
        {

            //copies the constant string
            for(const_i = 0; const_i < mult_const_len; const_i++)mult_const[const_i] = function[const_i+first_char_is_sign];
            
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
    
    for(; function[func_i] != '\0'; func_i++) //gets number length after the 'x' expression
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
            for(; const_i < div_const_len; const_i++)div_const[const_i] = function[(func_i - div_const_len) + const_i];

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

char* indef_integral(char* function) // positive integer polynomials only (MAKING THE OUTPUT THE INTEGRAL OF THE ENTIRE FUNCTION)
{
    char* parcial_indef_integral_str = NULL; // Parcial Indefinite Integral
    char* indef_integral_str = NULL; // Indefinite Integral
    char* exp = NULL; // Exponent of the function
    char* multiplying_const_str = NULL; // mult const str
    char* dividing_const_str = NULL; // div const str
    int exp_len = 0; // length of exponent str
    int exp_value = 0; // Exponent value
    int const_lens = 0; // constants lenghts
    int indef_integral_len = 0; 
    double multiplying_const = 0; // Multiplying Const
    double dividing_const = 0; // Dividing Const 
    int integral_i = 0; // exponent, function and integral Iterators
    char** function_list = NULL; // list containing individual functions
    int* functions_lens = NULL;
    int functions_count = 0; // number of functions in function_list

    if(function != NULL)
    {
        functions_count = my_math_function_count(function);
        functions_lens = (int*) malloc(sizeof(int) * (functions_count));

        if(functions_count > 0)
        {
            function_list = my_math_function_divider(function);
            
            if(function_list != NULL)
            {
                for(int i = 0; i < functions_count; i++)
                {
                    exp = exponent_str(function_list[i]);

                    dividing_const = (exponent_value(function_list[i]) + 1) * div_const_value(function_list[i]);
                    multiplying_const = mult_const_value(function_list[i]);

                    dividing_const_str = my_ftoa(dividing_const);
                    multiplying_const_str = my_ftoa(multiplying_const);
                

                    const_lens = my_strlen(dividing_const_str) + my_strlen(multiplying_const_str);
    

                    if(exp != NULL)
                    {   
                        exp_len = my_strlen(exp); // Getting string length

                        // if it's true, one more byte is needed because the next number string will have length "exponent_len + 1"
                        // and the integral will be divided by the same number, that's why is multiplied by 2 
                        if(exp_len == str_count_char(exp,'9'))
                        {
                            parcial_indef_integral_str = (char*)malloc(sizeof(char) * ((++exp_len) + CHARS_NEEDED + 1 + const_lens + 1));// +1 because of the sign
                            functions_lens[i] = (exp_len + CHARS_NEEDED  + const_lens);
                        }
                    
                        else 
                        {
                            parcial_indef_integral_str = (char*)malloc(sizeof(char) * (exp_len + CHARS_NEEDED + 1 + const_lens + 1));// +1 because of the sign
                            functions_lens[i] = (exp_len + CHARS_NEEDED  + const_lens);
                        }

                        if(parcial_indef_integral_str != NULL)
                        {
                            if(function_list[i][0] != '-')parcial_indef_integral_str[integral_i++] = '+'; 
                            else parcial_indef_integral_str[integral_i++] =function_list[i][0];

                            // multiplying the polinomial by the new exponent
                            for(int i = 0; i < my_strlen(multiplying_const_str); integral_i++, i++)parcial_indef_integral_str[integral_i] = multiplying_const_str[i]; 
                            // setting up polinomial integration string 
                            parcial_indef_integral_str[integral_i++] ='x';
                            parcial_indef_integral_str[integral_i++] ='^';

                            // adding +1 to the exponent
                            exp_value = my_atoi(exp) + 1;
                            free(exp); // Don't need "old" exponent
                            exp = my_itoa(exp_value); // getting new exponent
                            if(exp != NULL)
                            {
                                // copying the new exponent to the indefinite integral 
                                for(int i = 0; i < exp_len; integral_i++, i++)parcial_indef_integral_str[integral_i] = exp[i]; 

                                // setting up polinomial integration string 
                                parcial_indef_integral_str[integral_i++] ='/';

                                // dividing the polinomial by the new exponent
                                for(int i = 0; i < my_strlen(dividing_const_str); integral_i++, i++)parcial_indef_integral_str[integral_i] = dividing_const_str[i]; 
                                
                                // ending the string
                                parcial_indef_integral_str[integral_i] = '\0';
                            }
                        }
                    
                    }
                    else
                    {
                        //if the function is "C*x"

                        if(str_count_char(function,'x') == 1 && str_count_char(function,'^') == 0)
                        {
                            exp_len = 1;
                            parcial_indef_integral_str = (char*)malloc(sizeof(char) * (exp_len + CHARS_NEEDED + 1  + const_lens + 1));// +1 because of the sign
                            functions_lens[i] = (exp_len + CHARS_NEEDED  + const_lens);

                            if(parcial_indef_integral_str != NULL)
                            {
                                if(function_list[i][0] != '-')parcial_indef_integral_str[integral_i++] = '+'; 
                                else parcial_indef_integral_str[integral_i++] =function_list[i][0];
                                for(int i = 0; i < my_strlen(multiplying_const_str); integral_i++, i++)parcial_indef_integral_str[integral_i] = multiplying_const_str[i];
                                parcial_indef_integral_str[integral_i++] ='x';
                                parcial_indef_integral_str[integral_i++] ='^';
                                parcial_indef_integral_str[integral_i++] ='2';
                                parcial_indef_integral_str[integral_i++] ='/';
                                for(int i = 0; i < my_strlen(dividing_const_str); integral_i++, i++)parcial_indef_integral_str[integral_i] = dividing_const_str[i];
                                parcial_indef_integral_str[integral_i] ='\0';
                            }

                        }

                        //if the function is "C"

                        if(str_count_char(function,'x') == 0 && str_count_char(function,'^') == 0)
                        {
                            exp_len = 0;
                            parcial_indef_integral_str = (char*)malloc(sizeof(char) * ( (CHARS_NEEDED -1) + 1 + const_lens + 1));// for the 'x', '/', sign ,and for the '\0'
                            functions_lens[i] = ((CHARS_NEEDED -1) + const_lens);

                            if(parcial_indef_integral_str != NULL)
                            {
                                if(function_list[i][0] != '-')parcial_indef_integral_str[integral_i++] = '+'; 
                                else parcial_indef_integral_str[integral_i++] =function_list[i][0]; 
                                for(int i = 0; i < my_strlen(multiplying_const_str); integral_i++, i++)parcial_indef_integral_str[integral_i] = multiplying_const_str[i];
                                parcial_indef_integral_str[integral_i++] ='x';
                                parcial_indef_integral_str[integral_i++] ='/';
                                for(int i = 0; i < my_strlen(dividing_const_str); integral_i++, i++)parcial_indef_integral_str[integral_i] = dividing_const_str[i];
                                parcial_indef_integral_str[integral_i] ='\0';
                            }  
                        }
                    }
                    if(exp != NULL) free(exp); // freeing allocated str that won't return;
                    if(dividing_const_str != NULL)free(dividing_const_str);
                    if(multiplying_const_str != NULL)free(multiplying_const_str);
                    if(function_list[i]!= NULL)free(function_list[i]);
                    function_list[i] = parcial_indef_integral_str;

                    integral_i = 0;
                }
            }
        }
    }

    int i = 0;
    for(; i < functions_count; i++)indef_integral_len+= functions_lens[i];

    

    for(int p = 0; p < functions_count; p++)
    {
        printf("%s\n",function_list[p]);
    }

    indef_integral_str = (char*)malloc(sizeof(char) * (indef_integral_len + 1));
    
    int j = 0;
    i = 0;
    for(; i < functions_count; i++)
    {
        int k = j;
        for(; j <= my_strlen(function_list[i]); j++)indef_integral_str[j] = function_list[i][j-k];
        
    }

    if(function_list != NULL)
    {
        for(int k = 0; k < functions_count; k++)
        { 
            if(function_list[i]!= NULL)free(function_list[k]);
        }
        free(function_list);
    }
    if(functions_lens != NULL)free(functions_lens);

    return indef_integral_str;
}

double def_integral_value(char* function, double inf_lim, double sup_lim) // positive integer polynomials only 
{
    int exponent = 0; // exponent number
    double inf_value = 1, sup_value = 1; // Inferior Number and Superior Number, Numbers that we get after applying the inferior and superior limits
    double def_integral = 0, constant = 0; // integral value
    char** function_list = NULL; // list containing individual functions
    int functions_count = 0; // number of functions in function_list
    int function_sign = 1; // number is positive (1) or negative(-1) 

    if(function != NULL)
    {
        functions_count = my_math_function_count(function);
        
        if(functions_count > 0)
        {
            function_list = my_math_function_divider(function);

            if(function_list != NULL)
            {
                for(int i = 0; i < functions_count; i++)
                {
                    if(function_list[i][0] == '-')function_sign = -1;
                    else function_sign = 1; 
                    //Calculating Constants Value

                    constant = (mult_const_value(function_list[i])/div_const_value(function_list[i]));

                    // Calculating Integral

                    exponent = exponent_value(function) + 1; // Getting exponent value of the Indefinite Integral

                    if(exponent > 0) // calculating definite integral (only works with positive integer)
                    {
                        for(int j = 0; j < exponent;j++)
                        {
                            inf_value*=inf_lim;
                            sup_value*=sup_lim;
                        }
                        def_integral += function_sign * constant*((sup_value-inf_value)/exponent); 
                    }

                    inf_value = 1;
                    sup_value = 1;
                }
            }
        }
    }
    if(function_list != NULL)
    {
        for(int k = 0; k < functions_count; k++)free(function_list[k]);
        free(function_list);
    }

    return def_integral;
}

double my_math_function_centroid(char* function,double inf_lim, double sup_lim)
{
    double function_area = 0;
    double centroid_x = 0;
    double function_moment = 0;
    char* function_times_x = NULL;
    char** function_list = NULL; // list containing individual functions
    int function_list_len = 0;


    function_area = def_integral_value(function,inf_lim,sup_lim);

    if(function_area != 0)
    {
        function_list_len = my_math_function_count(function);

        
        if(function_list_len > 0)
        {
            function_list = my_math_function_divider(function);

            
            if(function_list != NULL)
            {
                for(int i = 0; i < function_list_len; i++)
                {
                    function_times_x = x_power_increment(function_list[i]);

                    if(function_times_x != NULL)
                    {
                        function_moment = def_integral_value(function_times_x,inf_lim,sup_lim);

                        centroid_x+= function_moment;

                        free(function_times_x);
                    }
                    else
                    {
                        centroid_x = 0;
                        break;
                    }
                }
            }

        }
    }

    if(function_list != NULL)
    {
        for(int i = 0; i < function_list_len; i++)free(function_list[i]);
        free(function_list);
    }
    if(centroid_x != 0)centroid_x/=function_area;

    return centroid_x;

}

char** my_math_function_divider(char* all_functions)
{
    int functions_count = 0; // counts how many functions the string has
    int i = 0, j = 0; // iterators
    int past_i_value = 0; // store the past value of "i" iterator 
    char** function_list = NULL; // vector containing all functions
    char* single_function = NULL; // single function string
    int* function_lens = NULL; // vector containing all functions lenghts

    if(all_functions != NULL) //if function string isn't NULL
    {
        functions_count = my_math_function_count(all_functions);

        if(functions_count > 0)
        { 
            function_lens = my_math_function_lens(all_functions); //stores the lenght of each individual function

            if(function_lens != NULL) // if we could allocate the int pointer
            {
                //it stores the ammount of functions that we will allocate in it
                function_list = (char**)malloc(sizeof(char*) * (functions_count));

                if(function_list != NULL) //if we could allocate the list of strings
                {
                    for(; i < functions_count; i++)function_list[i] = NULL; // initialize each pointers in "function_list" as NULL      

                    // setting up iterators values before entering the for loop
                    i = 0;
                    past_i_value = 0;

                    for(; j < functions_count; j++) // storing each individual function string
                    {
                        single_function = (char*)malloc(sizeof(char) *(function_lens[j] + 1)); // +1 because of the '\0' char

                        if(single_function != NULL) // if the string was allocated
                        {
                            for(; i < function_lens[j] + past_i_value; i++)
                            {
                                single_function[i-past_i_value] = all_functions[i]; // copies the function with it's sign 
                            }
                            single_function[i-past_i_value] = '\0'; // terminates the function string

                            function_list[j] = single_function; // stores the function string

                            past_i_value = i; // saves the "i" value from the for loop;
                        }
                        
                        else //some string couldn't be allocated for some reason (error or memory insufficient)
                        {
                            i = 0;

                            for(; i < functions_count; i++) if(function_list[i] != NULL) free(function_list[i]); // freeing all strings allocated
                            
                            free(function_list); // freeing the string pointer to indicate that something went wrong

                            break;
                        }
                    }
                }
            }
        }
    }

    if(function_lens != NULL)free(function_lens); // frees the pointer if it isn't NULL

    return function_list;

}

char* x_power_increment(char* function)
{
    char* exponent = NULL; // Exponent of the function
    char* x_incremented_function = NULL; // function with the "x" power incremented
    int exponent_len = 0; // length of exponent str
    int function_exponent_len = 0; // lenght of exponent in the function
    int function_len = 0; // length of function str
    int exponent_value = 0; // Exponent value 
    int i = 0,j = 0; // iterators

    if(function != NULL)
    {
        exponent = exponent_str(function); // gets exponent string

        if(exponent != NULL) // There´s a number after the '^' char
        {
            function_len = my_strlen(function); // Getting function length
            function_exponent_len = my_strlen(exponent); // Getting string length

            // if it's true, one more byte is needed because the next number string will have length "function_len + 1" 
            if(function_exponent_len == str_count_char(exponent,'9'))
            {
                x_incremented_function = (char*)malloc(sizeof(char) * (++function_len + 1));
                exponent_len = function_exponent_len + 1;
            }  
            else
            {
                x_incremented_function = (char*)malloc(sizeof(char) * (function_len + 1));
                exponent_len = function_exponent_len;
            }

            if(x_incremented_function != NULL)
            {
                // adding +1 to the exponent
                exponent_value = my_atoi(exponent) + 1;
                free(exponent); // Don't need "old" exponent
                exponent = my_itoa(exponent_value); // getting new exponent

                if(exponent != NULL)
                {
                    // copying the function till the '^' char
                    for(; function[i] != '^'; i++)x_incremented_function[i] = function[i];
                    x_incremented_function[i] = '^'; // putting the power symbol

                    // copying the new exponent to the function
                    for(; j < exponent_len; j++)x_incremented_function[i+j+1] = exponent[j];
                    i += function_exponent_len + 1; // next loop will start after the exponent number of the function

                    int len_diff = exponent_len - function_exponent_len; //length difference between the two exponents strings

                    for(; function[i] != '\0'; i++)x_incremented_function[i+len_diff] = function[i]; // copying the rest of the function str
                    x_incremented_function[i+len_diff] = '\0'; //finalizing the str

                }            
            }
            if(exponent != NULL) free(exponent); // freeing allocated str that won't return;
        }
        
        else
        {
            //if the function is "C*x"

            if(str_count_char(function,'x') == 1 && str_count_char(function,'^') == 0)
            {
                function_len = my_strlen(function); // Getting function length
                x_incremented_function = (char*)malloc(sizeof(char) * (function_len + 1 + 1 + 1)); // putting the "^", "2" and "\0" 

                if(x_incremented_function != NULL)
                {
                    char* increment_of_function_x = "x^2";

                    // copying function and increment_of_function_x
                    for(; function[i] != 'x'; i++)x_incremented_function[i] = function[i];
                    for(; j < 3; j++)x_incremented_function[i+j] = increment_of_function_x[j];
                    
                    i += 1;// copying the "/constant";
                    for(; function[i] != '\0'; i++)x_incremented_function[i+j-1] = function[i];

                    x_incremented_function[i+j-1] ='\0'; //finalizing str
                }

            }

            //if the function is "C"

            if(str_count_char(function,'x') == 0 && str_count_char(function,'^') == 0)
            {
                function_len = my_strlen(function); // Getting function length
                x_incremented_function = (char*)malloc(sizeof(char) * (function_len + 1 + 1));// for the 'x' and for the '\0'

                if(x_incremented_function != NULL)
                {
                    // setting up iterator for the loop
                    i = 0;

                    char increment_of_function_C = 'x';

                    // copying function and increment_of_function_C
                    if(function[0] == '+' || function[0] == '-')x_incremented_function[i++] = function[0];

                    // copying the function multiplier constant int/float
                    for(; ( (function[i] >= '0' && function[i] <= '9') || function[i] == '.' ); i++)x_incremented_function[i] = function[i];
                    x_incremented_function[i] = increment_of_function_C;

                    for(; function[i] != '\0'; i++)x_incremented_function[i+1] = function[i]; // copying the function divider constant int/float
                    
                    x_incremented_function[i+1] ='\0'; //finalizing str
                }  
            }
        }
    }

    return x_incremented_function; 
}

int my_math_function_count(char* all_functions)
{
    int i = 0; // iterator
    int functions_count = 0; // counts how many functions the string has

    if(all_functions != NULL)
    {
        functions_count = 1; // There's atleast one function

        if(all_functions[0] == '+' || all_functions[0] == '-')i++; // checks if the first char of the function it´s a sign, it´s needed for the for loop

        // counts how many functions the function has 
        // for example the function "x^2 + x + 5" it's a sum of 3 functions, "x^2", "x" and "5" 
        for(; all_functions[i] != '\0'; i++)if((all_functions[i] == '+' || all_functions[i] == '-')) functions_count++;
    }

    return functions_count;
}

int* my_math_function_lens(char* all_functions)
{
    int j = 0, i = 0; // Iterators
    int past_i_value = 0; // save past "i" iterator value
    int* function_lens = NULL; 
    int functions_count = 0; // Counts how many functions the function is made of

    if(all_functions != NULL)
    {
        if(all_functions[0] == '+' || all_functions[0] == '-')i++; // checks if the first char of the function it´s a sign, it´s needed for the for loop

        functions_count = my_math_function_count(all_functions); // gets ammount of functions
        
        if(functions_count > 0) //There's atleast one function
        {
            function_lens = (int*)malloc(sizeof(int) * functions_count); // allocate the ammount 

            if(function_lens != NULL) // function_lens could be allocated
            {

                for(;all_functions[i] != '\0'; i++) // counts each function length based on signs and '\0' chars
                {
                    if(all_functions[i] == '+' || all_functions[i] == '-')
                    {
                        function_lens[j] = i - past_i_value; // calculates  the function length 
                        j++;  // goes to the next "function_lens" pos 
                        past_i_value = i;  //saves the "i" value from the for loop;
                    }   
                }
                function_lens[j] = i - past_i_value; //last function lenght value;]
            }
        }
    }

    return function_lens;
}