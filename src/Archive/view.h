#ifndef CALC_VIEW_H_
#define CALC_VIEW_H_

#include "controller.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
// #include "extras/gui_textbox_extended.h"
#include "raygui.h"
#include "vaslib.h"

void DeleteWordFromInput(char* inputStr);
void ClearCalcDotArray(calc_dot* input, int elements);
void EqualsPressed(char* input_box_text, char* x_box_text,
                   char* solver_box_text, char* output_text, int* quake_counter,
                   int meme_mode, Sound input_sound, calc_dot* graph_dots);
void SoundAndMemeLogic(bool meme_mode, Sound input_sound, int* quake_counter);
#endif  // CALC_VIEW_H_
