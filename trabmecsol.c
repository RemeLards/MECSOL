#include "trabmecsol.h"


double force_distribution_validation(double bar_size, double force_density_pos, char* function, double inf_lim, double* sup_lim)
{
    double centroid_bar_pos = 0;

    if(function != NULL)
    {
        if(bar_size - (force_density_pos + (*sup_lim-inf_lim)) >= 0 ) // if the integral + the force density pos don't exceed the bar size
        {
            centroid_bar_pos = my_math_function_centroid(function,inf_lim,*sup_lim) - inf_lim + force_density_pos;
        }
        else
        {
            *sup_lim += bar_size - (force_density_pos + (*sup_lim-inf_lim)); // fixing the superior_lim, so the integral + the force density pos won't exceed the bar size
            printf("\n O Maior Limite Superior que pode ser colocado foi : %.5f\n\n",*sup_lim);
            centroid_bar_pos = my_math_function_centroid(function,inf_lim,*sup_lim) - inf_lim + force_density_pos;
        }
    }

    return centroid_bar_pos;
}

int* malloc_more_int_space(int* int_vector, int vector_size)// if int_vector is allocated
{
    int* new_int_vector = NULL;
    
    new_int_vector = (int*)malloc(sizeof(int) * (vector_size + 1)); // allocated one more "int" size memory
    
    if(new_int_vector != NULL)
    {
        for(int i = 0; i < vector_size; i++)new_int_vector[i] = int_vector[i]; // copies old vector

        if(int_vector!= NULL)free(int_vector); // free old vector
    }

    return new_int_vector;
}

double* malloc_more_double_space(double* double_vector, int vector_size)// if int_vector is allocated
{
    double* new_double_vector = NULL;
    
    new_double_vector = (double*)malloc(sizeof(double) * (vector_size + 1)); // allocated one more "int" size memory
    if(new_double_vector != NULL)
    {
        for(int i = 0; i < vector_size; i++)new_double_vector[i] = double_vector[i]; // copies old vector
        if(double_vector!= NULL)free(double_vector); // free old vector
    }
    return new_double_vector;
}

char** malloc_more_str_vector_space(char** str_vector, int vector_size)
{
    char** new_str_vector = NULL;
    
    new_str_vector = (char**)malloc(sizeof(char*) * (vector_size + 1)); // allocated one more "int" size memory
    if(new_str_vector != NULL)
    {
        for(int i = 0; i < vector_size; i++)new_str_vector[i] = str_vector[i]; // copies old vector
        if(str_vector!= NULL)free(str_vector); // free old vector
    }

    return new_str_vector;
}
