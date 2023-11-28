#include "vaslib.h"

#include <stdio.h>

void VasCleanUpTrailingZeroes(char *inputStr) {
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

int VasCountOfChars(char *inputStr, char *toFind) {
  int counter = 0, i = 0;
  while (inputStr[i] != '\0') {
    if (char_match(inputStr[i], toFind)) counter++;
    i++;
  }
  return counter;
}

void ThreeWaySplit(char *input_str, char left[vaslib_kSize],
                   char middle[vaslib_kSize], char right[vaslib_kSize],
                   int start, int end) {
  char temp_str[vaslib_kSize] = {0};
  if (start > -1 && start < end && end < strlen(input_str)) {
    strncpy(left, input_str, start + 1);

    strncpy(middle, input_str + start + 1, end - start - 1);
    if (end < (int)strlen(input_str)) {
      strcpy(right, input_str + start + (end - start));
    }
    strcpy(input_str, temp_str);
  }
}