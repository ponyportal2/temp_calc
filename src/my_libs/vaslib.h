#ifndef SRC_MY_LIBS_VASLIB_H_
#define SRC_MY_LIBS_VASLIB_H_
#include <stdbool.h>
#include <string.h>

#define vaslib_kSize 16384
void printStrCharByChar(char *inputStr);
void CleanUpSpaces(char *inputStr);
void nullCharArray(char *inputStr);
int count_of_chars(char *inputStr, char *toFind);
int findAndReplaceChar(char *inputStr, char *toFind, char toReplace);
void reverseString(char *string);
bool char_match(char inputChar, const char *inputCharArr);
void cleanUpTrailingZeroes(char *inputStr);
void SplitInHalf(char *inputStr, char left[vaslib_kSize],
                 char right[vaslib_kSize], int splitPos);
void threeWaySplit(char *inputStr, char left[vaslib_kSize],
                   char middle[vaslib_kSize], char right[vaslib_kSize],
                   int start, int end);
long double vasFabs(long double x);
#endif  // SRC_MY_LIBS_VASLIB_H_