#include "my_strings.h"
#include <stdio.h>

char* remove_spaces(char* string)//Returns a allocated pointer with the minimum space needed to "save" the string; 
{
    if(string != NULL)
    {
        char character_name[my_strlen(string) + 1];
        int x = 0, y = 0;
        int strlen;
        while(string[x] == ' ')x++;//Erasing Initial Spaces
        while(string[x] != '\0')
        {
            if (!(string[x] == ' '))//If next char is a space, the while jumps to the next till find a non-space character
            {
                character_name[y] = string[x];
                y++;
            }
            x++;//If current and next char is a "space", we jump to the next char
        }
        character_name[y] = '\0'; //Terminates the string with atleast one space;
        strlen = my_strlen(character_name) - 1; //Retuns the string length without counting the '\0' char
        if(character_name[strlen] == ' ')character_name[strlen] = '\0'; //If there´s a space at the end of the str it's removed, and the last char becomes a '\0' char        
        
        return my_strdup(character_name);//Returns a allocated pointer with the minimum space needed to "save" the string; 
    }
    return string; //Else Retuns the same string, because it's NULL
}

char* str_validation(int MAX_LEN)
{
    char str[MAX_LEN];
    fflush(stdin); //Cleaning Keyboard Buffer
    fgets(str, MAX_LEN ,stdin); //Gets string
    if(str[my_strlen(str)-1] == '\n')str[my_strlen(str)-1] = '\0'; // removes '\n' char that gets to the string (sometimes)

    return remove_spaces(str);   
}



int my_strlen(char* str)
{
    int len = 0;
    if(str != NULL) for(; str[len] != '\0';len++); // while char isn't '\0' increment the length number
    return len;
}

int str_find_char(char* str, char str_char) // Returns "chr" pos in the "str"
{
    int pos = 0;
    
    if(str != NULL)
    {
        for(; str[pos] != str_char;pos++) // while char isn't "chr" increment the length number
        {
            if(str[pos] == '\0')return -1; // if "chr" isn`t in str
        }
    }
    return pos;   
}

int str_count_char(char* str, char str_char) // counts ammount of "str_char" in a str
{
    int count = 0;
    
    if(str != NULL)
    {
        for(int i = 0; str[i] != '\0';i++)
        {
            if(str[i] == str_char)count++;
        }
    }
    return count;
}

char* my_strdup(char* str) //Alocates and retuns the str; 
{
    char* str_duplicated = NULL;
    if(str != NULL)
    {
        int i = 0;
        int str_len = my_strlen(str);
        str_duplicated = (char*)malloc(sizeof(char) * (str_len + 1));// "+1" because my_strlen() doesn't count '\0' char

        for(; i < str_len; i++)str_duplicated[i] = str[i];
        str_duplicated[i] = '\0'; // ending str;
    }
    
    return str_duplicated;
}





int my_atoi(char* str) // Converts strings to integers in decimal base
{
    int number = INT_MIN; // number converted
    if(str != NULL)
    {
        int multiplier = 1; // decimal base multiplier
        int number_start = -1; // first number pos
        int number_end = 0; // last number pos
        int negative = 0; // if number is negative (negative = 1) or no (negative = 0) 
        int i = 0; // iterators

        if(str[0] == '-') // if has the - sign
        {
            negative = 1;
            i++;
            
            for(; (str[i] >= '0' && str[i] <= '9'); i++)
            {
                if(number_start < 0 && (str[i] >= '0' && str[i] <= '9')) number_start = i;
            }
            if (i == 1)return number;// second char is a invalid char to transform to int
        }
        else
        {
            if(str[0] == '+') // if has the + sign
            {
                i++;
                for(; (str[i] >= '0' && str[i] <= '9'); i++)
                {
                    if(number_start < 0 && (str[i] >= '0' && str[i] <= '9')) number_start = i;
                }
                if (i == 1)return number;// second char is a invalid char to transform to int
            }
            else
            {
                for(; (str[i] >= '0' && str[i] <= '9'); i++)
                {
                    if(number_start < 0 && (str[i] >= '0' && str[i] <= '9')) number_start = i;
                }
                if (i == 0)return number;// second char is a invalid char to transform to int
            }

        }

        number_end = i - 1; // Last number pos

        i = number_start;
        for(; i < number_end; i++)multiplier*=10; // getting first number base 10 exponent to represent it in decimal base

        number = 0;
        
        i = number_start;
        for(; i <= number_end; i++)
        {
            number += (str[i] - '0') * multiplier; // "converting" to int
            multiplier/= 10;
        }

        if(negative == 1) number *= -1;
    }
    
    return number;
}

double my_atof(char* str) // Converts string to float in decimal base
{
    double number = my_atoi(str); // int number
    double decimal_multiplier = 1; // decimal base multiplier
    int negative_multiplier = 1; // if it's negative, it equals -1, else equals 1
    int number_end = 0; // last number pos
    int i = 0; // iterators

    if (number != INT_MIN)
    {
        int dot_pos = str_find_char(str,'.'); // find dot position

        if(dot_pos != -1)
        {
            i = dot_pos+1;
            for(; (str[i] >= '0' && str[i] <= '9'); i++); // counts string length
            number_end = i - 1; // can be an integer or a float
            if(number_end == dot_pos) return number; //if there's nothing after the '.'

            if(number < 0)negative_multiplier = -1;

            i = dot_pos+1;
            for(; i <= number_end; i++) // adding the pos '.' numbers
            {
                decimal_multiplier/= 10;
                number += (str[i] - '0') * decimal_multiplier * negative_multiplier; 
            } 
        }
    }

    return number;    
}

char* my_itoa(int int_n) // Converts an integer number in decimal base, and returns it as a allocated str
{
    int multiplier = 1; // decimal base multiplier
    int int_n_copy = int_n/10; // "int_n" have atleast 1 number, if that`s the case, "int_n_copy" will be 0;
    int int_n_len = 1; // "int_n" is atleast 1;
    char* n_str = NULL; // str to be returned
    int i = 0; // iterator

    // Calculates Integer length
    for(; int_n_copy != 0; int_n_len++)int_n_copy/= 10;
    for(int j = 1; j < int_n_len; j++)multiplier*=10;

    n_str = (char*)malloc(sizeof(char)*(int_n_len + 1)); // +1 for the '\0' char

    if(n_str != NULL)
    {
        int n_to_char; // number to character converter
        for(; i < int_n_len; i++)
        {
            n_to_char = (int_n/multiplier) - (int_n/(multiplier*10))*10; // calculates the number that will be converted to char
            n_str[i] = n_to_char + '0';
            multiplier/=10;
        }
        n_str[i] = '\0'; // finalizing str
    }

    return n_str;
}
