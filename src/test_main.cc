#include "gtest/gtest.h"
#include "logic_model.h"

#define EPS 0.0000009
#define EPSFOUR 0.0001
#define MAX_STRING_SIZE 16384
using st = std::string;

// TEST1
TEST(CalcTest, Test167) {
  char expression[MAX_STRING_SIZE] = "5+5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("10", NULL), strtold(outputStr, NULL), EPS);
}

// TEST3
TEST(CalcTest, Test3) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+-5678.1234*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)+6)";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("-40920.7057214", NULL), strtold(outputStr, NULL), EPS);
}

// TEST4
TEST(CalcTest, Test4) {
  char expression[MAX_STRING_SIZE] = "1000000^99";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("inf"), st(outputStr));
}

// TEST5
TEST(CalcTest, Test5) {
  char expression[MAX_STRING_SIZE] = "3.09mod";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TEST6
TEST(CalcTest, Test6) {
  char expression[MAX_STRING_SIZE] = "5*6/7";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("4.2857142857"), st(outputStr));
}

// TEST7
TEST(CalcTest, Test7) {
  char expression[MAX_STRING_SIZE] = "5/6*7";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("5.8333333331"), st(outputStr));
}

// TEST8
TEST(CalcTest, Test8) {
  char expression[MAX_STRING_SIZE] = "5-6+7";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("6.0"), st(outputStr));
}

// TEST9
TEST(CalcTest, Test9) {
  char expression[MAX_STRING_SIZE] = "5+6-7";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("4.0"), st(outputStr));
}

// TEST10
TEST(CalcTest, Test10) {
  char expression[MAX_STRING_SIZE] = "-(-5+aboba)";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TEST11
TEST(CalcTest, Test11) {
  char expression[MAX_STRING_SIZE] = "-5--6++7";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("8.0"), st(outputStr));
}

// TEST12
TEST(CalcTest, Test12) {
  char expression[MAX_STRING_SIZE] = "soc(0.99)";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TEST13
TEST(CalcTest, Test13) {
  char expression[MAX_STRING_SIZE] = "5+-6-+7";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-8.0"), st(outputStr));
}

// ------
// WITH X
// ------

// TESTX1
TEST(CalcTest, Testx1) {
  char expression[MAX_STRING_SIZE] = "5+x";
  char x[MAX_STRING_SIZE] = "5+5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("15", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX4
TEST(CalcTest, Testx4) {
  char expression[MAX_STRING_SIZE] = "45/x";
  char x[MAX_STRING_SIZE] = "9";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("5", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX8
TEST(CalcTest, Testx8) {
  char expression[MAX_STRING_SIZE] = "x*x";
  char x[MAX_STRING_SIZE] = "1000000000000000000000000000000000000000000000";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("999999999999999999998992975478877801608360559837361100082259766"
               "168576867"
               "30"
               "6596861455892480.0"),
            st(outputStr));
}

// TESTX9
TEST(CalcTest, Testx9) {
  char expression[MAX_STRING_SIZE] = "x^3 + x/2 + 56mod4";
  char x[MAX_STRING_SIZE] = "9.4342345235235";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("844.409", NULL), strtold(outputStr, NULL), EPSFOUR);
}

// TESTX10
TEST(CalcTest, Testx10) {
  char expression[MAX_STRING_SIZE] = "x^3 + x/2 + 56%4";
  char x[MAX_STRING_SIZE] = "9.4342345235235";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("844.409", NULL), strtold(outputStr, NULL), EPSFOUR);
}

// TESTX11
TEST(CalcTest, Testx11) {
  char expression[MAX_STRING_SIZE] = "x^2+x^3*(-4 * x)-100";
  char x[MAX_STRING_SIZE] = "-1000000";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-3999999999999000000069632.0"), st(outputStr));
}

// TESTX11_2
TEST(CalcTest, Testx11_2) {
  char expression[MAX_STRING_SIZE] =
      "(x^2+x^3*(-4 * x)-100)-(x^2+x^3*(-4 * x)-100)";
  char x[MAX_STRING_SIZE] = "-1000000";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("0", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX12
TEST(CalcTest, Testx12) {
  char expression[MAX_STRING_SIZE] = "x^1.1";
  char x[MAX_STRING_SIZE] = "-1000000";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("NAN encountered during calculation"), st(outputStr));
}

// TESTX13
TEST(CalcTest, Testx13) {
  char expression[MAX_STRING_SIZE] = "x^2-sqrt(x^x)";
  char x[MAX_STRING_SIZE] = "64";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-6277101735386680763835789423207666416102355444464034512896.0"),
            st(outputStr));
}

// TESTX14
TEST(CalcTest, Testx14) {
  char expression[MAX_STRING_SIZE] = "cos(acos(tan(atan(sin(x)))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("0.4794255386"), st(outputStr));
}

// TESTX15
TEST(CalcTest, Testx15) {
  char expression[MAX_STRING_SIZE] = "cos(acos(tan(atan(sin(sqrt(x))))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("0.6496369391"), st(outputStr));
}

// TESTX16
TEST(CalcTest, Testx16) {
  char expression[MAX_STRING_SIZE] =
      "cos(acos(tan(atan(sin(sqrt(x^sqrt(sqrt((5)*(+5%-4))))))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Brackets are invalid"), st(outputStr));
}

