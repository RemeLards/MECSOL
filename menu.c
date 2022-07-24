#include <stdio.h>
#include <stdlib.h>
#include "my_strings.h"

#define APOIO_SIMPLES 1
#define ENGASTE 2
#define LIVRE 3
#define USER_OP 1

void printTela_1()
{
    // Tela 1:
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forças internas em vigas apoiadas  =========\n");
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
    printf(" ========= Calculadora de forças internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Dentre os seguintes tipos de apoio:\n");
    printf("     1. Apoio Simples;\n");
    printf("     2. Engaste;\n");
    printf("     3. Livre;\n");
    printf(" =====================================================================\n\n");
}

void printEng_Eng_validation()
{
    printf("\n =====================================================================\n");
    printf("   Nao eh possivel utilizar dois engastes como apoio. Entre com \n outro tipo de apoio.\n");
    printf("   Precione 'ENTER' para continuar.");
    printf(" =====================================================================\n");
    system("pause");   
}

void print_Apoios_validation(char** tiposApoios, int apoio1, int apoio2, int pos_apoio2)
{
    system("cls");
    printf(" =====================================================================\n");
    printf(" ============================ Seus Apoios ============================\n");
    printf("   Tipo do primeiro apoio: %s;\n", tiposApoios[apoio1-1]);
    printf("   Tipo do segundo apoio: %s;\n", tiposApoios[apoio2-1]);
    printf("   Posicao do segundo apoio: %.2f;\n", pos_apoio2);
    printf(" =====================================================================\n");
}

void printTela_3()
{
    // Tela 3:
    system("cls");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forças internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Agora que ja temos os apoios definidos, entre com a quantia de \n");
    printf("   forcas externas atuantes na viga:\n");
}

int main ()
{   // Declaracao de variaveis:
    int userOp  = 0, opApoio1 = 0, opApoio2 = 0, valida = 0, op1 = 0, op2 = 0;
    double forca  = 0 , momento  = 0 , posApoio2  = 0, bar_size  = 0;
    char tiposApoios[] = {"Apoio Simples", "Engaste", "Livre"};
    char userInput[USER_OP + 1];

    printTela_1();
    printTela_2();

    while (op1 == 0)
    {
        printf("  Qual o tipo do apoio localizado na posição x = 0 (Extremidade Esquerda) ?");
        
        fflush(stdin); //Cleaning Keyboard Buffer
        fgets(userInput, USER_OP + 1  ,stdin); //Gets string
        if(userInput[my_strlen(userInput)-1] == '\n')userInput[my_strlen(userInput)-1] = '\0';// removes '\n' char that gets to the string (sometimes)
        
        opApoio1 = my_atoi(userInput);

        if(opApoio1 != LIVRE)
        {
            // Restricao dos tipos de apoio + selecao do segundo apoio
            while (valida == 0)
            {
                printf("\n\n  Qual o tipo do segundo apoio? ");
                
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
        }

        print_Apoios_validation(tiposApoios,opApoio1,opApoio2,posApoio2);
        //printf("   Os dados acima estão corretos? [S / N]\n");

        //Fazer isso depois! OBS: scanf assim NAO VAI FUNCIONAR!!!!

        //scanf("%c", &op2);

        /*if(op2 == 'S' || op2 == 's')
        {
            op1 == 1;
        }
        else 
        {
            printf(" =====================================================================\n");
            printf("   Por favor entre com os dados sobre os apoios novamente.\n");
            printf("   Precione 'ENTER' para continuar.\n");
            printf(" =====================================================================\n");
            system("pause");
        }*/
    }

    //scanf("%d", &qntdForcas);
    printTela_3();
    //double posForca [qntdForcas];
    //continuar a leitura da intensidade e posicao das forcas
    return 0;
}
