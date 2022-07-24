#include "menu.h"

void printTela_1()
{
    // Tela 1:
    system("cls");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forcas internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Pressione 'ENTER' para criar uma situacao;\n");
    printf(" =====================================================================\n");
    system("pause");
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
    system("pause");   
}

void print_Apoios_validation(char** tiposApoios, int apoio1, int apoio2, double pos_apoio2)
{
    system("cls");
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
    system("pause");
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
    system("pause");   
}

int main ()
{   // Declaracao de variaveis:
                                    // Menu Variables
    BAR barra;
    int opApoio1 = 0, opApoio2 = 0, valida = 0, op1 = 0, op2 = 0;
    double posApoio2  = 0, bar_size  = 0;
    char* tiposApoios[] = {"Apoio Simples", "Engaste", "Livre"};
    char userInput[USER_OP + 1];

                                    //CALCULOS
    int result = 0, userOp = 0;

                                    // Point Variable (Varíaveis Pontuais (ou seja Discretas, diferente da distruibuição de cargas))
    
    double point_force  = 0 , point_momento  = 0, distance = 0;

                                    // Continue Variables (Variáveis de Carga Distribuida)

    double force_density_pos = 0;
    int all_vectors_len = 0;
    double* vector_inf_lims = NULL;
    double* vector_sup_lims = NULL;
    double* vector_forces_func = NULL;
    double* vector_centroids_func = NULL;
    double* vector_moments_func = NULL;
    char** vector_of_functions = NULL;

    // User Input
    char* function_str = NULL;
    char* distance_str = NULL;
    char* inf_lim_str = NULL;
    char* sup_lim_str = NULL;
    char* user_confirmation = NULL;



    // Program Start
    printTela_1();
    printTela_2();

    while (op1 == 0)
    {
        printf("  Qual o tipo do apoio localizado na posicao x = 0 (Extremidade Esquerda) ? :    ");
        
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, USER_OP + 1  ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
        
        opApoio1 = my_atoi(userInput);

        if(opApoio1 != LIVRE)
        {
            // Restricao dos tipos de apoio + selecao do segundo apoio
            while (valida == 0)
            {
                printf("\n\n  Qual o tipo do segundo apoio? :    ");
                
                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, USER_OP + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
                
                opApoio2 = my_atoi(userInput);

                if((opApoio1 == ENGASTE) && (opApoio2 == ENGASTE)) printEng_Eng_validation();
                else valida = 1;
            }
            posApoio2 = bar_size; // por enquanto vamos trabalhar com apoios fixos nas extremidades
            /*printf("\n\n Qual a posicao em 'x' do segundo apoio?");
            scanf("%f", &posicao);*/

            print_Apoios_validation(tiposApoios,opApoio1,opApoio2,posApoio2);
            //printf("   Os dados acima estão corretos? [S / N]\n");

            //Fazer isso depois! OBS: scanf assim NAO VAI FUNCIONAR!!!!

            //scanf("%c", &op2);

            /*if(op2 == 'S' || op2 == 's') op1 = 1;
            else void print_posApoio2_validation(); */
        }
        else
        {
            printf("\n O Engaste foi colocado na extremidade esquerda da Barra \n");
            system("pause");
        }
        op1 = 1;

    }
    
    while(result == 0)
    {
        printTela_3();
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, USER_OP + 1  ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
        userOp = my_atoi(userInput);

        if(userOp == FORCA)
        {

        }
        if(userOp == MOMENTO)
        {

        }
        if(userOp == DISTRIBUICAO_DE_CARGA)
        {
            system("cls");
            printf("\n\n\n");
            printf(" OBS: Escreva numeros decimais com '.' (ex : 0.3 , 0.2465)\n\n");

            barra.size = 1; //DEPOIS TIRAR

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

                printf(" Escreva a distancia de onde sua funcao de carga partira (levando em consideracao que a coordenada x = 0, esta situada a esquerda da barra)  :  ");

                distance_str = str_validation(MAX_FUNCTION_LEN + 1);
                force_density_pos = my_atof(distance_str); //getting the start of the force_density
                free(distance_str);

                printf("\n\n");

                printf(" Escreva sua funcao carga (ex: 2x^3/5 - x que seria (2(x^3)/5) - x )  :  ");
                function_str = str_validation(MAX_FUNCTION_LEN + 1);
                vector_of_functions[all_vectors_len] = function_str; // getting and saving the force_density function
                printf("\n\n");

                printf(" Escreva o limite inferior de integracao :  ");
                inf_lim_str = str_validation(MAX_FUNCTION_LEN + 1);
                vector_inf_lims[all_vectors_len] = my_atof(inf_lim_str); // getting and saving the inferior limit of the force_density integration (to the force calculation)
                free(inf_lim_str);
                printf("\n\n");

                printf(" Escreva o limite superior de integracao  :  ");
                sup_lim_str = str_validation(MAX_FUNCTION_LEN + 1);    
                vector_sup_lims[all_vectors_len] = my_atof(sup_lim_str); // getting and saving the superior limit of the force_density integration (to the force calculation)
                free(sup_lim_str);
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
                    printf(" Quer colocar mais funcoes carga? (digite S ou N) : ");
                    user_confirmation = str_validation(USER_CHAR + 1);
                    
                    if( (user_confirmation[0] == 's' || user_confirmation[0] == 'S'))break;
                    if(user_confirmation[0] == 'n' || user_confirmation[0] == 'N')
                    {
                        user_wanna_quit = 1;
                        break;
                    }
                    free(user_confirmation);
                }
                system("cls");

            }
            for(int i = 0; i < all_vectors_len; i++)
            {
                printf(" A funcao de distribuicao de carga e : %s\n",vector_of_functions[i]);
                printf(" O limite inferior e : %.4f\n",vector_inf_lims[i]);
                printf(" O limite superior e : %.4f\n",vector_sup_lims[i]);
                printf(" A posicao do Centroide na Barra e : %.4f\n",vector_centroids_func[i]);
                printf(" A forca e : %.4f\n",vector_forces_func[i]);
                printf(" O Inicio da Distribuicao e : %.4f\n",vector_centroids_func[i] - my_math_function_centroid(vector_of_functions[i],vector_inf_lims[i],vector_sup_lims[i]));
                printf(" O momento e : %.4f\n",vector_moments_func[i]);
                printf("\n\n");
            }
            system("pause");

        }

        if(userOp == RESULTADO) result = 1;
        
        if(userOp < FORCA || userOp > RESULTADO)print_UserOp_validation();

    }

    //plotar grafico e bla bla bla 
    
    
    // Liberando Memoria (Progama Ira Fechar)
    if(all_vectors_len > 0)
    {
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
