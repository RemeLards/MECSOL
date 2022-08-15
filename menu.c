#include "menu.h"
#include "pbPlots.h"
#include "supportLib.h"

#define CDW_N_OF_POINTS 10

typedef struct 
{
    double x;
    double y;

} POINT;


int cmp_point(const void * a, const void * b)
{
    POINT* pA = (POINT*)a ;
    POINT* pB = (POINT*)b ;
    int ret;
    if(pA->x < pB->x )ret=-1;
    else if(pA->x > pB->x )ret=1;
    else ret = 0;

   return ( ret );
}

void printTela_1()
{
    // Tela 1:
    system("cls");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forcas internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Pressione 'ENTER' para criar uma situacao;\n");
    printf(" =====================================================================\n\n");
}

void printTela_2()
{
    // Tela 2:
    system("cls");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forcas internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Dentre os seguintes tipos de apoio, escolha um:\n");
    printf("     1. Apoio Simples\n");
    printf("     2. Engaste\n");
    printf("     3. Livre\n");
    printf(" =====================================================================\n\n");
}

void printEng_Eng_validation()
{
    printf("\n =====================================================================\n");
    printf("   Nao eh possivel utilizar dois engastes como apoio. Entre com \n outro tipo de apoio.\n");
    printf("   Pressione 'ENTER' para continuar.");
    printf(" =====================================================================\n"); 
}

void print_Apoios_validation(char** tiposApoios, int apoio1, int apoio2, double pos_apoio1, double pos_apoio2)
{
    system("cls");
    printf(" =====================================================================\n");
    printf(" ============================ Seus Apoios ============================\n");
    printf("   Tipo do primeiro apoio: %s\n", tiposApoios[apoio1-1]);
    printf("   Tipo do segundo apoio: %s\n", tiposApoios[apoio2-1]);
    printf("   Posicao do primeiro apoio: %.2f\n", pos_apoio1);
    printf("   Posicao do segundo apoio: %.2f\n", pos_apoio2);
    printf(" =====================================================================\n");
}

void print_posApoio2_validation()
{
    printf(" =====================================================================\n");
    printf("   Por favor entre com os dados sobre os apoios novamente.\n");
    printf("   Pressione 'ENTER' para continuar.\n");
    printf(" =====================================================================\n");
}

void print_tipos_de_perfis_de_vigas()
{
    printf("=====================================================================\n");
    printf(" Agora escolha o tipo de perfis de viga.\n");
    printf("    1. Circular\n");
    printf("    2. Retangular\n");
    printf("    3. Triangular\n");
    printf("    4. Tipo U\n");
    printf("    5. Tipo H\n");
    printf("    6. Tipo I\n");
    printf("    7. Tipo T\n");
    printf(" =====================================================================\n");

}

void printTela_3()
{
    // Tela 3:
    system("cls");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forcas internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Dentre os seguintes tipos de acoes externas, escolha uma:\n");
    printf("     1. Forca\n");
    printf("     2. Momento (GRAFICO SE COLOCA MOMENTO NAO ESTA MUITO CERTO) \n");
    printf("     3. Distribuicao de Carga ( NAO DEU TEMPO DE IMPLEMENTAR GRAFICO)\n");
    printf("     4. Resultado Final \n");
    printf(" =====================================================================\n\n");
}

void print_UserOp_validation()
{
    printf("\n =========================================================\n");
    printf("   Opcao Invalida. Aperte Enter E Digite Uma Opcao Disponivel.\n");
    printf(" ===========================================================\n");  
}

void print_UserOp_validation02()
{
    printf("\n =====================================================================\n");
    printf("   Nao eh possivel utilizar apoio simples com apoio livre. Entre com \n outro tipo de apoio.\n");
    printf("   Pressione 'ENTER' para continuar.\n");
    printf(" =====================================================================\n");

}

void print_Uservalidation03()
{
    printf("\n =====================================================================\n");
    printf("   Nao e possivel utilizar engaste com apoio simples. Situacao estaticamente indetermindada\n");
    printf("   Pressione 'ENTER' para continuar.\n");
    printf(" =====================================================================\n");

}

