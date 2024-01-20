#include "view.h"

#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "style_dark.h"
#include "vaslib.h"

namespace s21 {

int S21View::ViewMain(S21Controller& the_controller) {
  srand(time(NULL));
  InitWindow(calc_kScreenWidth, calc_kScreenHeight, "SmartCalc");
  SetExitKey(0);
  bool exit_window = false;
  bool show_message_box = false;
  S21ControllerConstants::calc_dot* graph_dots =
      new S21ControllerConstants::calc_dot[calc_kGraphDotsCount_local];
  UninitCalcDotArray(graph_dots, calc_kGraphDotsCount_local);
  Color background_color_value = CLITERAL(Color){33, 33, 33, 33};
  int q = 0;  // used for quakes in meme mode
  int quake_counter = 0;
  SetTargetFPS(60);
  GuiLoadStyleDark();
  GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
  InitAudioDevice();
  Sound fx_wav = LoadSound("a.wav");
  // Text box fields:
  char input_box_field[S21ControllerConstants::calc_kMaxStrSize] = {0},
       x_box_field[S21ControllerConstants::calc_kMaxStrSize] = {0},
       solver_box_field[S21ControllerConstants::calc_kMaxStrSize] = {0},
       output_box_field[S21ControllerConstants::calc_kMaxStrSize] = {0},
       x_zoom_text[S21ControllerConstants::calc_kMaxStrSize] = {0},
       y_zoom_text[S21ControllerConstants::calc_kMaxStrSize] = {0};
  // Copying default text to text fields:
  strcpy(input_box_field, calc_kInputBoxDefaultText.c_str());
  strcpy(x_box_field, calc_kXBoxDefaultText.c_str());
  strcpy(solver_box_field, calc_kSolverDefaultText.c_str());
  strcpy(output_box_field, calc_kOutputDefaultText.c_str());
  strcpy(x_zoom_text, "-1000000");
  strcpy(y_zoom_text, "1000000");
  int zoom_multiplier = 1;
  // Text box edit modes:
  bool input_box_edit_mode = false;
  bool x_box_edit_mode = false;
  bool solver_box_edit_mode = false;
  // Limit box fields:
  char x_axis_lower_limit_box_field[S21ControllerConstants::calc_kMaxStrSize] =
      {0},
       y_axis_lower_limit_box_field[S21ControllerConstants::calc_kMaxStrSize] =
           {0},
       x_axis_higher_limit_box_field[S21ControllerConstants::calc_kMaxStrSize] =
           {0},
       y_axis_higher_limit_box_field[S21ControllerConstants::calc_kMaxStrSize] =
           {0};
  strcpy(x_axis_lower_limit_box_field, "-1000000");
  strcpy(y_axis_lower_limit_box_field, "-1000000");
  strcpy(x_axis_higher_limit_box_field, "1000000");
  strcpy(y_axis_higher_limit_box_field, "1000000");
  bool x_axis_lower_limit_box_edit_mode = false;
  bool y_axis_lower_limit_box_edit_mode = false;
  bool x_axis_higher_limit_box_edit_mode = false;
  bool y_axis_higher_limit_box_edit_mode = false;
  char x_lower_limit_text[S21ControllerConstants::calc_kMaxStrSize] = {0};
  char y_lower_limit_text[S21ControllerConstants::calc_kMaxStrSize] = {0};
  char x_higher_limit_text[S21ControllerConstants::calc_kMaxStrSize] = {0};
  char y_higher_limit_text[S21ControllerConstants::calc_kMaxStrSize] = {0};
  strcpy(x_lower_limit_text, "X Lower Limit");
  strcpy(y_lower_limit_text, "Y Lower Limit");
  strcpy(x_higher_limit_text, "X Higher Limit");
  strcpy(y_higher_limit_text, "Y Higher Limit");
  // MAIN LOOP:
  while (!exit_window) {  // Will detect window close button or ESC
    if (quake_counter > 0) {
      q = rand() % 40 - 20;
      quake_counter--;
    }
    exit_window = WindowShouldClose();
    if (IsKeyPressed(KEY_ESCAPE)) show_message_box = !show_message_box;
    if (IsKeyPressed(KEY_LEFT)) DeleteWordFromInput(input_box_field);
    BeginDrawing();
    ClearBackground(background_color_value);
    // Ways of cleaning the input boxes fast:
    if (IsKeyDown(KEY_RIGHT_ALT) && IsKeyPressed(KEY_BACKSPACE)) {
      strcpy(input_box_field, "\0");
    }
    if (IsKeyDown(KEY_RIGHT_SHIFT) && IsKeyPressed(KEY_BACKSPACE)) {
      strcpy(x_box_field, "\0");
    }
    if (IsKeyDown(KEY_BACKSLASH) && IsKeyPressed(KEY_BACKSPACE)) {
      strcpy(solver_box_field, "\0");
    }
    // Zoom in and zoom out:
    if (IsKeyDown(KEY_RIGHT_ALT) && IsKeyPressed(KEY_EQUAL)) {
      zoom_multiplier *= 10;
      if (zoom_multiplier > 100) zoom_multiplier = 100;
      sprintf(x_zoom_text, "%.0Lf",
              (long double)1000000 / zoom_multiplier * -1);
      sprintf(y_zoom_text, "%.0Lf", (long double)1000000 / zoom_multiplier);
    }
    if (IsKeyDown(KEY_RIGHT_ALT) && IsKeyPressed(KEY_MINUS)) {
      zoom_multiplier /= 10;
      if (zoom_multiplier < 1) zoom_multiplier = 1;
      sprintf(x_zoom_text, "%.0Lf",
              (long double)1000000 / zoom_multiplier * -1);
      sprintf(y_zoom_text, "%.0Lf", (long double)1000000 / zoom_multiplier);
    }
    // Margin (used everywhere):
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
                   input_box_field, S21ControllerConstants::calc_kMaxStrSize,
                   input_box_edit_mode)) {
      input_box_edit_mode = !input_box_edit_mode;
    }
    // Output box:
    GuiTextBox(
        (Rectangle){
            ui_input_wid_end + margin + q, calc_kScreenHeight - margin * 3 + q,
            calc_kScreenWidth - (calc_kScreenWidth * 0.637) - margin * 2,
            margin},
        output_box_field, S21ControllerConstants::calc_kMaxStrSize, false);
    // X input:
    int x_input_wid_end = calc_kScreenWidth / 2 - margin * 2;
    if (GuiTextBox(
            (Rectangle){margin * 2 + q, calc_kScreenHeight - margin * 4 + q,
                        x_input_wid_end, margin},
            x_box_field, S21ControllerConstants::calc_kMaxStrSize,
            x_box_edit_mode)) {
      x_box_edit_mode = !x_box_edit_mode;
    }
    // Solver answer input:
    if (GuiTextBox((Rectangle){x_input_wid_end + margin * 2 + q,
                               calc_kScreenHeight - margin * 4 + q,
                               calc_kScreenWidth / 2 - margin, margin},
                   solver_box_field, S21ControllerConstants::calc_kMaxStrSize,
                   solver_box_edit_mode)) {
      solver_box_edit_mode = !solver_box_edit_mode;
    }
    // Clear button:
    if (GuiButton(
            (Rectangle){calc_kScreenWidth - (calc_kScreenWidth - margin) + q,
                        calc_kScreenHeight - margin * 5.25 + q, margin * 2,
                        margin},
            "Clear")) {
      strcpy(input_box_field, "\0");
      strcpy(x_box_field, "\0");
      strcpy(solver_box_field, "\0");
      strcpy(output_box_field, calc_kOutputDefaultText.c_str());
    }
    // Limits:
    // ----------
    // X lower limit:
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin * 6.25 + q,
                    (float)calc_kScreenHeight / 2 - margin * 3.25 + q - 10, 0,
                    0},
        x_lower_limit_text, S21ControllerConstants::calc_kMaxStrSize, false);
    if (GuiTextBox(
            (Rectangle){(float)calc_kScreenWidth / 2 - margin * 6 + q,
                        (float)calc_kScreenHeight / 2 - margin * 3 + q - 10,
                        margin * 1.9, margin * 0.5},
            x_axis_lower_limit_box_field,
            S21ControllerConstants::calc_kMaxStrSize,
            x_axis_lower_limit_box_edit_mode)) {
      x_axis_lower_limit_box_edit_mode = !x_axis_lower_limit_box_edit_mode;
    }
    // X higher limit:
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin * 6.35 + q,
                    (float)calc_kScreenHeight / 2 - margin * 2.25 + q - 10, 0,
                    0},
        x_higher_limit_text, S21ControllerConstants::calc_kMaxStrSize, false);
    if (GuiTextBox(
            (Rectangle){(float)calc_kScreenWidth / 2 - margin * 6 + q,
                        (float)calc_kScreenHeight / 2 - margin * 2 + q - 10,
                        margin * 1.9, margin * 0.5},
            x_axis_higher_limit_box_field,
            S21ControllerConstants::calc_kMaxStrSize,
            x_axis_higher_limit_box_edit_mode)) {
      x_axis_higher_limit_box_edit_mode = !x_axis_higher_limit_box_edit_mode;
    }
    int ylm = 20;  // Y limits margin;
    // Y higher limit:
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin + q,
                    (float)calc_kScreenHeight / 2 - margin * 8 + q + ylm, 0, 0},
        y_higher_limit_text, S21ControllerConstants::calc_kMaxStrSize, false);
    if (GuiTextBox(
            (Rectangle){(float)calc_kScreenWidth / 2 - margin + q,
                        (float)calc_kScreenHeight / 2 - margin * 7.75 + q + ylm,
                        margin * 1.9, margin * 0.5},
            y_axis_higher_limit_box_field,
            S21ControllerConstants::calc_kMaxStrSize,
            y_axis_higher_limit_box_edit_mode)) {
      y_axis_higher_limit_box_edit_mode = !y_axis_higher_limit_box_edit_mode;
    }
    // Y lower limit:
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin + q,
                    (float)calc_kScreenHeight / 2 - margin * 7 + q + ylm, 0, 0},
        y_lower_limit_text, S21ControllerConstants::calc_kMaxStrSize, false);
    if (GuiTextBox(
            (Rectangle){(float)calc_kScreenWidth / 2 - margin + q,
                        (float)calc_kScreenHeight / 2 - margin * 6.75 + q + ylm,
                        margin * 1.9, margin * 0.5},
            y_axis_lower_limit_box_field,
            S21ControllerConstants::calc_kMaxStrSize,
            y_axis_lower_limit_box_edit_mode)) {
      y_axis_lower_limit_box_edit_mode = !y_axis_lower_limit_box_edit_mode;
    }
    // Limits end
    // ----------
    // X scale label:
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin * 5.65 + q,
                    (float)calc_kScreenHeight / 2 - margin + q - 10, 0, 0},
        x_zoom_text, S21ControllerConstants::calc_kMaxStrSize, false);
    // Y scale label:
    GuiSetState(STATE_FOCUSED);
    GuiTextBox(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin + q,
                    (float)calc_kScreenHeight / 2 - margin * 6 + q + 30, 0, 0},
        y_zoom_text, S21ControllerConstants::calc_kMaxStrSize, false);
    // Calculate logic and equals button:
    GuiSetState(STATE_NORMAL);
    if (GuiButton(
            (Rectangle){calc_kScreenWidth - (calc_kScreenWidth - (margin)) + q,
                        calc_kScreenHeight - margin * 4 + q, margin, margin},
            "=") ||
        IsKeyPressed(KEY_ENTER)) {
      ParamsForCalculation params;
      strcpy(params.input_box_text, input_box_field);
      strcpy(params.x_box_text, x_box_field);
      strcpy(params.solver_box_text, solver_box_field);
      strcpy(params.output_box_text, output_box_field);
      params.quake_counter = &quake_counter;
      params.input_sound = fx_wav;
      params.graph_dots = graph_dots;
      params.the_controller = &the_controller;
      // printf("\n%Lf\n", sinl(-4));
      CommunicateWithLogicModel(&params);
      strcpy(output_box_field, params.output_box_text);
    }
    // Grid for the graph:
    GuiGrid(
        (Rectangle){(float)calc_kScreenWidth / 2 - margin * 4 + q,
                    (float)calc_kScreenHeight / 2 - margin * 5 + q, 300, 300},
        "Grid for the graph", 50, 4);
    // Graph button:
    if (GuiButton(
            (Rectangle){
                calc_kScreenWidth - (calc_kScreenWidth - margin * 3.25) + q,
                calc_kScreenHeight - margin * 5.25 + q, margin * 2, margin},
            "Graph")) {
      graph_dots[0].x = calc_kViewGraphUninit - 1;
      ParamsForCalculation params;
      strcpy(params.input_box_text, input_box_field);
      strcpy(params.x_box_text, x_box_field);
      strcpy(params.solver_box_text, solver_box_field);
      strcpy(params.output_box_text, output_box_field);
      params.quake_counter = &quake_counter;
      params.input_sound = fx_wav;
      params.graph_dots = graph_dots;
      params.the_controller = &the_controller;
      CommunicateWithLogicModel(&params);
      strcpy(output_box_field, params.output_box_text);
    }
    // Draw whole graph:
    for (int i = 0; i < calc_kGraphDotsCount_local; ++i) {
      if (graph_dots[i].x != calc_kViewGraphUninit) {
        long double y_upper = strtold(y_axis_higher_limit_box_field, NULL);
        long double x_upper = strtold(x_axis_higher_limit_box_field, NULL);
        long double y_lower = strtold(y_axis_lower_limit_box_field, NULL);
        long double x_lower = strtold(x_axis_lower_limit_box_field, NULL);
        if ((graph_dots[i].x > x_lower && graph_dots[i].x < x_upper) &&
            (graph_dots[i].y > y_lower && graph_dots[i].y < y_upper) &&
            (graph_dots[i].x > -1000000 / zoom_multiplier &&
             graph_dots[i].x < 1000000 / zoom_multiplier) &&
            (graph_dots[i].y > -1000000 / zoom_multiplier &&
             graph_dots[i].y < 1000000 / zoom_multiplier)) {
          DrawPixel((long double)calc_kScreenWidth / 2 +
                        (graph_dots[i].x * 0.00015 * zoom_multiplier) - 9,
                    (long double)calc_kScreenHeight / 2 -
                        (graph_dots[i].y * 0.00015 * zoom_multiplier) - 50,
                    RED);
        }
      }
    }
    // Status bar:
    GuiStatusBar(
        (Rectangle){0, calc_kScreenHeight - margin, calc_kScreenWidth, margin},
        "SmartCalc");
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
  delete[] graph_dots;
  UnloadSound(fx_wav);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}

