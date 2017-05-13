/**
 * This program accepts an input file that is written in a programming language
 * and then it figures out which characters are accepts in the program's
 * language or not. It then writes to an file each character name and if it
 * is a token or not.
 *
 * tokenizer.c - A simple token recognizer.
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
#include "tokenizer.h"

/*
 * Figures out if the char that line is currently pointing to is any
 * reconized token for the tokenizer. If it is then it increments the line
 * and puts what token it is to whatever the token_ptr is pointing to.
 *
 * @param char *token_ptr pointer to an char array
 */
extern char *line ; // imported global var from main
//char token_ptr[LINE];
int is_error; // error value for non lexeme

/*
 * Detects what a char is exactly in the legal char's used in the program 
 * language.
 * @param token_ptr is a pointer to one char
 * @return token_ptr which is the token that was detected 
 */
char* get_token(char *token_ptr){

        //checks to see if the char is +
        if(*line == '+'){
            token_ptr[0] = '+';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the char is -
        else if(*line == '-'){
            token_ptr[0] = '-';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the char is *
        else if(*line ==  '*'){
            token_ptr[0] = '*';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the char is /
        else if(*line == '/'){
            token_ptr[0] = '/';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the char is (
        else if(*line == '('){
            token_ptr[0] = '(';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the char is )
        else if(*line == ')'){
            token_ptr[0] = ')';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the char is ^
        else if(*line == '^'){
            token_ptr[0] = '^';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the char is ;
        else if(*line == ';'){
            token_ptr[0] = ';';
            token_ptr[1] = '\0';
            line++;
            return token_ptr;
        }

        //checks to see if the next token is = or ==
        else if(*line == '='){
            line++;
            if(*line == '='){
                token_ptr[0] = '=';
                token_ptr[1] = '=';
                token_ptr[2] = '\0';
                line++;
                return token_ptr;
            }
            else{

                token_ptr[0] = '=';
                token_ptr[1] = '\0';
                return token_ptr;
            }
        }

        //checks to see if the token is < or <=
        else if(*line == '<'){
            line++;
            if(*line == '='){
                token_ptr[0] = '<';
                token_ptr[1] = '=';
                token_ptr[2] = '\0';
                line++;
            return token_ptr;
            }
            else{
                token_ptr[0] = '<';
                token_ptr[1] = '\0';
            return token_ptr;
            }
        }

        //checks to see if the token is > or >=
        else if(*line == '>'){
            line++;
            if(*line == '='){
                token_ptr[0] = '>';
                token_ptr[1] = '=';
                token_ptr[2] = '\0';
                line++;
            return token_ptr;
            }
            else{
                token_ptr[0] = '>';
                token_ptr[1] = '\0';
            return token_ptr;
            }
        }

        //checks to see if the token is ! or !=
        else if(*line == '!'){
            line++;
            if(*line == '='){
                token_ptr[0] = '!';
                token_ptr[1] = '=';
                token_ptr[2] = '\0';
                line++;
            return token_ptr;
            }
            else{
                token_ptr[0] = '!';
                token_ptr[1] = '\0';
            return token_ptr;
            }
        }

        //checks to see if the next token is a digit or multiple digits
        else if( isdigit(*line)){
            int i = 0;
            token_ptr[i] = *line;
            line++;
            i++;
            while(isdigit(*line)){
                token_ptr[i] = *line;
                line++;
                i++;
            }
                token_ptr[i] = '\0';
            return token_ptr;
        }

        //if none of the above is accepted then this creates an error
        else if(*line != '\0'){
            token_ptr[0] = *line;
            token_ptr[1] = '\0';
            line++;
            is_error = 1;
            return token_ptr;
        }
        return token_ptr;
}
