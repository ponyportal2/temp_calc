#ifndef CALC_CONTROLLER_CONSTANTS_H_
#define CALC_CONTROLLER_CONSTANTS_H_
#include <stdbool.h>

namespace s21 {
class S21ControllerConstants {
 public:
  static constexpr int calc_kMaxStrSize = 16384;
  static constexpr int calc_kGraphDotsCount = 20000;

  enum CalculationType {
    calc_kNoCalculation = 0,
    calc_kCalculate,
    calc_kCalculateWithX,
    calc_kSolve,
    calc_kGraph
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
    calc_dot* graph_dots;
  } calc_to_view_struct;
};
}  // namespace s21
#endif  // CALC_CONTROLLER_CONSTANTS_H_