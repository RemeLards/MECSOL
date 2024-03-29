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
    system("cls");
    printf("=====================================================================\n");
    printf(" Agora escolha o tipo de perfis de viga.\n");
    printf("    1. Circular\n");
    printf("    2. Retangular\n");
    printf("    3. Triangular\n");
    printf("    4. Tipo U\n");
    printf("    5. Tipo H\n");
    printf("    6. Tipo I\n");
    printf("    7. Tipo T\n");
    printf(" =====================================================================\n\n");

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
{   
    // Declaracao de variaveis:
    
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
    char* tiposApoios[] = {"Apoio Simples", "Engaste", "Livre"};
    int tiposVigas = 0;
    char userInput[30 + 1];
    char GetChar[1 + 1];

    //VIGAS
    
    double beam_radius = 0;
    double beam_square = 0;
    double beam_side_1 = 0;
    double beam_side_2 = 0;
    double beam_side_3 = 0;
    double beam_height = 0;
    double beam_width = 0;
    double beam_thickness = 0;
    double x_centroid = 0;
    double y_centroid = 0;
    double x_moment = 0;
    double y_moment = 0;
    double x_centroid_aux1 = 0;
    double y_centroid_aux1 = 0;
    double x_moment_aux1 = 0;
    double y_moment_aux1 = 0;
    double x_centroid_aux2 = 0;
    double y_centroid_aux2 = 0;
    double x_moment_aux2 = 0;
    double y_moment_aux2 = 0;
    double x_centroid_aux3 = 0;
    double y_centroid_aux3 = 0;
    double x_moment_aux3 = 0;
    double y_moment_aux3 = 0;
    double area1 = 0;
    double area2 = 0;
    double area3 = 0;
    double y_distance1 = 0;
    double y_distance2 = 0;
    double y_distance3 = 0;
    double x_distance1 = 0;
    double x_distance2 = 0;
    double x_distance3 = 0;


                                    //CALCULOS
    int actions_chosen = 0, supports_chosen = 0, beam_chosen = 0, max_strain_done = 0;

                                    // Point Variable (Varíaveis Pontuais (ou seja Discretas, diferente da distruibuição de cargas))

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

                                    // Graph Vectors

    int theres_a_pure_moment = 0;

                                    //Discrete
    double* x_discrete_moment = NULL;
    double* y_discrete_moment = NULL;
    double* x_discrete_force = NULL;     
    double* y_discrete_force = NULL;
                                    //Continuous
    double* x_continuous_moment = NULL;
    double* y_continuous_moment = NULL;
    double* x_continuous_force = NULL;     
    double* y_continuous_force = NULL;
    

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

        if(opApoio1 >= APOIO_SIMPLES && opApoio1 <= LIVRE)
        {


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

                    if(opApoio2 >= APOIO_SIMPLES && opApoio2 <= LIVRE)
                    {
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

                    else
                    {
                        print_UserOp_validation();
                        fflush(stdin); //Cleaning Keyboard Buffer
                        fgets(GetChar, 1 + 1 ,stdin); //Gets string
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

        else
        {
            print_UserOp_validation();
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(GetChar, 1 + 1 ,stdin); //Gets string
        }

    }
    
    while (beam_chosen == 0)
    {
        print_tipos_de_perfis_de_vigas();

        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, 30 + 1 ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

        tiposVigas = my_atoi(userInput);
        if(tiposVigas >= CIRCULAR && tiposVigas <= TIPO_T)
        {
            if(tiposVigas == CIRCULAR)
            {
                printf("Entre com o valor do raio da viga em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_radius = my_atof(userInput);

                x_centroid = y_centroid = beam_radius;

                x_moment = y_moment = (PI*(beam_radius*beam_radius*beam_radius*beam_radius))/4;
            }
            else if(tiposVigas == RETANGULAR)
            {
                printf("Entre com o valore de altura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_height = my_atof(userInput);
                
                printf("Entre com o valor de largura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_width = my_atof(userInput);

                x_centroid = beam_width/2;
                y_centroid = beam_height/2;

                x_moment = beam_width*(beam_height*beam_height*beam_height)/12;
                y_moment = (beam_width*beam_width*beam_width)*beam_height/12;

            }
            else if(tiposVigas == TRIANGULAR)
            {
                printf("Entre com o valor do primeiro base do triangulo em metros: ");
                
                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");
                
                beam_width = my_atof(userInput);

                printf("Entre com o valor do segundo altura do triangulo em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_height= my_atof(userInput);

                y_centroid = beam_height/3;

                x_moment = (beam_width*(beam_height*beam_height*beam_height))/36;
            
            }
            else if(tiposVigas == TIPO_U)
            {
                printf("Entre com o valor de altura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_height = my_atof(userInput);

                printf("Entre com o valor da largura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_width = my_atof(userInput);

                printf("Entres com o valor da espessura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_thickness = my_atof(userInput);

                //VIGA U
                //CENTROIDE
                x_centroid_aux1 = beam_thickness/2;
                y_centroid_aux1 = beam_height/2;
                area1 = beam_height*beam_thickness;
                x_centroid_aux2 = beam_width/2;
                y_centroid_aux2 = beam_thickness/2;
                area2 = beam_thickness*(beam_width -(2*beam_thickness));
                x_centroid_aux3 = beam_width - (beam_thickness/2);
                //y_centroid_aux3 = y_centroid_aux1
                //area3 = area1

                x_centroid = ((x_centroid_aux1*area1) + (x_centroid_aux2*area2) + (x_centroid_aux3*area1))/(2*area1 + area2);
                y_centroid = ((2*y_centroid_aux1*area1) + ((y_centroid_aux2)*area2))/(2*area1 + area2);

                //MOMENTO
                y_distance1 = y_centroid_aux1 - y_centroid;
                y_distance2 = y_centroid_aux2 - y_centroid;
                //y_distance3 = y_centroid_aux1
                x_distance1 = x_centroid_aux1 - x_centroid;
                x_distance2 = x_centroid_aux2 - x_centroid;
                x_distance3 = x_centroid_aux3 - x_centroid;

                x_moment_aux1 = (beam_thickness*(beam_height*beam_height*beam_height)/12) + (area1*(y_distance1*y_distance1));
                y_moment_aux1 = (beam_height*(beam_thickness*beam_thickness*beam_thickness)/12) + (area1*(x_distance1*x_distance1));
                x_moment_aux2 = ((beam_width - (beam_thickness/2))*(beam_thickness*beam_thickness*beam_thickness)/12) + (area2*(y_distance2*y_distance2));
                y_moment_aux2 = (beam_thickness*((beam_width - (beam_thickness/2))*(beam_width - (beam_thickness/2))*(beam_width - (beam_thickness/2)))/12) + (area2*(x_distance2*x_distance2));
                //x_moment_aux3 = x_moment_aux1;
                y_moment_aux3 = (beam_height*(beam_thickness*beam_thickness*beam_thickness)/12) + (area1*(x_distance3*x_distance3));

                x_moment = (2*x_moment_aux1) + x_moment_aux2;
                y_moment = y_moment_aux1 + y_moment_aux2 + y_moment_aux3;

            }
            else if(tiposVigas == TIPO_H)
            {
                printf("Entre com o valor de altura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_height = my_atof(userInput);

                printf("Entre com o valor da largura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_width = my_atof(userInput);

                printf("Entre com o valor da espessura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_thickness = my_atof(userInput);

                //VIGA H
                //CENTROIDE
                x_centroid_aux1 = beam_thickness/2;
                y_centroid_aux1 = beam_height/2;
                area1 = beam_height*beam_thickness;
                x_centroid_aux2 = beam_width/2;
                y_centroid_aux2 = beam_height/2;
                area2 = beam_thickness*(beam_width -(2*beam_thickness));
                x_centroid_aux3 = beam_width - (beam_thickness/2);
                //y_centroid_aux3 = y_centroid_aux1
                //area3 = area1

                x_centroid = ((x_centroid_aux1*area1) + (x_centroid_aux2*area2) + (x_centroid_aux3*area1))/(2*area1 + area2);
                y_centroid = ((2*y_centroid_aux1*area1) + ((y_centroid_aux2)*area2))/(2*area1 + area2);

                //MOMENTO
                y_distance1 = y_centroid_aux1 - y_centroid;
                y_distance2 = y_centroid_aux2 - y_centroid;
                //y_distance3 = y_centroid_aux1
                x_distance1 = x_centroid_aux1 - x_centroid;
                x_distance2 = x_centroid_aux2 - x_centroid;
                x_distance3 = x_centroid_aux3 - x_centroid;

                x_moment_aux1 = (beam_thickness*(beam_height*beam_height*beam_height)/12) + (area1*(y_distance1*y_distance1));
                y_moment_aux1 = (beam_height*(beam_thickness*beam_thickness*beam_thickness)/12) + (area1*(x_distance1*x_distance1));
                x_moment_aux2 = ((beam_width - (beam_thickness/2))*(beam_thickness*beam_thickness*beam_thickness)/12) + (area2*(y_distance2*y_distance2));
                y_moment_aux2 = (beam_thickness*((beam_width - (beam_thickness/2))*(beam_width - (beam_thickness/2))*(beam_width - (beam_thickness/2)))/12) + (area2*(x_distance2*x_distance2));
                //x_moment_aux3 = x_moment_aux1;
                y_moment_aux3 = (beam_height*(beam_thickness*beam_thickness*beam_thickness)/12) + (area1*(x_distance3*x_distance3));

                x_moment = (2*x_moment_aux1) + x_moment_aux2;
                y_moment = y_moment_aux1 + y_moment_aux2 + y_moment_aux3;

            }
            else if(tiposVigas == TIPO_I)
            {
                printf("Entre com o valor de altura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_height = my_atof(userInput);

                printf("Entre com o valor da largura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_width = my_atof(userInput);

                printf("Entre com o valor da espessura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_thickness = my_atof(userInput);
                //VIGA I
                //CENTROIDE
                x_centroid_aux1 = beam_width/2;
                y_centroid_aux1 = beam_height - (beam_thickness/2);
                area1 = beam_width*beam_thickness;
                x_centroid_aux2 = beam_width/2;
                y_centroid_aux2 = ((beam_height - (beam_thickness*2))/2) + beam_thickness;
                area2 = beam_thickness*(beam_height -(2*beam_thickness));
                //x_centroid_aux3 = x_centroid_aux1
                y_centroid_aux3 = beam_thickness/2;
                //area3 = area1
                
                x_centroid = ((2*x_centroid_aux1*area1) + (x_centroid_aux2*area2))/(2*area1 + area2);
                y_centroid = ((y_centroid_aux1*area1) + ((y_centroid_aux2)*area2) + (y_centroid_aux3*area1))/(2*area1 + area2);

                //MOMENTO
                y_distance1 = y_centroid_aux1 - y_centroid;
                y_distance2 = y_centroid_aux2 - y_centroid;
                y_distance3 = y_centroid_aux3 - y_centroid;
                x_distance1 = x_centroid_aux1 - x_centroid;
                x_distance2 = x_centroid_aux2 - x_centroid;
                // x_distance3 = x_distance1
                x_moment_aux1 = (beam_width*(beam_thickness*beam_thickness*beam_thickness)/12) + (area1*(y_distance1*y_distance1));
                y_moment_aux1 = (beam_thickness*(beam_width*beam_width*beam_width)/12) + (area1*(x_distance1*x_distance1));
                x_moment_aux2 = (beam_thickness*(beam_width*beam_width*beam_width)/12) + (area2*(y_distance2*y_distance2));
                y_moment_aux2 = (beam_width*(beam_thickness*beam_thickness*beam_thickness)/12) + (area2*(x_distance2*x_distance2));
                x_moment_aux3 = (beam_width*(beam_thickness*beam_thickness*beam_thickness)/12) + (area1*(y_distance3*y_distance3));
                //y_moment_aux3 = y_moment_aux1

                x_moment = x_moment_aux1 + x_moment_aux2 + x_moment_aux3;
                y_moment = 2*y_moment_aux1 + y_moment_aux2;
            }
            else if(tiposVigas == TIPO_T)
            {
                printf("Entre com o valor de altura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_height = my_atof(userInput);

                printf("Entre com o valor da largura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_width = my_atof(userInput);

                printf("Entre com o valor da espessura em metros: ");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(userInput, 30 + 1 ,stdin); //Gets string
                if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)

                printf("\n\n");

                beam_thickness = my_atof(userInput);

                x_centroid_aux1 = beam_width/2;
                y_centroid_aux1 = beam_height - (beam_thickness/2);
                area1 = beam_width*beam_thickness;
                x_centroid_aux2 = beam_width/2;
                y_centroid_aux2 = (beam_height - beam_thickness)/2;
                area2 = beam_thickness*(beam_height - beam_thickness);

                x_centroid = ((x_centroid_aux1*area1) + (x_centroid_aux2*area2))/(area1 + area2);
                y_centroid = ((y_centroid_aux1*area1) + ((y_centroid_aux2)*area2))/(area1 +area2);

                y_distance1 = y_centroid_aux1 - y_centroid;
                y_distance2 = y_centroid_aux2 - y_centroid;
                x_distance1 = x_centroid_aux1 - x_centroid;
                x_distance2 = x_centroid_aux2 - x_centroid;

                x_moment_aux1 = (beam_width*(beam_thickness*beam_thickness*beam_thickness)/12) + (area1*(y_distance1*y_distance1));
                y_moment_aux1 = (beam_thickness*(beam_width*beam_width*beam_width)/12) + (area1*(x_distance1*x_distance1));
                x_moment_aux2 = (beam_thickness*(beam_width*beam_width*beam_width)/12) + (area2*(y_distance2*y_distance2));
                y_moment_aux2 = (beam_width*(beam_thickness*beam_thickness*beam_thickness)/12) + (area2*(x_distance2*x_distance2));
                
                x_moment = x_moment_aux1 + x_moment_aux2;
                y_moment = y_moment_aux1 + y_moment_aux2;
            }         
            if(tiposVigas == TRIANGULAR)
            {
                printf("O primeiro momento de area em x e:%.2f\n", x_centroid);
                printf("O primento momento de area em y e:%.2f\n", y_centroid);
                printf("O segundo momento de area em x e:%.2f\n", x_moment);
                printf("   Pressione 'ENTER' para continuar.\n");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(GetChar, 1 + 1 ,stdin); //Gets string
                
            }
            else 
            {
                printf("O primeiro momento de area em x e:%.2f\n", x_centroid);
                printf("O primento momento de area em y e:%.2f\n", y_centroid);
                printf("O segundo momento de area em x e:%.2f\n", x_moment);
                printf("O segundo momento de area em y e:%.2f\n", y_moment);
                printf("   Pressione 'ENTER' para continuar.\n");

                fflush(stdin); //Cleaning Keyboard Buffer
                fgets(GetChar, 1 + 1 ,stdin); //Gets string
            }
            beam_chosen++;
        }
        else
        {
            print_UserOp_validation();
            fflush(stdin); //Cleaning Keyboard Buffer
            fgets(GetChar, 1 + 1 ,stdin); //Gets string
        }
        
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
            double total_moment_on_bar = 0;

            // Vectors that will be used to print the Force graph
            // times 2, because every force needs a u(x) (Heaviside function) to represent it
            // so in the same point we need two distinct values, so that we can simulate a u(x) function
            x_discrete_force = (double*)malloc(sizeof(double) * (2*(all_discrete_variables_vectors_len+1)));
            y_discrete_force = (double*)malloc(sizeof(double) * (2*(all_discrete_variables_vectors_len+1)));

            // Vectors that will be used to print the Moment graph
            x_discrete_moment = (double*)malloc(sizeof(double) * (all_discrete_variables_vectors_len + 2 + 2*(pure_moment_len)));
            y_discrete_moment = (double*)malloc(sizeof(double) * (all_discrete_variables_vectors_len + 2 + 2*(pure_moment_len)));

            // Structs that will sort the Forces and Moments based on its distance
            POINT vector_of_moment_points[all_discrete_variables_vectors_len+1];
            POINT vector_of_force_points[all_discrete_variables_vectors_len+ 1];

            int i = 0;
            // Sum Of Reaction Forces caused by the forces
            for(; i < all_discrete_variables_vectors_len; i++)total_force_on_bar += -point_force[i];

            // Reaction Moments caused by the Pure Moments 
            i = 0;
            for(; i < pure_moment_len; i++) total_moment_on_bar += -point_pure_moment[i];

            //Calculating Force on the Right and Left Apoio Simples
            i = 0;
            for(; i < all_discrete_variables_vectors_len; i++)Apoio_simples_R.force_y += -(point_force[i] * (point_force_distance[i] - Apoio_simples_L.distance));
            Apoio_simples_R.force_y += total_moment_on_bar;
            Apoio_simples_R.force_y /= Apoio_simples_R.distance;

            Apoio_simples_L.force_y = total_force_on_bar - Apoio_simples_R.force_y;

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
            }
            for(int k = 0; k < pure_moment_len; k++)
            {
                vector_of_moment_points[i+k].x = pure_moment_distance[k];
                vector_of_moment_points[i+k].y = point_pure_moment[k];
            }
            //printf("\n\n");

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
            for(; i < all_discrete_variables_vectors_len + 1 + pure_moment_len; i++)
            {
                if(i > 0)
                {
                    x_discrete_moment[i] = vector_of_moment_points[i].x;

                    if(i > 1) Apoio_simples_add_moment +=  -vector_of_moment_points[i-1].y;
                    Apoio_simples_resultant_moment  = Apoio_simples_resultant_force * x_discrete_moment[i] + Apoio_simples_add_moment;
            
                    y_discrete_moment[i] = Apoio_simples_resultant_moment ;

                    //printf("Forca Resultante na Secao : %f\n",Apoio_simples_resultant_force );
                    //printf("Momento adicionado na Secao : %f\n",Apoio_simples_add_moment );
                    //printf(" x : %f |  y: %f \n", x_discrete_moment[i], y_discrete_moment[i]);
                    //printf("Momento Resultante na Secao : %f\n\n",Apoio_simples_resultant_moment);

                    Apoio_simples_resultant_force += (vector_of_moment_points[i].y/vector_of_moment_points[i].x);

                    
                }
                else
                {
                    x_discrete_moment[i] = vector_of_moment_points[i].x;
                    y_discrete_moment[i] = vector_of_moment_points[i].y;
                    //printf(" x : %f |  y: %f \n", x_discrete_moment[0], y_discrete_moment[0]); 
                }
            }
            //Last Moment Value and Distance 
            x_discrete_moment[i] = barra.size;
            y_discrete_moment[i] = 0;
            //printf(" x : %f |  y: %f \n", x_discrete_moment[i], y_discrete_moment[i]); 
            //printf("\n\n");


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
                    y_discrete_force[(2*j)-1] = y_discrete_force[(2*j) - 2];

                    
                    x_discrete_force[2*j] = vector_of_force_points[j].x;

                    Apoio_simples_L.force_y += vector_of_force_points[j].y;
                    y_discrete_force[2*j] = Apoio_simples_L.force_y ;

                    //printf(" x : %f |  y: %f \n",x_discrete_force[2*i - 1],y_discrete_force[2*i - 1]);
                    //printf(" x : %f |  y: %f \n",x_discrete_force[2*i],y_discrete_force[2*i]);

                }
                else
                {
                    x_discrete_force[j] = vector_of_force_points[j].x;
                    y_discrete_force[j] = vector_of_force_points[j].y;
                    //printf(" x : %f |  y: %f \n",x_discrete_force[i],y_discrete_force[i]);
                }
                
            }
            // Last Force Value (it happens because there's two supports one on each edge )
            if(j > 0)
            {
                x_discrete_force[2*j-1] = barra.size;
                y_discrete_force[2*j-1] = y_discrete_force[2*(j-1)];
            }

            //printf(" x : %f |  y: %f \n",x_discrete_force[i],y_discrete_force[i]);
            //printf("\n\n");

            //for(int k = 0; k < 2*(all_discrete_variables_vectors_len + 1) ; k++)
            //{
            //    printf(" x : %f |  y: %f \n",x_discrete_force[k],y_discrete_force[k]);      
            //}

            //PLOTTING GRAPH
            RGBABitmapImageReference* imageRef1 = CreateRGBABitmapImageReference();
            RGBABitmapImageReference* imageRef2 = CreateRGBABitmapImageReference();
            StringReference* ErrorMessage1;
            StringReference* ErrorMessage2;  

            DrawScatterPlot(imageRef1, 600, 400, x_discrete_force, 2*(all_discrete_variables_vectors_len + 1), y_discrete_force,
                            2*(all_discrete_variables_vectors_len + 1), ErrorMessage1);
            size_t lenght_f;
            double* pngData_f = ConvertToPNG(&lenght_f, imageRef1->image);
            WriteToFile(pngData_f, lenght_f, "forca_cortante.png");

            DrawScatterPlot(imageRef2, 600, 400, x_discrete_moment, all_discrete_variables_vectors_len + 2 + 2*(pure_moment_len),
                            y_discrete_moment, all_discrete_variables_vectors_len + 2 + 2*(pure_moment_len), ErrorMessage2);
            size_t lenght_m;
            double* pngData_m = ConvertToPNG(&lenght_m, imageRef2->image);
            WriteToFile(pngData_m, lenght_m, "momento_fletor.png");
        }

        if(all_discrete_variables_vectors_len == 0)
        {
            double total_force_on_bar = 0;
            double total_moment_on_bar = 0;

            // Vectors that will be used to print the Force graph
            // times 2, because every force needs a u(x) (Heaviside function) to represent it
            // so in the same point we need two distinct values, so that we can simulate a u(x) function
            x_continuous_force = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1));
            y_continuous_force = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1));

            // Vectors that will be used to print the Moment graph
            x_continuous_moment = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS *all_continuous_variables_vectors_len) + 2 + 2*(pure_moment_len)));
            y_continuous_moment = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS *all_continuous_variables_vectors_len) + 2 + 2*(pure_moment_len)));

            // Structs that will sort the Forces and Moments based on its distance
            POINT vector_of_moment_points[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1];
            POINT vector_of_force_points[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1];

            int i = 0;
            // Sum Of Reaction Forces caused by the forces
            for(; i < all_continuous_variables_vectors_len; i++)total_force_on_bar += -vector_forces_func[i];

            // Reaction Moments caused by the Pure Moments 
            i = 0;
            for(; i < pure_moment_len; i++) total_moment_on_bar += -vector_moments_func[i];

            //Calculating Force on the Right and Left Apoio Simples
            i = 0;
            for(; i < all_continuous_variables_vectors_len; i++)Apoio_simples_R.force_y += -(vector_forces_func[i] * (vector_centroids_func[i] - Apoio_simples_L.distance));
            Apoio_simples_R.force_y += total_moment_on_bar;
            Apoio_simples_R.force_y /= Apoio_simples_R.distance;

            Apoio_simples_L.force_y = total_force_on_bar - Apoio_simples_R.force_y;

                //Discrete Momento Fletor
            
             //First Moment and Distance Value
            vector_of_moment_points[0].x = 0;
            vector_of_moment_points[0].y = 0;

            // Adding Moment Values to be sorted by their distances
            i = 1;
            for(int k = 0; k < all_continuous_variables_vectors_len; k++)
            {
                double function_distance_parser = (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                double function_force_integral_parser = 0;
                char* force_function_symbolic_integral = indef_integral_C_value(indef_integral(vector_of_functions[k]),Apoio_simples_L.force_y);
                char* moment_function_symbolic_integral = indef_integral(force_function_symbolic_integral);
                //printf("force_function_symbolic_integral : %s\n",force_function_symbolic_integral);
                //printf("moment_function_symbolic_integral : %s\n",moment_function_symbolic_integral);

                for(; i <= CDW_N_OF_POINTS ; i++)
                {
                    vector_of_moment_points[i].x = vector_force_density_pos[k] + function_distance_parser;
                    
                    function_force_integral_parser = def_integral_value(force_function_symbolic_integral ,vector_inf_lims[k],vector_inf_lims[k] + function_distance_parser);
                    vector_of_moment_points[i].y = function_force_integral_parser;

                    function_distance_parser += (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                }
                //free(force_function_symbolic_integral);
                //free(moment_function_symbolic_integral);
                //printf("\n\n");
            }
            for(int k = 0; k < pure_moment_len; k++)
            {
                vector_of_moment_points[i+k].x = pure_moment_distance[k];
                vector_of_moment_points[i+k].y = point_pure_moment[k];
                //printf(" x : %f |  y: %f \n", vector_of_moment_points[i+k].x, vector_of_moment_points[i+k].y);
            }
            //printf("\n\n");

            // "qsort()" sorts all the Moment Values, based on their distances
            qsort(vector_of_moment_points,all_discrete_variables_vectors_len+1,sizeof(POINT),cmp_point);

            // Storing Sorted Moment Values and Their distances
            // To Plot the Moment Graph The Moment Value it's delayed by one loop, while it´s distance dont
            // It Works because when we go to the next distance, the peak moment value (old value) occurs in that distance
            // That's why it´s delayed 

            // As the program goes to the bar sections, we add the forces of the sections

            // Storing Sorted Moment Values and Their distances
            i = 0;
            for(; i < (CDW_N_OF_POINTS *all_continuous_variables_vectors_len) + 2 + 2*(pure_moment_len); i++)
            {
                if(i > 0)
                {
                    x_continuous_moment[i] = vector_of_moment_points[i].x;


                    y_continuous_moment[i] =  vector_of_moment_points[i].y;

                    //printf("Momento Resultante na Secao : %f\n\n", y_continuous_moment[i]);
                }
                else
                {
                    x_continuous_moment[i] = vector_of_moment_points[i].x;
                    y_continuous_moment[i] = vector_of_moment_points[i].y;
                    //printf(" x : %f |  y: %f \n", x_discrete_moment[0], y_discrete_moment[0]); 
                }
            }
            i = 0;        


                //Continuous Forca Cortante
            
            int j = 0;
            //First Force and Distance Value
            vector_of_force_points[0].x = 0;
            vector_of_force_points[0].y = 0;

            // Adding Force Values to be sorted by their distances
            j = 1;
            for(int k = 0; k < all_continuous_variables_vectors_len; k++)
            {
                double function_distance_parser = (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                for(; j <= CDW_N_OF_POINTS ; j++)
                {
                    vector_of_force_points[j].x = vector_force_density_pos[k] + function_distance_parser;
                    
                    vector_of_force_points[j].y  = def_integral_value(vector_of_functions[k],vector_inf_lims[k],vector_inf_lims[k] + function_distance_parser);

                    function_distance_parser += (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                }
            }
            // "qsort()" sorts all the Forces Values, based on their distances
            qsort(vector_of_force_points,(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1,sizeof(POINT),cmp_point);
            

            // Storing Sorted Moment Values and Their distances
            j = 0;
            for(; j < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1; j++)
            {
                x_continuous_force[j] = vector_of_force_points[j].x;
                y_continuous_force[j] = Apoio_simples_L.force_y + vector_of_force_points[j].y;
                //printf("forca em y : %f\n",y_continuous_force[j]);

            }


            //printf(" x : %f |  y: %f \n",x_discrete_force[i],y_discrete_force[i]);
            //printf("\n\n");

            //for(int k = 0; k < 2*(all_discrete_variables_vectors_len + 1) ; k++)
            //{
            //    printf(" x : %f |  y: %f \n",x_discrete_force[k],y_discrete_force[k]);      
            //}

            //PLOTTING GRAPH
            RGBABitmapImageReference* imageRef1 = CreateRGBABitmapImageReference();
            RGBABitmapImageReference* imageRef2 = CreateRGBABitmapImageReference();
            StringReference* ErrorMessage1;
            StringReference* ErrorMessage2;  

            DrawScatterPlot(imageRef1, 600, 400, x_continuous_force, (CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1, y_continuous_force,
                            (CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1, ErrorMessage1);
            size_t lenght_f;
            double* pngData_f = ConvertToPNG(&lenght_f, imageRef1->image);
            WriteToFile(pngData_f, lenght_f, "forca_cortante.png");

            DrawScatterPlot(imageRef2, 600, 400, x_continuous_moment,(CDW_N_OF_POINTS *all_continuous_variables_vectors_len) + 2 + 2*(pure_moment_len),
                            y_continuous_moment, (CDW_N_OF_POINTS *all_continuous_variables_vectors_len) + 2 + 2*(pure_moment_len), ErrorMessage2);
            size_t lenght_m;
            double* pngData_m = ConvertToPNG(&lenght_m, imageRef2->image);
            WriteToFile(pngData_m, lenght_m, "momento_fletor.png");
        }

    }
    
    if( (opApoio1 == ENGASTE && opApoio2 == LIVRE) || (opApoio1 == LIVRE && opApoio2 == ENGASTE) )
    {

        if(all_continuous_variables_vectors_len == 0)
        {
            // Vectors that will be used to print the Force graph
            x_discrete_force = (double*)malloc(sizeof(double) * ((2*all_discrete_variables_vectors_len)+1));
            y_discrete_force = (double*)malloc(sizeof(double) * ((2*all_discrete_variables_vectors_len)+1));

            if(pure_moment_len > 0)theres_a_pure_moment++;

            // Vectors that will be used to print the Moment graph
            x_discrete_moment = (double*)malloc(sizeof(double) * (all_discrete_variables_vectors_len+ 1 + theres_a_pure_moment));
            y_discrete_moment = (double*)malloc(sizeof(double) * (all_discrete_variables_vectors_len+ 1 + theres_a_pure_moment));

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
            Engaste.moment_y = vector_of_moment_points[0].y;

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
            x_continuous_force = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1));
            y_continuous_force = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1));

            if(pure_moment_len > 0)theres_a_pure_moment++;

            // Vectors that will be used to print the Moment graph
            x_continuous_moment = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1 + theres_a_pure_moment));
            y_continuous_moment = (double*)malloc(sizeof(double) * ((CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1 + theres_a_pure_moment));

            // Structs that will sort the Forces and Moments based on its distance
            POINT vector_of_moment_points[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1];
            POINT vector_of_force_points[(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1];

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
            //printf("Forca do Engaste : %f \n",Engaste.force_y);

            // Reaction Moments caused by the Pure Moments
            i = 0;
            for(; i < pure_moment_len; i++)Engaste.moment_y += -point_pure_moment[i];
            //if(theres_a_pure_moment == 1)printf("Momento do Engaste Apos Adicao Dos Momentos Puros: %f\n",Engaste.moment_y);
            //printf("\n\n\n");
                
                //Continuous Momento Fletor
            
            // First Moment and Distance Value
            vector_of_moment_points[0].x = 0;
            vector_of_moment_points[0].y = 0;

            // Adding Moment Values to be sorted by their distances
            i = 1;
            for(int k = 0; k < all_continuous_variables_vectors_len; k++)
            {
                double function_distance_parser = (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                double function_force_integral_parser = 0;
                char* force_function_symbolic_integral = indef_integral_C_value(indef_integral(vector_of_functions[k]),Engaste.force_y);

                for(; i <= CDW_N_OF_POINTS ; i++)
                {
                    vector_of_moment_points[i].x = vector_force_density_pos[k] + function_distance_parser;
                    
                    function_force_integral_parser = def_integral_value(force_function_symbolic_integral ,vector_inf_lims[k],vector_inf_lims[k] + function_distance_parser);
                    vector_of_moment_points[i].y = -function_force_integral_parser;


                    function_distance_parser += (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                }
                free(force_function_symbolic_integral);

            }

            // "qsort()" sorts all the Moment Values, based on their distances
            qsort(vector_of_moment_points,(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1,sizeof(POINT),cmp_point);

            // Storing Sorted Moment Values and Their distances
            i = 0;
            for(; i < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1; i++)
            {
                x_continuous_moment[i] = vector_of_moment_points[i].x;
                y_continuous_moment[i] = Engaste.moment_y + vector_of_moment_points[i].y;
                //printf("momento em y : %f\n",y_continuous_moment[i]);
            }
            if(theres_a_pure_moment == 1)
            {
                x_continuous_moment[i] = barra.size;
                y_continuous_moment[i] = Engaste.moment_y;
            }
            i = 0;

                //Continuous Forca Cortante

            int j = 0;
            //First Force and Distance Value
            vector_of_force_points[0].x = 0;
            vector_of_force_points[0].y = 0;

            // Adding Force Values to be sorted by their distances
            j = 1;
            for(int k = 0; k < all_continuous_variables_vectors_len; k++)
            {
                double function_distance_parser = (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                for(; j <= CDW_N_OF_POINTS ; j++)
                {
                    vector_of_force_points[j].x = vector_force_density_pos[k] + function_distance_parser;
                    
                    vector_of_force_points[j].y  = def_integral_value(vector_of_functions[k],vector_inf_lims[k],vector_inf_lims[k] + function_distance_parser);

                    function_distance_parser += (vector_sup_lims[k] - vector_inf_lims[k])/CDW_N_OF_POINTS;
                }
            }

            // "qsort()" sorts all the Forces Values, based on their distances
            qsort(vector_of_force_points,(CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1,sizeof(POINT),cmp_point);


            // Storing Sorted Moment Values and Their distances
            j = 0;
            for(; j < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len) + 1; j++)
            {
                x_continuous_force[j] = vector_of_force_points[j].x;
                y_continuous_force[j] = Engaste.force_y + vector_of_force_points[j].y;
                //printf("forca em y : %f\n",y_continuous_force[j]);

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
    
    double x_max = 0;
    double moment_max = 0;

    while (max_strain_done == 0)
    {
        if( (opApoio1 == ENGASTE && opApoio2 == LIVRE) || (opApoio1 == LIVRE && opApoio2 == ENGASTE) && all_continuous_variables_vectors_len == 0)
        {
            for(int i = 0; i < (2*all_discrete_variables_vectors_len)+1; i++)
            {
                if(y_discrete_force[i] == 0)
                {
                    x_max = x_discrete_force[i];
                    break;
                }
            }
            moment_max = Engaste.moment_y;
            max_strain_done++;      
        }

        if( (opApoio1 == ENGASTE && opApoio2 == LIVRE) || (opApoio1 == LIVRE && opApoio2 == ENGASTE) && all_discrete_variables_vectors_len == 0)
        {
            for(int i = 0; i < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1; i++)
            {
                if(y_continuous_force[i] == 0)
                {
                    x_max = x_continuous_force[i];
                    break;
                }
            }
            moment_max = Engaste.moment_y;
            max_strain_done++;
        }
        
        if( opApoio1 == APOIO_SIMPLES && opApoio2 == APOIO_SIMPLES && all_continuous_variables_vectors_len == 0)
        {
            for(int i = 0; i < 2*(all_discrete_variables_vectors_len+1); i++)
            {
                if(y_discrete_force[i] == 0)
                {
                    x_max = x_discrete_force[i];
                    break;
                }
            }
            for(int i = 0; i < all_discrete_variables_vectors_len + 2 + 2*(pure_moment_len); i++)
            {
                if(x_discrete_moment[i] == x_max)
                {
                    moment_max = y_discrete_moment[i];
                    break;
                }
            }
            max_strain_done++;
        }

        if( opApoio1 == APOIO_SIMPLES && opApoio2 == APOIO_SIMPLES && all_discrete_variables_vectors_len == 0)
        {
            for(int i = 0; i < (CDW_N_OF_POINTS * all_continuous_variables_vectors_len)+1; i++)
            {
                if(y_continuous_force[i] == 0)
                {
                    x_max = x_continuous_force[i];
                    break;
                }
            }
            for(int i = 0; i < (CDW_N_OF_POINTS *all_continuous_variables_vectors_len) + 2 + 2*(pure_moment_len); i++)
            {
                if(x_continuous_moment[i] == x_max)
                {
                    moment_max = y_continuous_moment[i];
                    break;
                }
            }
               
            max_strain_done++;
        }
    }

    double c = 0;
    double max_strain = 0;
    
    //Tensão Max Abs
    if(tiposVigas == CIRCULAR)c = beam_radius;
    else
    {   
        if ((beam_height - y_centroid) > y_centroid) c = beam_height - y_centroid;
        else c = y_centroid;
    }

    max_strain = (moment_max*c)/x_moment;
    printf("A tensao maxima absoluta eh: %f Pa\n", max_strain);
    printf("A posicao longitudinal eh: %.2f m\n", x_max);
    printf("A posicao transversal eh: %.2f m\n", c);

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
    if(opApoio1 == APOIO_SIMPLES && opApoio2 == APOIO_SIMPLES)
    {
        if(all_continuous_variables_vectors_len == 0)
        {
            free(x_discrete_force);
            free(y_discrete_force);
            free(x_discrete_moment);
            free(y_discrete_moment);
        }
        if(all_discrete_variables_vectors_len == 0)
        {
            free(x_continuous_force);
            free(y_continuous_force);
            free(x_continuous_moment);
            free(y_continuous_moment);
        }
    }
    if((opApoio1 == ENGASTE && opApoio2 == LIVRE) || (opApoio1 == LIVRE && opApoio2 == ENGASTE) )
    {
        if(all_continuous_variables_vectors_len == 0)
        {
            free(x_discrete_force);
            free(y_discrete_force);
            free(x_discrete_moment);
            free(y_discrete_moment);
        }
        if(all_discrete_variables_vectors_len == 0)
        {
            free(x_continuous_force);
            free(y_continuous_force);
            free(x_continuous_moment);
            free(y_continuous_moment);
        }
    }
    
    return 0;
}