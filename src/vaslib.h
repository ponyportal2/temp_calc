#ifndef VAS_VASLIB_H_
#define VAS_VASLIB_H_

#include <stdlib.h>
#include <string.h>

#define vas_kMaxStringSize 16384

void VasCpy(char *input, const int position, const char *what_to_copy);
int VasInsert(char *input, int const position, const char *what_to_copy);
void VasReplace(char *input, const char *what_to_find, const char *to_replace);
void VasCleanUpSpaces(char *input_str);
bool VasCharMatch(const char input_char, const char *input_char_arr_to_find);
int VasCountOfChars(const char *input_str, const char *to_find);
void VasReverseCharArray(char *string);
void VasCleanUpTrailingZeroes(char *input_str);
// ----------------

void VasCpy(char *input, const int position, const char *what_to_copy) {
  for (int i = 0; i < strlen(what_to_copy); ++i) {
    input[position + i] = what_to_copy[i];
  }
}

// TODO: this function
int VasInsert(char *input, int const position, const char *what_to_copy) {
  int valid = 0;
  char temp_input[vas_kMaxStringSize] = {0};
  if (position <= strlen(input) && position > -1) {
    valid = 1;
    char left[vas_kMaxStringSize] = {0};
    char right[vas_kMaxStringSize] = {0};
    strncpy(left, input, position);
    strcpy(right, input + position);
    strcpy(temp_input, left);
    strcat(temp_input, what_to_copy);
    strcat(temp_input, right);
    strcpy(input, temp_input);
    printf("<%s>\n<%s>\n", left, right);
  }
  return valid;
}

void VasReplace(char *input, const char *what_to_find, const char *to_replace) {
  int what_to_find_len = strlen(what_to_find);
  char temp_str[vas_kMaxStringSize] = {0};
  for (int i = 0; i < strlen(input); ++i) {
    strncpy(temp_str, input + i, what_to_find_len);
    if (!strcmp(temp_str, what_to_find)) {
      VasCpy(input, i, to_replace);
    }
  }
}

void VasCleanUpSpaces(char *input_str) {
  char temp_str[vas_kMaxStringSize] = {0};
  int i = 0, j = 0;
  while (input_str[i] != '\0') {
    if (input_str[i] != ' ' && input_str[i] != '\n' && input_str[i] != '\t') {
      temp_str[j] = input_str[i];
      ++j;
    }
    ++i;
  }
  strcpy(input_str, temp_str);
}

bool VasCharMatch(const char char_to_match, const char *char_array_to_match) {
  bool match = 0;
  int i = 0;
  while (char_array_to_match[i] != '\0') {
    if (char_array_to_match[i] == char_to_match) {
      match = true;
    }
    ++i;
  }
  return match;
}

int VasCountOfChars(const char *input_str, const char *to_find) {
  int counter = 0, i = 0;
  while (input_str[i] != '\0') {
    if (VasCharMatch(input_str[i], to_find)) counter++;
    i++;
  }
  return counter;
}

void VasReverseCharArray(char *string) {
  char temp[vas_kMaxStringSize] = {0};
  strcpy(temp, string);
  int length = strlen(string), i = 0;
  for (; i < length; i++) string[i] = temp[length - i - 1];
  string[i] = '\0';
}

void VasCleanUpTrailingZeroes(char *input_str) {
  int i = strlen(input_str) - 1;
  bool loop_break = false;
  if (VasCharMatch('.', input_str) == true) {
    while (loop_break == false && i > -1) {
      if ((i - 1 > 0) && input_str[i] == '0' && input_str[i - 1] != '.') {
        input_str[i] = '\0';
      } else {
        loop_break = true;
      }
      i--;
    }
  }
}

#endif  // VAS_VASLIB_H_