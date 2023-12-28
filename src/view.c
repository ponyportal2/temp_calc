#include "view.h"

#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "style_dark.h"
#include "vaslib.h"

#ifdef CALC_MEME
#define CALC_MEME 1
#else
#define CALC_MEME 0
#endif  // CALC_MEME

const long long int calc_kViewGraphUninit =
    -1527219354888013218690209950634698640695279350620336683.0;
const int calc_kViewGraphDotsCount = 20000;
const int calc_kScreenWidth = 1280;
const int calc_kScreenHeight = 720;

const char* calc_kXBoxDefaultText =
    "Write your x here, SHIFT + BACKSPACE to clear this field";
const char* calc_kInputBoxDefaultText =
    "Write your expression here, OPTION(Alt) + BACKSPACE to clear this field,"
    "use LEFT ARROW key to delete whole words or numbers";
const char* calc_kSolverDefaultText =
    "Write expected answer for the solver here, \\ + BACKSPACE to clear this "
    "field";
const char* calc_kOutputDefaultText = "Output will be here";

typedef struct calc_pixel_t {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} calc_pixel;

int main() {
  srand(time(NULL));
  InitWindow(calc_kScreenWidth, calc_kScreenHeight, "SmartCalc");
  SetExitKey(0);
  bool exit_window = false;
  bool show_message_box = false;
  bool meme_mode = CALC_MEME;
  calc_dot graph_dots[calc_kViewGraphDotsCount];
  ClearCalcDotArray(graph_dots, calc_kViewGraphDotsCount);
  Color background_color_value = CLITERAL(Color){33, 33, 33, 33};
  int q = 0;  // used for quakes in meme mode
  int quake_counter = 0;
  SetTargetFPS(60);
  GuiLoadStyleDark();
  GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
  InitAudioDevice();
  Sound fx_wav = LoadSound("a.wav");
  char input_box_text[calc_kMaxStrSize] = {0},
       x_box_text[calc_kMaxStrSize] = {0},
       solver_box_text[calc_kMaxStrSize] = {0},
       output_box_text[calc_kMaxStrSize] = {0};
  // Copying default text to text fields
  strcpy(input_box_text, calc_kInputBoxDefaultText);
  strcpy(x_box_text, calc_kXBoxDefaultText);
  strcpy(solver_box_text, calc_kSolverDefaultText);
  strcpy(output_box_text, calc_kOutputDefaultText);
  // Text box edit modes:
  bool input_box_edit_mode = false;
  bool x_box_edit_mode = false;
  bool solver_box_edit_mode = false;

  // MAIN LOOP:
  while (!exit_window) {  // Will detect window close button or ESC
    if (quake_counter > 0) {
      q = rand() % 40 - 20;
      quake_counter--;
    }
    exit_window = WindowShouldClose();
    if (IsKeyPressed(KEY_ESCAPE)) show_message_box = !show_message_box;
    if (IsKeyPressed(KEY_LEFT)) DeleteWordFromInput(input_box_text);
    BeginDrawing();
    ClearBackground(background_color_value);
    // Ways of cleaning the input boxes fast:
    if (IsKeyDown(KEY_RIGHT_ALT) && IsKeyPressed(KEY_BACKSPACE)) {
      strcpy(input_box_text, "\0");
    }
    if (IsKeyDown(KEY_RIGHT_SHIFT) && IsKeyPressed(KEY_BACKSPACE)) {
      strcpy(x_box_text, "\0");
    }
    if (IsKeyDown(KEY_BACKSLASH) && IsKeyPressed(KEY_BACKSPACE)) {
      strcpy(solver_box_text, "\0");
    }
    const int margin = 40;
    // Decorative box:
    GuiGroupBox(
        (Rectangle){calc_kScreenWidth - (calc_kScreenWidth - margin) + q,
                    calc_kScreenHeight - (calc_kScreenHeight - margin) + q,
                    calc_kScreenWidth - margin * 2,
                    calc_kScreenHeight - margin * 3},
        "SmartCalc");
    GuiSetState(STATE_NORMAL);
    // Input box:
    int ui_input_wid_end =
        calc_kScreenWidth - (calc_kScreenWidth * 0.30) - margin * 2;
    if (GuiTextBox((Rectangle){margin + q, calc_kScreenHeight - margin * 3 + q,
                               ui_input_wid_end, margin},
                   input_box_text, calc_kMaxStrSize, input_box_edit_mode)) {
      input_box_edit_mode = !input_box_edit_mode;
    }
    // Output box:
    GuiTextBox(
        (Rectangle){
            ui_input_wid_end + margin + q, calc_kScreenHeight - margin * 3 + q,
            calc_kScreenWidth - (calc_kScreenWidth * 0.637) - margin * 2,
            margin},
        output_box_text, calc_kMaxStrSize, false);
    // X input:
    int x_input_wid_end = calc_kScreenWidth / 2 - margin * 2;
    if (GuiTextBox(
            (Rectangle){margin * 2 + q, calc_kScreenHeight - margin * 4 + q,
                        x_input_wid_end, margin},
            x_box_text, calc_kMaxStrSize, x_box_edit_mode)) {
      x_box_edit_mode = !x_box_edit_mode;
    }
    // Solver answer input:
    if (GuiTextBox((Rectangle){x_input_wid_end + margin * 2 + q,
                               calc_kScreenHeight - margin * 4 + q,
                               calc_kScreenWidth / 2 - margin, margin},
                   solver_box_text, calc_kMaxStrSize, solver_box_edit_mode)) {
      solver_box_edit_mode = !solver_box_edit_mode;
    }
    // Clear button:
    if (GuiButton(
            (Rectangle){calc_kScreenWidth - (calc_kScreenWidth - margin) + q,
                        calc_kScreenHeight - margin * 5.25 + q, margin * 2,
                        margin},
            "Clear")) {
      strcpy(input_box_text, "\0");
      strcpy(x_box_text, "\0");
      strcpy(solver_box_text, "\0");
      strcpy(output_box_text, "\0");
    }
    // Grid for the graph:
    GuiGrid(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin * 4 + q,
                    (float)calc_kScreenHeight / 2 - margin * 5 + q, 300, 300},
        "Grid for the graph", 50, 4);
    // Y scale label:
    GuiSetState(STATE_FOCUSED);
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin + q,
                    (float)calc_kScreenHeight / 2 - margin * 6 + q + 30, 0, 0},
        "y: 1000000", calc_kMaxStrSize, false);
    // X scale label:
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin * 6 + q,
                    (float)calc_kScreenHeight / 2 - margin + q - 10, 0, 0},
        "x: -1000000", calc_kMaxStrSize, false);
    // Calculate logic:
    GuiSetState(STATE_NORMAL);
    if (GuiButton(
            (Rectangle){calc_kScreenWidth - (calc_kScreenWidth - (margin)) + q,
                        calc_kScreenHeight - margin * 4 + q, margin, margin},
            "=") ||
        IsKeyPressed(KEY_ENTER)) {
      EqualsPressed(input_box_text, x_box_text, solver_box_text,
                    output_box_text, &quake_counter, meme_mode, fx_wav,
                    graph_dots);
    }
    // Status bar:
    GuiStatusBar(
        (Rectangle){0, calc_kScreenHeight - margin, calc_kScreenWidth, margin},
        "SmartCalc");
    // Draw whole graph:
    for (int i = 0; i < calc_kViewGraphDotsCount; ++i) {
      if (graph_dots[i].x != calc_kViewGraphUninit) {
        DrawPixel(
            (long double)calc_kScreenWidth / 2 + (graph_dots[i].x * 0.00015),
            (long double)calc_kScreenHeight / 2 - 30 -
                (graph_dots[i].y * 0.00015),
            RED);
        ++i;
      }
    }
    // Exit logic:
    if (show_message_box) {
      DrawRectangle(0, 0, calc_kScreenWidth, calc_kScreenHeight,
                    Fade(RAYWHITE, 0.8f));
      int exit_result =
          GuiMessageBox((Rectangle){(float)calc_kScreenWidth / 2,
                                    (float)calc_kScreenHeight / 2, 250, 100},
                        GuiIconText(ICON_EXIT, "Close Window"),
                        "Do you really want to exit?", "Yes;No");
      if ((exit_result == 0) || (exit_result == 2)) {
        show_message_box = false;
      } else if (exit_result == 1) {
        exit_window = true;
      }
    }
    EndDrawing();
  }
  UnloadSound(fx_wav);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}

