#include "my_strings.h"
#include <stdio.h>


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

int str_find_char(char* str, char str_char) // Returns "chr" pos in the "str"
{
    int pos;
    for(pos = 0; str[pos] != str_char;pos++) // while char isn't "chr" increment the lenght number
    {
        if(str[pos] == '\0')return -1; // if "chr" isn`t in str
    }
    return pos;   
}

int my_atoi(char* str) // Converts strings to integers
{
    int multiplier = 1; // decimal base multiplier
    int number = 0; // number converted
    int number_start = -1; // first number pos
    int number_end = 0; // last number pos
    int negative = 0; // if number is negative (negative = 1) or no (negative = 0) 
    int i = 0; // iterators

    if(str[0] == '-') // if number is negative
    {
        negative = 1;
        
        for(i = 1; (str[i] >= '0' && str[i] <= '9'); i++)
        {
            if(number_start < 0 && (str[i] >= '0' && str[i] <= '9')) number_start = i;
        }
        if (i == 1)return INT_MIN;// second char is a invalid char to transform to int
    }
    else
    {
        if(str[0] == '+') // if has the + sign
        {
            for(i = 1; (str[i] >= '0' && str[i] <= '9'); i++)
            {
                if(number_start < 0 && (str[i] >= '0' && str[i] <= '9')) number_start = i;
            }
            if (i == 1)return INT_MIN;// second char is a invalid char to transform to int
        }
        else
        {
            for(i = 0; (str[i] >= '0' && str[i] <= '9'); i++)
            {
                if(number_start < 0 && (str[i] >= '0' && str[i] <= '9')) number_start = i;
            }
            if (i == 0)return INT_MIN;// second char is a invalid char to transform to int
        }

    }

    number_end = i - 1; // Last number pos

    for(i = number_start; i < number_end; i++)multiplier*=10; // getting first number base 10 exponent to represent it in decimal base

    for(i = number_start; i <= number_end; i++)
    {
        number += (str[i] - '0') * multiplier; // "converting" to int
        multiplier/= 10;
    }

    if(negative == 1) number *= -1;

    return number;
}

double my_atof(char* str) // Converts string to float 
{
    double number = my_atoi(str); // int number
    double decimal_multiplier = 1; // decimal base multiplier
    int negative_multiplier = 1; // if it's negative, it equals -1, else equals 1
    int number_end = 0; // last number pos
    int i = 0; // iterators
    
    if (number != INT_MIN);
    {
        int dot_pos = str_find_char(str,'.'); // find dot position

        if(dot_pos != -1)
        {
            for(i = dot_pos+1; (str[i] >= '0' && str[i] <= '9'); i++); // counts string lenght
            number_end = i - 1; // can be a number or a '.'
            if(number_end == dot_pos) return number; //if there's nothing after the '.'

            if(number < 0)negative_multiplier = -1;

            for(i = dot_pos+1; i <= number_end; i++)
            {
                decimal_multiplier/= 10;
                number += (str[i] - '0') * decimal_multiplier * negative_multiplier; // adding the pos '.' float numbers
            } 
        }
    }

    return number;    
}
