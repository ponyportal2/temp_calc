#include "logic_model.h"

#include "vaslib.h"

// TODO: DOUBLE DOT
const int calc_kUninit = -68;
#define CALC_STR_(X) #X
#define CALC_STR(X) CALC_STR_(X)
#define CALC_SPRINTF_PRECISION 10

enum calc_Oper {
  calc_Oper_kNone = 0,
  calc_Oper_kMinus,
  calc_Oper_kAcos,
  calc_Oper_kAsin,
  calc_Oper_kAtan,
  calc_Oper_kSqrt,
  calc_Oper_kCos,
  calc_Oper_kSin,
  calc_Oper_kTan,
  calc_Oper_kLog,
  calc_Oper_kLn,
};

// LEFT BRACKET OPERATIONS:
#define CALC_OPER_MINUS 1
#define CALC_OPER_ACOS 2
#define CALC_OPER_ASIN 3
#define CALC_OPER_ATAN 4
#define CALC_OPER_SQRT 5
#define CALC_OPER_COS 6
#define CALC_OPER_SIN 7
#define CALC_OPER_TAN 8
#define CALC_OPER_LOG 9
#define CALC_OPER_LN 10

void CalcErrorMessage(enum calc_Err error_enum, char *error_message) {
  const char *DivisionByZero_message = "Division by zero is impossible";
  const char *Nan_message = "NAN encountered during calculation";
  const char *BracketsAreInvaild_message = "Brackets are invalid";
  const char *InvalidSymbols_message = "Invalid symbols encountered";
  if (error_enum == calc_Err_kDivisionByZero) {
    strcpy(error_message, DivisionByZero_message);
  } else if (error_enum == calc_Err_kNan) {
    strcpy(error_message, Nan_message);
  } else if (error_enum == calc_Err_kBracketsAreInvaild) {
    strcpy(error_message, BracketsAreInvaild_message);
  } else if (error_enum == calc_Err_kInvalidSymbols) {
    strcpy(error_message, InvalidSymbols_message);
  }
}

// Binary search solver:
// bool binarySearchSolver(char *expression, char *expectedAnswerStr, bool dir,
//                         char *possibleAnswer) {
//   long double expectedAnswer = 0.0L;
//   expectedAnswer = strtold(expectedAnswerStr, NULL);
//   char localExpression[MAX_STRING_SIZE] = {0};
//   long double answerNum = 0.0L;
//   char answerStr[MAX_STRING_SIZE] = {0};
//   long double top = (long double)(DBL_MAX - 1.0L) / 2.0L;
//   long double mid = 0.53534534;
//   long double bot = (long double)(-DBL_MAX + 1.0L) / 2.0L;
//   char midStr[MAX_STRING_SIZE] = {0};
//   long counter = 0;
//   bool returnValue = false;
//   bool whileBreakInvalidInput = false;
//   do {
//     strcpy(localExpression, expression);
//     sprintfHelper(midStr, mid);
//     replaceX(localExpression, midStr);
//     Calculate(localExpression, answerStr, 0);
//     if (strcmp(answerStr, MES_OPER_PASS_BRACKETS_COUNT_INVALID) != 0 &&
//         strcmp(answerStr, MES_OPER_PASS_INVALID_SYMBOLS) != 0 &&
//         strcmp(answerStr, MES_OPER_PASS_TIMEOUT) != 0) {
//       answerNum = strtold(answerStr, NULL);
//       counter++;
//       if (dir == 0) {
//         if (answerNum < expectedAnswer) {
//           bot = mid;
//           mid = (long double)(top + mid) / 2.0L;
//         }
//         if (answerNum > expectedAnswer) {
//           top = mid;
//           mid = (long double)(bot + mid) / 2.0L;
//         }
//       } else if (dir == 1) {
//         if (answerNum > expectedAnswer) {
//           bot = mid;
//           mid = (long double)(top + mid) / 2.0L;
//         }
//         if (answerNum < expectedAnswer) {
//           top = mid;
//           mid = (long double)(bot + mid) / 2.0L;
//         }
//       }
//       UnlockCalculate();
//     } else {
//       whileBreakInvalidInput = true;
//     }
//   } while (fabsl(answerNum - expectedAnswer) > 0.0000001 &&
//            counter < MAX_SOLVER_LOOPS && whileBreakInvalidInput == false);
//   if (counter < MAX_SOLVER_LOOPS && whileBreakInvalidInput == false) {
//     // sprintf(possibleAnswer, "%.6f", (double)mid);  // WIN
//     sprintf(possibleAnswer, "%.6Lf", mid);  // MAC
//     cleanUpTrailingZeroes(possibleAnswer);
//     returnValue = true;
//   }
//   UnlockCalculate();
//   return returnValue;
// }

