#ifndef CALC_CONTROLLER_H_
#define CALC_CONTROLLER_H_
#include <stdbool.h>

#include "controller_constants.h"
#include "logic_model.h"

namespace s21 {
class S21Controller {
 public:
  // Public methods:
  void ControllerCommunicate(
      S21ControllerConstants::view_to_calc_struct view_to_calc,
      S21ControllerConstants::calc_to_view_struct calc_to_view);

  void ControllerUnlockCalculate();

 private:
  s21::S21LogicModel the_model;
};

}  // namespace s21
#endif  // CALC_CONTROLLER_H_