#include "logic_model.h"

#include "vaslib.h"

#define CALC_STR_(X) #X
#define CALC_STR(X) CALC_STR_(X)
#define CALC_SPRINTF_PRECISION 10

const int calc_kUninit = -68;
const int calc_kMaxSolverLoops = 5000;
const long double calc_kInfinity =
    999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.0L;
const long double calc_kSolverMidDefault = 0.0000001;

char *acos_str = "acos", *asin_str = "asin", *atan_str = "atan",
     *sqrt_str = "sqrt", *cos_str = "cos", *sin_str = "sin", *tan_str = "tan",
     *log_str = "log", *ln_str = "ln", *m_str = "_";

void CalcErrorMessage(enum CalcErr error_enum, char *error_message) {
  const char *DivisionByZero_message = "Division by zero is impossible";
  const char *Nan_message = "NAN encountered during calculation";
  const char *BracketsAreInvaild_message = "Brackets are invalid";
  const char *InvalidSymbols_message = "Invalid symbols encountered";
  const char *SolverTimeout_message = "Solver timeout reached";
  if (error_enum == calc_Err_kDivisionByZero) {
    strcpy(error_message, DivisionByZero_message);
  } else if (error_enum == calc_Err_kNan) {
    strcpy(error_message, Nan_message);
  } else if (error_enum == calc_Err_kBracketsAreInvaild) {
    strcpy(error_message, BracketsAreInvaild_message);
  } else if (error_enum == calc_Err_kInvalidSymbols) {
    strcpy(error_message, InvalidSymbols_message);
  } else if (error_enum == calc_Err_kSolverTimeout) {
    strcpy(error_message, SolverTimeout_message);
  }
}

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