// TESTX19
TEST(CalcTest, Testx19) {
  char expression[MAX_STRING_SIZE] =
      "cos(acos(tan(atan(sin(sqrt(0.35469507876))))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("0.5609747685"), st(outputStr));
}

// TESTX20
TEST(CalcTest, Testx20) {
  char expression[MAX_STRING_SIZE] =
      "=cos(acos(tan(atan(sin(sqrt(0.35469507876))))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX21
TEST(CalcTest, Testx21) {
  char expression[MAX_STRING_SIZE] = "5";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("5", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX22
TEST(CalcTest, Testx22) {
  char expression[MAX_STRING_SIZE] = "5";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("5", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX23
TEST(CalcTest, Testx23) {
  char expression[MAX_STRING_SIZE] = "asin(cos(x))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("1.0708", NULL), strtold(outputStr, NULL), EPSFOUR);
}

// TESTX24
TEST(CalcTest, Testx24) {
  char expression[MAX_STRING_SIZE] = "asin(cos(sqrt(-x)))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("NAN encountered during calculation"), st(outputStr));
}

// TESTX25
TEST(CalcTest, Testx25) {
  char expression[MAX_STRING_SIZE] = "log(x)";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-0.2291479884"), st(outputStr));
}

// TESTX26
TEST(CalcTest, Testx26) {
  char expression[MAX_STRING_SIZE] = "ln(x)";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-0.5276327421"), st(outputStr));
}

// TESTX27
TEST(CalcTest, Testx27) {
  char expression[MAX_STRING_SIZE] = "=fsdfsdfsdf";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX28
TEST(CalcTest, Testx28) {
  char expression[MAX_STRING_SIZE] = "5(6)(7)";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("210.0"), st(outputStr));
}

// TESTX30
TEST(CalcTest, Testx30) {
  char expression[MAX_STRING_SIZE] = "-5-+5--2*+5/+1";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("0.0"), st(outputStr));
}

// TESTX31
TEST(CalcTest, Testx31) {
  char expression[MAX_STRING_SIZE] = "-5^-5";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-0.00032"), st(outputStr));
}

// TESTX32
TEST(CalcTest, Testx32) {
  char expression[MAX_STRING_SIZE] = "+5^+5";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("3125.0"), st(outputStr));
}

// TESTX33
TEST(CalcTest, Testx33) {
  char expression[MAX_STRING_SIZE] = "+5%+4";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("1.0"), st(outputStr));
}

// TESTX34
TEST(CalcTest, Testx34) {
  char expression[MAX_STRING_SIZE] = "-5%-4";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-1.0"), st(outputStr));
}

// TESTX35
TEST(CalcTest, Testx35) {
  char expression[MAX_STRING_SIZE] = "-(-5)%-4";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("1.0"), st(outputStr));  // maybe incorrect
}

// TESTX36
TEST(CalcTest, Testx36) {
  char expression[MAX_STRING_SIZE] = "--5%-4";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("1.0"), st(outputStr));  // maybe incorrect
}

// TESTX_E_29
TEST(CalcTest, Testxe29) {
  char expression[MAX_STRING_SIZE] = "(+5)-(+5)-(-2)*(+5)/(+1)";
  char x[MAX_STRING_SIZE] = "0.59";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("10.0"), st(outputStr));
}

// TESTX_E_7
TEST(CalcTest, Testxe7) {
  char expression[MAX_STRING_SIZE] =
      "-0.68*x*x*x*x-0.1*x*x*x-0.01*x*x-0.0*x*x*x";
  char x[MAX_STRING_SIZE] = "1000000000000000000000000000000000000000000000";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-inf"), st(outputStr));
}