void S21View::CommunicateWithLogicModel(ParamsForCalculation* params) {
  S21ControllerConstants::view_to_calc_struct view_to_calc;
  S21ControllerConstants::calc_to_view_struct calc_to_view;
  view_to_calc.calculation_type = S21ControllerConstants::calc_kNoCalculation;
  view_to_calc.calc_input = new char[S21ControllerConstants::calc_kMaxStrSize];
  view_to_calc.x_variable = new char[S21ControllerConstants::calc_kMaxStrSize];
  view_to_calc.solver_variable =
      new char[S21ControllerConstants::calc_kMaxStrSize];
  view_to_calc.unlock = false;
  calc_to_view.answer = new char[S21ControllerConstants::calc_kMaxStrSize];
  calc_to_view.graph_dots =
      new S21ControllerConstants::calc_dot[calc_kGraphDotsCount_local];
  UninitCalcDotArray(calc_to_view.graph_dots, calc_kGraphDotsCount_local);
  if (params->graph_dots[0].x == calc_kViewGraphUninit - 1) {
    view_to_calc.calculation_type = S21ControllerConstants::calc_kGraph;
  }
  UninitCalcDotArray(params->graph_dots, calc_kGraphDotsCount_local);
  if (view_to_calc.calculation_type != S21ControllerConstants::calc_kGraph) {
    if (strcmp(params->x_box_text, calc_kXBoxDefaultText.c_str()) != 0 &&
        strlen(params->x_box_text) && strpbrk(params->input_box_text, "Xx") &&
        !strpbrk(params->x_box_text, "Xx")) {
      view_to_calc.calculation_type =
          S21ControllerConstants::calc_kCalculateWithX;
    } else if (strcmp(params->solver_box_text,
                      calc_kSolverDefaultText.c_str()) != 0 &&
               strlen(params->solver_box_text) &&
               strpbrk(params->input_box_text, "Xx")) {
      view_to_calc.calculation_type = S21ControllerConstants::calc_kSolve;
    } else if (strcmp(params->input_box_text,
                      calc_kInputBoxDefaultText.c_str()) != 0 &&
               strlen(params->input_box_text)) {
      view_to_calc.calculation_type = S21ControllerConstants::calc_kCalculate;
    }
  }
  if (view_to_calc.calculation_type == S21ControllerConstants::calc_kGraph) {
    if (strpbrk(params->input_box_text, "Xx")) {
      strcpy(view_to_calc.calc_input, params->input_box_text);
      params->the_controller->ControllerCommunicate(view_to_calc, calc_to_view);
      CopyDotsToLocal(params->graph_dots, calc_to_view.graph_dots);
    } else if (!strpbrk(params->input_box_text, "Xx")) {
      strcpy(params->output_box_text,
             "X variable is required for graph calculation");
    }
  } else if (view_to_calc.calculation_type ==
             S21ControllerConstants::calc_kCalculate) {
    strcpy(view_to_calc.calc_input, params->input_box_text);
    params->the_controller->ControllerCommunicate(view_to_calc, calc_to_view);
    strcpy(params->output_box_text, calc_to_view.answer);
  } else if (view_to_calc.calculation_type ==
             S21ControllerConstants::calc_kCalculateWithX) {
    strcpy(view_to_calc.calc_input, params->input_box_text);
    strcpy(view_to_calc.x_variable, params->x_box_text);
    params->the_controller->ControllerCommunicate(view_to_calc, calc_to_view);
    strcpy(params->output_box_text, calc_to_view.answer);
  } else if (view_to_calc.calculation_type ==
             S21ControllerConstants::calc_kSolve) {
    strcpy(view_to_calc.calc_input, params->input_box_text);
    strcpy(view_to_calc.solver_variable, params->solver_box_text);
    params->the_controller->ControllerCommunicate(view_to_calc, calc_to_view);
    strcpy(params->output_box_text, "");
    strcat(params->output_box_text, "Solver answer = ");
    strcat(params->output_box_text, calc_to_view.answer);
  }
  SoundAndMemeLogic(CALC_MEME, params->input_sound, params->quake_counter);
  if (view_to_calc.calc_input) delete[] view_to_calc.calc_input;
  if (view_to_calc.x_variable) delete[] view_to_calc.x_variable;
  if (view_to_calc.solver_variable) delete[] view_to_calc.solver_variable;
  if (calc_to_view.answer) delete[] calc_to_view.answer;
  if (calc_to_view.graph_dots) delete[] calc_to_view.graph_dots;
  params->the_controller->ControllerUnlockCalculate();
}