void TestCalculate(char *input, char *output) {
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
      "0123456789 +-*/% .~ ( ) cos sin tan acos asin atan sqrt ln log ^ e mod ";
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

enum CalcErr Validation(const char *expression) {
  enum CalcErr expression_error = calc_Err_kOk;
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
  int with_output = CALC_WITH_OUTPUT;
  if (view_to_calc.unlock == true) locked = false;
  if (view_to_calc.unlock == false && locked == false) {
    locked = true;
    if (view_to_calc.calculation_type == calc_kCalculateWithX) {
      ReplaceX(view_to_calc.calc_input, view_to_calc.x_variable);
    }
    char expression[calc_kMaxStrSize] = {0};
    strcpy(expression, view_to_calc.calc_input);
    enum CalcErr expression_error = Validation(expression);
    if (!expression_error) {
      TransformUnariesModSpaces(expression);
      AddMultSigns(expression);
      AddOuterBrackets(expression);
      int start = calc_kUninit, end = calc_kUninit, missing_brackets = 0;
      bool calc_finished = false;
      while (!missing_brackets && !calc_finished && !expression_error) {
        if (with_output) printf("%s\n", expression);
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
        expression_error = UnfoldBrackets(expression, start, end);
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
                      enum CalcErr calc_error) {
  int with_output = CALC_WITH_OUTPUT;
  if (expression[0] == '~') expression[0] = '-';
  if (calc_error != calc_Err_kOk) {
    CalcErrorMessage(calc_error, output_answer);
  } else if (!IsJustANumber(expression)) {
    calc_error = calc_Err_kInvalidSymbols;
    CalcErrorMessage(calc_error, output_answer);
  } else {
    long double final_result = strtold(expression, NULL);
    if (final_result > calc_kInfinity) {
      strcpy(output_answer, "inf");
    } else if (final_result < (calc_kInfinity * -1)) {
      strcpy(output_answer, "-inf");
    } else {
      SprintfHelper(output_answer, final_result);
      VasCleanUpSpaces(output_answer);
      VasCleanUpTrailingZeroes(output_answer);
    }
  }
  if (with_output) printf("\nFINAL ANSWER: %s\n\n", output_answer);
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

enum CalcErr UnfoldBrackets(char *input_str, int start_in, int end_in) {
  int i = start_in;  // left bracket index
  char left_chunk[5] = {0};
  for (int j = 1; j <= 4; ++j) {
    if (input_str[i - j] > -1) left_chunk[j - 1] = input_str[i - j];
  }
  VasReverseCharArray(left_chunk);
  char left[calc_kMaxStrSize] = {0}, mid[calc_kMaxStrSize] = {0},
       right[calc_kMaxStrSize] = {0}, temp_str[calc_kMaxStrSize] = {0};
  enum CalcErr err = calc_Err_kOk;
  ThreeWaySplit(input_str, left, mid, right, start_in, end_in);
  if (strstr(left_chunk, acos_str)) {
    err = UnfoldHelper(acosl, left, mid, right, input_str, acos_str);
  } else if (strstr(left_chunk, asin_str)) {
    err = UnfoldHelper(asinl, left, mid, right, input_str, asin_str);
  } else if (strstr(left_chunk, atan_str)) {
    err = UnfoldHelper(atanl, left, mid, right, input_str, atan_str);
  } else if (strstr(left_chunk, sqrt_str)) {
    if (mid[0] == '-' || mid[0] == '~') {  // negative sqrt is a complex number
      err = calc_Err_kNan;
    } else {
      err = UnfoldHelper(sqrtl, left, mid, right, input_str, sqrt_str);
    }
  } else if (strstr(left_chunk, cos_str)) {
    err = UnfoldHelper(cosl, left, mid, right, input_str, cos_str);
  } else if (strstr(left_chunk, sin_str)) {
    err = UnfoldHelper(sinl, left, mid, right, input_str, sin_str);
  } else if (strstr(left_chunk, tan_str)) {
    err = UnfoldHelper(tanl, left, mid, right, input_str, tan_str);
  } else if (strstr(left_chunk, log_str)) {
    err = UnfoldHelper(log10l, left, mid, right, input_str, log_str);
  } else if (left_chunk[strlen(left_chunk) - 1] == 'n' &&
             left_chunk[strlen(left_chunk) - 2] == 'l') {
    err = UnfoldHelper(logl, left, mid, right, input_str, ln_str);
  } else if (strlen(left_chunk) && left_chunk[strlen(left_chunk) - 1] == '_') {
    if (mid[0] == '~') {
      mid[0] = '+';
    } else if (mid[0] != '~') {
      strcpy(temp_str, "-");
      strcat(temp_str, mid);
      strcpy(mid, temp_str);
    }
    DeleteBrackets(left, right);
    left[strlen(left) - 1] = '\0';
    Recombine(input_str, left, mid, right);
  } else if (strlen(left_chunk) &&
             !VasCharMatch(left_chunk[strlen(left_chunk) - 1], "^+*/%(")) {
    err = calc_Err_kInvalidSymbols;
  } else {  // just brackets
    DeleteBrackets(left, right);
    Recombine(input_str, left, mid, right);
  }
  return err;
}

enum CalcErr UnfoldHelper(long double (*fun)(long double), char *left,
                          char *middle, char *right, char *input_str,
                          char *oper_str) {
  enum CalcErr err = calc_Err_kOk;
  SprintfHelper(middle, fun(strtold(middle, NULL)));
  if (strstr("nan", middle) || strstr("NaN", middle) || strstr("NAN", middle)) {
    err = calc_Err_kNan;
  }
  DeleteBrackets(left, right);
  left[strlen(left) - strlen(oper_str)] = '\0';
  Recombine(input_str, left, middle, right);
  return err;
}

void DeleteBrackets(char *left, char *right) {
  if (strlen(left) > 0) left[strlen(left) - 1] = '\0';
  if (strlen(right) > 0) {
    char tempStr[calc_kMaxStrSize] = {0};
    strcpy(tempStr, (char *)right + 1);
    strcpy(right, tempStr);
  }
}

void TransformUnariesModSpaces(char *input) {
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
    VasReplace(input, "-(", "_(");
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
  char *to_match = "0123456789~. inf nan NAN e";
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

enum CalcErr ParseAndApplyOperators(char *mid_inp) {
  enum CalcErr err = calc_Err_kOk;
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

enum CalcErr OperatorPassLoop(char *input_mid, char *op_char) {
  enum CalcErr err = calc_Err_kOk;
  bool loop_break = false;
  while (VasCountOfChars(input_mid, op_char) > 0 && loop_break == false) {
    if (err = OperatorPass(input_mid, op_char)) loop_break = true;
  }
  return err;
}

enum CalcErr OperatorPass(char *input, char *op_char) {
  enum CalcErr err = calc_Err_kOk;
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
  char to_match[calc_kMaxStrSize] =
      "0123456789. inf NAN nan e";  // Minus is not checked
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

void BinarySearchSolver(view_to_calc_struct view_to_calc,
                        calc_to_view_struct calc_to_view) {
  long double calc_kSolverMidDiv = powl(10.0L, 50.0L);
  long double expected_answer = strtold(view_to_calc.solver_variable, NULL),
              answer_num = 0.0L;
  char local_expression[calc_kMaxStrSize] = {0},
       answer_str[calc_kMaxStrSize] = {0}, mid_str[calc_kMaxStrSize] = {0};
  long double top = (long double)(calc_kInfinity - 2.0L) / calc_kSolverMidDiv,
              mid = calc_kSolverMidDefault,
              bot = (long double)(-calc_kInfinity + 2.0L) / calc_kSolverMidDiv;
  int counter = 0, direction = 0;
  bool invalid_input = false;
  strcpy(local_expression, view_to_calc.calc_input);
  enum CalcErr expression_error = calc_Err_kOk;
  do {
    ++counter;
    strcpy(local_expression, view_to_calc.calc_input);
    SprintfHelper(mid_str, mid);
    ReplaceX(local_expression, mid_str);
    expression_error = Validation(local_expression);
    if (!expression_error) {
      TestCalculate(local_expression, answer_str);
      expression_error = Validation(answer_str);
      if (!expression_error) {
        answer_num = strtold(answer_str, NULL);
        if (!direction) {
          if (answer_num < expected_answer) {
            bot = mid;
            mid = (long double)(top + mid) / 2.0L;
          } else if (answer_num > expected_answer) {
            top = mid;
            mid = (long double)(bot + mid) / 2.0L;
          }
        } else if (direction) {
          if (answer_num > expected_answer) {
            bot = mid;
            mid = (long double)(top + mid) / 2.0L;
          } else if (answer_num < expected_answer) {
            top = mid;
            mid = (long double)(bot + mid) / 2.0L;
          }
        }
        if (counter == calc_kMaxSolverLoops / 2 && !direction) {
          direction = 1;
          top = (long double)(calc_kInfinity - 2.0L) / calc_kSolverMidDiv,
          mid = -calc_kSolverMidDefault,
          bot = (long double)(-calc_kInfinity + 2.0L) / calc_kSolverMidDiv;
        }
      }
    }
  } while (fabsl(answer_num - expected_answer) > 0.00000009 &&
           counter < calc_kMaxSolverLoops);
  if (counter >= calc_kMaxSolverLoops) {
    expression_error = calc_Err_kSolverTimeout;
  }
  sprintf(mid_str, "%.6Lf", mid);
  CalculatorOutput(mid_str, calc_to_view.answer, expression_error);
}
