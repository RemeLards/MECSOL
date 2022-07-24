#ifndef _TRAB_MECSOL
#define _TRAB_MECSOL

#define AMMOUNT_OF_DOUBLE_VECTORS 5 // for force, inferior limit, superior limit, centroid and moment
#define MAX_FUNCTION_LEN 30
#define USER_CHAR 1

#include "my_math.h"
#include "my_strings.h"
#include "objects_struct.h"
#include <stdio.h>
#include <stdlib.h>

double force_distribution_validation(double bar_size, double force_distribution_pos, char* function, double inf_lim, double* sup_lim);
int* malloc_more_int_space(int* int_vector, int vector_size);
double* malloc_more_double_space(double* double_vector, int vector_size);
char** malloc_more_str_vector_space(char** str_vector, int vector_size);


#endif

