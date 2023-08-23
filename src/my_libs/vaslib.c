#include "vaslib.h"

#include <stdio.h>

void cleanUpSpaces(char *inputStr) {
  char tempStr[VASLIBTHESIZE] = {0};
  int i = 0;
  int j = 0;
  while (inputStr[i] != '\0') {
    if (inputStr[i] != ' ' && inputStr[i] != '\n' && inputStr[i] != '\t') {
      tempStr[j] = inputStr[i];
      j++;
    }
    i++;
  }
  strcpy(inputStr, tempStr);
}

void cleanUpTrailingZeroes(char *inputStr) {
  int i = strlen(inputStr) - 1;
  bool whileBreak = false;
  if (charMatch('.', inputStr) == true) {
    while (whileBreak == false && i > -1) {
      if ((i - 1 > 0) && inputStr[i] == '0' && inputStr[i - 1] != '.') {
        inputStr[i] = '\0';
      } else {
        whileBreak = true;
      }
      i--;
    }
  }
}

int findCharCount(char *inputStr, char *toFind) {
  int counter = 0;
  int i = 0;
  while (inputStr[i] != '\0') {
    if (charMatch(inputStr[i], toFind)) counter++;
    i++;
  }
  return counter;
}

void reverseString(char *string) {
  char temp[VASLIBTHESIZE] = {0};
  strcpy(temp, string);
  int length = strlen(string);
  int i = 0;
  for (; i < length; i++) string[i] = temp[length - i - 1];
  string[i] = '\0';
}

bool charMatch(char inputChar, const char *inputCharArr) {
  int match = false;
  int i = 0;
  while (inputCharArr[i] != '\0') {
    if (inputCharArr[i] == inputChar) {
      match = true;
    }
    i++;
  }
  return match;
}

void twoWaySplit(char *inputStr, char left[VASLIBTHESIZE],
                 char right[VASLIBTHESIZE], int splitPos) {
  char tempStr[VASLIBTHESIZE] = {0};
  if (splitPos > -1 && splitPos < (int)strlen(inputStr)) {
    strncpy(left, inputStr, splitPos + 1);
    strcpy(right, inputStr + splitPos + 1);
  }
  strcpy(inputStr, tempStr);
}

void threeWaySplit(char *inputStr, char left[VASLIBTHESIZE],
                   char middle[VASLIBTHESIZE], char right[VASLIBTHESIZE],
                   int start, int end) {
  char tempStr[VASLIBTHESIZE] = {0};
  if (start > -1) {
    strncpy(left, inputStr, start + 1);
  }
  strncpy(middle, inputStr + start + 1, end - start - 1);
  if (end < (int)strlen(inputStr)) {
    strcpy(right, inputStr + start + (end - start));
  }
  strcpy(inputStr, tempStr);
}

int findAndReplaceChar(char *inputStr, char *toFind, char toReplace) {
  int counter = 0;
  int i = 0;
  while (inputStr[i] != '\0') {
    if (charMatch(inputStr[i], toFind)) inputStr[i] = toReplace;
    i++;
  }
  return counter;
}