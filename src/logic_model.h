#ifndef CALC_LOGIC_MODEL_H_
#define CALC_LOGIC_MODEL_H_
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller.h"

#ifndef MAC
#include <unistd.h>
#elif WIN
// #include <unistd.h>
#endif

#include "my_libs/vaslib.h"

#define STR_(X) #X
#define STR(X) STR_(X)

#define SPRINTF_PRECISION 10
#define MAX_SOLVER_LOOPS 10000
#define MAX_CALCULATIONS 10000

#define MAX_STRING_SIZE 16384
#define INFI 9999999999999999999999999999999999999999999999999999999999999999.0L
#define EPS 0.0000001
#define UNINIT -68

// OPERATION PASS ERROR TYPES:
#define OPER_PASS_DIVBYZERO 1
#define OPER_PASS_NAN 2
#define OPER_PASS_TIMEOUT 3
#define OPER_PASS_BRACKETS_COUNT_INVALID 4
#define OPER_PASS_INVALID_SYMBOLS 5

// LEFT BRACKET OPERATIONS:
#define BR_OPER_MINUS 1
#define BR_OPER_ACOS 2
#define BR_OPER_ASIN 3
#define BR_OPER_ATAN 4
#define BR_OPER_SQRT 5
#define BR_OPER_COS 6
#define BR_OPER_SIN 7
#define BR_OPER_TAN 8
#define BR_OPER_LOG 9
#define BR_OPER_LN 10

// CALCULATION ERROR MESSAGES:
#define MES_OPER_PASS_DIVBYZERO "Division by zero is impossible"
#define MES_OPER_PASS_NAN "NAN encountered during calculation"
#define MES_OPER_PASS_TIMEOUT "Input is probably invalid or NaN encountered"
#define MES_OPER_PASS_BRACKETS_COUNT_INVALID "Brackets count is invalid"
#define MES_OPER_PASS_INVALID_SYMBOLS "Invalid symbols encountered"

#define TEMPXNUMLINDIA 6001.0L  // linear solver range

void Calculate(view_to_calc_struct view_to_calc,
               calc_to_view_struct calc_to_view);

void unfoldHelper(long double (*f)(long double), char *left, char *middle,
                  char *right, char *inputStr, int howManyLetters, int *err);
bool binarySearchSolver(char *expression, char *expectedAnswerStr, bool dir,
                        char *possibleAnswer);
void linearSolver(char *expression, long double expectedAnswer);
void replaceX(char *inputStr, char *userX);
void addMultSignsToBrackets(char *inputStr);
void printHelper(char *inputStr);
void sprintfHelper(char *tempStr, long double calcResult);
void threeWaySplit(char *inputStr, char left[MAX_STRING_SIZE],
                   char middle[MAX_STRING_SIZE], char right[MAX_STRING_SIZE],
                   int start, int end);
int findDeepestBrackets(char *inputStr, int *startIn, int *endIn);
int IsBracketsCountValid(char *inputStr);
void transformUnariesAndMod(char *inputStr);
long double getLeftDigits(char *inputStr, int operatorPos, int *digitsEnd);
long double getRightDigits(char *inputStr, int operatorPos, int *digitsEnd);
void reverseString(char *string);
int parseAndApplyOperators(char *midStr);
void ourGcvt(long double value, char *buf, int ndigit);
bool zeroZeroes(char *str);
void nullCharArray(char *inputStr);
int operatorPass(char *inputMid, char opChar);
void cleanUpSpaces(char *inputStr);
int operatorCount(char *inputStr);
void recombine(char *inputStr, char *left, char *middle, char *right);
bool isJustANumber(char *inputStr);
void AddOuterBrackets(char *inputStr);
bool doesHaveBrackets(char *inputStr);
int checkLeftBracketOper(char *leftStr, int leftBracketIdx);
void strBracketDeletion(char *inputStr, int start, int end);
void pureLRBracketDeletion(char *left, char *right);
void wholeStrBracketDeletion(char *inputStr, int start, int end);
int findCharCount(char *inputStr, char *toFind);
int findAndReplaceChar(char *inputStr, char *toFind, char toReplace);
int unfoldBrackets(char *inputStr, int startIn, int endIn);
long double getLRDigits(char *inputMid, int operatorPos, int *digitsEnd,
                        bool isLeft);
long double getRightDigits(char *inputMid, int operatorPos, int *digitsEnd);
long double getLeftDigits(char *inputMid, int operatorPos, int *digitsEnd);
int operatorPassLoop(char *inputMid, char *opChar);
void sravnenieSC();
#endif  // CALC_LOGIC_MODEL_H_