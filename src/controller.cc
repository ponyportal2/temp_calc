#include "controller.h"

namespace s21 {
void S21Controller::ControllerCommunicate(
    S21ControllerConstants::view_to_calc_struct view_to_calc,
    S21ControllerConstants::calc_to_view_struct calc_to_view) {
  if (view_to_calc.calculation_type ==
          S21ControllerConstants::calc_kCalculate ||
      view_to_calc.calculation_type ==
          S21ControllerConstants::calc_kCalculateWithX) {
    the_model.Calculate(view_to_calc, calc_to_view);
  } else if (view_to_calc.calculation_type ==
             S21ControllerConstants::calc_kSolve) {
    the_model.BinarySearchSolver(view_to_calc, calc_to_view);
  } else if (view_to_calc.calculation_type ==
             S21ControllerConstants::calc_kGraph) {
    the_model.Graph(view_to_calc, calc_to_view);
  }
}

void S21Controller::ControllerUnlockCalculate() { the_model.UnlockCalculate(); }
}  // namespace s21