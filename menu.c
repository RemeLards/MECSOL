#include <stdio.h>
#include <stdlib.h>
#include "my_strings.h"

#define APOIO_SIMPLES 1
#define ENGASTE 2
#define LIVRE 3

int main ()
{   // Declaracao de variaveis:
    int userOp, opcaoApoio1, opcaoApoio2, qntdForcas, valida = 0, op1 = 0;
    double forca, momento, posicao;
    char op2, userInput[30];
    char* tiposApoios = {"Apoio Simples", "Engaste", "Livre"};

       // Tela 1:
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forças internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Pressione 'ENTER' para criar uma situacao;\n");
    printf(" =====================================================================\n");
    system("pause");

    // Tela 2:
    system("cls");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forças internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Dentre os seguintes tipos de apoio:\n");
    printf("     1. Apoio Simples;\n");
    printf("     2. Engaste;\n");
    printf("     3. Livre;\n");
    printf(" =====================================================================\n");

    while (op1 == 0)
    {
        printf("  Qual o tipo do apoio localizado na posição '0'?");
        scanf("%s", userInput);
        opcaoApoio1 = my_atoi(userInput);
        
        // Restricao dos tipos de apoio + selacao do segundo apoio
        while (valida == 0)
        {
            printf("\n\n  Qual o tipo do segundo apoio?");
            scanf("%s", userInput);
            opcaoApoio2 = my_atoi(userInput);

            if((opcaoApoio1 == ENGASTE) && (opcaoApoio2 == ENGASTE))
            {
                printf("\n =====================================================================\n");
                printf("   Nao eh possivel utilizar dois engastes como apoio. Entre com \n outro tipo de apoio.\n");
                printf("   Precione 'ENTER' para continuar.");
                printf(" =====================================================================\n");
                system("pause");
            } 
            else if ((opcaoApoio1 == LIVRE && opcaoApoio2 != ENGASTE) || (opcaoApoio2 == LIVRE && opcaoApoio1 != ENGASTE))
            {
                printf("\n =====================================================================\n");
                printf("   Para utilizar um apoio livre, o outro apoio tem que ser engaste.\n");
                printf("   Precione 'ENTER' para continuar.");
                printf(" =====================================================================\n");
                system("pause");
            }
            else {
                valida = 1;
            }
        }
        printf("\n\n Qual a posicao em 'x' do segundo apoio?");
        scanf("%f", &posicao);

        system("cls");
        printf(" =====================================================================\n");
        printf(" ============================ Seus Apoios ============================\n");
        printf("   Tipo do primeiro apoio: %s;\n", tiposApoios[opcaoApoio1-1]);
        printf("   Tipo do segundo apoio: %s;\n", tiposApoios[opcaoApoio2-1]);
        printf("   Posicao do segundo apoio: %.2f;\n", &posicao);
        printf(" =====================================================================\n");
        printf("   Os dados acima estão corretos? [S / N]\n");
        scanf("%c", &op2);

        if(op2 == 'S' || op2 == 's')
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
        }
    }

    // Tela 3:
    system("cls");
    printf(" =====================================================================\n");
    printf(" ========= Calculadora de forças internas em vigas apoiadas  =========\n");
    printf(" =====================================================================\n");
    printf("   Agora que ja temos os apoios definidos, entre com a quantia de \n");
    printf("   forcas externas atuantes na viga:\n");
    scanf("%d", &qntdForcas);

    double posForca [qntdForcas];
    //continuar a leitura da intensidade e posicao das forcas
    return 0;
}