void SplitInHalf(char *input_str, char *left, char *right, int split_pos) {
  if (split_pos > -1 && split_pos < (int)strlen(input_str)) {
    strncpy(left, input_str, split_pos + 1);
    strcpy(right, input_str + split_pos + 1);
  }
  strcpy(input_str, "\0");
}

bool AreBracketsValid(const char *input_str) {
  int i = 0, left_count = 0, right_count = 0, mismatch = 0;
  bool are_valid = false;
  while (input_str[i] != '\0' && mismatch > -1) {
    if (input_str[i] == '(') {
      mismatch++;
      left_count++;
    } else if (input_str[i] == ')') {
      mismatch--;
      right_count++;
    }
    ++i;
  }
  if (left_count == right_count) are_valid = true;
  if (left_count != right_count) are_valid = false;
  if (mismatch < 0) are_valid = false;
  return are_valid;
}

void UnlockCalculate() {
  view_to_calc_struct view_to_calc;
  view_to_calc.unlock = true;
  calc_to_view_struct calc_to_view;
  Calculate(view_to_calc, calc_to_view);
}

void TestCalculate(char *input, char *output, int dummy) {
  calc_to_view_struct calc_to_view;
  view_to_calc_struct view_to_calc;
  view_to_calc.calc_input = (char *)calloc(calc_kMaxStrSize, sizeof(char));
  calc_to_view.answer = (char *)calloc(calc_kMaxStrSize, sizeof(char));
  strcpy(view_to_calc.calc_input, input);
  view_to_calc.calculation_type = calc_kCalculate;
  view_to_calc.unlock = false;
  Calculate(view_to_calc, calc_to_view);
  strcpy(output, calc_to_view.answer);
  if (view_to_calc.calc_input) free(view_to_calc.calc_input);
  if (calc_to_view.answer) free(calc_to_view.answer);
  UnlockCalculate();
}

bool ContainsInvalidCharacters(const char *input_str) {
  const char *kAllowedCharacters =
      "0123456789 +-*/% . ( ) cos sin tan acos asin atan sqrt ln log ^ e mod ~";
  bool it_does = false;
  for (int i = 0; input_str[i] != '\0'; ++i) {
    if (VasCharMatch(input_str[i], kAllowedCharacters) == 0) {
      it_does = true;
    }
  }
  return it_does;
}

bool ContainsUnallowedRepeatingChars(const char *input_str) {
  const char *kUnallowedRepeating = "a cos sin tan sqrt ln log ^ e mod . * / %";
  bool it_does = false, loop_break = false;
  char previous_char = 0;
  for (int i = 0; input_str[i] != '\0' && !loop_break; ++i) {
    if (i != 0) {
      char current_char = input_str[i];
      if (current_char == previous_char &&
          VasCharMatch(input_str[i], kUnallowedRepeating)) {
        it_does = true;
        loop_break = true;
      }
      previous_char = current_char;
    } else if (i == 0) {
      previous_char = input_str[i];
    }
  }
  return it_does;
}

bool ContainsUnallowedTriples(const char *input) {
  bool it_does = false;
  if (strstr(input, "---") || strstr(input, "+++")) it_does = true;
  return it_does;
}

bool MultidotError(const char *input_str) {
  bool double_dot_found = false, number_started = false;
  int dot_count = 0;
  char to_match[calc_kMaxStrSize] = "0123456789.";
  for (int i = 0; input_str[i] != '\0' && !double_dot_found; ++i) {
    if (VasCharMatch(input_str[i], to_match)) {
      number_started == 1;
      if (input_str[i] == '.') ++dot_count;
    } else if (!VasCharMatch(input_str[i], to_match)) {
      number_started == 0;
      dot_count = 0;
    }
    if (dot_count > 1) double_dot_found = true;
  }
  return double_dot_found;
}