int main ()
{   // Declaracao de variaveis:
                                    // Menu Variables
    BAR barra;
    barra.size = 0;

    APOIO_S Apoio_simples_L; // Apoio simples on the Left side 
    Apoio_simples_L.force_y = 0;
    Apoio_simples_L.moment_y = 0;

    APOIO_S Apoio_simples_R; // Apoio simples on the right side
    Apoio_simples_R.force_y = 0;
    Apoio_simples_R.moment_y = 0;

    ENGST Engaste;
    Engaste.moment_x = 0;
    Engaste.moment_y = 0;
    Engaste.force_x = 0;
    Engaste.force_y = 0;

    int opApoio1 = 0, opApoio2 = 0, valida = 0, userOp = 0;
    double posApoio2  = 0;
    char* tiposApoios[] = {"Apoio Simples", "Engaste", "Livre"};
    int tiposVigas = 0;
    char userInput[30 + 1];
    char GetChar[1 + 1];

                                    //CALCULOS
    int actions_chosen = 0, supports_chosen = 0, beam_chosen = 0;

                                    // Point Variable (Varíaveis Pontuais (ou seja Discretas, diferente da distruibuição de cargas))
    
    //double point_force  = 0 , point_momento  = 0, distance = 0;

    int all_discrete_variables_vectors_len = 0;
    double* point_force = NULL;
    double* point_moment = NULL;
    double* point_force_distance = NULL;
    
    int pure_moment_len = 0;
    double* point_pure_moment = NULL;
    double* pure_moment_distance = NULL;
    
    char* distance_str = NULL;
    char* force_str = NULL;
    char* moment_str = NULL;

                                    // Continuous Variables (Variáveis de Carga Distribuida)

    int all_continuous_variables_vectors_len = 0;
    double* vector_force_density_pos = NULL;
    double* vector_inf_lims = NULL;
    double* vector_sup_lims = NULL;
    double* vector_forces_func = NULL;
    double* vector_centroids_func = NULL;
    double* vector_moments_func = NULL;
    char** vector_of_functions = NULL;


    // User Input
    char* function_str = NULL;
    char* function_distance_str = NULL;
    char* inf_lim_str = NULL;
    char* sup_lim_str = NULL;
    char* user_confirmation = NULL;

    // Program Start
    printTela_1();
    fflush(stdin); //Cleaning Keyboard Buffer
    fgets(GetChar, 1 + 1 ,stdin); //Gets string

    while (supports_chosen == 0)
    {
        printf("  Digite o Tamanho da barra :    ");

        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, 30 + 1 ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
        barra.size = my_atof(userInput);
        

        printTela_2();
        printf("  Qual o tipo do apoio localizado na posicao x = 0 (Extremidade Esquerda) ? :    ");
        
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, 30 + 1  ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
        
        opApoio1 = my_atoi(userInput);

        if(opApoio1 == APOIO_SIMPLES)
        {
            printf("  Qual a distancia da barra (comecando da extremidade esquerda) que voce quer colocar o apoio esquerdo ? :    ");
            
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(userInput, 30 + 1  ,stdin); //Gets string
            if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
            
            double distance_left_apoio = my_atof(userInput);
            if(distance_left_apoio < 0) distance_left_apoio = 0;
            if(distance_left_apoio > (barra.size/2)) distance_left_apoio = barra.size/2;

            Apoio_simples_L.distance = distance_left_apoio;
        }

        if(opApoio1 != LIVRE)
        {
            // Restricao dos tipos de apoio + selecao do segundo apoio
            while (valida == 0)
            {
                printf("\n\n  Qual o tipo do segundo apoio? :    ");
                
                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
                
                opApoio2 = my_atoi(userInput);

                if(opApoio1 == APOIO_SIMPLES && opApoio2 == APOIO_SIMPLES)
                {
                    printf("  Qual a distancia da barra (comecando da extremidade esquerda) que voce quer colocar o apoio direito ? :    ");
                    
                    fflush(stdin); //Cleaning Keyboard Buffer
                    fgets(userInput, 30 + 1  ,stdin); //Gets string
                    if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
                    
                    double distance_right_apoio = my_atof(userInput);
                    if(distance_right_apoio > barra.size) distance_right_apoio = barra.size;
                    if(distance_right_apoio < (barra.size/2))
                    {
                        distance_right_apoio = barra.size/2;
                        if(Apoio_simples_L.distance == barra.size/2)distance_right_apoio = (barra.size/1.5);
                    }

                    Apoio_simples_R.distance = distance_right_apoio;
                }


                if((opApoio1 == ENGASTE) && (opApoio2 == ENGASTE))
                {
                    printEng_Eng_validation();
                    fflush(stdin); //Cleaning Keyboard Buffer
                    fgets(GetChar, 1 + 1 ,stdin); //Gets string
                }
                
                else
                {
                    if((opApoio1 == APOIO_SIMPLES) && (opApoio2 == LIVRE))
                    {
                        print_UserOp_validation02();
                        fflush(stdin); //Cleaning Keyboard Buffer
                        fgets(GetChar, 1 + 1 ,stdin); //Gets string
                    }

                    else 
                    {
                        if ((opApoio1 == ENGASTE && opApoio2 == APOIO_SIMPLES) || (opApoio1 == APOIO_SIMPLES && opApoio2 == ENGASTE))
                        {
                            print_Uservalidation03();
                            fflush(stdin); //Cleaning Keyboard Buffer
                            fgets(GetChar, 1 + 1 ,stdin); //Gets string
                        }
                        else valida = 1;
                    }
                }

            }
            
            print_Apoios_validation(tiposApoios,opApoio1,opApoio2,Apoio_simples_L.distance,Apoio_simples_R.distance);
            printf("\n   Pressione 'ENTER' para continuar.\n");
            
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(GetChar, 1 + 1 ,stdin); //Gets string
        }
           
        else
        {
            opApoio2 = ENGASTE;
            printf("\n\n O Engaste foi colocado na extremidade esquerda da Barra \n\n");
            printf("\n   Pressione 'ENTER' para continuar.\n");
            
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(GetChar, 1 + 1 ,stdin); //Gets string
        }
        supports_chosen++;

    }
    
    while (beam_chosen == 0)
    {
        print_tipos_de_perfis_de_vigas();

        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, 30 + 1 ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

        tiposVigas = my_atoi(userInput);
        
    }

    while(actions_chosen == 0)
    {
        printTela_3();
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, 30 + 1  ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
        userOp = my_atoi(userInput);

        if(userOp == FORCA)
        {
            system("cls");
            printf("\n\n\n");
            printf(" OBS: Escreva numeros decimais com '.' (ex : 0.3 , 0.2465)\n\n");
            
            int user_wanna_quit = 0;

            while(user_wanna_quit == 0)
            {
                point_force = malloc_more_double_space(point_force, all_discrete_variables_vectors_len);
                point_moment = malloc_more_double_space(point_moment, all_discrete_variables_vectors_len);
                point_force_distance = malloc_more_double_space(point_force_distance, all_discrete_variables_vectors_len);

                printf("Escreva a localizacao da sua forca na barra  :  ");
                distance_str = str_validation(MAX_FUNCTION_LEN +1);
                point_force_distance[all_discrete_variables_vectors_len] = my_atof(distance_str);
                if(point_force_distance[all_discrete_variables_vectors_len] > barra.size)point_force_distance[all_discrete_variables_vectors_len] = barra.size;
                if(point_force_distance[all_discrete_variables_vectors_len] < 0)point_force_distance[all_discrete_variables_vectors_len] = 0;
                if(distance_str != NULL) free(distance_str);
                printf("\n\n");
            
                printf("Escreva a intensidade da forca (OBS : O sentido positivo e para cima) :  ");
                force_str = str_validation(MAX_FUNCTION_LEN +1);
                point_force[all_discrete_variables_vectors_len] = my_atof(force_str);
                if(force_str != NULL) free(force_str);
                printf("\n\n");

                point_moment[all_discrete_variables_vectors_len] = point_force[all_discrete_variables_vectors_len] * point_force_distance[all_discrete_variables_vectors_len];
                
                all_discrete_variables_vectors_len++; 
                while(1)
                {
                    printf(" Quer colocar mais forcas? (digite S ou N) : ");
                    user_confirmation = str_validation(USER_CHAR + 1);
                    
                    if( (user_confirmation[0] == 's' || user_confirmation[0] == 'S'))break;
                    if(user_confirmation[0] == 'n' || user_confirmation[0] == 'N')
                    {
                        user_wanna_quit = 1;
                        break;
                    }
                    free(user_confirmation);
                    printf("\n\n");
                }

                free(user_confirmation);
                system("cls");
            }

            for(int i = 0; i < all_discrete_variables_vectors_len; i++)
            {
                printf(" Sua forca e : %.4f\n",point_force[i]);
                printf(" Sua distancia e : %.4f\n",point_force_distance[i]);
                printf(" Seu momento e : %.4f\n",point_moment[i]);
                printf("\n\n");
            }

            printf("\n   Pressione 'ENTER' para continuar.\n");
            
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(GetChar, 1 + 1 ,stdin); //Gets string
            
        }
        if(userOp == MOMENTO)
        {
            system("cls");
            printf("\n\n\n");
            printf(" OBS: Escreva numeros decimais com '.' (ex : 0.3 , 0.2465)\n\n");
            
            int user_wanna_quit = 0;

            while(user_wanna_quit == 0)
            {
                point_pure_moment = malloc_more_double_space(point_pure_moment, pure_moment_len);
                pure_moment_distance = malloc_more_double_space(pure_moment_distance, pure_moment_len);

                printf("Escreva a localizacao da sua momento na barra  :  ");
                distance_str = str_validation(MAX_FUNCTION_LEN +1);
                pure_moment_distance[pure_moment_len] = my_atof(distance_str);
                if(pure_moment_distance[pure_moment_len] > barra.size)pure_moment_distance[pure_moment_len] = barra.size;
                if(pure_moment_distance[pure_moment_len] < 0)pure_moment_distance[pure_moment_len] = 0;
                if(distance_str != NULL) free(distance_str);
                printf("\n\n");

                printf("Escreva a intensidade do momento  (OBS : O sentido positivo e o antihorario)  :  ");
                moment_str = str_validation(MAX_FUNCTION_LEN +1);
                point_pure_moment[pure_moment_len] = my_atof(moment_str);
                if(moment_str != NULL) free(moment_str);
                printf("\n\n");
                
                pure_moment_len++; 
                while(1)
                {
                    printf(" Quer colocar mais momentos? (digite S ou N) : ");
                    user_confirmation = str_validation(USER_CHAR + 1);
                    
                    if( (user_confirmation[0] == 's' || user_confirmation[0] == 'S'))break;
                    if(user_confirmation[0] == 'n' || user_confirmation[0] == 'N')
                    {
                        user_wanna_quit = 1;
                        break;
                    }
                    free(user_confirmation);
                    printf("\n\n");
                }

                free(user_confirmation);
                system("cls");
            }

            for(int i = 0; i < pure_moment_len; i++) // Showing all moments and their distances
            {
                printf(" Sua distancia e : %.4f\n",pure_moment_distance[i]);
                printf(" Seu momento e : %.4f\n",point_pure_moment[i]);
                printf("\n\n");
            }
            printf("\n   Pressione 'ENTER' para continuar.\n"); // The program stops and wait till the user press ENTER
            
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(GetChar, 1 + 1 ,stdin); //Gets string
        }
        if(userOp == DISTRIBUICAO_DE_CARGA)
        {
            system("cls");
            printf("\n\n\n");
            printf(" OBS: Escreva numeros decimais com '.' (ex : 0.3 , 0.2465)\n\n");

            int user_wanna_quit = 0;
            
            while(user_wanna_quit == 0) //********************FAZER TRATAMENTO DE ERRO DEPOIS********************//
            {
                // allocating one more space for each vector
                //************************** NAO SEI PORQUE NAO FUNCIONA **************************
                //for(int i = 0; i < AMMOUNT_OF_DOUBLE_VECTORS; i++)all_double_vectors[i] = malloc_more_double_space(all_double_vectors[i],all_vectors_len);

                vector_of_functions = malloc_more_str_vector_space(vector_of_functions,all_continuous_variables_vectors_len);
                vector_inf_lims = malloc_more_double_space(vector_inf_lims,all_continuous_variables_vectors_len);
                vector_sup_lims = malloc_more_double_space(vector_sup_lims,all_continuous_variables_vectors_len);
                vector_forces_func = malloc_more_double_space(vector_forces_func,all_continuous_variables_vectors_len);
                vector_centroids_func = malloc_more_double_space(vector_centroids_func,all_continuous_variables_vectors_len);
                vector_moments_func = malloc_more_double_space(vector_moments_func,all_continuous_variables_vectors_len);
                vector_force_density_pos = malloc_more_double_space(vector_force_density_pos,all_continuous_variables_vectors_len);

                printf(" Escreva a distancia de onde sua funcao de carga partira (levando em consideracao que a coordenada x = 0, esta situada a esquerda da barra)  :  ");

                function_distance_str = str_validation(MAX_FUNCTION_LEN + 1);
                vector_force_density_pos[all_continuous_variables_vectors_len] = my_atof(function_distance_str); //getting the start of the force_density
                if(vector_force_density_pos[all_continuous_variables_vectors_len] > barra.size)vector_force_density_pos[all_continuous_variables_vectors_len] = barra.size;
                if(vector_force_density_pos[all_continuous_variables_vectors_len] < 0)vector_force_density_pos[all_continuous_variables_vectors_len] = 0;
                free(function_distance_str);

                printf("\n\n");

                printf(" Escreva sua funcao carga (ex: 2x^3/5 - x que seria (2(x^3)/5) - x )  :  ");
                function_str = str_validation(MAX_FUNCTION_LEN + 1);
                vector_of_functions[all_continuous_variables_vectors_len] = function_str; // getting and saving the force_density function
                printf("\n\n");

                printf(" Escreva o limite inferior de integracao :  ");
                inf_lim_str = str_validation(MAX_FUNCTION_LEN + 1);
                vector_inf_lims[all_continuous_variables_vectors_len] = my_atof(inf_lim_str); // getting and saving the inferior limit of the force_density integration (to the force calculation)
                free(inf_lim_str);
                printf("\n\n");

                printf(" Escreva o limite superior de integracao  :  ");
                sup_lim_str = str_validation(MAX_FUNCTION_LEN + 1);    
                vector_sup_lims[all_continuous_variables_vectors_len] = my_atof(sup_lim_str); // getting and saving the superior limit of the force_density integration (to the force calculation)
                free(sup_lim_str);
                printf("\n\n");

                //getting function centroid considering bar coordinates /max centroid considering bar coordinates  if the (force_density_pos + (sup_lim - inf_lim)) exceeds the bar length
                //And fixing the superior limit if needed
                vector_centroids_func[all_continuous_variables_vectors_len] = force_distribution_validation(barra.size,vector_force_density_pos[all_continuous_variables_vectors_len],function_str,
                                                                                        vector_inf_lims[all_continuous_variables_vectors_len],&vector_sup_lims[all_continuous_variables_vectors_len]);
                //getting total force 
                vector_forces_func[all_continuous_variables_vectors_len] = def_integral_value(function_str,vector_inf_lims[all_continuous_variables_vectors_len],vector_sup_lims[all_continuous_variables_vectors_len]); 

                // getting moment done by the force * centroid 
                vector_moments_func[all_continuous_variables_vectors_len] = vector_forces_func[all_continuous_variables_vectors_len] * vector_centroids_func[all_continuous_variables_vectors_len];

                // saving information that all vectors went up by one size of its type
                all_continuous_variables_vectors_len++;
                while(1)
                {
                    printf(" Quer colocar mais funcoes carga? (digite S ou N) : ");
                    user_confirmation = str_validation(USER_CHAR + 1);
                    
                    if( (user_confirmation[0] == 's' || user_confirmation[0] == 'S'))break;
                    if(user_confirmation[0] == 'n' || user_confirmation[0] == 'N')
                    {
                        user_wanna_quit = 1;
                        break;
                    }
                    free(user_confirmation);
                    printf("\n\n");
                }
                free(user_confirmation);

                system("cls");

            }
            for(int i = 0; i < all_continuous_variables_vectors_len; i++)
            {
                printf(" A funcao de distribuicao de carga e : %s\n",vector_of_functions[i]);
                printf(" O limite inferior e : %.4f\n",vector_inf_lims[i]);
                printf(" O limite superior e : %.4f\n",vector_sup_lims[i]);
                printf(" A posicao do Centroide na Barra e : %.4f\n",vector_centroids_func[i]);
                printf(" A forca e : %.4f\n",vector_forces_func[i]);
                printf(" O Inicio da Distribuicao e : %.4f\n",vector_force_density_pos[i]);
                printf(" O momento e : %.4f\n",vector_moments_func[i]);
                printf("\n\n");
            }
            printf("\n   Pressione 'ENTER' para continuar.\n");
            
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(GetChar, 1 + 1 ,stdin); //Gets string

        }

        if(userOp == RESULTADO) actions_chosen = 1;
        
        if(userOp < FORCA || userOp > RESULTADO)print_UserOp_validation();

    }

    //plotar grafico e bla bla bla 

    if(opApoio1 == APOIO_SIMPLES && opApoio2 == APOIO_SIMPLES)
    {
        if(all_continuous_variables_vectors_len == 0)
        {
            double total_force_on_bar = 0;

            // Vectors that will be used to print the Force graph
            // times 2, because every force needs a u(x) (Heaviside function) to represent it
            // so in the same point we need two distinct values, so that we can simulate a u(x) function
            
            double x_discrete_force[2*(all_discrete_variables_vectors_len+1)];     
            double y_force_discrete[2*(all_discrete_variables_vectors_len+1)];

            // Vectors that will be used to print the Moment graph
            double x_discrete_moment[all_discrete_variables_vectors_len+2];
            double y_moment_discrete[all_discrete_variables_vectors_len+2];

            // Structs that will sort the Forces and Moments based on its distance
            POINT vector_of_moment_points[all_discrete_variables_vectors_len+1];
            POINT vector_of_force_points[all_discrete_variables_vectors_len+ 1];

            int i = 0;
            // Sum Of Reaction Forces caused by the forces
            for(; i < all_discrete_variables_vectors_len; i++)total_force_on_bar += -point_force[i];

            //Calculating Force on the Right and Left Apoio Simples
            i = 0;
            for(; i < all_discrete_variables_vectors_len; i++)Apoio_simples_R.force_y += -(point_force[i] * (point_force_distance[i] - Apoio_simples_L.distance));
            Apoio_simples_R.force_y /= Apoio_simples_R.distance;

            Apoio_simples_L.force_y = total_force_on_bar - Apoio_simples_R.force_y; 

            // Reaction Moments caused by the Pure Moments
            // There is no need for one more memory space on the moment vectors because of the Pure Moment
            // The explanation is that, the total moment will be 0 in the end 
            i = 0;
            for(; i < pure_moment_len; i++) Apoio_simples_L.moment_y += -point_pure_moment[i];

                //Discrete Momento Fletor
            
            //First Moment and Distance Value
            vector_of_moment_points[0].x = 0;
            vector_of_moment_points[0].y = 0;

            // Adding Moment Values to be sorted by their distances
            i = 1;
            for(; i < all_discrete_variables_vectors_len + 1; i++)
            {
                vector_of_moment_points[i].x = point_force_distance[i-1];
                vector_of_moment_points[i].y = point_moment[i-1];
                printf(" x : %f |  y: %f \n", vector_of_moment_points[i].x, vector_of_moment_points[i].y);
            }
            printf("\n\n");

            // "qsort()" sorts all the Moment Values, based on their distances
            qsort(vector_of_moment_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

            // Storing Sorted Moment Values and Their distances
            // To Plot the Moment Graph The Moment Value it's delayed by one loop, while it´s distance dont
            // It Works because when we go to the next distance, the peak moment value (old value) occurs in that distance
            // That's why it´s delayed 

            // As the program goes to the bar sections, we add the forces of the sections
            double Apoio_simples_resultant_force = Apoio_simples_L.force_y;
            double Apoio_simples_resultant_moment = 0;
            double Apoio_simples_add_moment = 0;

            i = 0;
            for(; i < all_discrete_variables_vectors_len + 1; i++)
            {
                if(i > 0)
                {
                    x_discrete_moment[i] = vector_of_moment_points[i].x;

                    if(i > 1) Apoio_simples_add_moment +=  -vector_of_moment_points[i-1].y;
                    Apoio_simples_resultant_moment  = Apoio_simples_resultant_force * x_discrete_moment[i] + Apoio_simples_add_moment;
            
                    y_moment_discrete[i] = Apoio_simples_resultant_moment ;

                    //printf("Forca Resultante na Secao : %f\n",Apoio_simples_resultant_force );
                    //printf("Momento adicionado na Secao : %f\n",Apoio_simples_add_moment );
                    printf(" x : %f |  y: %f \n", x_discrete_moment[i], y_moment_discrete[i]);
                    //printf("Momento Resultante na Secao : %f\n\n",Apoio_simples_resultant_moment);

                    Apoio_simples_resultant_force += (vector_of_moment_points[i].y/vector_of_moment_points[i].x);
                    
                }
                else
                {
                    x_discrete_moment[i] = vector_of_moment_points[i].x;
                    y_moment_discrete[i] = vector_of_moment_points[i].y;
                    printf(" x : %f |  y: %f \n\n", x_discrete_moment[0], y_moment_discrete[0]); 
                }
            }
            //Last Moment Value and Distance 
            x_discrete_moment[i] = barra.size;
            y_moment_discrete[i] = 0;
            printf(" x : %f |  y: %f \n", x_discrete_moment[i], y_moment_discrete[i]); 
            printf("\n\n");


                //Discrete Forca Cortante
            
            //First Force and Distance Value
            vector_of_force_points[0].x = 0;
            vector_of_force_points[0].y = Apoio_simples_L.force_y;

            int j = 1;
            // Adding Force Values to be sorted by their distances
            for(; j < all_discrete_variables_vectors_len+1; j++)
            {
                vector_of_force_points[j].x = point_force_distance[j-1];
                vector_of_force_points[j].y = point_force[j-1];
            }
            
            // "qsort()" sorts all the Moment Values, based on their distances
            qsort(vector_of_force_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

            // Storing Sorted Forces Values and Their distances
            // But Forces Values need two points in the same distance when Force changes
            // Because the Force graph works like a sum of Heaviside functions ("u(x)")

            j = 0;
            for(; j < all_discrete_variables_vectors_len + 1; j++)
            {
                if(j > 0)
                {
                    // Fazendo um Degrau (colocando 2 valores diferentes no mesmo ponto)
                    x_discrete_force[(2*j)-1] =  vector_of_force_points[j].x;
                    y_force_discrete[(2*j)-1] = y_force_discrete[(2*j) - 2];

                    
                    x_discrete_force[2*j] = vector_of_force_points[j].x;

                    Apoio_simples_L.force_y += vector_of_force_points[j].y;
                    y_force_discrete[2*j] = Apoio_simples_L.force_y ;

                    //printf(" x : %f |  y: %f \n",x_discrete_force[2*i - 1],y_force_discrete[2*i - 1]);
                    //printf(" x : %f |  y: %f \n",x_discrete_force[2*i],y_force_discrete[2*i]);

                }
                else
                {
                    x_discrete_force[j] = vector_of_force_points[j].x;
                    y_force_discrete[j] = vector_of_force_points[j].y;
                    //printf(" x : %f |  y: %f \n",x_discrete_force[i],y_force_discrete[i]);
                }
                
            }
            // Last Force Value (it happens because there's two supports one on each edge )
            if(j > 0)
            {
                x_discrete_force[2*j-1] = barra.size;
                y_force_discrete[2*j-1] = y_force_discrete[2*(j-1)];
            }

            //printf(" x : %f |  y: %f \n",x_discrete_force[i],y_force_discrete[i]);
            //printf("\n\n");

            //for(int k = 0; k < 2*(all_discrete_variables_vectors_len + 1) ; k++)
            //{
            //    printf(" x : %f |  y: %f \n",x_discrete_force[k],y_force_discrete[k]);      
            //}

            //PLOTTING GRAPH
            RGBABitmapImageReference* imageRef1 = CreateRGBABitmapImageReference();
            RGBABitmapImageReference* imageRef2 = CreateRGBABitmapImageReference();
            StringReference* ErrorMessage1;
            StringReference* ErrorMessage2;  

            DrawScatterPlot(imageRef1, 600, 400, x_discrete_force, 2*(all_discrete_variables_vectors_len + 1), y_force_discrete, 2*(all_discrete_variables_vectors_len + 1), ErrorMessage1);
            size_t lenght_f;
            double* pngData_f = ConvertToPNG(&lenght_f, imageRef1->image);
            WriteToFile(pngData_f, lenght_f, "forca_cortante.png");

            DrawScatterPlot(imageRef2, 600, 400, x_discrete_moment, all_discrete_variables_vectors_len + 2, y_moment_discrete, all_discrete_variables_vectors_len + 2, ErrorMessage2);
            size_t lenght_m;
            double* pngData_m = ConvertToPNG(&lenght_m, imageRef2->image);
            WriteToFile(pngData_m, lenght_m, "momento_fletor.png");
        }

        if(all_discrete_variables_vectors_len == 0)
        {

        }

    }
    
    if(opApoio1 == ENGASTE && opApoio2 == LIVRE || opApoio1 == LIVRE && opApoio2 == ENGASTE)
    {

        if(all_continuous_variables_vectors_len == 0)
        {
            // Vectors that will be used to print the Force graph
            double x_discrete_force[(2*all_discrete_variables_vectors_len)+1];     
            double y_discrete_force[(2*all_discrete_variables_vectors_len)+1];

            int theres_a_pure_moment = 0;
            if(pure_moment_len > 0)theres_a_pure_moment++;

            // Vectors that will be used to print the Moment graph
            double x_discrete_moment[all_discrete_variables_vectors_len+ 1 + theres_a_pure_moment];
            double y_discrete_moment[all_discrete_variables_vectors_len+ 1 + theres_a_pure_moment];

            // Structs that will sort the Forces and Moments based on its distance
            POINT vector_of_moment_points[all_discrete_variables_vectors_len+1];
            POINT vector_of_force_points[all_discrete_variables_vectors_len+1];

            int i = 0;
            // Reaction Forces and Moments caused by the forces

            i = 0;
            for(; i < all_discrete_variables_vectors_len; i++)
            {
                Engaste.moment_y += -point_moment[i];
                Engaste.force_y += -point_force[i];
            }
            //printf("-------------VALORES NO ENGASTE-------------\n");
            //printf("Momento do Engaste : %f\n",Engaste.moment_y);
            //printf("Forca do Enagste : %f \n",Engaste.force_y);

            // Reaction Moments caused by the Pure Moments
            i = 0;
            for(; i < pure_moment_len; i++)Engaste.moment_y += -point_pure_moment[i];
            //if(theres_a_pure_moment == 1)printf("Momento do Engaste Apos Adicao Dos Momentos Puros: %f\n",Engaste.moment_y);
            //printf("\n\n\n");
                
                //Discrete Momento Fletor
            
            // First Moment and Distance Value
            vector_of_moment_points[0].x = 0;
            vector_of_moment_points[0].y = Engaste.moment_y;

            // Adding Moment Values to be sorted by their distances
            i = 1;
            for(; i < all_discrete_variables_vectors_len+1; i++)
            {
                vector_of_moment_points[i].x = point_force_distance[i-1];
                vector_of_moment_points[i].y = point_moment[i-1];
            }

            // "qsort()" sorts all the Moment Values, based on their distances
            qsort(vector_of_moment_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

            // Storing Sorted Moment Values and Their distances
            i = 0;
            for(; i < all_discrete_variables_vectors_len + 1; i++)
            {
                x_discrete_moment[i] = vector_of_moment_points[i].x;
                if(i > 0)Engaste.moment_y += vector_of_moment_points[i].y;
                y_discrete_moment[i] = Engaste.moment_y;
            }
            if(theres_a_pure_moment == 1)
            {
                x_discrete_moment[i] = barra.size;
                y_discrete_moment[i] = Engaste.moment_y;
            }
            //printf("-------------VALORES DE MOMENTOS ORDENADOS-------------\n");
            //i = 0;
            //for(;i < all_discrete_variables_vectors_len + 1 + theres_a_pure_moment; i++)
            //{
            //    printf("Distancia : %f\n",x_discrete_moment[i]);
            //    printf("Momento : %f \n\n",y_discrete_moment[i]);        
            //}
            //printf("\n\n\n");

                //Discrete Forca Cortante

            int j = 0;
            //First Force and Distance Value
            vector_of_force_points[0].x = 0;
            vector_of_force_points[0].y = Engaste.force_y;

            j = 1;
            // Adding Force Values to be sorted
            for(; j < all_discrete_variables_vectors_len+1; j++)
            {
                vector_of_force_points[j].x = point_force_distance[j-1];
                vector_of_force_points[j].y = point_force[j-1];
            }

            // "qsort()" sorts all the Forces Values, based on their distances
            qsort(vector_of_force_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

            // Storing Sorted Forces Values and Their distances
            // But Forces Values need two points in the same distance when Force changes
            // Because the force graph works like a sum of Heaviside functions ("u(x)")

            j = 0;
            for(; j < all_discrete_variables_vectors_len + 1; j++)
            {
                if(j > 0)
                {
                    // Fazendo um Degrau (colocando 2 valores diferentes no mesmo ponto)
                    x_discrete_force[(2*j)-1] = vector_of_force_points[j].x;
                    y_discrete_force[(2*j)-1] = y_discrete_force[(2*j) - 2];

                    
                    x_discrete_force[2*j] = vector_of_force_points[j].x;

                    Engaste.force_y += vector_of_force_points[j].y;
                    y_discrete_force[2*j] = Engaste.force_y ;

                }
                else
                {
                    x_discrete_force[j] = vector_of_force_points[j].x;
                    y_discrete_force[j] = vector_of_force_points[j].y;
                }  
            }


            //PLOTTING GRAPH
            RGBABitmapImageReference* imageRef1 = CreateRGBABitmapImageReference();
            RGBABitmapImageReference* imageRef2 = CreateRGBABitmapImageReference();
            StringReference* ErrorMessage1;
            StringReference* ErrorMessage2;  

            DrawScatterPlot(imageRef1, 600, 400, x_discrete_force, (2*all_discrete_variables_vectors_len) + 1,
                                                y_discrete_force, (2*all_discrete_variables_vectors_len) + 1, ErrorMessage1);
            size_t lenght_f;
            double* pngData_f = ConvertToPNG(&lenght_f, imageRef1->image);
            WriteToFile(pngData_f, lenght_f, "forca_cortante.png");

            DrawScatterPlot(imageRef2, 600, 400, x_discrete_moment, all_discrete_variables_vectors_len + 1 + theres_a_pure_moment,
                                                y_discrete_moment, all_discrete_variables_vectors_len + 1 + theres_a_pure_moment, ErrorMessage2);
            size_t lenght_m;
            double* pngData_m = ConvertToPNG(&lenght_m, imageRef2->image);
            WriteToFile(pngData_m, lenght_m, "momento_fletor.png");
        }

        if(all_discrete_variables_vectors_len == 0)
        {
            // Vectors that will be used to print the Force graph
            double x_continuous_force[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1];     
            double y_continuous_force[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1];

            int theres_a_pure_moment = 0;
            if(pure_moment_len > 0)theres_a_pure_moment++;

            // Vectors that will be used to print the Moment graph
            double x_continuous_moment[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1 + theres_a_pure_moment];
            double y_continuous_moment[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1 + theres_a_pure_moment];

            // Structs that will sort the Forces and Moments based on its distance
            POINT vector_of_moment_points[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) +1];
            POINT vector_of_force_points[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) +1];

            int i = 0;
            // Reaction Forces and Moments caused by the forces

            i = 0;
            for(; i <  all_continuous_variables_vectors_len; i++)
            {
                Engaste.moment_y += -vector_moments_func[i];
                Engaste.force_y += -vector_forces_func[i];
            }
            //printf("-------------VALORES NO ENGASTE-------------\n");
            //printf("Momento do Engaste : %f\n",Engaste.moment_y);
            //printf("Forca do Enagste : %f \n",Engaste.force_y);

            // Reaction Moments caused by the Pure Moments
            i = 0;
            for(; i < pure_moment_len; i++)Engaste.moment_y += -point_pure_moment[i];
            //if(theres_a_pure_moment == 1)printf("Momento do Engaste Apos Adicao Dos Momentos Puros: %f\n",Engaste.moment_y);
            //printf("\n\n\n");
                
                //Continuous Momento Fletor
            
            // First Moment and Distance Value
            vector_of_moment_points[0].x = 0;
            vector_of_moment_points[0].y = Engaste.moment_y;

            // Adding Moment Values to be sorted by their distances
            for(int k = 0; k < all_continuous_variables_vectors_len; k++)
            {
                i = 1;
                double function_distance_parser = (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                double function_force_parser = 0;
                for(; i < CDW_N_OF_POINTS ; i++)
                {
                    vector_of_moment_points[i].x = vector_force_density_pos[k] + function_distance_parser;
                    
                    function_force_parser = def_integral_value(vector_of_functions[k],vector_inf_lims[k],vector_inf_lims[k] + function_distance_parser);
                    vector_of_moment_points[i].y = vector_of_moment_points[i].x * function_distance_parser;

                    function_force_parser += (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                }
            }

            // "qsort()" sorts all the Moment Values, based on their distances
            qsort(vector_of_moment_points,(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1,sizeof(POINT),cmp_point);

            // Storing Sorted Moment Values and Their distances
            i = 0;
            for(; i < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1; i++)
            {
                x_continuous_moment[i] = vector_of_moment_points[i].x;
                if(i > 0)Engaste.moment_y += vector_of_moment_points[i].y;
                y_continuous_moment[i] = Engaste.moment_y;
            }
            if(theres_a_pure_moment == 1)
            {
                x_continuous_moment[i] = barra.size;
                y_continuous_moment[i] = Engaste.moment_y;
            }

                //Continuous Forca Cortante

            int j = 0;
            //First Force and Distance Value
            vector_of_force_points[0].x = 0;
            vector_of_force_points[0].y = Engaste.force_y;

            j = 1;
            // Adding Force Values to be sorted
            for(; j < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1; j++)
            {
                vector_of_force_points[j].x = point_force_distance[j-1];
                vector_of_force_points[j].y = point_force[j-1];
            }

            // "qsort()" sorts all the Forces Values, based on their distances
            qsort(vector_of_force_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

            // Storing Sorted Forces Values and Their distances
            // But Forces Values need two points in the same distance when Force changes
            // Because the force graph works like a sum of Heaviside functions ("u(x)")

            j = 0;
            for(; j < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1; j++)
            {
                if(j > 0)
                {
                    // Fazendo um Degrau (colocando 2 valores diferentes no mesmo ponto)
                    x_continuous_force[(2*j)-1] = vector_of_force_points[j].x;
                    y_continuous_force[(2*j)-1] = y_continuous_force[(2*j) - 2];

                    
                    x_continuous_force[2*j] = vector_of_force_points[j].x;

                    Engaste.force_y += vector_of_force_points[j].y;
                    y_continuous_force[2*j] = Engaste.force_y ;

                }
                else
                {
                    x_continuous_force[j] = vector_of_force_points[j].x;
                    y_continuous_force[j] = vector_of_force_points[j].y;
                }  
            }


            //PLOTTING GRAPH
            RGBABitmapImageReference* imageRef1 = CreateRGBABitmapImageReference();
            RGBABitmapImageReference* imageRef2 = CreateRGBABitmapImageReference();
            StringReference* ErrorMessage1;
            StringReference* ErrorMessage2;  

            DrawScatterPlot(imageRef1, 600, 400, x_continuous_force, (CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1,
                                                y_continuous_force, (CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1, ErrorMessage1);
            size_t lenght_f;
            double* pngData_f = ConvertToPNG(&lenght_f, imageRef1->image);
            WriteToFile(pngData_f, lenght_f, "forca_cortante.png");

            DrawScatterPlot(imageRef2, 600, 400, x_continuous_moment, (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1 + theres_a_pure_moment,
                                                y_continuous_moment, (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1 + theres_a_pure_moment, ErrorMessage2);
            size_t lenght_m;
            double* pngData_m = ConvertToPNG(&lenght_m, imageRef2->image);
            WriteToFile(pngData_m, lenght_m, "momento_fletor.png");
        }

    }
    
    // Liberando Memoria (Progama Ira Fechar)
    if(all_discrete_variables_vectors_len > 0)
    {
        free(point_force);
        free(point_force_distance);
        free(point_moment);
    }
    if(pure_moment_len > 0)
    {
        free(point_pure_moment);
        free(pure_moment_distance);
    }
    if(all_continuous_variables_vectors_len > 0)
    {
        free(vector_inf_lims);
        free(vector_sup_lims);
        free(vector_forces_func);
        free(vector_centroids_func);
        free(vector_moments_func);
        free(vector_force_density_pos);
    }
    if(vector_of_functions != NULL)
    {
        for(int i = 0; i < all_continuous_variables_vectors_len; i++)
        {
            if(vector_of_functions[i] != NULL)free(vector_of_functions[i]);
        }
        free(vector_of_functions);    
    }
    
    return 0;
}
