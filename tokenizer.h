/**
 * Header file for the tokenizer.c program
 *
 * @author Ethan Roland, Nick Sprinkle
 * @version 18 April 2016
 *
 */

#ifndef HEADER_H
#define HEADER_H

/* Constants */
#define LINE 100
#define TSIZE 20
#define TRUE 1
#define ARGUMENTS 3
#define FALSE 0

/**
* function prototypes
*/ 

void whitespace();
char* get_token(char *);

#endif



