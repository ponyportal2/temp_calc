#ifndef CALC_VIEW_H_
#define CALC_VIEW_H_

#include "controller.h"
#include "controller_constants.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
// #include "extras/gui_textbox_extended.h"
#include <string>

#include "raygui.h"
#include "vaslib.h"

namespace s21 {
class S21View {
 public:
  int ViewMain(S21Controller& the_controller);

 private:
  struct ParamsForCalculation {
    char input_box_text[S21ControllerConstants::calc_kMaxStrSize];
    char x_box_text[S21ControllerConstants::calc_kMaxStrSize];
    char solver_box_text[S21ControllerConstants::calc_kMaxStrSize];
    char output_box_text[S21ControllerConstants::calc_kMaxStrSize];
    int* quake_counter;
    Sound input_sound;
    S21ControllerConstants::calc_dot* graph_dots;
    S21Controller* the_controller;
  };
  void DeleteWordFromInput(char* inputStr);
  void UninitCalcDotArray(S21ControllerConstants::calc_dot* input,
                          int elements);
  void CommunicateWithLogicModel(ParamsForCalculation* params);
  void SoundAndMemeLogic(bool meme_mode, Sound input_sound, int* quake_counter);
  void CopyDotsToLocal(S21ControllerConstants::calc_dot* to,
                       S21ControllerConstants::calc_dot* from);
  void PrintDotArray(S21ControllerConstants::calc_dot* input);

#ifdef CALC_MEME
#define CALC_MEME 1
#else
#define CALC_MEME 0
#endif  // CALC_MEME

  static constexpr long long int calc_kViewGraphUninit = -1527219354888013218;
  static constexpr int calc_kScreenWidth = 1280;
  static constexpr int calc_kScreenHeight = 720;
  static constexpr int calc_kGraphDotsCount_local =
      S21ControllerConstants::calc_kGraphDotsCount;
  const std::string calc_kXBoxDefaultText =
      "Write your x here, SHIFT + BACKSPACE to clear this field";
  const std::string calc_kInputBoxDefaultText =
      "Write your expression here, OPTION(Alt) + BACKSPACE to clear this field,"
      "use LEFT ARROW key to delete whole words or numbers";
  const std::string calc_kSolverDefaultText =
      "Write expected answer for the solver here, \\ + BACKSPACE to clear this "
      "field";
  const std::string calc_kOutputDefaultText = "Output will be here";
};
}  // namespace s21
#endif  // CALC_VIEW_H_
