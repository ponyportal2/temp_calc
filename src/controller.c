#include "controller.h"

#include "logic_model.h"

void ControllerCommunicate(view_to_calc_struct view_to_calc,
                           calc_to_view_struct calc_to_view) {
  Calculate(view_to_calc, calc_to_view);
}

void ControllerUnlockCalculate() { UnlockCalculate(); }