#include "menu.h"
#include "pbPlots.h"
#include "supportLib.h"


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
    system("clear");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forcas internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Pressione 'ENTER' para criar uma situacao;\n");
    printf(" =====================================================================\n\n");
}

void printTela_2()
{
    // Tela 2:
    system("clear");
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

void print_Apoios_validation(char** tiposApoios, int apoio1, int apoio2, double pos_apoio2)
{
    system("clear");
    printf(" =====================================================================\n");
    printf(" ============================ Seus Apoios ============================\n");
    printf("   Tipo do primeiro apoio: %s\n", tiposApoios[apoio1-1]);
    printf("   Tipo do segundo apoio: %s\n", tiposApoios[apoio2-1]);
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

void printTela_3()
{
    // Tela 3:
    system("clear");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forcas internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Dentre os seguintes tipos de acoes externas, escolha uma:\n");
    printf("     1. Forca\n");
    printf("     2. Momento\n");
    printf("     3. Distribuicao de Carga\n");
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
    printf("   Nao eh possivel utilizar engaste com apoio simples. Situacao estaticamente indetermindada\n");
    printf("   Pressione 'ENTER' para continuar.\n");
    printf(" =====================================================================\n");

}
int main ()
{   // Declaracao de variaveis:
                                    // Menu Variables
    BAR barra;
    ENGST Engaste;
    APOIO_S Apoio_simples;
    int opApoio1 = 0, opApoio2 = 0, valida = 0, op1 = 0, op2 = 0;
    double posApoio2  = 0, bar_size  = 0;
    char* tiposApoios[] = {"Apoio Simples", "Engaste", "Livre"};
    char userInput[30 + 1];
    char GetChar[1 + 1];

                                    //CALCULOS
    int result = 0, userOp = 0;

                                    // Point Variable (Varíaveis Pontuais (ou seja Discretas, diferente da distruibuição de cargas))
    
    //double point_force  = 0 , point_momento  = 0, distance = 0;

    int all_discrete_variables_vectors_len = 0;
    double* point_force = NULL;
    double* point_moment = NULL;
    double* point_force_distance = NULL;
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

    while (op1 == 0)
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

        if(opApoio1 != LIVRE)
        {
            // Restricao dos tipos de apoio + selecao do segundo apoio
            while (valida == 0)
            {
                printf("\n\n  Qual o tipo do segundo apoio? :    ");
                
                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30+1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
                
                opApoio2 = my_atoi(userInput);

                if((opApoio1 == ENGASTE) && (opApoio2 == ENGASTE)) printEng_Eng_validation();
                
                else if((opApoio1 == APOIO_SIMPLES) && (opApoio2 == LIVRE)) print_UserOp_validation02();
               
                else if ((opApoio1 == ENGASTE && opApoio2 == APOIO_SIMPLES) || (opApoio1 == APOIO_SIMPLES && opApoio2 == ENGASTE)) print_Uservalidation03();

                else valida = 1;
                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(GetChar, 1 + 1 ,stdin); //Gets string
            }
            posApoio2 = barra.size; 

            print_Apoios_validation(tiposApoios,opApoio1,opApoio2,posApoio2);
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
        op1 = 1;

    }
    

    while(result == 0)
    {
        printTela_3();
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, 30 + 1  ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
        userOp = my_atoi(userInput);

        if(userOp == FORCA)
        {
            system("clear");
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
                system("clear");
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
            system("clear");
            printf("\n\n\n");
            printf(" OBS: Escreva numeros decimais com '.' (ex : 0.3 , 0.2465)\n\n");
            
            int user_wanna_quit = 0;

            while(user_wanna_quit == 0)
            {
                point_force = malloc_more_double_space(point_force, all_discrete_variables_vectors_len);
                point_moment = malloc_more_double_space(point_moment, all_discrete_variables_vectors_len);
                point_force_distance = malloc_more_double_space(point_force_distance, all_discrete_variables_vectors_len);

                printf("Escreva a localizacao da sua momento na barra  :  ");
                distance_str = str_validation(MAX_FUNCTION_LEN +1);
                point_force_distance[all_discrete_variables_vectors_len] = my_atof(distance_str);
                if(point_force_distance[all_discrete_variables_vectors_len] > barra.size)point_force_distance[all_discrete_variables_vectors_len] = barra.size;
                if(point_force_distance[all_discrete_variables_vectors_len] < 0)point_force_distance[all_discrete_variables_vectors_len] = 0;
                if(distance_str != NULL) free(distance_str);
                printf("\n\n");

                printf("Escreva a intensidade do momento  (OBS : O sentido positivo e o horario)  :  ");
                moment_str = str_validation(MAX_FUNCTION_LEN +1);
                point_moment[all_discrete_variables_vectors_len] = my_atof(moment_str);
                if(moment_str != NULL) free(moment_str);
                printf("\n\n");

                point_force[all_discrete_variables_vectors_len] = point_moment[all_discrete_variables_vectors_len] / point_force_distance[all_discrete_variables_vectors_len];
                
                all_discrete_variables_vectors_len++; 
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
                system("clear");
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
        if(userOp == DISTRIBUICAO_DE_CARGA)
        {
            system("clear");
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

                system("clear");

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

        if(userOp == RESULTADO) result = 1;
        
        if(userOp < FORCA || userOp > RESULTADO)print_UserOp_validation();

    }

    //plotar grafico e bla bla bla 

    if(opApoio1 == APOIO_SIMPLES && opApoio2 == APOIO_SIMPLES)
    {
        double x_discrete_moment[all_discrete_variables_vectors_len+2];
        double y_moment_discrete[all_discrete_variables_vectors_len+2];

        double x_discrete_force[2*(all_discrete_variables_vectors_len+1)];     
        double y_force_discrete[2*(all_discrete_variables_vectors_len+1)];
        

        POINT vector_of_moment_points[all_discrete_variables_vectors_len+1];
        POINT vector_of_force_points[all_discrete_variables_vectors_len+ 1];



        for(int i = 0; i < all_discrete_variables_vectors_len; i++)
        {
            Apoio_simples.moment_y += -point_moment[i]/2;
            Apoio_simples.force_y += -point_force[i]/2;
        }

            //Discrete Momento Fletor
        vector_of_moment_points[0].x = 0;
        vector_of_moment_points[0].y = 0;
        vector_of_moment_points[1].x = 0;
        vector_of_moment_points[1].y = Apoio_simples.moment_y;


        for(int i = 2; i < all_discrete_variables_vectors_len + 2; i++)
        {
            vector_of_moment_points[i].x = point_force_distance[i-2];
            vector_of_moment_points[i].y = point_moment[i-2];
        }

        qsort(vector_of_moment_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);
        vector_of_moment_points[1].x = vector_of_moment_points[2].x;

        for(int i = 0; i < all_discrete_variables_vectors_len + 2; i++)
        {
            x_discrete_moment[i] = vector_of_moment_points[i].x;
            Apoio_simples.moment_y += vector_of_moment_points[i].y;
            y_moment_discrete[i] = Apoio_simples.moment_y;
        }
        for(int i = 0; i < all_discrete_variables_vectors_len + 2; i++)
        {
            if(i < all_discrete_variables_vectors_len + 1)
            {
                x_discrete_moment[i] =  x_discrete_moment[i+1];
            }
        }


        //Discrete Forca Cortante

        vector_of_force_points[0].x = 0;
        vector_of_force_points[0].y = Apoio_simples.force_y;

        for(int i = 1; i < all_discrete_variables_vectors_len+1; i++)
        {
            vector_of_force_points[i].x = point_force_distance[i-1];
            vector_of_force_points[i].y = point_force[i-1];
        }

        qsort(vector_of_force_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

        int i = 0;
        for(; i < all_discrete_variables_vectors_len + 1; i++)
        {
            if(i > 0)
            {
                // Fazendo um Degrau (colocando 2 valores diferentes no mesmo ponto)
                x_discrete_force[(2*i)-1] =  vector_of_force_points[i].x;
                y_force_discrete[(2*i)-1] = y_force_discrete[(2*i) - 2];

                
                x_discrete_force[2*i] = vector_of_force_points[i].x;

                Apoio_simples.force_y += vector_of_force_points[i].y;
                y_force_discrete[2*i] = Apoio_simples.force_y ;

                printf(" x : %f |  y: %f \n",x_discrete_force[2*i - 1],y_force_discrete[2*i - 1]);
                printf(" x : %f |  y: %f \n",x_discrete_force[2*i],y_force_discrete[2*i]);

            }
            else
            {
                x_discrete_force[i] = vector_of_force_points[i].x;
                y_force_discrete[i] = vector_of_force_points[i].y;
                printf(" x : %f |  y: %f \n",x_discrete_force[i],y_force_discrete[i]);
            }
            
        }
        if(i > 0)
        {
            x_discrete_force[2*i-1] = barra.size;
            y_force_discrete[2*i-1] = y_force_discrete[2*(i-1)];
        }

        printf(" x : %f |  y: %f \n",x_discrete_force[i],y_force_discrete[i]);
        printf("\n\n");

        for(int k = 0; k < 2*(all_discrete_variables_vectors_len + 1) ; k++)
        {
            printf(" x : %f |  y: %f \n",x_discrete_force[k],y_force_discrete[k]);      
        }

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
    
    if(opApoio1 == ENGASTE && opApoio2 == LIVRE || opApoio1 == LIVRE && opApoio2 == ENGASTE)
    {
        double x_discrete_moment[all_discrete_variables_vectors_len+1];
        double y_moment_discrete[all_discrete_variables_vectors_len+1];

        double x_discrete_force[(2*all_discrete_variables_vectors_len)+1];     
        double y_force_discrete[(2*all_discrete_variables_vectors_len)+1];
        

        POINT vector_of_moment_points[all_discrete_variables_vectors_len+1];
        POINT vector_of_force_points[all_discrete_variables_vectors_len+1];



        for(int i = 0; i < all_discrete_variables_vectors_len; i++)
        {
            Engaste.moment_y += -point_moment[i];
            Engaste.force_y += -point_force[i];
        }

            //Discrete Momento Fletor
        vector_of_moment_points[0].x = 0;
        vector_of_moment_points[0].y = Engaste.moment_y;


        for(int i = 1; i < all_discrete_variables_vectors_len+1; i++)
        {
            vector_of_moment_points[i].x = point_force_distance[i-1];
            vector_of_moment_points[i].y = point_moment[i-1];
        }

        qsort(vector_of_moment_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

        for(int i = 0; i < all_discrete_variables_vectors_len + 1; i++)
        {
            x_discrete_moment[i] = vector_of_moment_points[i].x;
            Engaste.moment_y += vector_of_moment_points[i].y;
            y_moment_discrete[i] = Engaste.moment_y;
        }


        //Discrete Forca Cortante
        
        vector_of_force_points[0].x = 0;
        vector_of_force_points[0].y = Engaste.force_y;


        for(int i = 1; i < all_discrete_variables_vectors_len+1; i++)
        {
            vector_of_force_points[i].x = point_force_distance[i-1];
            vector_of_force_points[i].y = point_force[i-1];
        }

        qsort(vector_of_force_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

        for(int i = 0; i < all_discrete_variables_vectors_len + 1; i++)
        {
            if(i > 0)
            {
                // Fazendo um Degrau (colocando 2 valores diferentes no mesmo ponto)
                x_discrete_force[(2*i)-1] =  vector_of_force_points[i].x;
                y_force_discrete[(2*i)-1] = y_force_discrete[(2*i) - 2];

                
                x_discrete_force[2*i] = vector_of_force_points[i].x;

                Engaste.force_y += vector_of_force_points[i].y;
                y_force_discrete[2*i] = Engaste.force_y ;

            }
            else
            {
                x_discrete_force[i] = vector_of_force_points[i].x;
                y_force_discrete[i] = vector_of_force_points[i].y;
            }
            
        }




        
        /*
        double x_cord_continuous[all_continuous_variables_vectors_len + 1];
        double y_cord_force_continuous[all_continuous_variables_vectors_len + 1];
        double y_cord_moment_continuous[all_continuous_variables_vectors_len + 1];

        for(int j = 0; j < all_continuous_variables_vectors_len; j++)
        {
            Engaste.force_y += -vector_forces_func[j];
            Engaste.moment_y += -vector_moments_func[j];
            x_cord_continuous[j] = vector_force_density_pos[j];
            y_cord_force_continuous[j] = vector_forces_func[j];
            y_cord_moment_continuous[j] = vector_moments_func[j];
        }*/

        //PLOTTING GRAPH
        RGBABitmapImageReference* imageRef1 = CreateRGBABitmapImageReference();
        RGBABitmapImageReference* imageRef2 = CreateRGBABitmapImageReference();
        StringReference* ErrorMessage1;
        StringReference* ErrorMessage2;  

        DrawScatterPlot(imageRef1, 600, 400, x_discrete_force, (2*all_discrete_variables_vectors_len) + 1, y_force_discrete, (2*all_discrete_variables_vectors_len) + 1, ErrorMessage1);
        size_t lenght_f;
        double* pngData_f = ConvertToPNG(&lenght_f, imageRef1->image);
        WriteToFile(pngData_f, lenght_f, "forca_cortante.png");

        DrawScatterPlot(imageRef2, 600, 400, x_discrete_moment, all_discrete_variables_vectors_len + 1, y_moment_discrete, all_discrete_variables_vectors_len + 1, ErrorMessage2);
        size_t lenght_m;
        double* pngData_m = ConvertToPNG(&lenght_m, imageRef2->image);
        WriteToFile(pngData_m, lenght_m, "momento_fletor.png");


    }
    
    // Liberando Memoria (Progama Ira Fechar)
    if(all_discrete_variables_vectors_len > 0)
    {
        free(point_force);
        free(point_force_distance);
        free(point_moment);
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
