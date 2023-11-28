#ifndef SRC_MY_LIBS_VASLIB_H_
#define SRC_MY_LIBS_VASLIB_H_
#include <stdbool.h>
#include <string.h>

#define vaslib_kSize 16384
void printStrCharByChar(char *inputStr);
void CleanUpSpaces(char *inputStr);
void nullCharArray(char *inputStr);
int VasCountOfChars(char *inputStr, char *toFind);
int VasFindAndReplaceChar(char *inputStr, char *toFind, char toReplace);
void VasReverseCharArray(char *string);
bool char_match(char inputChar, const char *inputCharArr);
void VasCleanUpTrailingZeroes(char *inputStr);
void SplitInHalf(char *inputStr, char left[vaslib_kSize],
                 char right[vaslib_kSize], int splitPos);
void ThreeWaySplit(char *inputStr, char left[vaslib_kSize],
                   char middle[vaslib_kSize], char right[vaslib_kSize],
                   int start, int end);
long double vasFabs(long double x);
#endif  // SRC_MY_LIBS_VASLIB_H_