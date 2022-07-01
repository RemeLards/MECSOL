#ifndef _MY_STRINGS_
#define _MY_STRINGS_
#include <string.h>

//-------------------------
//FUNCTIONS PROTOTYPES
//-------------------------

char* remove_spaces(char* string);//Remove extra spaces
int my_strlen(char* str); //Returns str lenght
int my_atoi(char* str); //expects a string contaning only a number, and this number has to be an integer
float my_atof(char* str); //expects a string contaning only a number
int findchr(char* str, char chr); // Returns "chr" pos in the "str"

#endif
