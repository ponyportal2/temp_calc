#ifndef VAS_VASLIB_H_
#define VAS_VASLIB_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
namespace vaslib {

static constexpr int vas_kMaxStringSize = 16384;

void VasCpy(char *input, const int position, const char *what_to_copy);
int VasInsert(char *input, int const position, const char *what_to_copy);
void VasReplace(char *input, const char *what_to_find, const char *to_replace);
void VasCleanUpSpaces(char *input_str);
bool VasCharMatch(const char input_char, const char *input_char_arr_to_find);
void VasClearCharArray(char *input_str, int array_size);
int VasCountOfChars(const char *input_str, const char *to_find);
void VasReverseCharArray(char *string);
void VasCleanUpTrailingZeroes(char *input_str);
}  // namespace vaslib
#endif  // VAS_VASLIB_H_