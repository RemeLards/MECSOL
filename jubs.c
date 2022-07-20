#include <stdio.h>
#include <stdlib.h>

char* vaidarmerda(char* str_copiada) //&numero_copiado = 0x9283648923
{
    char* str_copiada_modificada = NULL; ;//p
    //...
    return str_copiada_modificada;
}

int main()
{
    char* str = "oi9999";
    printf("%p\n",str);
    vaidarmerda(str);
    printf("%s \n",str);
    return 0;
}