enum calc_Err Validation(const char *expression) {
  enum calc_Err expression_error = calc_Err_kOk;
  if (!AreBracketsValid(expression)) {
    expression_error = calc_Err_kBracketsAreInvaild;
  }
  if (ContainsInvalidCharacters(expression) ||
      ContainsUnallowedRepeatingChars(expression) ||
      ContainsUnallowedTriples(expression) || MultidotError(expression)) {
    expression_error = calc_Err_kInvalidSymbols;
  }
  return expression_error;
}

// Main calculation:
void Calculate(view_to_calc_struct view_to_calc,
               calc_to_view_struct calc_to_view) {
  static bool locked = false;
  if (view_to_calc.unlock == true) locked = false;
  if (view_to_calc.unlock == false && locked == false) {
    locked = true;
    if (view_to_calc.calculation_type == calc_kCalculateWithX) {
      ReplaceX(view_to_calc.calc_input, view_to_calc.x_variable);
    }
    char expression[calc_kMaxStrSize] = {0};
    strcpy(expression, view_to_calc.calc_input);
    enum calc_Err expression_error = Validation(expression);
    if (!expression_error) {
      TransformUnariesModAndSpaces(expression);
      AddMultSigns(expression);
      AddOuterBrackets(expression);
      int start = calc_kUninit, end = calc_kUninit, missing_brackets = 0;
      bool calc_finished = false;
      while (!missing_brackets && !calc_finished && !expression_error) {
        printf("%s\n", expression);
        char prev_expression[calc_kMaxStrSize] = {0};
        strcpy(prev_expression, expression);
        char left[calc_kMaxStrSize] = {0}, middle[calc_kMaxStrSize] = {0},
             right[calc_kMaxStrSize] = {0};
        missing_brackets = FindDeepestBrackets(expression, &start, &end);
        if (missing_brackets) break;
        ThreeWaySplit(expression, left, middle, right, start, end);
        expression_error = ParseAndApplyOperators(middle);
        if (expression_error) break;
        Recombine(expression, left, middle, right);
        missing_brackets = FindDeepestBrackets(expression, &start, &end);
        expression_error = unfoldBrackets(expression, start, end);
        if (!DoesHaveBrackets(expression) && !IsJustANumber(expression)) {
          AddOuterBrackets(expression);
        } else if (!DoesHaveBrackets(expression)) {
          calc_finished = true;
        }
        if (strcmp(prev_expression, expression) == 0) calc_finished = true;
      }
    }
    CalculatorOutput(expression, calc_to_view.answer, expression_error);
  }
}

void CalculatorOutput(char *expression, char *output_answer,
                      enum calc_Err calc_error) {
  if (expression[0] == '~') expression[0] = '-';
  if (calc_error != calc_Err_kOk) {
    CalcErrorMessage(calc_error, output_answer);
  } else if (!IsJustANumber(expression)) {
    calc_error = calc_Err_kInvalidSymbols;
    CalcErrorMessage(calc_error, output_answer);
  } else {
    long double final_result = strtold(expression, NULL);
    if (final_result > INFI) {
      strcpy(output_answer, "inf");
    } else if (final_result < (INFI * -1)) {
      strcpy(output_answer, "-inf");
    } else {
      SprintfHelper(output_answer, final_result);
      VasCleanUpSpaces(output_answer);
      VasCleanUpTrailingZeroes(output_answer);
    }
  }
  printf("\nFINAL ANSWER: %s\n\n", output_answer);
};

void AddOuterBrackets(char *input_str) {
  char temp_str[calc_kMaxStrSize] = {0};
  strcat(temp_str, "(");
  strcat(temp_str, input_str);
  strcat(temp_str, ")");
  strcpy(input_str, temp_str);
}

bool DoesHaveBrackets(char *input_str) {
  return (VasCharMatch('(', input_str) || VasCharMatch(')', input_str));
}

void ReplaceX(char *input_str, const char *input_x) {
  char input_x_local[calc_kMaxStrSize] = {0};
  strcpy(input_x_local, input_x);
  if (input_x_local[0] == '-') input_x_local[0] = '~';
  for (int i = 0; input_str[i] != '\0';) {
    if (input_str[i] == 'x' || input_str[i] == 'X') {
      char temp_str[calc_kMaxStrSize] = {0}, left[calc_kMaxStrSize] = {0},
           right[calc_kMaxStrSize] = {0};
      SplitInHalf(input_str, left, right, i);
      strncpy(temp_str, left, strlen(left) - 1);
      strcat(temp_str, input_x_local);
      strcat(temp_str, right);
      strcpy(input_str, temp_str);
      i = 0;
    } else {
      ++i;
    }
  }
}