// TESTX_E_6
TEST(CalcTest, Testxe6) {
  char expression[MAX_STRING_SIZE] =
      "-0.68*x*x*x*x-0.1*x*x*x-0.01*x*x-0.0*x*x*x";
  char x[MAX_STRING_SIZE] = "0";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("0", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX_E_2
TEST(CalcTest, Testxe2) {
  char expression[MAX_STRING_SIZE] =
      "-(+5-(+6-(-7-(-1-(+3+4+x*-6+-3/-4++5++7)))))";
  char x[MAX_STRING_SIZE] = "-54343.43434";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("-326073.35604", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX_E_3
TEST(CalcTest, Testxe3) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)+6)";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("-40920.7057214", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX_VAL_1
TEST(CalcTest, Testxval1) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)+**6)";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_VAL_2
TEST(CalcTest, Testxval2) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)+&6)";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_VAL_3
TEST(CalcTest, Testxval3) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)+++6)";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_VAL_4
TEST(CalcTest, Testxval4) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)---6)";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_VAL_5
TEST(CalcTest, Testxval5) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)-sqtr(6))";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_VAL_6
TEST(CalcTest, Testxval6) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)-soc(6))";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_VAL_7
TEST(CalcTest, Testxval7) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)-sc(6))";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_E_18
TEST(CalcTest, Testxval18) {
  char expression[MAX_STRING_SIZE] = "sin(sqrt(x^((-21)^(1/4))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("NAN encountered during calculation"), st(outputStr));
}

// TESTX_E_69
TEST(CalcTest, Testxval69) {
  char expression[MAX_STRING_SIZE] = "45/x";
  char x[MAX_STRING_SIZE] = "0";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Division by zero is impossible"), st(outputStr));
}

// TESTX_E_69_2
TEST(CalcTest, Testxval692) {
  char expression[MAX_STRING_SIZE] = "45.0.0/x";
  char x[MAX_STRING_SIZE] = "0";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX_VAL_8
TEST(CalcTest, Testxval8) {
  char expression[MAX_STRING_SIZE] =
      "-(-(-3*(-(-(3*4+x*-6+-3/-4+5+7)*(2/5)+4/(9-5*(5/6))))-5)-s(6))";
  char x[MAX_STRING_SIZE] = "-5678.1234";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TEST2
TEST(CalcTest, Test2) {
  char expression[MAX_STRING_SIZE] =
      "-(+5-(+6-(-7-(-1-(+3+4+-54343.43434*-6+-3/-4++5++7)))))";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_NEAR(strtold("-326073.35604", NULL), strtold(outputStr, NULL), EPS);
}

// TESTX17
TEST(CalcTest, Testx17) {
  char expression[MAX_STRING_SIZE] =
      "cos(acos(tan(atan(sin(sqrt(x^sqrt(sqrt((5)*(+5%4))t)))))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX177
TEST(CalcTest, Testx177) {
  char expression[MAX_STRING_SIZE] =
      "cos(acos(tan(atan(sin(sqrt(x^sqrt(sqrt((5)*(+5%4)))))))))";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("0.5609747685"), st(outputStr));
}

// TESTX178
TEST(CalcTest, Testx178) {
  char expression[MAX_STRING_SIZE] = "x*0.1.4";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX179
TEST(CalcTest, Testx179) {
  char expression[MAX_STRING_SIZE] = "x*0.14";
  char x[MAX_STRING_SIZE] = "0.5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("0.07"), st(outputStr));
}

// TESTX180
TEST(CalcTest, Testx180) {
  char expression[MAX_STRING_SIZE] = "sqrt(x)";
  char x[MAX_STRING_SIZE] = "-1";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("NAN encountered during calculation"), st(outputStr));
}

// TEST181
TEST(CalcTest, Test181) {
  char expression[MAX_STRING_SIZE] = "6(5)7(8)(9)(10)(11)(12)(13)(14)(15)";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("54486432000.0"), st(outputStr));
}

// TEST182
TEST(CalcTest, Test182) {
  char expression[MAX_STRING_SIZE] = "6((-5a))7(8)(9)(10)(11)(12)(13)(14)(15)";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TESTX183
TEST(CalcTest, Testx183) {
  char expression[MAX_STRING_SIZE] = "asin(sqrt(-1))";
  char x[MAX_STRING_SIZE] = "-1";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.ReplaceX(expression, x);
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("NAN encountered during calculation"), st(outputStr));
}

// TEST184
TEST(CalcTest, Test184) {
  char expression[MAX_STRING_SIZE] = "6()-5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("Invalid symbols encountered"), st(outputStr));
}

// TEST185
TEST(CalcTest, Test185) {
  char expression[MAX_STRING_SIZE] = "6(1)-5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("1.0"), st(outputStr));
}

// TEST186
TEST(CalcTest, Test186) {
  char expression[MAX_STRING_SIZE] = "6(1)~5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-30.0"), st(outputStr));
}

