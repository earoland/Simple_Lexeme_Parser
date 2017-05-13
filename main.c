/**
 * This program accepts an input file that is written in a programming language
 * and then it figures out which characters are accepts in the program's
 * language or not. It then writes to an file each character name and if it
 * is a token or not.
 *
 * tokenizer.c - A simple token recognizer.
 *
 *
 * NOTE: The terms 'token' and 'lexeme' are used interchangeably in this
 *       program.
 *
 * @authors Ethan Roland & Nick Sprinkle
 * @version 18 April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parser.h"
#include "tokenizer.h"
#include "main.h"

// global variables
char *line;             // Global pointer to line of input
char *buffer;           // Global pointer to a Buffer array
char token[LINE];       // Global pointer to a token array
char input_line[LINE];  // Global pointer to the line of input
char trimmed_line[LINE];// Global pointer to the trimmed input
int is_error = 0;       // error value for non lexemes
int missing_parenthesis = 0; // errror value for a missing closing parenthesis
int missing_semicolon = 0; // error value for a missing semicolon
size_t length = 100;    // size_t input for getline

/**
* Reads in the files, assigns the values to correct locations in variables,
* then proceeds to do a loop for each line in the file which calls the
* get_token() function this changes the token array in the main function
* which gives the first element, and then the programs writes the element
* to the file. Then Repeats the get_token() process until the line is done,
* and then does the same thing for the next line until the file is out of
* lines.
*
* @param int argc is number of command line arguments
* @param char* argv[] array of command line arguments made by user
*
* Where the first element in the array of command line input is the executable
* file, the second is the input file, and the third is the file to be
* written to.
*/
int main(int argc, char* argv[]) {
   int value;
   int cont = 1;
   
   while (cont != 0){
       is_error = 0;
       missing_parenthesis = 0;
       missing_semicolon = 0;
       printf("\nPlease enter expression: ");
       getline(&buffer, &length, stdin);
       strncpy(input_line, buffer, 100);
       remove_spaces(trimmed_line, input_line);
       line  =  trimmed_line;
       if((trimmed_line[0] == 'q') /*&& (sizeof(trimmed_line) == 1)*/){
           cont = 0;
       }else{
           token[0] = '\0';
           value = bexpr(token);


        if(value == ERROR) {
            if(missing_parenthesis == 1 && is_error == 0){
                printf("===> ) Expected\n");
                printf("Syntax Error");
            }
            if(missing_semicolon == 1 && is_error == 0){
                printf("Syntax Error");

            }
            if( is_error == 1){
            printf("===> %s \n", token);
            printf("Lexical Error: not a lexeme\n");
            }
        }else{
            printf("Syntax OK \nValue is %d", value);
        }
      }
   }
   printf("Goodbye!\n");
   return 0;
}

/*
 * Removes the white space in the input string.
 * @param trimmed result of the string without whitespace
 * @paramn untrimmed the input string to be trimmed of whitespace
 */
void remove_spaces( char* trimmed, char* untrimmed){
    while( *untrimmed != '\0'){
        if(!isspace(*untrimmed)){
            *trimmed = *untrimmed;
            trimmed++;
        }
        untrimmed++;
    }
    *trimmed = '\0';
}
