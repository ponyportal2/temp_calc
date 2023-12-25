#ifndef CALC_CONTROLLER_H_
#define CALC_CONTROLLER_H_
#include <stdbool.h>

#define calc_kMaxStrSize 16384

enum CalculationType {
  calc_kNoCalculation = 0,
  calc_kCalculate,
  calc_kCalculateWithX,
  calc_kSolve
};

typedef struct calc_dot_t {
  long double x;
  long double y;
} calc_dot;

typedef struct view_to_calc_struct_t {
  char* x_variable;
  char* solver_variable;
  char* calc_input;
  enum CalculationType calculation_type;
  bool unlock;
} view_to_calc_struct;

typedef struct calc_to_view_struct_t {
  char* answer;
  calc_dot* logic_model_graph_dots;
} calc_to_view_struct;

void ControllerCommunicate(view_to_calc_struct view_to_calc,
                           calc_to_view_struct calc_to_view);

void ControllerUnlockCalculate();

#endif  // CALC_CONTROLLER_H_