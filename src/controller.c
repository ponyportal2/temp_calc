#include "controller.h"

#include "logic_model.h"

void ControllerCommunicate(view_to_calc_struct view_to_calc,
                           calc_to_view_struct calc_to_view) {
  if (view_to_calc.calculation_type == calc_kCalculate ||
      view_to_calc.calculation_type == calc_kCalculateWithX) {
    Calculate(view_to_calc, calc_to_view);
  } else if (view_to_calc.calculation_type == calc_kSolve) {
    BinarySearchSolver(view_to_calc, calc_to_view);
  }
}

void ControllerUnlockCalculate() { UnlockCalculate(); }