#ifndef CALC_LOGIC_MODEL_H_
#define CALC_LOGIC_MODEL_H_
#include <math.h>
#include <stdio.h>

#include <string>

#include "controller_constants.h"

#ifndef MAC
#include <unistd.h>
#elif WIN
// #include <unistd.h>
#endif

namespace s21 {

class S21LogicModel {
 public:
  // Public methods:
  void TestCalculate(char *input, char *output);
  void UnlockCalculate();
  void Calculate(S21ControllerConstants::view_to_calc_struct view_to_calc,
                 S21ControllerConstants::calc_to_view_struct calc_to_view);
  void BinarySearchSolver(
      S21ControllerConstants::view_to_calc_struct view_to_calc,
      S21ControllerConstants::calc_to_view_struct calc_to_view);
  void Graph(S21ControllerConstants::view_to_calc_struct view_to_calc,
             S21ControllerConstants::calc_to_view_struct calc_to_view);
  void ReplaceX(char *input_str, const char *input_x);

 private:
#ifdef CALC_WITH_OUTPUT
#define CALC_WITH_OUTPUT 1
#else
#define CALC_WITH_OUTPUT 0
#endif  // CALC_WITH_OUTPUT

#define CALC_STR_(X) #X
#define CALC_STR(X) CALC_STR_(X)
#define CALC_SPRINTF_PRECISION 10

  enum CalcErr {
    calc_Err_kOk = 0,
    calc_Err_kDivisionByZero,
    calc_Err_kNan,
    calc_Err_kBracketsAreInvaild,
    calc_Err_kInvalidSymbols,
    calc_Err_kSolverTimeout
  };

  // Private constants:
  static constexpr int calc_kUninit = -68;
  static constexpr int calc_kMaxSolverLoops = 5000;
  static constexpr long double calc_kInfinity =
      999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.0L;
  static constexpr long double calc_kSolverMidDefault = 0.0000001;
  static constexpr long double calc_kGraphDotsCount_local =
      S21ControllerConstants::calc_kGraphDotsCount;
  const std::string calc_kAllowedCharacters =
      "0123456789 +-*/%~ . ( ) cos sin tan acos asin atan sqrt ln log ^ e mod ";
  const std::string acos_str = "acos", asin_str = "asin", atan_str = "atan",
                    sqrt_str = "sqrt", cos_str = "cos", sin_str = "sin",
                    tan_str = "tan", log_str = "log", ln_str = "ln",
                    m_str = "_";

  const std::string DivisionByZero_message = "Division by zero is impossible";
  const std::string Nan_message = "NAN encountered during calculation";
  const std::string BracketsAreInvaild_message = "Brackets are invalid";
  const std::string InvalidSymbols_message = "Invalid symbols encountered";
  const std::string SolverTimeout_message = "Solver timeout reached";

  // Private methods:
  int OperCount(char *input);
  bool ContainsUnallowedTriplesAndWeirdness(const char *input_str);
  enum CalcErr Validation(const char *expression);
  void CalculatorOutput(char *expression, char *output_answer,
                        enum CalcErr calc_error);
  bool WeirdEnding(const char *input);
  bool ContainsInvalidCharacters(const char *input_str,
                                 const char *allowed_chars);
  bool ContainsUnallowedRepeatingChars(const char *input_str);
  enum CalcErr UnfoldHelper(long double (*fun)(long double), char *left,
                            char *middle, char *right, char *input_str,
                            const char *oper_str);
  void SprintfHelper(char *tempStr, long double calcResult);
  void ThreeWaySplit(char *input_str, char *left, char *middle, char *right,
                     int start, int end);
  int FindDeepestBrackets(char *inputStr, int *startIn, int *endIn);
  void CalcErrorMessage(enum CalcErr error_enum, char *error_message);
  void SplitInHalf(char *input_str, char *left, char *right, int split_pos);
  bool AreBracketsValid(const char *inputStr);
  void TransformUnariesModSpaces(char *inputStr);
  void AddMultSigns(char *input);
  enum CalcErr ParseAndApplyOperators(char *midStr);
  CalcErr OperatorPassLoop(char *input_mid, const char *op_char);
  CalcErr OperatorPass(char *input, const char *op_char);
  void CleanUpSpaces(char *inputStr);
  void Recombine(char *inputStr, char *left, char *middle, char *right);
  bool IsJustANumber(char *inputStr);
  bool MultidotError(const char *input_str);
  void AddOuterBrackets(char *inputStr);
  bool DoesHaveBrackets(char *inputStr);
  void DeleteBrackets(char *left, char *right);
  enum CalcErr UnfoldBrackets(char *inputStr, int startIn, int endIn);
  long double GetLeftOrRightDigits(char *inputMid, int operatorPos,
                                   int *digitsEnd, bool isLeft);
  long double RNum(char *inputMid, int operatorPos, int *digitsEnd);
  long double LNum(char *inputMid, int operatorPos, int *digitsEnd);
  int PossibleFalseZero(const char *input);
};
}  // namespace s21
#endif  // CALC_LOGIC_MODEL_H_
