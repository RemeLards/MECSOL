#include <stdlib.h>
#include "my_strings.h"

#ifndef _MATH_INTEGRAL
#define _MATH_INTEGRAL


char* indef_integral(char* function); //Returns a allocated str containing the indifinite integral
double def_integral(char* function, float inf_lim, float sup_lim);

#endif