int FindDeepestBrackets(char *input_str, int *start_in, int *end_in) {
  int has_error = 0, i = 0, start = calc_kUninit, end = calc_kUninit;
  bool loop_break = false;
  while (loop_break == false) {
    if (input_str[i] == '(') {
      start = i;
    } else if (input_str[i] == ')') {
      end = i;
      loop_break = true;
    } else if (input_str[i] == '\0') {
      if (start == calc_kUninit || end == calc_kUninit) has_error = 1;
      loop_break = true;
    }
    ++i;
  }
  if (has_error == 0) {
    *start_in = start;
    *end_in = end;
  }
  return has_error;
}

enum calc_Err unfoldBrackets(char *input_str, int start_in, int end_in) {
  enum calc_Oper oper = checkLeftBracketOper(input_str, start_in);
  char left[calc_kMaxStrSize] = {0}, mid[calc_kMaxStrSize] = {0},
       right[calc_kMaxStrSize] = {0}, temp_str[calc_kMaxStrSize] = {0};
  enum calc_Err err = calc_Err_kOk;
  ThreeWaySplit(input_str, left, mid, right, start_in, end_in);
  if (oper == CALC_OPER_MINUS) {
    if (mid[0] == '~') {
      strcpy(temp_str, (char *)mid + 1);
    } else if (mid[0] != '~') {
      strcat(temp_str, "~");
      strcat(temp_str, mid);
    }
    strcpy(mid, temp_str);
    DeleteBrackets(left, right);
    left[strlen(left) - 1] = '\0';
    Recombine(input_str, left, mid, right);
  } else if (oper == CALC_OPER_ACOS) {
    unfoldHelper(acosl, left, mid, right, input_str, 4, &err);
  } else if (oper == CALC_OPER_ASIN) {
    unfoldHelper(asinl, left, mid, right, input_str, 4, &err);
  } else if (oper == CALC_OPER_ATAN) {
    unfoldHelper(atanl, left, mid, right, input_str, 4, &err);
  } else if (oper == CALC_OPER_SQRT) {
    if (mid[0] == '-' || mid[0] == '~') {  // negative sqrt is a complex number
      err = calc_Err_kNan;
    } else {
      unfoldHelper(sqrtl, left, mid, right, input_str, 4, &err);
    }
  } else if (oper == CALC_OPER_COS) {
    unfoldHelper(cosl, left, mid, right, input_str, 3, &err);
  } else if (oper == CALC_OPER_SIN) {
    unfoldHelper(sinl, left, mid, right, input_str, 3, &err);
  } else if (oper == CALC_OPER_TAN) {
    unfoldHelper(tanl, left, mid, right, input_str, 3, &err);
  } else if (oper == CALC_OPER_LOG) {
    unfoldHelper(log10l, left, mid, right, input_str, 3, &err);
  } else if (oper == CALC_OPER_LN) {
    unfoldHelper(logl, left, mid, right, input_str, 2, &err);
  } else if (oper == 0) {
    DeleteBrackets(left, right);
    Recombine(input_str, left, mid, right);
  }
  return err;
}

void unfoldHelper(long double (*f)(long double), char *left, char *middle,
                  char *right, char *inputStr, int howManyLetters,
                  enum calc_Err *err) {
  SprintfHelper(middle, f(strtold(middle, NULL)));
  if (strstr("nan", middle) || strstr("NaN", middle) || strstr("NAN", middle)) {
    *err = calc_Err_kNan;
  }
  DeleteBrackets(left, right);
  left[strlen(left) - howManyLetters] = '\0';
  Recombine(inputStr, left, middle, right);
}

