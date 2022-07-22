#include <stdio.h>
#include "my_strings.h"

int main()
{
    char* int_str = my_itoa(9499);

    printf("int converted : %s\n",int_str);


    if(int_str !=NULL)free(int_str);

    return 0;


}