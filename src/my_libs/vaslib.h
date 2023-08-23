#ifndef SRC_MY_LIBS_VASLIB_H_
#define SRC_MY_LIBS_VASLIB_H_
#include <stdbool.h>
#include <string.h>

#define VASLIBTHESIZE 16384
void printStrCharByChar(char *inputStr);
void cleanUpSpaces(char *inputStr);
void nullCharArray(char *inputStr);
int findCharCount(char *inputStr, char *toFind);
int findAndReplaceChar(char *inputStr, char *toFind, char toReplace);
void reverseString(char *string);
bool charMatch(char inputChar, const char *inputCharArr);
void cleanUpTrailingZeroes(char *inputStr);
void twoWaySplit(char *inputStr, char left[VASLIBTHESIZE],
                 char right[VASLIBTHESIZE], int splitPos);
void threeWaySplit(char *inputStr, char left[VASLIBTHESIZE],
                   char middle[VASLIBTHESIZE], char right[VASLIBTHESIZE],
                   int start, int end);
long double vasFabs(long double x);
#endif  // SRC_MY_LIBS_VASLIB_H_