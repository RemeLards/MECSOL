#include <stdio.h>
#include "my_strings.h"

int main()
{
    char function_str[31];

    printf("Escreva sua funcao carga :  ");
    fflush(stdin); //Cleaning Keyboard Buffer
    fgets(function_str, 31 ,stdin); //Gets Character Name
    if(function_str[my_strlen(function_str)-1] == '\n')function_str[my_strlen(function_str)-1] = '\0';//Erasing the "\n" character in the end of fgets(), if it gets into the string
    
    char* str_nspaces = remove_spaces(function_str);//If there's more than 1 space

    // getting and saving the force_density function
    printf("\nuser function : %s",function_str);
    printf("\n\n");
    printf("string without spaces : %s\n",str_nspaces);

    if(str_nspaces != NULL)free(str_nspaces);
    return 0;

}