void EqualsPressed(char* input_box_text, char* x_box_text,
                   char* solver_box_text, char* output_text, int* quake_counter,
                   int meme_mode, Sound input_sound, calc_dot* graph_dots) {
  char result_text[calc_kMaxStrSize] = {0};
  ClearCalcDotArray(graph_dots, calc_kViewGraphDotsCount);
  view_to_calc_struct view_to_calc;
  calc_to_view_struct calc_to_view;
  view_to_calc.calculation_type = calc_kNoCalculation;
  view_to_calc.calc_input = (char*)calloc(calc_kMaxStrSize, sizeof(char));
  view_to_calc.x_variable = (char*)calloc(calc_kMaxStrSize, sizeof(char));
  view_to_calc.solver_variable = (char*)calloc(calc_kMaxStrSize, sizeof(char));
  calc_to_view.answer = (char*)calloc(calc_kMaxStrSize, sizeof(char));
  if (strcmp(x_box_text, calc_kXBoxDefaultText) != 0 && strlen(x_box_text) &&
      strpbrk(input_box_text, "Xx") && !strpbrk(x_box_text, "Xx")) {
    view_to_calc.calculation_type = calc_kCalculateWithX;
  } else if (strcmp(solver_box_text, calc_kSolverDefaultText) != 0 &&
             strlen(solver_box_text) && strpbrk(input_box_text, "Xx")) {
    view_to_calc.calculation_type = calc_kSolve;
  } else if (strcmp(input_box_text, calc_kInputBoxDefaultText) != 0 &&
             strlen(input_box_text)) {
    view_to_calc.calculation_type = calc_kCalculate;
  }
  if (view_to_calc.calculation_type == calc_kCalculate) {
    strcpy(view_to_calc.calc_input, input_box_text);
    ControllerCommunicate(view_to_calc, calc_to_view);
    strcpy(output_text, calc_to_view.answer);
  } else if (view_to_calc.calculation_type == calc_kCalculateWithX) {
    strcpy(view_to_calc.calc_input, input_box_text);
    strcpy(view_to_calc.x_variable, x_box_text);
    ControllerCommunicate(view_to_calc, calc_to_view);
    strcpy(output_text, calc_to_view.answer);
    // ADD GRAPH DRAWING HERE LATER
  } else if (view_to_calc.calculation_type == calc_kSolve) {
    strcpy(view_to_calc.calc_input, input_box_text);
    strcpy(view_to_calc.solver_variable, solver_box_text);
    ControllerCommunicate(view_to_calc, calc_to_view);
    if (!strcmp(calc_to_view.answer, "0.0") ||
        !strcmp(calc_to_view.answer, "-0.0")) {
      strcpy(output_text, "0 or Error");
    } else {
      strcpy(output_text, calc_to_view.answer);
    }
  }
  SoundAndMemeLogic(CALC_MEME, input_sound, quake_counter);
  if (view_to_calc.calc_input) free(view_to_calc.calc_input);
  if (view_to_calc.x_variable) free(view_to_calc.x_variable);
  if (view_to_calc.solver_variable) free(view_to_calc.solver_variable);
  if (calc_to_view.answer) free(calc_to_view.answer);
  ControllerUnlockCalculate();
}

void SoundAndMemeLogic(bool meme_mode, Sound input_sound, int* quake_counter) {
  if (meme_mode) {
    input_sound = LoadSound("c.wav");
    *quake_counter = 240;
  }
  PlaySound(input_sound);
}

void ClearCalcDotArray(calc_dot* input, int n) {
  for (int i = 0; i < n; ++i) {
    input[i].x = calc_kViewGraphUninit;
    input[i].y = calc_kViewGraphUninit;
  }
}

void DeleteWordFromInput(char* input_str) {
  const char* stop_characters = " +-*/^%()";
  if (strlen(input_str) > 0) {
    int i = strlen(input_str) - 1;
    bool loop_break = false;
    if (VasCharMatch(input_str[i], stop_characters)) {
      input_str[i] = '\0';
    } else {
      while (i > -1 && loop_break == false) {
        if (!VasCharMatch(input_str[i], stop_characters)) {
          input_str[i] = '\0';
        } else {
          loop_break = true;
        }
        --i;
      }
    }
  }
}