// TEST187
TEST(CalcTest, Test187) {
  char expression[MAX_STRING_SIZE] = "~5";
  char outputStr[MAX_STRING_SIZE] = {0};
  s21::S21LogicModel the_model;
  the_model.TestCalculate(expression, outputStr);
  EXPECT_EQ(st("-5.0"), st(outputStr));
}

// TEST GRAPH 1
TEST(Graph, Test1) {
  int calc_kGraphDotsCount_local =
      s21::S21ControllerConstants::calc_kGraphDotsCount;
  s21::S21ControllerConstants::view_to_calc_struct view_to_calc;
  s21::S21ControllerConstants::calc_to_view_struct calc_to_view;
  view_to_calc.calculation_type = s21::S21ControllerConstants::calc_kGraph;
  view_to_calc.calc_input = new char[MAX_STRING_SIZE];
  view_to_calc.x_variable = new char[MAX_STRING_SIZE];
  view_to_calc.solver_variable = new char[MAX_STRING_SIZE];
  view_to_calc.unlock = false;
  calc_to_view.answer = new char[MAX_STRING_SIZE];
  calc_to_view.graph_dots =
      new s21::S21ControllerConstants::calc_dot[calc_kGraphDotsCount_local];
  strcpy(view_to_calc.calc_input, "1+x");
  s21::S21LogicModel the_model;
  the_model.Graph(view_to_calc, calc_to_view);
  char temp[s21::S21ControllerConstants::calc_kMaxStrSize] = {0};
  sprintf(temp, "%Lf", calc_to_view.graph_dots[2].y);
  EXPECT_EQ(st(temp), st("-999799.000000"));
  if (view_to_calc.calc_input) delete[] view_to_calc.calc_input;
  if (view_to_calc.x_variable) delete[] view_to_calc.x_variable;
  if (view_to_calc.solver_variable) delete[] view_to_calc.solver_variable;
  if (calc_to_view.answer) delete[] calc_to_view.answer;
  if (calc_to_view.graph_dots) delete[] calc_to_view.graph_dots;
}

// TEST SOLVER 1
TEST(Graph, Solver1) {
  s21::S21ControllerConstants::view_to_calc_struct view_to_calc;
  s21::S21ControllerConstants::calc_to_view_struct calc_to_view;
  view_to_calc.calculation_type = s21::S21ControllerConstants::calc_kSolve;
  view_to_calc.calc_input = new char[MAX_STRING_SIZE];
  view_to_calc.x_variable = new char[MAX_STRING_SIZE];
  view_to_calc.solver_variable = new char[MAX_STRING_SIZE];
  view_to_calc.unlock = false;
  calc_to_view.answer = new char[MAX_STRING_SIZE];
  strcpy(view_to_calc.calc_input, "1+x");
  strcpy(view_to_calc.solver_variable, "5");
  s21::S21LogicModel the_model;
  the_model.BinarySearchSolver(view_to_calc, calc_to_view);
  EXPECT_EQ(st(calc_to_view.answer), st("4.0"));
  if (view_to_calc.calc_input) delete[] view_to_calc.calc_input;
  if (view_to_calc.x_variable) delete[] view_to_calc.x_variable;
  if (view_to_calc.solver_variable) delete[] view_to_calc.solver_variable;
  if (calc_to_view.answer) delete[] calc_to_view.answer;
}

// TEST SOLVER 2
TEST(Graph, Solver2) {
  s21::S21ControllerConstants::view_to_calc_struct view_to_calc;
  s21::S21ControllerConstants::calc_to_view_struct calc_to_view;
  view_to_calc.calculation_type = s21::S21ControllerConstants::calc_kSolve;
  view_to_calc.calc_input = new char[MAX_STRING_SIZE];
  view_to_calc.x_variable = new char[MAX_STRING_SIZE];
  view_to_calc.solver_variable = new char[MAX_STRING_SIZE];
  view_to_calc.unlock = false;
  calc_to_view.answer = new char[MAX_STRING_SIZE];
  strcpy(view_to_calc.calc_input, "1+x");
  strcpy(view_to_calc.solver_variable, "-5");
  s21::S21LogicModel the_model;
  the_model.BinarySearchSolver(view_to_calc, calc_to_view);
  EXPECT_EQ(st(calc_to_view.answer), st("-6.0"));
  if (view_to_calc.calc_input) delete[] view_to_calc.calc_input;
  if (view_to_calc.x_variable) delete[] view_to_calc.x_variable;
  if (view_to_calc.solver_variable) delete[] view_to_calc.solver_variable;
  if (calc_to_view.answer) delete[] calc_to_view.answer;
}

int main(int argc, char* argv[]) {
  testing::GTEST_FLAG(throw_on_failure) = true;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
