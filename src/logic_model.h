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

#define MAX_SOLVER_LOOPS 10000
#define MAX_CALCULATIONS 10000

#define INFI 9999999999999999999999999999999999999999999999999999999999999999.0L
#define UNINIT -68

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

#define TEMPXNUMLINDIA 6001.0L  // linear solver range

enum calc_CalculationError {
  calcerr_kNoError = 0,
  calcerr_kDivisionByZero,
  calcerr_kNan,
  calcerr_kBracketsAreInvaild,
  calcerr_kInvalidSymbols
};

void TestCalculate(char *input, char *output, int dummy);
void UnlockCalculate();

bool ContainsUnallowedTriples(const char *input_str);

int Validation(const char *expression);

void Calculate(view_to_calc_struct view_to_calc,
               calc_to_view_struct calc_to_view);

void CalculatorOutput(char *expression, char *output_answer,
                      enum calc_CalculationError calc_error);

void unfoldHelper(long double (*f)(long double), char *left, char *middle,
                  char *right, char *inputStr, int howManyLetters, int *err);
bool binarySearchSolver(char *expression, char *expectedAnswerStr, bool dir,
                        char *possibleAnswer);
void linearSolver(char *expression, long double expectedAnswer);
void ReplaceX(char *input_str, const char *input_x);
void addMultSignsToBrackets(char *inputStr);
void printHelper(char *inputStr);
void SprintfHelper(char *tempStr, long double calcResult);
void ThreeWaySplit(char *input_str, char *left, char *middle, char *right,
                   int start, int end);
int FindDeepestBrackets(char *inputStr, int *startIn, int *endIn);
void CalcErrorMessage(int error_enum, char *error_message);
void SplitInHalf(char *input_str, char *left, char *right, int split_pos);
bool AreBracketsValid(const char *inputStr);
void TransformUnariesModAndSpaces(char *inputStr);
void AddMultSigns(char *input);
long double LNum(char *inputStr, int operatorPos, int *digitsEnd);
long double RNum(char *inputStr, int operatorPos, int *digitsEnd);
int ParseAndApplyOperators(char *midStr);
void ourGcvt(long double value, char *buf, int ndigit);
bool zeroZeroes(char *str);
void nullCharArray(char *inputStr);
int OperatorPass(char *inputMid, char *opChar);
void CleanUpSpaces(char *inputStr);
int OperCount(char *inputStr);
void Recombine(char *inputStr, char *left, char *middle, char *right);
bool IsJustANumber(char *inputStr);
bool MultidotError(const char *input_str);
void AddOuterBrackets(char *inputStr);
bool doesHaveBrackets(char *inputStr);
int checkLeftBracketOper(char *leftStr, int leftBracketIdx);
void strBracketDeletion(char *inputStr, int start, int end);
void DeleteBrackets(char *left, char *right);
void wholeStrBracketDeletion(char *inputStr, int start, int end);
int unfoldBrackets(char *inputStr, int startIn, int endIn);
long double GetLeftOrRightDigits(char *inputMid, int operatorPos,
                                 int *digitsEnd, bool isLeft);
long double RNum(char *inputMid, int operatorPos, int *digitsEnd);
long double LNum(char *inputMid, int operatorPos, int *digitsEnd);
int OperatorPassLoop(char *inputMid, char *opChar);
void sravnenieSC();
#endif  // CALC_LOGIC_MODEL_H_