#ifndef CALC_LOGIC_MODEL_H_
#define CALC_LOGIC_MODEL_H_
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller.h"
#include "vaslib.h"

#ifndef MAC
#include <unistd.h>
#elif WIN
// #include <unistd.h>
#endif

#define MAX_SOLVER_LOOPS 10000
#define MAX_CALCULATIONS 10000

#define INFI 9999999999999999999999999999999999999999999999999999999999999999.0L
#define UNINIT -68

#define TEMPXNUMLINDIA 6001.0L  // linear solver range

enum calc_Err {
  calc_Err_kOk = 0,
  calc_Err_kDivisionByZero,
  calc_Err_kNan,
  calc_Err_kBracketsAreInvaild,
  calc_Err_kInvalidSymbols
};

int OperCount(char *input);
void TestCalculate(char *input, char *output, int dummy);
void UnlockCalculate();

bool ContainsUnallowedTriples(const char *input_str);

enum calc_Err Validation(const char *expression);

void Calculate(view_to_calc_struct view_to_calc,
               calc_to_view_struct calc_to_view);

void CalculatorOutput(char *expression, char *output_answer,
                      enum calc_Err calc_error);

void unfoldHelper(long double (*f)(long double), char *left, char *middle,
                  char *right, char *inputStr, int howManyLetters,
                  enum calc_Err *err);
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
void CalcErrorMessage(enum calc_Err error_enum, char *error_message);
void SplitInHalf(char *input_str, char *left, char *right, int split_pos);
bool AreBracketsValid(const char *inputStr);
void TransformUnariesModAndSpaces(char *inputStr);
void AddMultSigns(char *input);
long double LNum(char *inputStr, int operatorPos, int *digitsEnd);
long double RNum(char *inputStr, int operatorPos, int *digitsEnd);
enum calc_Err ParseAndApplyOperators(char *midStr);
void ourGcvt(long double value, char *buf, int ndigit);
bool zeroZeroes(char *str);
void nullCharArray(char *inputStr);
enum calc_Err OperatorPass(char *inputMid, char *opChar);
void CleanUpSpaces(char *inputStr);
int OperCount(char *inputStr);
void Recombine(char *inputStr, char *left, char *middle, char *right);
bool IsJustANumber(char *inputStr);
bool MultidotError(const char *input_str);
void AddOuterBrackets(char *inputStr);
bool DoesHaveBrackets(char *inputStr);
enum calc_Oper checkLeftBracketOper(char *left_str, int left_bracket_idx);
void strBracketDeletion(char *inputStr, int start, int end);
void DeleteBrackets(char *left, char *right);
void wholeStrBracketDeletion(char *inputStr, int start, int end);
enum calc_Err unfoldBrackets(char *inputStr, int startIn, int endIn);
long double GetLeftOrRightDigits(char *inputMid, int operatorPos,
                                 int *digitsEnd, bool isLeft);
long double RNum(char *inputMid, int operatorPos, int *digitsEnd);
long double LNum(char *inputMid, int operatorPos, int *digitsEnd);
enum calc_Err OperatorPassLoop(char *inputMid, char *opChar);
void sravnenieSC();
#endif  // CALC_LOGIC_MODEL_H_