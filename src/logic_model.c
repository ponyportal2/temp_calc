#include "logic_model.h"

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

// Main calculation:
void Calculate(view_to_calc_struct view_to_calc,
               calc_to_view_struct calc_to_view) {
  static bool forceOneInst = false;
  char *invalidCharList = "`<>?|;}{[]±§!@#$=";
  if (view_to_calc.unlock == true) forceOneInst = false;
  if (forceOneInst == false && view_to_calc.unlock == false) {
    forceOneInst = true;
    if (view_to_calc.calculation_type == calc_kCalculateWithX) {
      replaceX(view_to_calc.calc_input, view_to_calc.x_variable);
    }
    char lExpression[MAX_STRING_SIZE] = {0};
    strcpy(lExpression, view_to_calc.calc_input);
    int err = 0;
    int calculationCount = 0;
    if (IsBracketsCountValid(lExpression) == 1 &&
        findCharCount(invalidCharList, lExpression) == 0) {
      transformUnariesAndMod(lExpression);
      cleanUpSpaces(lExpression);
      addMultSignsToBrackets(lExpression);
      AddOuterBrackets(lExpression);
      int start = UNINIT;
      int end = UNINIT;
      int bracketsError = 0;
      bool allCalculationsFinished = false;
      bool whileBreak = false;
      while (allCalculationsFinished == false && bracketsError == 0 &&
             calculationCount < MAX_CALCULATIONS && whileBreak == false &&
             err == 0) {
        char left[MAX_STRING_SIZE] = {0};
        char middle[MAX_STRING_SIZE] = {0};
        char right[MAX_STRING_SIZE] = {0};
        bracketsError = findDeepestBrackets(lExpression, &start, &end);
        if (bracketsError == 0) {
          threeWaySplit(lExpression, left, middle, right, start, end);
          err = parseAndApplyOperators(middle);
          if (err == 0) {
            recombine(lExpression, left, middle, right);
            bracketsError = findDeepestBrackets(lExpression, &start, &end);
            if (bracketsError == 0) {
              err = unfoldBrackets(lExpression, start, end);
              if (!doesHaveBrackets(lExpression) &&
                  !isJustANumber(lExpression)) {
                AddOuterBrackets(lExpression);
              } else if (!doesHaveBrackets(lExpression)) {
                allCalculationsFinished = true;
              }
            } else {
              printf("\n>BRACKETS ERROR<");
            }
          } else {  // there are errors like div by zero
            whileBreak = true;
          }
        }
        calculationCount++;
      }
    } else if (IsBracketsCountValid(lExpression) != 1) {
      err = OPER_PASS_BRACKETS_COUNT_INVALID;
    } else if (findCharCount(invalidCharList, lExpression) > 0) {
      err = OPER_PASS_INVALID_SYMBOLS;
    }

    // OUTPUT LOGIC:
    // =============
    if (calculationCount > MAX_CALCULATIONS - 2) err = OPER_PASS_TIMEOUT;
    if (err == 0) {
      if (lExpression[0] == '~') lExpression[0] = '-';
      if (strtold(lExpression, NULL) > INFI) {
        strcpy(calc_to_view.answer, "inf");
      } else if (strtold(lExpression, NULL) < (INFI * -1)) {
        strcpy(calc_to_view.answer, "-inf");
      } else {
        sprintfHelper(calc_to_view.answer, strtold(lExpression, NULL));
        cleanUpSpaces(calc_to_view.answer);
        cleanUpTrailingZeroes(calc_to_view.answer);
      }
    } else if (err == OPER_PASS_DIVBYZERO) {
      strcpy(calc_to_view.answer, MES_OPER_PASS_DIVBYZERO);
    } else if (err == OPER_PASS_NAN) {
      strcpy(calc_to_view.answer, MES_OPER_PASS_NAN);
    } else if (err == OPER_PASS_TIMEOUT) {
      strcpy(calc_to_view.answer, MES_OPER_PASS_TIMEOUT);
    } else if (err == OPER_PASS_BRACKETS_COUNT_INVALID) {
      strcpy(calc_to_view.answer, MES_OPER_PASS_BRACKETS_COUNT_INVALID);
    } else if (err == OPER_PASS_INVALID_SYMBOLS) {
      strcpy(calc_to_view.answer, MES_OPER_PASS_INVALID_SYMBOLS);
    }
  }
}

