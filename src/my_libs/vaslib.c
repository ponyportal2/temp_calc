#include "vaslib.h"

#include <stdio.h>

void CleanUpSpaces(char *input_str) {
  char temp_str[vaslib_kSize] = {0};
  int i = 0, j = 0;
  while (input_str[i] != '\0') {
    if (input_str[i] != ' ' && input_str[i] != '\n' && input_str[i] != '\t') {
      temp_str[j] = input_str[i];
      j++;
    }
    i++;
  }
  strcpy(input_str, temp_str);
}

void cleanUpTrailingZeroes(char *inputStr) {
  int i = strlen(inputStr) - 1;
  bool whileBreak = false;
  if (char_match('.', inputStr) == true) {
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

int count_of_chars(char *inputStr, char *toFind) {
  int counter = 0, i = 0;
  while (inputStr[i] != '\0') {
    if (char_match(inputStr[i], toFind)) counter++;
    i++;
  }
  return counter;
}

void reverseString(char *string) {
  char temp[vaslib_kSize] = {0};
  strcpy(temp, string);
  int length = strlen(string);
  int i = 0;
  for (; i < length; i++) string[i] = temp[length - i - 1];
  string[i] = '\0';
}

bool char_match(char char_to_match, const char *char_array_to_match) {
  bool match = false;
  int i = 0;
  while (char_array_to_match[i] != '\0') {
    if (char_array_to_match[i] == char_to_match) {
      match = true;
    }
    ++i;
  }
  return match;
}
void threeWaySplit(char *inputStr, char left[vaslib_kSize],
                   char middle[vaslib_kSize], char right[vaslib_kSize],
                   int start, int end) {
  char tempStr[vaslib_kSize] = {0};
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
    if (char_match(inputStr[i], toFind)) inputStr[i] = toReplace;
    i++;
  }
  return counter;
}