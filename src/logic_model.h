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

#ifdef CALC_WITH_OUTPUT
#define CALC_WITH_OUTPUT 1
#else
#define CALC_WITH_OUTPUT 0
#endif  // CALC_WITH_OUTPUT

enum CalcErr {
  calc_Err_kOk = 0,
  calc_Err_kDivisionByZero,
  calc_Err_kNan,
  calc_Err_kBracketsAreInvaild,
  calc_Err_kInvalidSymbols,
  calc_Err_kSolverTimeout
};

int OperCount(char *input);
void TestCalculate(char *input, char *output);
void UnlockCalculate();

bool ContainsUnallowedTriples(const char *input_str);

enum CalcErr Validation(const char *expression);

void Calculate(view_to_calc_struct view_to_calc,
               calc_to_view_struct calc_to_view);

void CalculatorOutput(char *expression, char *output_answer,
                      enum CalcErr calc_error);

enum CalcErr UnfoldHelper(long double (*fun)(long double), char *left,
                          char *middle, char *right, char *input_str,
                          char *oper_str);
void BinarySearchSolver(view_to_calc_struct view_to_calc,
                        calc_to_view_struct calc_to_view);
void Graph(view_to_calc_struct view_to_calc, calc_to_view_struct calc_to_view);
void linearSolver(char *expression, long double expectedAnswer);
void ReplaceX(char *input_str, const char *input_x);
void addMultSignsToBrackets(char *inputStr);
void printHelper(char *inputStr);
void SprintfHelper(char *tempStr, long double calcResult);
void ThreeWaySplit(char *input_str, char *left, char *middle, char *right,
                   int start, int end);
int FindDeepestBrackets(char *inputStr, int *startIn, int *endIn);
void CalcErrorMessage(enum CalcErr error_enum, char *error_message);
void SplitInHalf(char *input_str, char *left, char *right, int split_pos);
bool AreBracketsValid(const char *inputStr);
void TransformUnariesModSpaces(char *inputStr);
void AddMultSigns(char *input);
long double LNum(char *inputStr, int operatorPos, int *digitsEnd);
long double RNum(char *inputStr, int operatorPos, int *digitsEnd);
enum CalcErr ParseAndApplyOperators(char *midStr);
void ourGcvt(long double value, char *buf, int ndigit);
bool zeroZeroes(char *str);
void nullCharArray(char *inputStr);
enum CalcErr OperatorPass(char *inputMid, char *opChar);
void CleanUpSpaces(char *inputStr);
int OperCount(char *inputStr);
void Recombine(char *inputStr, char *left, char *middle, char *right);
bool IsJustANumber(char *inputStr);
bool MultidotError(const char *input_str);
void AddOuterBrackets(char *inputStr);
bool DoesHaveBrackets(char *inputStr);
// enum calc_Oper CheckLeftBracketOper(char *left_str, int left_bracket_idx);
void strBracketDeletion(char *inputStr, int start, int end);
void DeleteBrackets(char *left, char *right);
void wholeStrBracketDeletion(char *inputStr, int start, int end);
enum CalcErr UnfoldBrackets(char *inputStr, int startIn, int endIn);
long double GetLeftOrRightDigits(char *inputMid, int operatorPos,
                                 int *digitsEnd, bool isLeft);
long double RNum(char *inputMid, int operatorPos, int *digitsEnd);
long double LNum(char *inputMid, int operatorPos, int *digitsEnd);
enum CalcErr OperatorPassLoop(char *inputMid, char *opChar);
void sravnenieSC();
#endif  // CALC_LOGIC_MODEL_H_