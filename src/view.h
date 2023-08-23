#ifndef CALC_VIEW_H_
#define CALC_VIEW_H_
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
// #include "extras/gui_textbox_extended.h"
#include "controller.h"
#include "raygui.h"

#define XBOX_DEFAULT_TEXT \
  "Write your x here, SHIFT + BACKSPACE to clear this field"
#define INPUTBOX_DEFAULT_TEXT                                                 \
  "Write your expression here, OPTION(Alt) + BACKSPACE to clear this field, " \
  "use LEFT ARROW key to delete whole words or numbers"
#define SOLVER_DEFAULT_TEXT                                       \
  "Write expected answer for the solver here, \\ + BACKSPACE to " \
  "clear this field"

void DeleteWordFromInput(char* inputStr);
void ClearCalcDotArray(calc_dot* input, int elements);
void equalsPressed(char* input_box_text, char* x_box_text,
                   char* solver_box_text, char* output_text, int* quake_counter,
                   int meme_mode, calc_dot* graph_dots);
void cleanUpSlashN(char* inputStr);
void SoundAndMemeLogic(bool meme_mode, int* quake_counter);
void drawNinePixelsGrid(calc_dot position, Color color);
#endif  // CALC_VIEW_H_