enum calc_Oper checkLeftBracketOper(char *left_str, int left_bracket_idx) {
  enum calc_Oper left_bracket_oper = calc_Oper_kNone;
  int i = left_bracket_idx;
  char temp_str[5] = {0};
  VasClearCharArray(temp_str, 5);
  for (int j = 1; j <= 4; ++j) {
    if (left_str[i - j] > -1) temp_str[j - 1] = left_str[i - j];
  }
  VasReverseCharArray(temp_str);
  if (strstr(temp_str, "acos")) {
    left_bracket_oper = calc_Oper_kAcos;
  } else if (strstr(temp_str, "asin")) {
    left_bracket_oper = calc_Oper_kAsin;
  } else if (strstr(temp_str, "atan")) {
    left_bracket_oper = calc_Oper_kAtan;
  } else if (strstr(temp_str, "sqrt")) {
    left_bracket_oper = calc_Oper_kSqrt;
  } else if (strstr(temp_str, "cos")) {
    left_bracket_oper = calc_Oper_kCos;
  } else if (strstr(temp_str, "sin")) {
    left_bracket_oper = calc_Oper_kSin;
  } else if (strstr(temp_str, "tan")) {
    left_bracket_oper = calc_Oper_kTan;
  } else if (strstr(temp_str, "log")) {
    left_bracket_oper = calc_Oper_kLog;
  } else if (strstr(temp_str, "ln")) {
    left_bracket_oper = calc_Oper_kLn;
  } else if (strstr(temp_str, "_")) {
    left_bracket_oper = calc_Oper_kMinus;
  }
  return left_bracket_oper;
}

void DeleteBrackets(char *left, char *right) {
  if (strlen(left) > 0) left[strlen(left) - 1] = '\0';
  if (strlen(right) > 0) {
    char tempStr[calc_kMaxStrSize] = {0};
    strcpy(tempStr, (char *)right + 1);
    strcpy(right, tempStr);
  }
}

void TransformUnariesModAndSpaces(char *input) {
  char before[calc_kMaxStrSize] = {0};
  do {
    strcpy(before, input);
    if (input[0] == '-' && input[1] == '(') {
      VasCpy(input, 0, "_(");  // -( starting unary
    } else if (input[0] == '-' && input[1] == '-') {
      VasCpy(input, 0, "  ");  // -- starting unary
    } else if (input[0] == '-') {
      VasCpy(input, 0, "~");  // any other - starting unary:
    } else if (input[0] == '+') {
      VasCpy(input, 0, " ");  // + starting unary:
    }
    VasReplace(input, "(-(", "(_(");
    VasReplace(input, "mod", "  %");
    VasReplace(input, "++", "+ ");
    VasReplace(input, "-+", "- ");
    VasReplace(input, "+-", "+~");
    VasReplace(input, "~-", " +");
    VasReplace(input, "--", " +");
    VasReplace(input, "(+", "( ");
    VasReplace(input, "(-", "(~");
    VasReplace(input, "/+", "/ ");
    VasReplace(input, "/-", "/~");
    VasReplace(input, "*+", "* ");
    VasReplace(input, "*-", "*~");
    VasReplace(input, "^+", "^ ");
    VasReplace(input, "^-", "^~");
    VasReplace(input, "%+", "% ");
    VasReplace(input, "%-", "%~");
    VasCleanUpSpaces(input);
  } while (strcmp(before, input) != 0);
}

void AddMultSigns(char *input) {
  int err = 0;
  for (int i = 0; input[i] != '\0'; ++i) {
    if ((input[i] >= 48 && input[i] <= 57) && input[i + 1] == '(') {
      VasInsert(input, i + 1, "*");
    } else if (input[i] == ')' && (input[i + 1] >= 48 && input[i + 1] <= 57)) {
      VasInsert(input, i + 1, "*");
    } else if (input[i] == ')' && input[i + 1] == '~') {
      VasInsert(input, i + 1, "*");
    } else if (input[i] == ')' && input[i + 1] == '(') {
      VasInsert(input, i + 1, "*");
    }
  }
}

void Recombine(char *input_str, char *left, char *middle, char *right) {
  strcpy(input_str, left);
  strcat(input_str, middle);
  strcat(input_str, right);
}

long double LNum(char *input_mid, int oper_pos, int *digits_end) {
  return GetLeftOrRightDigits(input_mid, oper_pos, digits_end, true);
}

long double RNum(char *input_mid, int oper_pos, int *digits_end) {
  return GetLeftOrRightDigits(input_mid, oper_pos, digits_end, false);
}

