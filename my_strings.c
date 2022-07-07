#include "my_strings.h"

char* remove_spaces(char* string)//Returns a allocated pointer with the minimum space needed to "save" the string; 
{
    if(string != NULL)
    {
        char character_name[my_strlen(string)];
        int x = 0, y = 0;
        int strlen;
        char* str_nspaces;
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




int my_strlen(char* str)
{
    int len = 0;
    if(str != NULL) for(len = 0; str[len] != '\0';len++); // while char isn't '\0' increment the length number
    return len;
}

int str_find_char(char* str, char str_char) // Returns "chr" pos in the "str"
{
    int pos = 0;
    
    if(str != NULL)
    {
        for(pos = 0; str[pos] != str_char;pos++) // while char isn't "chr" increment the length number
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
        int str_len = my_strlen(str);
        char* str_duplicated =(char*)malloc(sizeof(char) * (str_len + 1));

        for(int i = 0; i < str_len+1; i++)str_duplicated[i] = str[i]; // "+1" because my_strlen() doesn't count '\0' char
    }
    return str_duplicated;
}





int my_atoi(char* str) // Converts strings to integers in decimal base
{
    int number = 0; // number converted
    if(str != NULL)
    {
        int multiplier = 1; // decimal base multiplier
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
    }
    number = INT_MIN;
    
    return number;
}

double my_atof(char* str) // Converts string to float in decimal base
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
            for(i = dot_pos+1; (str[i] >= '0' && str[i] <= '9'); i++); // counts string length
            number_end = i - 1; // can be an integer or a float
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

char* my_itoa(int int_n) // Converts an integer number in decimal base, and returns it as a allocated str
{
    int multiplier = 1; // decimal base multiplier
    int int_n_copy = int_n/10; // "int_n" have atleast 1 number, if that`s the case, "int_n_copy" will be 0;
    int int_n_len = 1; // "int_n" is atleast 1;
    char* n_str; // str to be returned
    int i = 0; // iterator

    // Calculates Integer length
    for(int_n_len; int_n_copy != 0; int_n_len++)int_n_copy/= 10;
    for(int i = 1; i < int_n_len; i++)multiplier*=10;

    n_str = (char*)malloc(sizeof(char)*(int_n_len + 1)); // +1 for the '\0' char

    for(i = 0; i < int_n_len; i++)
    {
        int n_to_char = (int_n/multiplier) - (int_n/(multiplier*10))*10; // calculates the number that will be converted to char
        n_str[i] = n_to_char + '0';
        multiplier/=10;
    }
    n_str[i] = '\0';

    return n_str;
}