void S21View::SoundAndMemeLogic(bool meme_mode, Sound input_sound,
                                int* quake_counter) {
  if (meme_mode) {
    input_sound = LoadSound("c.wav");
    *quake_counter = 240;
  }
  PlaySound(input_sound);
}

void S21View::UninitCalcDotArray(S21ControllerConstants::calc_dot* input,
                                 int n) {
  for (int i = 0; i < n; ++i) {
    input[i].x = calc_kViewGraphUninit;
    input[i].y = calc_kViewGraphUninit;
  }
}

void S21View::DeleteWordFromInput(char* input_str) {
  const char* stop_characters = " +-*/^%()";
  if (strlen(input_str) > 0) {
    int i = strlen(input_str) - 1;
    bool loop_break = false;
    if (vaslib::VasCharMatch(input_str[i], stop_characters)) {
      input_str[i] = '\0';
    } else {
      while (i > -1 && loop_break == false) {
        if (!vaslib::VasCharMatch(input_str[i], stop_characters)) {
          input_str[i] = '\0';
        } else {
          loop_break = true;
        }
        --i;
      }
    }
  }
}

void S21View::CopyDotsToLocal(S21ControllerConstants::calc_dot* to,
                              S21ControllerConstants::calc_dot* from) {
  for (int i = 0; i < calc_kGraphDotsCount_local; ++i) {
    to[i].x = from[i].x;
    to[i].y = from[i].y;
  }
}
}  // namespace s21

int main() {
  s21::S21View the_view;
  s21::S21Controller the_controller;
  the_view.ViewMain(the_controller);
  return 0;
}