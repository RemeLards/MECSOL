#ifndef _MY_STRINGS_

#define _MY_STRINGS_

#define INT_MIN	-2147483648

#define DECIMAL_NUMBERS_NEEDED 2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//-------------------------
//FUNCTIONS PROTOTYPES
//-------------------------

char* remove_spaces(char* string);//Remove extra spaces
char* str_validation(int MAX_LEN);

int my_strlen(char* str); //Returns str length
int str_find_char(char* str, char str_char); // Returns "char" pos in the "str"
int str_count_char(char* str, char str_char); // counts ammount of "str_char" in a str
char* my_strdup(char* str); //Alocates and retuns the str 

int my_atoi(char* str); //expects a string contaning only an integer number in decimal base
double my_atof(char* str); //expects a string contaning only a number in decimal base
char* my_itoa(int int_n); // expects an integer number in decimal base, and returns it as a allocated str
char* my_ftoa(double int_n); // expects an double/float number in decimal base, and returns it as a allocated str

#endif
