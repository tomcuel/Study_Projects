#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__


/////////////////////////////////////////////////////////////////////////////////////
// Conversion Summary :
/**
 * Convert_Letter_to_Number - converts a letter to a number
 * Convert_Number_to_Letter - converts a number to a letter
 * 
 * Will be use in the chessboard rendering, to show the row (number) and the column (letter) of the pieces
 * since it's displayed like that on the chessboard
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function that converts a letter to a number (don't know if it will be useful, but it's here just in case)
/**
 * @param letter - the letter to convert
 * @return int - the number corresponding to the letter
 * -1, if the letter is not a valid letter
**/
/////////////////////////////////////////////////////////////////////////////////////
int Convert_Letter_to_Number(char letter);


/////////////////////////////////////////////////////////////////////////////////////
// Function that converts a number to a letter in miniuscule (will be used to print the move and the log)
/**
 * @param number - the number to convert
 * @return char - the letter corresponding to the number
 * -1, if the number is not a valid number
**/
/////////////////////////////////////////////////////////////////////////////////////
char Convert_Number_to_Letter_Min(int number);


/////////////////////////////////////////////////////////////////////////////////////
// Function that converts a number to a letter (will be used to search for the letter to print on the board)
/**
 * @param number - the number to convert
 * @return char - the letter corresponding to the number
 * -1, if the number is not a valid number
**/
/////////////////////////////////////////////////////////////////////////////////////
char Convert_Number_to_Letter_Maj(int number);


#endif /* __CONVERSIONS_H__ */