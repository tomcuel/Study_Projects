#include "Conversion.h"

#include <stdio.h>
#include <stdlib.h>

int main (){

    char letter = 'A';
    int number = 3;

    printf("Letter %c converted to number: %d\n", letter, Convert_Letter_to_Number(letter));
    printf("Number %d converted to letter: %c\n", number, Convert_Number_to_Letter_Maj(number));

    return EXIT_SUCCESS;
}