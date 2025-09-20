#include "Conversion.h"


int Convert_Letter_to_Number(char letter){
	// Check if the letter is a valid letter (A-H or a-h)

	// Majuscule
	if (letter >= 'A' && letter <= 'H')
		return letter - 'A';

	// Minuscule
	if (letter >= 'a' && letter <= 'h')
		return letter - 'a';
	return -1;
}


char Convert_Number_to_Letter_Min(int number){
	// Check if the number is a valid number (0-7)
	if (number >= 0 && number <= 7)
		// translate the number to a letter
		return number + 'a';
	return -1;
}


char Convert_Number_to_Letter_Maj(int number){
	// Check if the number is a valid number (0-7)
	if (number >= 0 && number <= 7)
		// translate the number to a letter
		return number + 'A';
	return -1;
}