long double GetLeftOrRightDigits(char *input, int oper_position,
                                 int *digits_end, bool is_left) {
  char *to_match = "0123456789~. inf nan NAN";
  char final_number[calc_kMaxStrSize] = {0};
  int i = 0;
  if (is_left) i = oper_position - 1;
  if (!is_left) i = oper_position + 1;
  bool loop_break = false;
  while (loop_break == false) {
    if (input[i] != '~') {
      char temp_str[2] = {input[i], '\0'};
      strcat(final_number, temp_str);
    } else {
      strcat(final_number, "-");
    }
    if (is_left) --i;
    if (!is_left) ++i;
    if (i < 0 || i == (int)strlen(input) || input[i] == '\0') loop_break = true;
    if (VasCharMatch(input[i], to_match) != true) loop_break = true;
  }
  *digits_end = i;
  if (is_left) VasReverseCharArray(final_number);
  return strtold(final_number, NULL);
}

int OperCount(char *input) { return VasCountOfChars(input, "^/*%-+"); }

enum calc_Err ParseAndApplyOperators(char *mid_inp) {
  enum calc_Err err = calc_Err_kOk;
  bool loop_break = false;
  while (1) {
    if (err = OperatorPassLoop(mid_inp, "^")) break;
    if (err = OperatorPassLoop(mid_inp, "/*%")) break;
    while (VasCountOfChars(mid_inp, "-") > 0) {
      if (mid_inp[0] == '-' && OperCount(mid_inp) == 1) mid_inp[0] = '~';
      if (err = OperatorPassLoop(mid_inp, "-+")) break;
    }
    if (err = OperatorPassLoop(mid_inp, "-+")) break;
    if (OperCount(mid_inp) < 1 || IsJustANumber(mid_inp)) break;
  }
  return err;
}

enum calc_Err OperatorPassLoop(char *input_mid, char *op_char) {
  enum calc_Err err = calc_Err_kOk;
  bool loop_break = false;
  while (VasCountOfChars(input_mid, op_char) > 0 && loop_break == false) {
    if (err = OperatorPass(input_mid, op_char)) loop_break = true;
  }
  return err;
}

enum calc_Err OperatorPass(char *input, char *op_char) {
  enum calc_Err err = calc_Err_kOk;
  int i = 0, res_start = calc_kUninit, res_end = calc_kUninit;
  long double result = 0.0L;
  char char_array_result[calc_kMaxStrSize] = {0};
  bool zero_div = false;
  while (input[i] != '\0' && !zero_div) {
    if (VasCharMatch(input[i], op_char)) {
      switch (input[i]) {
        case '^':
          result = powl(LNum(input, i, &res_start), RNum(input, i, &res_end));
          break;
        case '%':
          result = fmodl(LNum(input, i, &res_start), RNum(input, i, &res_end));
          break;
        case '*':
          result = LNum(input, i, &res_start) * RNum(input, i, &res_end);
          break;
        case '/':
          if (RNum(input, i, &res_end) == 0) {
            zero_div == true;
            err = calc_Err_kDivisionByZero;
          } else {
            result = LNum(input, i, &res_start) / RNum(input, i, &res_end);
          }
          break;
        case '+':
          result = LNum(input, i, &res_start) + RNum(input, i, &res_end);
          break;
        case '-':
          result = LNum(input, i, &res_start) - RNum(input, i, &res_end);
          break;
      }
      SprintfHelper(char_array_result, result);
      if (char_array_result[0] == '-') char_array_result[0] = '~';
      TransformUnariesModAndSpaces(input);
      if (OperCount(input) > 0) {
        char left[calc_kMaxStrSize] = {0}, middle[calc_kMaxStrSize] = {0},
             right[calc_kMaxStrSize] = {0};
        ThreeWaySplit(input, left, middle, right, res_start, res_end);
        Recombine(input, left, char_array_result, right);
      } else if (OperCount(input) == 0) {
        strcpy(input, char_array_result);
      }
    }
    ++i;
  }
  if (result != result && err == 0) err = calc_Err_kNan;
  return err;
}

void SprintfHelper(char *temp_str, long double input) {
  sprintf(temp_str, "%." CALC_STR(CALC_SPRINTF_PRECISION) "Lf", input);
}

void ThreeWaySplit(char *input, char *left, char *middle, char *right,
                   int start, int end) {
  if (start >= 0) strncpy(left, input, start + 1);
  strncpy(middle, input + start + 1, end - start - 1);
  if (end < (int)strlen(input)) strcpy(right, input + start + (end - start));
  strcpy(input, "\0");
}

