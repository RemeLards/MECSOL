#include "trabmecsol.h"

#define AMMOUNT_OF_DOUBLE_VECTORS 5 // for force, inferior limit, superior limit, centroid and moment
#define MAX_FUNCTION_LEN 30


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
            printf("\nO Maior Limite Superior que pode ser colocado foi : %.5f\n\n",*sup_lim);
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

int main(int argc, char** argv)
{
    BAR barra;
    //APOIO_L apoio_livre;
    //ENGST engaste;

    barra.size = 1;

    double force_density_pos = 0;
    
    char** vector_of_functions = NULL;

    double* vector_inf_lims = NULL;

    double* vector_sup_lims = NULL;
    
    double* vector_forces_func = NULL;

    double* vector_centroids_func = NULL;

    double* vector_moments_func = NULL;

    char user_option = '\0';

    //************************** NAO SEI PORQUE NAO FUNCIONA **************************
    //double* all_double_vectors[AMMOUNT_OF_DOUBLE_VECTORS] = {vector_forces_func, vector_inf_lims, vector_sup_lims, vector_centroids_func, vector_moments_func};
    
    int all_vectors_len = 0;

    char function_str[MAX_FUNCTION_LEN + 1];
    char distance_str[MAX_FUNCTION_LEN + 1];
    char inf_lim_str[MAX_FUNCTION_LEN + 1]; 
    char sup_lim_str[MAX_FUNCTION_LEN + 1];


    int user_wanna_quit = 0;
    while(user_wanna_quit == 0) //********************FAZER TRATAMENTO DE ERRO DEPOIS********************//
    {
        // allocating one more space for each vector
        //************************** NAO SEI PORQUE NAO FUNCIONA **************************
        //for(int i = 0; i < AMMOUNT_OF_DOUBLE_VECTORS; i++)all_double_vectors[i] = malloc_more_double_space(all_double_vectors[i],all_vectors_len);

        vector_of_functions = malloc_more_str_vector_space(vector_of_functions,all_vectors_len);
        vector_inf_lims = malloc_more_double_space(vector_inf_lims,all_vectors_len);
        vector_sup_lims = malloc_more_double_space(vector_sup_lims,all_vectors_len);
        vector_forces_func = malloc_more_double_space(vector_forces_func,all_vectors_len);
        vector_centroids_func = malloc_more_double_space(vector_centroids_func,all_vectors_len);
        vector_moments_func = malloc_more_double_space(vector_moments_func,all_vectors_len);

        printf("Escreva a distancia de onde sua funcao de carga partira (levando em consideracao que a coordenada x = 0, esta situada a esquerda da barra)  :  ");
        
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(distance_str, 31 ,stdin); //Gets string
        if(distance_str[my_strlen(distance_str)-1] == '\n')distance_str[my_strlen(distance_str)-1] = '\0'; // removes '\n' char that gets to the string (sometimes)
        
        force_density_pos = my_atof(distance_str); //getting the start of the force_density 
        printf("\n\n");

        printf("Escreva sua funcao carga :  ");

        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(function_str, 31 ,stdin); //Gets string
        if(function_str[my_strlen(function_str)-1] == '\n')function_str[my_strlen(function_str)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

        vector_of_functions[all_vectors_len] = remove_spaces(function_str); // getting and saving the force_density function
        printf("\n\n");

        printf("Escreva o limite inferior :  ");
        
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(inf_lim_str, 31 ,stdin); //Gets string
        if(inf_lim_str[my_strlen(inf_lim_str)-1] == '\n')inf_lim_str[my_strlen(inf_lim_str)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

        vector_inf_lims[all_vectors_len] = my_atof(inf_lim_str); // getting and saving the inferior limit of the force_density integration (to the force calculation)
        printf("\n\n");

        printf("Escreva o limite superior :  ");
        
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(sup_lim_str, 31 ,stdin); //Gets string
        if(sup_lim_str[my_strlen(sup_lim_str)-1] == '\n')sup_lim_str[my_strlen(sup_lim_str)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

        vector_sup_lims[all_vectors_len] = my_atof(sup_lim_str); // getting and saving the superior limit of the force_density integration (to the force calculation)
        printf("\n\n");

        //getting function centroid considering bar coordinates /max centroid considering bar coordinates  if the (force_density_pos + (sup_lim - inf_lim)) exceeds the bar length
        //And fixing the superior limit if needed
        vector_centroids_func[all_vectors_len] = force_distribution_validation(barra.size,force_density_pos,function_str,
                                                                                vector_inf_lims[all_vectors_len],&vector_sup_lims[all_vectors_len]);
        //getting total force 
        vector_forces_func[all_vectors_len] = def_integral_value(function_str,vector_inf_lims[all_vectors_len],vector_sup_lims[all_vectors_len]); 

        // getting moment done by the force * centroid 
        vector_moments_func[all_vectors_len] = vector_forces_func[all_vectors_len] * vector_centroids_func[all_vectors_len];

        // saving information that all vectors went up by one size of its type
        all_vectors_len++;
        while(1)
        {
            printf("Quer colocar mais funcoes carga? (digite S ou N) : ");
            scanf(" %c",&user_option);
            if(user_option == 's' || user_option == 'S')break;
            if(user_option == 'n' || user_option == 'N')break;
        }
        
        if(user_option == 'n' || user_option == 'N')user_wanna_quit = 1;

    }

    //print all functions and it's effects on the bar one by one
    for(int i = 0; i < all_vectors_len; i++)
    {
        printf("A funcao e : %s\n",vector_of_functions[i]);
        printf("O limite inferior e : %.4f\n",vector_inf_lims[i]);
        printf("o limite superior e : %.4f\n",vector_sup_lims[i]);
        printf("A posicao do Centroide na Barra e : %.4f\n",vector_centroids_func[i]);
        printf("A forca e : %.4f\n",vector_forces_func[i]);
        printf("O Inicio da Distribuicao e : %.4f\n",vector_centroids_func[i] - my_math_function_centroid(vector_of_functions[i],vector_inf_lims[i],vector_sup_lims[i]));
        printf("O momento e : %.4f\n",vector_moments_func[i]);
        printf("\n\n");
    }
    // freeing all vectors and strings after end of the program
    
    //for(int i = 0; i < all_vectors_len; i++)free(all_double_vectors[i]); //************************** NAO SEI PORQUE NAO FUNCIONA **************************
    
    if(all_vectors_len > 0)
    {
        free(vector_of_functions);
        free(vector_inf_lims);
        free(vector_sup_lims);
        free(vector_forces_func);
        free(vector_centroids_func);
        free(vector_moments_func);
    }
    if(vector_of_functions != NULL)
    {
        for(int i = 0; i < all_vectors_len; i++)
        {
            if(vector_of_functions[i] != NULL)free(vector_of_functions[i]);
        }
        free(vector_of_functions);    
    }

    return 0;
}