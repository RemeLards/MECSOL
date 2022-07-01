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
    for(len = 0; str[len] != '\0';len++); // while char isn't '\0' increment the lenght number
    return len;
}

int findchr(char* str, char chr) // Returns "chr" pos in the "str"
{
    int pos;
    for(pos = 0; str[pos] != chr;pos++) // while char isn't "chr" increment the lenght number
    {
        if(str[pos] == '\0')return -1; // if "chr" isn`t in str
    }
    return pos;   
}

int my_atoi(char* str) //expects a string contaning only a number, and this number has to be an integer
{
    int str_len = my_strlen(str);
    int multiplier = 1;
    int number = 0;

    for(int i = 1; i < str_len; i++)multiplier*=10;

    for(int i = 0; i < str_len; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            number += (str[i] - '0') * multiplier; // "converting" to int
            multiplier/= 10;
        }
        else return -1; //if there isn't a number in the string

    }

    return number;
}

float my_atof(char* str) //expects a string contaning only a number
{
    int str_len = my_strlen(str);
    int multiplier = 1;
    float number = 0;
    int char_pos = findchr(str,'.');

    if(char_pos != -1)
    {
            
    }

    for(int i = 0; i < str_len; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            number += (str[i] - '0') * multiplier; // "converting" to int
            multiplier/= 10;
        }
        else return -1; //if there isn't a number in the string

    }

    return number;    
}
