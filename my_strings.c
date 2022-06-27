#include "my_strings.h"

char* remove_spaces(char* string)//Returns a malloced pointer with the minimum space needed to "save" the string; 
{
    char character_name[31];
    int x = 0, y = 0;
    int strlen;
    while(string[x] == ' ')x++;//Erasing Initial Spaces
    while(string[x] != '\0')
    {
        if (!(string[x] == ' ' && string[x+1] == ' '))//If next char is a space, the while jumps to the next till find a non-space character
        {
            character_name[y] = string[x];
            y++;
        }
        x++;//If current and next char is a "space", we jump to the next char
    }
    character_name[y] = '\0'; //Terminates the string with atleast one space;
    strlen = my_strlen(character_name) - 1; //Retuns the string lenght without counting the '\0' char
    if(character_name[strlen] == ' ')character_name[strlen] = '\0'; //If there´s a space at the end of the str it's removed, and the last char becomes a '\0' char

    return strdup(character_name); //Returns a malloced pointer with the minimum space needed to "save" the string; 
}

int my_strlen(char* str)
{
    int len;
    for(len = 0; str[len] != '\0';len++);
    return len;
}
