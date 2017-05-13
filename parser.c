/*
 *
 * parser.c - recursive descent parser for a simple expression language.
 *            Most of the functions in this file model a Non-terminal in the
 *            grammar listed below
 * Author: Ethan Roland and Nick Sprinkle
 * Date:   4/18/2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "tokenizer.h"
#include "parser.h"

/*
 * <bexpr> ::= <expr> ;
 * <expr> ::=  <term> <ttail>
 * <ttail> ::=  <add_sub_tok> <term> <ttail> | e
 * <term> ::=  <stmt> <stail>
 * <stail> ::=  <mult_div_tok> <stmt> <stail> | e
 * <stmt> ::=  <factor> <ftail>
 * <ftail> ::=  <compare_tok> <factor> <ftail> | e
 * <factor> ::=  <expp> ^ <factor> | <expp>
 * <expp> ::=  ( <expr> ) | <num>
 * <add_sub_tok> ::=  + | -
 * <mul_div_tok> ::=  * | /
 * <compare_tok> ::=  < | > | <= | >= | ! = | ==
 * <num> ::=  {0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9}+
 */
extern char *line;  //imported pointer to ain's trimmed_line
extern int is_error; //imported error for non lexeme
extern int missing_parenthesis; //imported error for missing parenthesis
extern int missing_semicolon;  // imported error for missing semicolon

/*
 * The <bexpr> non-terminal for the parse tree. Turns the non-terminal
 * to the non-terminal <expr>
 * @param *token accepts a token
 * @return value the number for the math done
 * @return ERROR is a error number for incorrect syntax
 */
// <bexpr> ::= <expr> ;
int bexpr(char *token){
    get_token(token);
    int value = expr(token);
    if (!strncmp(token, ";", 1)){
        return value;
    }else{
        missing_semicolon = 1;
        return ERROR;
    }
}

/*
 *Turns the non-terminal <expr> into <term><ttail>. Enters into <term> 
 * if term returns a error then it returns the subtotal. Enters into <ttail>
 * if a error is not found.
 * @param token is part of the input string
 * @return subtotal is being returned if error
 * @return ttail is being returned if syntax is correct
 */
// <expr> -> <term> <ttail>
int expr(char *token){
   int subtotal = term(token);

   if (subtotal == ERROR){
      return subtotal;
   }else{
      return ttail(token, subtotal);
   }
}

/*
 * Tells if the token is a + or - sign. 
 * @param token which is the string that being input.
 * @param subtotal is the amount for the math that has been done.
 */
//<ttail> -> <add_sub_tok> <term> <ttail> | e
int ttail(char *token, int subtotal)
{
   int term_value;

   if (!strncmp(token, "+", 1))
   {
      add_sub_tok(token);
      term_value = term(token);

      // if term returned an error, give up otherwise call ttail
      if (term_value == ERROR)
         return term_value;
      else
         return ttail(token, (subtotal + term_value));
   }
   else if(!strncmp(token, "-", 1))
   {
      add_sub_tok(token);
      term_value = term(token);

      // if term returned an error, give up otherwise call ttail
      if (term_value == ERROR)
         return term_value;
      else
         return ttail(token, (subtotal - term_value));
   }
   /* empty string */
   else
      return subtotal;
}

/*
 * Breaks <term> into <stmt><stail>. 
 * @param token which is the string that is being input
 * @return subtotal if an error happens
 * @return stail which is the recursion for entering stail
 */
// <term> ::=  <stmt> <stail>
int term(char *token){
   int subtotal = stmt(token);
   if (subtotal == ERROR){
      return subtotal;
   }else{
      return stail(token, subtotal);
   }
}

/*
 * Detects if a multipler operator is needed to happen such as * or /.
 * @param token is the part of the string the parse tree is trying to figure
 *      out
 * @param subtotal is the part of the so far total of math that has been done
 * @return amount for the math that has been done
 */
// <stail> ::=  <mult_div_tok> <stmt> <stail> | e
int stail(char *token, int subtotal){
  int stmt_value;

   if (!strncmp(token, "*", 1))
   {
      mul_div_tok(token);
      stmt_value = stmt(token);

      // if term returned an error, give up otherwise call ttail
      if (stmt_value == ERROR)
         return stmt_value;
      else
         return stail(token, (subtotal * stmt_value));
   }
   else if(!strncmp(token, "/", 1))
   {
      mul_div_tok(token);
      stmt_value = stmt(token);

      // if term returned an error, give up otherwise call ttail
      if (stmt_value == ERROR)
         return stmt_value;
      else
         return stail(token, (subtotal / stmt_value));
   }
   /* empty string */
   else
      return subtotal;
}

