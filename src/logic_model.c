#include "logic_model.h"

#include "vaslib.h"
// TODO: DOUBLE DOT

enum calc_CalculationError {
  calcerr_kNoError = 0,
  calcerr_kDivisionByZero,
  calcerr_kNan,
  calcerr_kBracketsAreInvaild,
  calcerr_kInvalidSymbols
};

void CalcErrorMessage(int error_enum, char *error_message) {
  const char *DivisionByZero_message = "Division by zero is impossible";
  const char *Nan_message = "NAN encountered during calculation";
  const char *BracketsAreInvaild_message = "Brackets are invalid";
  const char *InvalidSymbols_message = "Invalid symbols encountered";
  if (error_enum == calcerr_kDivisionByZero) {
    strcpy(error_message, DivisionByZero_message);
  } else if (error_enum == calcerr_kNan) {
    strcpy(error_message, Nan_message);
  } else if (error_enum == calcerr_kBracketsAreInvaild) {
    strcpy(error_message, BracketsAreInvaild_message);
  } else if (error_enum == calcerr_kInvalidSymbols) {
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

// Splits the input string into left and right parts up to split_pos inclusive
void SplitInHalf(char *input_str, char left[calc_kMaxStringSize],
                 char right[calc_kMaxStringSize], int split_pos) {
  if (split_pos > -1 && split_pos < (int)strlen(input_str)) {
    strncpy(left, input_str, split_pos + 1);
    strcpy(right, input_str + split_pos + 1);
  }
  // char tempStr[calc_kMaxStringSize] = {0}; // ????
  // strcpy(input_str, tempStr);  // ????
}

bool AreBracketsValid(const char *input_str) {
  int i = 0, left_count = 0, right_count = 0, mismatch = 0;
  bool is_valid = false;
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
  if (left_count == right_count) is_valid = true;
  if (left_count != right_count) is_valid = false;
  if (mismatch < 0) is_valid = false;
  return is_valid;
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
  view_to_calc.calc_input = (char *)calloc(calc_kMaxStringSize, sizeof(char));
  calc_to_view.answer = (char *)calloc(calc_kMaxStringSize, sizeof(char));
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

int Validation(const char *expression) {
  int expression_error = calcerr_kNoError;
  if (!AreBracketsValid(expression)) {
    expression_error = calcerr_kBracketsAreInvaild;
  }
  if (ContainsInvalidCharacters(expression) ||
      ContainsUnallowedRepeatingChars(expression) ||
      ContainsUnallowedTriples(expression)) {
    expression_error = calcerr_kInvalidSymbols;
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
    char expression[calc_kMaxStringSize] = {0};
    strcpy(expression, view_to_calc.calc_input);
    int expression_error = Validation(expression);
    if (expression_error == calcerr_kNoError) {
      printf(">>%s<<\n", expression);
      TransformUnariesModAndSpaces(expression);
      addMultSignsToBrackets(expression);
      addOuterBrackets(expression);
      int start = UNINIT, end = UNINIT, bracketsError = 0;
      bool allCalculationsFinished = false, loop_break = false;
      while (allCalculationsFinished == false && bracketsError == 0 &&
             loop_break == false && expression_error == 0) {
        char prev_l_expression[calc_kMaxStringSize] = {0};
        strcpy(prev_l_expression, expression);
        // printf("\n{%s}\n", expression);
        char left[calc_kMaxStringSize] = {0}, middle[calc_kMaxStringSize] = {0},
             right[calc_kMaxStringSize] = {0};
        bracketsError = findDeepestBrackets(expression, &start, &end);
        if (bracketsError == 0) {
          ThreeWaySplit(expression, left, middle, right, start, end);
          // printf("\nleft:[%s]middle:[%s]right:[%s]\n", left, middle, right);
          expression_error = parseAndApplyOperators(middle);
          if (expression_error != 0) loop_break = true;
          if (expression_error == 0) {
            recombine(expression, left, middle, right);
            bracketsError = findDeepestBrackets(expression, &start, &end);
            // if (bracketsError != 0) printf("\n>BRACKETS ERROR<");
            expression_error = unfoldBrackets(expression, start, end);
            if (!doesHaveBrackets(expression) && !isJustANumber(expression)) {
              addOuterBrackets(expression);
            } else if (!doesHaveBrackets(expression)) {
              allCalculationsFinished = true;
            }
          }
        }
        // printf("\n[%s]\n", expression);
        if (!AreBracketsValid(expression)) {
          expression_error = calcerr_kBracketsAreInvaild;
        }
        if (strcmp(prev_l_expression, expression) == 0) loop_break = true;
      }
    }

    // OUTPUT LOGIC:
    // =============
    if (expression_error == calcerr_kNoError) {
      if (expression[0] == '~') expression[0] = '-';
      if (strtod(expression, NULL) > INFI) {
        strcpy(calc_to_view.answer, "inf");
      } else if (strtod(expression, NULL) < (INFI * -1)) {
        strcpy(calc_to_view.answer, "-inf");
      } else {
        sprintfHelper(calc_to_view.answer, strtod(expression, NULL));
        VasCleanUpSpaces(calc_to_view.answer);
        VasCleanUpTrailingZeroes(calc_to_view.answer);
      }
      printf("\nTHE ANSWER:%s\n", calc_to_view.answer);
    } else {
      CalcErrorMessage(expression_error, calc_to_view.answer);
    }
  }
}

void addOuterBrackets(char *inputStr) {
  char tempStr[calc_kMaxStringSize] = {0};
  strcat(tempStr, "(");
  strcat(tempStr, inputStr);
  strcat(tempStr, ")");
  strcpy(inputStr, tempStr);
}

bool doesHaveBrackets(char *inputStr) {
  bool yesItDoesHaveBrackets = false;
  int i = 0;
  bool whileBreak = false;
  while (inputStr[i] != '\0' && whileBreak == false) {
    if (inputStr[i] == '(' || inputStr[i] == ')') {
      yesItDoesHaveBrackets = true;
      whileBreak = true;
    }
    i++;
  }
  return yesItDoesHaveBrackets;
}

void ReplaceX(char *input_str, const char *input_x) {
  char input_x_local[calc_kMaxStringSize] = {0};
  strcpy(input_x_local, input_x);
  if (input_x_local[0] == '-') input_x_local[0] = '~';
  int i = 0;
  while (input_str[i] != '\0') {
    if (input_str[i] == 'x' || input_str[i] == 'X') {
      char tempStr[calc_kMaxStringSize] = {0}, left[calc_kMaxStringSize] = {0},
           right[calc_kMaxStringSize] = {0};
      SplitInHalf(input_str, left, right, i);
      strncpy(tempStr, left, strlen(left) - 1);
      strcat(tempStr, input_x_local);
      strcat(tempStr, right);
      strcpy(input_str, tempStr);
      i = 0;
    } else {
      i++;
    }
  }
}

int findDeepestBrackets(char *inputStr, int *startIn, int *endIn) {
  int hasError = 0;
  int i = 0;
  int start = UNINIT;
  int end = UNINIT;
  bool whileBreak = false;
  while (whileBreak == false) {
    if (inputStr[i] == '(') {
      start = i;
    } else if (inputStr[i] == '\0') {
      if (start == UNINIT && end == UNINIT) {
        hasError = -1;  // hasError -1 means no brackets found
      } else if (start == UNINIT || end == UNINIT) {
        hasError = 1;  // hasError 1 means no starting or ending brackets
      }
      whileBreak = true;
    } else if (inputStr[i] == ')') {
      end = i;
      whileBreak = true;
    }
    i++;
  }
  if (hasError == 0) {
    *startIn = start;
    *endIn = end;
  }
  return hasError;
}

int unfoldBrackets(char *inputStr, int startIn, int endIn) {
  int oper = checkLeftBracketOper(inputStr, startIn);
  char left[calc_kMaxStringSize] = {0};
  char middle[calc_kMaxStringSize] = {0};
  char right[calc_kMaxStringSize] = {0};
  char tempStr[calc_kMaxStringSize] = {0};
  int err = 0;  // error for the return
  ThreeWaySplit(inputStr, left, middle, right, startIn, endIn);
  if (oper == BR_OPER_MINUS) {
    if (middle[0] == '~') {
      strcpy(tempStr, (char *)middle + 1);
    } else if (middle[0] != '~') {
      strcat(tempStr, "~");
      strcat(tempStr, middle);
    }
    strcpy(middle, tempStr);
    DeleteBrackets(left, right);
    left[strlen(left) - 1] = '\0';
    recombine(inputStr, left, middle, right);
  } else if (oper == BR_OPER_ACOS) {
    unfoldHelper(acosl, left, middle, right, inputStr, 4, &err);
  } else if (oper == BR_OPER_ASIN) {
    unfoldHelper(asinl, left, middle, right, inputStr, 4, &err);
  } else if (oper == BR_OPER_ATAN) {
    unfoldHelper(atanl, left, middle, right, inputStr, 4, &err);
  } else if (oper == BR_OPER_SQRT) {
    if (middle[0] != '-' && middle[0] != '~') {
      unfoldHelper(sqrtl, left, middle, right, inputStr, 4, &err);
    } else {  // negative sqrt is a complex number
      err = calcerr_kNan;
    }
  } else if (oper == BR_OPER_COS) {
    unfoldHelper(cosl, left, middle, right, inputStr, 3, &err);
  } else if (oper == BR_OPER_SIN) {
    unfoldHelper(sinl, left, middle, right, inputStr, 3, &err);
  } else if (oper == BR_OPER_TAN) {
    unfoldHelper(tanl, left, middle, right, inputStr, 3, &err);
  } else if (oper == BR_OPER_LOG) {
    unfoldHelper(log10l, left, middle, right, inputStr, 3, &err);
  } else if (oper == BR_OPER_LN) {
    unfoldHelper(logl, left, middle, right, inputStr, 2, &err);
  } else if (oper == 0) {
    DeleteBrackets(left, right);
    recombine(inputStr, left, middle, right);
  }
  return err;
}

void unfoldHelper(long double (*f)(long double), char *left, char *middle,
                  char *right, char *inputStr, int howManyLetters, int *err) {
  sprintfHelper(middle, f(strtold(middle, NULL)));
  if (strstr("nan", middle) || strstr("NaN", middle) || strstr("NAN", middle)) {
    *err = calcerr_kNan;
  }
  DeleteBrackets(left, right);
  left[strlen(left) - howManyLetters] = '\0';
  recombine(inputStr, left, middle, right);
}

int checkLeftBracketOper(char *leftStr, int leftBracketIdx) {
  int leftBracketOperation = 0;
  int i = leftBracketIdx;
  char minFour = UNINIT;
  char minThree = UNINIT;
  char minTwo = UNINIT;
  char minOne = UNINIT;
  if ((leftStr[i - 4]) > -1) minFour = leftStr[i - 4];
  if ((leftStr[i - 3]) > -1) minThree = leftStr[i - 3];
  if ((leftStr[i - 2]) > -1) minTwo = leftStr[i - 2];
  if ((leftStr[i - 1]) > -1) minOne = leftStr[i - 1];
  if (minFour == 'a' && minThree == 'c' && minTwo == 'o' && minOne == 's') {
    leftBracketOperation = BR_OPER_ACOS;
  } else if (minFour == 'a' && minThree == 's' && minTwo == 'i' &&
             minOne == 'n') {
    leftBracketOperation = BR_OPER_ASIN;
  } else if (minFour == 'a' && minThree == 't' && minTwo == 'a' &&
             minOne == 'n') {
    leftBracketOperation = BR_OPER_ATAN;
  } else if (minFour == 's' && minThree == 'q' && minTwo == 'r' &&
             minOne == 't') {
    leftBracketOperation = BR_OPER_SQRT;
  } else if (minThree == 'c' && minTwo == 'o' && minOne == 's') {
    leftBracketOperation = BR_OPER_COS;
  } else if (minThree == 's' && minTwo == 'i' && minOne == 'n') {
    leftBracketOperation = BR_OPER_SIN;
  } else if (minThree == 't' && minTwo == 'a' && minOne == 'n') {
    leftBracketOperation = BR_OPER_TAN;
  } else if (minThree == 'l' && minTwo == 'o' && minOne == 'g') {
    leftBracketOperation = BR_OPER_LOG;
  } else if (minTwo == 'l' && minOne == 'n') {
    leftBracketOperation = BR_OPER_LN;
  } else if (minOne == '_') {
    leftBracketOperation = BR_OPER_MINUS;
  }
  return leftBracketOperation;
}

void DeleteBrackets(char *left, char *right) {
  if (strlen(left) > 0) left[strlen(left) - 1] = '\0';
  if (strlen(right) > 0) {
    char tempStr[calc_kMaxStringSize] = {0};
    strcpy(tempStr, (char *)right + 1);
    strcpy(right, tempStr);
  }
}

void TransformUnariesModAndSpaces(char *input) {
  char before[calc_kMaxStringSize] = {0};
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
    VasReplace(input, "~-", " +");  // ??
    VasReplace(input, "--", " +");  // ??
                                    // simple replacements:
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

// otdelno
// {"(-(", "(_("}
// otdelno
// {")-", ")*-"}, {")(", ")*("}, {")0", ")*0"},
//       {")1", ")*1"}, {")2", ")*2"}, {")3", ")*3"}, {")4", ")*4"}, {")5",
//       ")*5"},
//       {")6", ")*6"}, {")7", ")*7"}, {")8", ")*8"}, {")9", ")*9"}, {"0(",
//       "0*("},
//       {"1(", "1*("}, {"2(", "2*("}, {"3(", "3*("}, {"4(", "4*("}, {"5(",
//       "5*("},
//       {"6(", "6*("}, {"7(", "7*("}, {"8(", "8*("}, {"9(", "9*("}

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

int operatorCount(char *inputStr) {
  char *toMatch = "+-*/^%";
  int i = 0;
  int operatorCounter = 0;
  while (inputStr[i] != '\0') {
    if (VasCharMatch(inputStr[i], toMatch) == true) {
      operatorCounter++;
    }
    i++;
  }
  return operatorCounter;
}

void recombine(char *inputStr, char *left, char *middle, char *right) {
  char tempStr[calc_kMaxStringSize] = {0};
  strcpy(tempStr, left);
  strcat(tempStr, middle);
  strcat(tempStr, right);
  strcpy(inputStr, tempStr);
}

long double getLeftDigits(char *inputMid, int operatorPos, int *digitsEnd) {
  return getLRDigits(inputMid, operatorPos, digitsEnd, true);
}

long double getRightDigits(char *inputMid, int operatorPos, int *digitsEnd) {
  return getLRDigits(inputMid, operatorPos, digitsEnd, false);
}

long double getLRDigits(char *input, int oper_position, int *digits_end,
                        bool is_left) {
  char *to_match = "0123456789~. inf nan NAN";
  char final_number[calc_kMaxStringSize] = {0};
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

    if (is_left) i--;
    if (!is_left) i++;

    if (i < 0 || i == (int)strlen(input) || input[i] == '\0') loop_break = true;
    if (VasCharMatch(input[i], to_match) != true) loop_break = true;
  }
  *digits_end = i;
  if (is_left) VasReverseCharArray(final_number);
  // printf("final number:%s\n", final_number);
  return strtod(final_number, NULL);
}

int parseAndApplyOperators(char *midStr) {
  int err = 0;
  bool whileBreak = false;
  while (whileBreak == false) {
    err = operatorPassLoop(midStr, "^");
    if (err != 0) break;
    err = operatorPassLoop(midStr, "/");
    if (err != 0) break;
    err = operatorPassLoop(midStr, "*");
    if (err != 0) break;
    err = operatorPassLoop(midStr, "%");
    if (err != 0) break;
    while (VasCountOfChars(midStr, "-") != 0) {
      // using just this instead of transformUnariesAndMod:
      if (midStr[0] == '-' && operatorCount(midStr) == 1) midStr[0] = '~';
      if (VasCountOfChars(midStr, "~") == 1 && midStr[0] != '~') {
        VasFindAndReplaceChar(midStr, "~", '-');
      }
      err = operatorPass(midStr, '-');
      if (err != 0) break;
    }
    err = operatorPassLoop(midStr, "+");
    if (err != 0) break;
    if (operatorCount(midStr) < 1 || isJustANumber(midStr)) {
      whileBreak = true;
    }
  }
  return err;
}

int operatorPassLoop(char *inputMid, char *opChar) {
  int err = 0;
  bool whileBreak = false;
  while (VasCountOfChars(inputMid, opChar) != 0 && whileBreak == false) {
    err = operatorPass(inputMid, opChar[0]);
    if (err) whileBreak = true;
  }
  return err;
}

int operatorPass(char *inputMid, char opChar) {
  int i = 0;
  int err = 0;
  int resultStart = UNINIT;
  int resultEnd = UNINIT;
  long double calcResult = 0.0L;
  char sprintfResult[calc_kMaxStringSize] = {0};
  bool whileBreak = false;
  while (inputMid[i] != '\0' && whileBreak == false) {
    if (inputMid[i] == opChar) {
      switch (opChar) {
        case '*':
          calcResult = (long double)getLeftDigits(inputMid, i, &resultStart) *
                       (long double)getRightDigits(inputMid, i, &resultEnd);
          sprintfHelper(sprintfResult, calcResult);
          break;
        case '/':

          if (getRightDigits(inputMid, i, &resultEnd) != 0) {
            calcResult = (long double)getLeftDigits(inputMid, i, &resultStart) /
                         (long double)getRightDigits(inputMid, i, &resultEnd);
            sprintfHelper(sprintfResult, calcResult);
          } else {
            err = calcerr_kDivisionByZero;
            whileBreak = true;
          }
          break;
        case '+':
          calcResult = (long double)getLeftDigits(inputMid, i, &resultStart) +
                       (long double)getRightDigits(inputMid, i, &resultEnd);
          sprintfHelper(sprintfResult, calcResult);
          break;
        case '-':
          calcResult = (long double)getLeftDigits(inputMid, i, &resultStart) -
                       (long double)getRightDigits(inputMid, i, &resultEnd);
          sprintfHelper(sprintfResult, calcResult);
          break;
        case '^':
          calcResult = powl(getLeftDigits(inputMid, i, &resultStart),
                            getRightDigits(inputMid, i, &resultEnd));
          sprintfHelper(sprintfResult, calcResult);
          break;
        case '%':
          calcResult = fmodl(getLeftDigits(inputMid, i, &resultStart),
                             getRightDigits(inputMid, i, &resultEnd));
          sprintfHelper(sprintfResult, calcResult);
          break;
      }
      // using just this instead of transformUnariesAndMod:
      if (sprintfResult[0] == '-') sprintfResult[0] = '~';
      // changeAllUnaries(resultGcvt); // probably shouldn't be here
      if (operatorCount(inputMid) > 0) {
        char left[calc_kMaxStringSize] = {0};
        char middle[calc_kMaxStringSize] = {0};
        char right[calc_kMaxStringSize] = {0};
        ThreeWaySplit(inputMid, left, middle, right, resultStart, resultEnd);
        strcpy(inputMid, left);
        strcat(inputMid, sprintfResult);
        strcat(inputMid, right);
      } else if (operatorCount(inputMid) == 0) {
        strcpy(inputMid, sprintfResult);
      } else {
        printf("\nDAFAQ\n");
      }
    }
    i++;
  }
  if (calcResult != calcResult && err == 0) {  // checking for NAN
    err = calcerr_kNan;
  }
  return err;
}

void sprintfHelper(char *tempStr, long double longDoubleInput) {
  // sprintf(tempStr, "%." STR(SPRINTF_PRECISION) "lf",
  //         (double)longDoubleInput);  //  WIN
  sprintf(tempStr, "%." STR(SPRINTF_PRECISION) "Lf", longDoubleInput);  // MAC
}

// TODO Optimize: this function
void ThreeWaySplit(char *input_str, char left[calc_kMaxStringSize],
                   char middle[calc_kMaxStringSize],
                   char right[calc_kMaxStringSize], int start, int end) {
  char temp_str[calc_kMaxStringSize] = {0};
  if (start > -1) {
    strncpy(left, input_str, start + 1);
  }
  strncpy(middle, input_str + start + 1, end - start - 1);
  if (end < (int)strlen(input_str)) {
    strcpy(right, input_str + start + (end - start));
  }
  strcpy(input_str, temp_str);
}

bool isJustANumber(char *inputStr) {
  char toMatch[calc_kMaxStringSize] = "0123456789. inf";
  int i = 0;
  bool bIsJustANumber = true;
  if (strlen(inputStr) > 0) {
    if (inputStr[0] == '-' || inputStr[0] == '~') i = 1;
    bool whileBreak = false;
    while (whileBreak == false && inputStr[i] != '\0') {
      if (VasCharMatch(inputStr[i], toMatch) == false) {
        bIsJustANumber = false;
        whileBreak = true;
      }
      i++;
    }
  } else {
    printf("\nEMPTY STRING IN IS JUST A NUMBER\n");
  }
  return bIsJustANumber;
}

void addMultSignsToBrackets(char *inputStr) {
  int i = 0;
  char tempStr[calc_kMaxStringSize] = {0};
  char left[calc_kMaxStringSize] = {0};
  char right[calc_kMaxStringSize] = {0};
  char *toMatch = "0123456789.";
  while (inputStr[i] != '\0') {
    bool leftBracketCondition =
        inputStr[i] == ')' && VasCharMatch(inputStr[i + 1], toMatch);
    bool rightBracketCondition =
        inputStr[i + 1] == '(' && VasCharMatch(inputStr[i], toMatch);
    if (leftBracketCondition == true || rightBracketCondition == true) {
      SplitInHalf(inputStr, left, right, i);
      strcpy(tempStr, left);
      strcat(tempStr, "*");
      strcat(tempStr, right);
      strcpy(inputStr, tempStr);
      i = 0;
    } else if (inputStr[i] == ')' && inputStr[i + 1] == '(') {
      SplitInHalf(inputStr, left, right, i);
      strcpy(tempStr, left);
      strcat(tempStr, "*");
      strcat(tempStr, right);
      strcpy(inputStr, tempStr);
    } else {
      i++;
    }
  }
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
