#include <stdlib.h>
#include "my_strings.h"

#ifndef _MATH_INTEGRAL
#define _MATH_INTEGRAL


char* indef_integral(char* function); //Returns a malloced str containing the indifinite integral
float def_integral(char* function, float inf_lim, float sup_lim);

#endif