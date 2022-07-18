#include <stdlib.h>
#include "my_strings.h"

#ifndef _MATH_INTEGRAL
#define _MATH_INTEGRAL


char* indef_integral_ncosnt(char* function); // Returns a allocated str containing the indifinite integral without constants included
double def_integral_value(char* function, double inf_lim, double sup_lim); // Returns integral value
char** my_math_function_divider(char* function); // Divides polynomial function sums in a vector cointaining each polynomial of the function
double my_math_function_centroid(char* function, double inf_lim, double sup_lim);  // Retuns function "x" value centroid 
int my_math_function_count(char* all_functions); // counts how many functions the function has  
int* my_math_function_lens(char* all_functions); // gets all lenghts of all functions that all_function is made of  
char* x_power_increment(char* function); // increments "x" power in a function by 1 , only works with positive integers numbers

char* exponent_str(char* function); // Returns the string containing the exponent
char* mult_const_str(char* function); // Returns the string containing the constant multiplying the integral
char* div_const_str(char* function); // Returns the string containing the constant dividing the integral

int exponent_value(char* function); // Returns exponent value
double mult_const_value(char* function); // Returns the constant value multiplying the integral
double div_const_value(char* function); // Returns the constant value dividing the integral

#endif