void AddOuterBrackets(char *inputStr) {
  char tempStr[MAX_STRING_SIZE] = {0};
  strcat(tempStr, "(");
  strcat(tempStr, inputStr);
  strcat(tempStr, ")");
  strcpy(inputStr, tempStr);
}

int IsBracketsCountValid(char *inputStr) {
  bool yesItIsValid = 0;
  int i = 0;
  int leftBracketsCount = 0;
  int rightBracketsCount = 0;
  int isCorrect = 0;
  while (inputStr[i] != '\0' && isCorrect > -1) {
    if (inputStr[i] == '(') {
      isCorrect++;
      leftBracketsCount++;
    } else if (inputStr[i] == ')') {
      isCorrect--;
      rightBracketsCount++;
    }
    i++;
  }
  if (leftBracketsCount == rightBracketsCount) {
    yesItIsValid = 1;
  }
  if (isCorrect < 0) {
    yesItIsValid = 0;
  }
  return yesItIsValid;
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

void replaceX(char *inputStr, char *userX) {
  int i = 0;
  char userXLocal[MAX_STRING_SIZE] = {0};
  strcpy(userXLocal, userX);
  if (userXLocal[0] == '-') userXLocal[0] = '~';
  while (inputStr[i] != '\0') {
    if (inputStr[i] == 'x' || inputStr[i] == 'X') {
      char tempStr[MAX_STRING_SIZE] = {0};
      char left[MAX_STRING_SIZE] = {0};
      char right[MAX_STRING_SIZE] = {0};
      twoWaySplit(inputStr, left, right, i);
      strncpy(tempStr, left, strlen(left) - 1);
      strcat(tempStr, userXLocal);
      strcat(tempStr, right);
      strcpy(inputStr, tempStr);
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
  char left[MAX_STRING_SIZE] = {0};
  char middle[MAX_STRING_SIZE] = {0};
  char right[MAX_STRING_SIZE] = {0};
  char tempStr[MAX_STRING_SIZE] = {0};
  int err = 0;  // error for the return
  threeWaySplit(inputStr, left, middle, right, startIn, endIn);
  if (oper == BR_OPER_MINUS) {
    if (middle[0] == '~') {
      strcpy(tempStr, (char *)middle + 1);
    } else if (middle[0] != '~') {
      strcat(tempStr, "~");
      strcat(tempStr, middle);
    }
    strcpy(middle, tempStr);
    pureLRBracketDeletion(left, right);
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
      err = OPER_PASS_NAN;
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
    pureLRBracketDeletion(left, right);
    recombine(inputStr, left, middle, right);
  }
  return err;
}

void unfoldHelper(long double (*f)(long double), char *left, char *middle,
                  char *right, char *inputStr, int howManyLetters, int *err) {
  sprintfHelper(middle, f(strtold(middle, NULL)));
  if (strstr("nan", middle) || strstr("NaN", middle) || strstr("NAN", middle)) {
    *err = OPER_PASS_NAN;
  }
  pureLRBracketDeletion(left, right);
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

void pureLRBracketDeletion(char *left, char *right) {
  if (strlen(left) > 0) left[strlen(left) - 1] = '\0';
  if (strlen(right) > 0) {
    char tempStr[MAX_STRING_SIZE] = {0};
    strcpy(tempStr, (char *)right + 1);
    strcpy(right, tempStr);
  }
}

void transformUnariesAndMod(char *inputStr) {
  bool whileBreak = false;
  int a = 0;
  int b = 1;
  int c = 2;
  while (whileBreak == false) {
    if (a == 0 && inputStr[0] == '-') {
      // -( starting unary:
      if (inputStr[1] == '(') {
        inputStr[0] = '_';
        // --starting unary:
      } else if (inputStr[1] == '-') {
        inputStr[0] = ' ';
        inputStr[1] = ' ';
      } else {
        // any other - starting unary:
        inputStr[0] = '~';
      }
      // (-( simple negative reversion:
    } else if (inputStr[a] == '(' && inputStr[b] == '-' && inputStr[c] == '(') {
      inputStr[b] = '_';
      // (- (+ unary:
    } else if (a == 0 && inputStr[0] == '+') {
      inputStr[0] = ' ';
      // (- (+ unary:
    } else if (inputStr[a] == '(' && inputStr[b] == '-') {
      inputStr[b] = '~';
    } else if (inputStr[a] == '(' && inputStr[b] == '+') {
      inputStr[b] = ' ';
      // /+ *+ unary:
    } else if (inputStr[a] == '/' && inputStr[b] == '+') {
      inputStr[b] = ' ';
    } else if (inputStr[a] == '*' && inputStr[b] == '+') {
      inputStr[b] = ' ';
      // /- *- unary:
    } else if (inputStr[a] == '/' && inputStr[b] == '-') {
      inputStr[b] = '~';
    } else if (inputStr[a] == '*' && inputStr[b] == '-') {
      inputStr[b] = '~';
      // ^+ ^- unary:
    } else if (inputStr[a] == '^' && inputStr[b] == '+') {
      inputStr[b] = ' ';
    } else if (inputStr[a] == '^' && inputStr[b] == '-') {
      inputStr[b] = '~';
      // %- %+ unary:
    } else if (inputStr[a] == '%' && inputStr[b] == '+') {
      inputStr[b] = ' ';
    } else if (inputStr[a] == '%' && inputStr[b] == '-') {
      inputStr[b] = '~';
      // +- -- unary:
    } else if (inputStr[a] == '+' && inputStr[b] == '-') {
      inputStr[b] = '~';
      // weird --(~-) case:
    } else if (inputStr[a] == '~' && inputStr[b] == '-') {
      inputStr[a] = ' ';
      inputStr[b] = '+';
    } else if (inputStr[a] == '-' && inputStr[b] == '-') {  // ??
      inputStr[a] = ' ';
      inputStr[b] = '+';
      // ++ -+ unary:
    } else if (inputStr[a] == '+' && inputStr[b] == '+') {
      inputStr[b] = ' ';
    } else if (inputStr[a] == '-' && inputStr[b] == '+') {
      inputStr[b] = ' ';
      // ~- unary:
    } else if (inputStr[a] == '~' && inputStr[b] == '-') {
      inputStr[b] = '~';
      // mod to %:
    } else if (inputStr[a] == 'm' && inputStr[b] == 'o' && inputStr[c] == 'd') {
      inputStr[a] = ' ';
      inputStr[b] = ' ';
      inputStr[c] = '%';
      // exit condition:
    } else if (inputStr[a] == '\0') {
      whileBreak = true;
    }
    a++;
    b++;
    c++;
  }
}

int operatorCount(char *inputStr) {
  char *toMatch = "+-*/^%";
  int i = 0;
  int operatorCounter = 0;
  while (inputStr[i] != '\0') {
    if (charMatch(inputStr[i], toMatch) == true) {
      operatorCounter++;
    }
    i++;
  }
  return operatorCounter;
}

void recombine(char *inputStr, char *left, char *middle, char *right) {
  char tempStr[MAX_STRING_SIZE] = {0};
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

long double getLRDigits(char *inputMid, int operatorPos, int *digitsEnd,
                        bool isLeft) {
  char *toMatch = "0123456789~. ";
  char finalLeftDigit[MAX_STRING_SIZE] = {0};
  int i = 0;
  if (isLeft) i = operatorPos - 1;
  if (!isLeft) i = operatorPos + 1;
  int j = 0;
  int minusesCount = 0;
  bool whileBreak = false;
  // using just this instead of transformUnariesAndMod:
  if (isLeft && inputMid[0] == '-') inputMid[0] = '~';
  while (whileBreak == false) {
    if (inputMid[i] == '~') {
      finalLeftDigit[j] = '-';
      j++;
    } else {
      finalLeftDigit[j] = inputMid[i];
      j++;
    }
    if (isLeft) i--;
    if (!isLeft) i++;
    // Break conditions:
    if (isLeft && i < 0) whileBreak = true;
    if (!isLeft && i == (int)strlen(inputMid)) whileBreak = true;
    if (inputMid[i] == '\0') whileBreak = true;
    if (charMatch(inputMid[i], toMatch) != true) whileBreak = true;
  }
  if (minusesCount > 1) {
    printf("A LOT OF MINUSES!");
  }
  *digitsEnd = i;
  if (isLeft) reverseString(finalLeftDigit);
  return strtold(finalLeftDigit, NULL);
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
    while (findCharCount(midStr, "-") != 0) {
      // using just this instead of transformUnariesAndMod:
      if (midStr[0] == '-' && operatorCount(midStr) == 1) midStr[0] = '~';
      if (findCharCount(midStr, "~") == 1 && midStr[0] != '~') {
        findAndReplaceChar(midStr, "~", '-');
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
  while (findCharCount(inputMid, opChar) != 0 && whileBreak == false) {
    err = operatorPass(inputMid, opChar[0]);
    if (err) whileBreak = true;
  }
  return err;
}

int operatorPass(char *inputMid, char opChar) {
  int i = 0;
  bool err = 0;
  int resultStart = UNINIT;
  int resultEnd = UNINIT;
  long double calcResult = 0.0L;
  char sprintfResult[MAX_STRING_SIZE] = {0};
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
            err = OPER_PASS_DIVBYZERO;
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
        char left[MAX_STRING_SIZE] = {0};
        char middle[MAX_STRING_SIZE] = {0};
        char right[MAX_STRING_SIZE] = {0};
        threeWaySplit(inputMid, left, middle, right, resultStart, resultEnd);
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
    err = OPER_PASS_NAN;
  }
  return err;
}

void sprintfHelper(char *tempStr, long double longDoubleInput) {
  // sprintf(tempStr, "%." STR(SPRINTF_PRECISION) "lf",
  //         (double)longDoubleInput);  //  WIN
  sprintf(tempStr, "%." STR(SPRINTF_PRECISION) "Lf", longDoubleInput);  // MAC
}

bool isJustANumber(char *inputStr) {
  char toMatch[MAX_STRING_SIZE] = "0123456789. inf";
  int i = 0;
  bool bIsJustANumber = true;
  if (inputStr[0] == '-' || inputStr[0] == '~') i = 1;
  if (strlen(inputStr) > 0) {
    bool whileBreak = false;
    while (whileBreak == false && inputStr[i] != '\0') {
      if (charMatch(inputStr[i], toMatch) == false) {
        bIsJustANumber = false;
        whileBreak = true;
      }
      i++;
    }
  } else {
    // printf("\nEMPTY STRING IN IS JUST A NUMBER\n");
  }
  return bIsJustANumber;
}

void addMultSignsToBrackets(char *inputStr) {
  int i = 0;
  char tempStr[MAX_STRING_SIZE] = {0};
  char left[MAX_STRING_SIZE] = {0};
  char right[MAX_STRING_SIZE] = {0};
  char *toMatch = "0123456789.";
  while (inputStr[i] != '\0') {
    bool leftBracketCondition =
        inputStr[i] == ')' && charMatch(inputStr[i + 1], toMatch);
    bool rightBracketCondition =
        inputStr[i + 1] == '(' && charMatch(inputStr[i], toMatch);
    if (leftBracketCondition == true || rightBracketCondition == true) {
      twoWaySplit(inputStr, left, right, i);
      strcpy(tempStr, left);
      strcat(tempStr, "*");
      strcat(tempStr, right);
      strcpy(inputStr, tempStr);
      i = 0;
    } else if (inputStr[i] == ')' && inputStr[i + 1] == '(') {
      twoWaySplit(inputStr, left, right, i);
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