bool IsJustANumber(char *input_str) {
  char to_match[calc_kMaxStrSize] = "0123456789. inf NAN nan";
  int i = 0;
  bool is_num = true;
  if (strlen(input_str) == 0) is_num = false;
  if (input_str[0] == '-' || input_str[0] == '~') i = 1;
  while (is_num && input_str[i] != '\0') {
    if (VasCharMatch(input_str[i], to_match) == false) is_num = false;
    ++i;
  }
  return is_num;
}

// FOR DEBUGGING:
// --------------

// void sravnenieSC() {
//   long double aboba = 0.0L;
//   aboba = sqrt(-100);
//   // printf("%.10f", (double)aboba);  // WIN
//   printf("%.10Lf", aboba);  // MAG
// }

// void printHelper(char *inputStr) {
//   char tempStr[MAX_STRING_SIZE] = {0};
//   strcpy(tempStr, inputStr);
//   cleanUpTrailingZeroes(tempStr);
//   printf("[%s]\n", tempStr);
// }

// UNUSED:
// -------

// void strBracketDeletion(char *inputStr, int start, int end) {
//   char tempStr[MAX_STRING_SIZE] = {0};
//   if (start > -1) {
//     strncat(tempStr, inputStr, start);
//   }
//   strncat(tempStr, inputStr + start + 1, end - start - 1);
//   if (end < (int)strlen(inputStr)) {
//     strcat(tempStr, inputStr + start + (end - start) + 1);
//   }
//   strcpy(inputStr, tempStr);
// }

// enum calc_kAreBracketsValid {
//   calc_kBracketsValid = 0,
//   calc_kBracketsInvalid,
//   calc_kNoBrackets,
// };

// void TransformUnariesAndMod(char *input) {
//   char before[calc_kMaxStringSize] = {0};
//   do {
//     strcpy(before, input);
//     if (input[0] == '+' && strlen(input) > 0) input[0] = ' ';
//     if (strlen(input) >= 2 && input[0] == '-') {
//       if (input[1] == '-') {
//         input[0] = ' ';
//         input[1] = ' ';
//       } else if (input[1] == '(') {
//         input[0] = '_';
//       } else {
//         input[0] = '~';
//       }
//     }
//     const char *map_pair[][2] = {
//         {"++", "+ "}, {"-+", "- "}, {"-+", "- "},       {"(-", "(~"},
//         {"(+", "( "}, {"/+", "/ "}, {"/+", "/ "},       {"*+", "* "},
//         {"/-", "/~"}, {"*-", "*~"}, {"^+", "^ "},       {"^-", "^~"},
//         {"%+", "% "}, {"%-", "%~"}, {"+-", "+~"},       {"+-", "+~"},
//         {"-~", " +"}, {"~-", "~~"}, /*?*/ {"--", " +"},
//     };
//     const char *map_tri[][3] = {
//         {"(-(", "(_("},
//         {"mod", "  %"},
//     };
//     char temp_str[4] = {0};
//     for (int i = 0; i <= strlen(input) && strlen(input) >= 2; ++i) {
//       temp_str[0] = input[i];
//       temp_str[1] = input[i + 1];
//       for (int j = 0; j < sizeof(map_pair) / sizeof(map_pair[0]); ++j) {
//         if (strcmp(temp_str, map_pair[i][0]) == 0) {
//           input[i] = map_pair[j][1][0];
//           input[i + 1] = map_pair[j][1][1];
//         }
//       }
//       temp_str[2] = input[i + 2];
//       for (int j = 0; j < sizeof(map_tri) / sizeof(map_tri[0]); ++j) {
//         if (strcmp(temp_str, map_tri[i][0]) == 0) {
//           input[i] = map_tri[j][1][0];
//           input[i + 1] = map_tri[j][1][1];
//           input[i + 2] = map_tri[j][1][2];
//         }
//       }
//       strcpy(temp_str, "");
//     }
//     VasCleanUpSpaces(input);
//   } while (strcmp(input, before) != 0);
// }

// TODO another function, but for * between and after/before brackets

// printf("\nleft:[%s]middle:[%s]right:[%s]\n", left, middle, right);