#include "trabmecsol.h"

double force_distribution_validation(double bar_size, double force_distribution_pos, char* function, double inf_lim, double* sup_lim)
{
    double centroid_bar_pos = 0;

    if(function != NULL)
    {
        if(bar_size - (force_distribution_pos + (*sup_lim-inf_lim)) >= 0 )
        {
            centroid_bar_pos = my_math_function_centroid(function,inf_lim,*sup_lim) - inf_lim + force_distribution_pos;
        }
        else
        {
            *sup_lim += bar_size - (force_distribution_pos + (*sup_lim-inf_lim));
            printf("\nO Maior Limite Superior que pode ser colocado foi : %.5f\n\n",*sup_lim);
            centroid_bar_pos = my_math_function_centroid(function,inf_lim,*sup_lim) - inf_lim + force_distribution_pos;
        }
    }
   
    return centroid_bar_pos;
}

int* int_vector_one_more_space(int* int_vector, int vector_size)// if int_vector is allocated
{
    int* new_int_vector = NULL;
    
    if(int_vector != NULL)
    {
        new_int_vector = (int*)malloc(sizeof(int) * (vector_size + 1)); // allocated one more "int" size memory
        for(int i = 0; i < vector_size; i++)new_int_vector[i] = int_vector[i]; // copies old vector
        free(int_vector); // free old vector
    }

    return new_int_vector;
}

int main(int argc, char** argv)
{
    BAR barra;
    APOIO_L apoio_livre;
    ENGST engaste;

    barra.size = 1;
    double force_distribution_pos = 0;
    char* function = "x^2";
    
    double force_func = 0;
    int* vector_forces_func = NULL;

    double moment_func = 0;
    int* vector_moment_func = NULL;

    double centroid = 0;
    int* vector_centroid_func = NULL;

    char** vector_of_functions = NULL;

    double inf_lim = 0;
    int* vector_inf_lim = NULL;

    double sup_lim = 0;
    int* vector_sup_lim = NULL;

    int vector_for_function_size = 0;

    char function_scanf[30];
    char distance_scanf[30];
    char inf_lim_scanf[30]; 
    char sup_lim_scanf[30];


    int user_wanna_continue = 1;

    while(user_wanna_continue == 1)
    {
        printf("Write the distance from the bar left edge  :  ");
        scanf("%s",distance_scanf);
        force_distribution_pos = my_atof(distance_scanf);
        printf("\n\n");

        printf("Write your force distribution function :  ");
        scanf("%s",function_scanf);
        printf("\n\n");

        printf("Write your inferior limit :  ");
        scanf("%s",inf_lim_scanf);
        inf_lim = my_atof(inf_lim_scanf);
        printf("\n\n");

        printf("Write your superior limit :  ");
        scanf("%s",sup_lim_scanf);
        sup_lim = my_atof(sup_lim_scanf);
        printf("\n\n");
        
        force_func = def_integral_value(function_scanf,inf_lim,sup_lim);
        centroid = force_distribution_validation(barra.size,force_distribution_pos,function,inf_lim,&sup_lim);

        user_wanna_continue = 0;

    }

    printf("A funcao e : %s\n",function_scanf);
    printf("O limite inferior e : %.2f\n",inf_lim);
    printf("o limite superior e : %.2f\n",sup_lim);
    printf("A posicao do Centroide na Barra e : %.2f\n",centroid);
    printf("A forca e : %.2f\n",force_func);
    printf("A distancia e : %.2f\n",force_distribution_pos);
    printf("O momento e : %.2f\n",force_func * centroid);

    return 0;
}