/*
 * Breaksn <stmt> into <factor><ftail>.
 * @param token is the part of the string the parse tree is trying to detect
 * @return subtotal if an error has happen
 * @return ftail for the compare operators
 */
// <stmt> ::=  <factor> <ftail>
int stmt(char *token){
    int subtotal = factor(token);
    if (subtotal == ERROR){
        return subtotal;
    }else{
        return ftail(token, subtotal);
    }
}

/*
 * Figures out if token is a logical operator such as <, >, =, ==, <=, >=
 * @param token what is trying to be detected
 * @param subtotal amount so far done
 * @return amount after the math has been done
 */
// <ftail> ::=  <compare_tok> <factor> <ftail> | e
int ftail( char *token, int subtotal){
    int factor_value;

   if (!strncmp(token, "<", 1))
   {
      compare_tok(token);
      factor_value = factor(token);

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(token, (subtotal < factor_value));
   }
   else if(!strncmp(token, ">", 1))
   {
      compare_tok(token);
      factor_value = factor(token);

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(token, (subtotal > factor_value));
   }
   else if(!strncmp(token, "<=", 1))
   {
      compare_tok(token);
      factor_value = factor(token);

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(token, (subtotal <= factor_value));
   }
   else if(!strncmp(token, ">=", 1))
   {
      compare_tok(token);
      factor_value = factor(token);

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(token, (subtotal >= factor_value));
   }
   else if(!strncmp(token, "!=", 1))
   {
      compare_tok(token);
      factor_value = factor(token);

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(token, (subtotal != factor_value));
   }
   else if(!strncmp(token, "==", 1))
   {
      compare_tok(token);
      factor_value = factor(token);

      // if term returned an error, give up otherwise call ttail
      if (factor_value == ERROR)
         return factor_value;
      else
         return ftail(token, (subtotal == factor_value));
   }
   /* empty string */
   else
      return subtotal;
}

/*
 * Breaks the <factor> into <expp>^<factor> or <expp>.
 * @param token the part of the string that the parser has gotten too
 * @return the amount for the math done so far
 */
// <factor> ::=  <expp> ^ <factor> | <expp>
int factor(char *token){

    int subtotal = expp(token);
    int expp_value;
    if (subtotal == ERROR){
        return subtotal;
    }else{
        if (!strncmp(token, "^", 1)){
        expon_tok(token);
        expp_value = factor(token);
        int powered = pow(subtotal, expp_value);
        return (powered);
        }
        else{
            return subtotal;
        }
    }
}

/*
 * Breaks <expp> into ( <expr> ) or <num>
 * @param token which is the part of the input line that being detected
 * @return the correct math that has been done
 */
// <expp> ::=  ( <expr> ) | <num>
int expp(char *token){
    if(!strncmp(token, "(", 1)){
        get_token(token);
        int ret = expr(token);
        if(strncmp(token, ")", 1)){
            missing_parenthesis = 1;
            return ERROR;
        }
        get_token(token);
        return ret;
    }else{
        return num(token);
    }
}

/*
 * Calls tokenizer to detect if the token is a addition operator.
 * @param token that is being detected
 */
// <add_sub_tok> ::=  + | -
void add_sub_tok(char *token){
    get_token(token);
}

/*
 * Calls tokenizer to detect if the token is a multiplexor operator.
 * @param token is the token that is being detected
 */
// <mul_div_tok> ::=  * | /
void mul_div_tok(char *token){
    get_token(token);
}

/*
 * Calls the tokenizer to detect if a logical operator.
 * @param token is the token that is being detected
 */
// <compare_tok> ::=  < | > | <= | >= | ! = | ==
void compare_tok(char *token){
    get_token(token);
}

/*
 * Calls the tokenizer to detect if it is a exponent.
 * @param token that is being detected
 */
void expon_tok(char *token){
    get_token(token);
}

/*
 * Calls the is_number() function to detect what number the token is
 * @param token that is being detected
 * @return rint the number that was detected
 */
// <num> ::=  {0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9}+
int num(char *token){
    int rint = is_number(token);
    return rint;
}

/*
 * Tells if it is a number and if it is a number returns the number.
 * @param token which is the token that being detected
 * @return the number that was detected
 */
int is_number(char *token){
    char* lex = token;
    if(is_error == 0){
    int val = atoi(lex);
    get_token(token);
    return val;
    }else{
        return ERROR;
    }
}
