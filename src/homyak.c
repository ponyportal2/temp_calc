// if (input[i] == op_char) {
//   if (op_char == '*') {
//     calc_result = (long double)LeftDigits(input, i, &result_start) *
//                   (long double)RightDigits(input, i, &result_end);
//     sprintfHelper(sprintf_result, calc_result);
//   } else if (op_char == '/') {
//     if (RightDigits(input, i, &result_end) != 0) {
//       calc_result = (long double)LeftDigits(input, i, &result_start) /
//                     (long double)RightDigits(input, i, &result_end);
//     } else {
//       err = calcerr_kDivisionByZero;
//       loop_break = true;
//     }
//     break;
//   } else if (op_char == '+') {
//     calc_result = (long double)LeftDigits(input, i, &result_start) +
//                   (long double)RightDigits(input, i, &result_end);
//   } else if (op_char == '-') {
//     calc_result = (long double)LeftDigits(input, i, &result_start) -
//                   (long double)RightDigits(input, i, &result_end);
//   } else if (op_char == '^') {
//     calc_result = powl(LeftDigits(input, i, &result_start),
//                        RightDigits(input, i, &result_end));
//   } else if (op_char == "%") {
//     calc_result = fmodl(LeftDigits(input, i, &result_start),
//                         RightDigits(input, i, &result_end));
//   }
// }

// int parseAndApplyOperators(char *midStr) {
//   enum calc_CalculationError err = 0;
//   bool loop_break = false;
//   while (loop_break == false) {
//     if (err = operatorPassLoop(midStr, "^")) loop_break = true;
//     if (err = operatorPassLoop(midStr, "/")) loop_break = true;
//     if (err = operatorPassLoop(midStr, "*")) loop_break = true;
//     if (err = operatorPassLoop(midStr, "%")) loop_break = true;
//     while (VasCountOfChars(midStr, "-") != 0) {
//       if (midStr[0] == '-' && operatorCount(midStr) == 1) midStr[0] = '~';
//       if (VasCountOfChars(midStr, "~") == 1 && midStr[0] != '~') {
//         VasReplace(midStr, "~", "-");
//       }
//       if (operatorPassLoop(midStr, "-")) loop_break = true;
//     }
//     err = operatorPassLoop(midStr, "+");
//     if (err != 0) break;
//     if (operatorCount(midStr) < 1 || isJustANumber(midStr)) {
//       loop_break = true;
//     }
//   }
//   return err;
// }

// -------------------

// TESTSOLVER2

// #test solver2

// char inputBoxText[MAX_STRING_SIZE] = "x^2-sqrt(x^x)";
// char solverBoxText[MAX_STRING_SIZE] = "64";
// char possibleAnswer[MAX_STRING_SIZE] = {0};

// if (!binarySearchSolver(inputBoxText, solverBoxText, 0, possibleAnswer)) {
//   binarySearchSolver(inputBoxText, solverBoxText, 1, possibleAnswer);
// }

// ck_assert_str_eq("8.0", possibleAnswer);

// TESTX13

// #test calcx13

// char expression[MAX_STRING_SIZE] = "x^2-sqrt(x^x)";
// char x[MAX_STRING_SIZE] = "64";
// char outputStr[MAX_STRING_SIZE] = {0};
// replaceX(expression, x);
// calculate(expression, outputStr, 0);
// // printf("\n>>%s<<\n",outputStr);

// ck_assert_ldouble_eq_tol(strtold("1",NULL), strtold(outputStr,NULL), EPS);

// ---------------------------------------------------------
// HOMYAK:
// S21_THE_CALC.C
// ---------------------------------------------------------

// calculate debug:

// printf("\nPREPAR>L:%s\nM:%s\nE:%s\n", left, middle, right);
// printf("\n>>%i<<\n", err);
// printf("\nPreRecomb: L:%s\nM:%s\nE:%s\n", left, middle, right);
// printf("\nle:%s", lExpression);
// printf("\nPR>L:%s\nM:%s\nE:%s\nT:%s\n", left, middle, right,
//  expression);
// printf("\nPOSREK: T:%s\n", lExpression);  //!!!!!!!!!!!
// printf("\nle:%s", lExpression);
// printf("\nle:%s", lExpression);
// printf("\nL:%s\nM:%s\nE:%s\nT:%s\n", left, middle, right,
//        lExpression);
// printf("\nPOSLAS: T:%s\n", lExpression);  //!!!!!!!!!!!
// printf("\n{{%i}}\n", isBracketsCountValid(expression));  //
// DAFAQ}
// printf("\n%i,%i\n", (int)!doesHaveBrackets(lExpression),
//        (int)!isJustANumber(lExpression));

// what is actually happening:
// findDeepestBrackets(expression, &start, &end);
// threeWaySplit(expression, left, middle, right, start, end);
// parseAndApplyOperators(middle);
// recombine(expression, left, middle, right);
// findDeepestBrackets(expression, &start, &end);
// unfoldBrackets(expression, start, end);

// -------
// OPERPASS DEBUG:

// nullTheArray(resultGcvt); // maybe not needed
// if (calcResult >= HUGEE * -1 && calcResult <= HUGEE) {
// }
// printf("Multiply:%.19Lg\n", strtold(sprintfResult, NULL));
// //!!!!!!!!!!!
// printf("Divide:%.19Lg\n", strtold(sprintfResult, NULL));
// //!!!!!!!!!!!
// printf("Add:%.19Lg\n", strtold(sprintfResult, NULL));
// //!!!!!!!!!!!
// printf("Subtract:%.19Lg\n", strtold(sprintfResult, NULL));
// //!!!!!!!!!!!
// printf("%Lf,%Lf\n",
//        (long double)getLeftDigits(inputMid, i, &resultStart),
//        (long double)getRightDigits(inputMid, i, &resultEnd));
// //!!!!!!!!!!!
// printf("Power:%.19Lg\n", strtold(sprintfResult, NULL));
//!!!!!!!!!!!
// printf("Mod:%.19Lg\n", strtold(sprintfResult, NULL));
//!!!!!!!!!!!

// printf("\nOPERPASS SPLIT:\n");  //!!!!!!!!!!!
// printf("[%.19Lg]\n", strtold(left, NULL));
// printf("[%s]", middle);
// printf("[%.19Lg]\n", strtold(sprintfResult, NULL));
// printf("[%.19Lg]\n\n", strtold(right, NULL));
// sleep(1);
// printf("{%s}\n", inputStr);

// -------

// printf("\n%i\n", err);
// printf("inputStr: %s\n", inputStr);
// printf("inputStr: %s\n", inputStr);

// printf("\n%i,%i\n", start, end);

// printf(">>[%c]<<\n", leftStr[i - 1]);

// printf("\nL:%s\nM:%s\nE:%s\nT:%s\n", left, middle, right, inputStr);

// printf("<<%s>>\n", left);
// printf("%s\n", tempStr);

// printf("expression:[%s]\n", expression);
// printf("midStr:[%s]\n", midStr);

// printf("<BOT:%.11Lf,MID:%.11Lf,TOP:%.11Lf\n", bot, mid, top);

// printf("Possible answer: %s\n", midStr);

// if (counter % 100000 == 0) printf("%." STR(SPRINTF_PRECISION) "Lf\n",
// mid);

// printf("[%i]", inputStr[i]);

// char toMatch[MAX_STRING_SIZE] = {'0', '1', '2', '3', '4', '5',
//                          '6', '7', '8', '9', '.'};

// printf("%.1Lf<<\n", tempAnswerNum);
// printf("%.1Lf<<\n", expectedAnswer);
// printf("%.1Lf<<\n", vasFabs(tempAnswerNum) - vasFabs(expectedAnswer));

// printf("{%Lf}\n", strtold(finalLeftDigit, NULL));

// printf("POST UNARY:%s\n", expression);
// findOrDelDeepestBrackets(expression, &start, &end, false);
// printf("POS DELETE:%s\n", expression);
// printf("expression:%s\n", expression);
// findOrDelDeepestBrackets(expression, &start, &end, true);
// threeWaySplit(expression, left, middle, right, start, end);

// printf("start:[%i],end:[%i]", start, end);

// case '-':
//   // printf("%Lf\n",
//   //        getLeftDigits(inputStr, i) - getRightDigits(inputStr, i));
//   ourGcvt((getLeftDigits(inputStr, i, &resultStart) -
//            getRightDigits(inputStr, i, &resultEnd)),
//           resultGcvt, 8);
//   printf("Subtract:%s\n", resultGcvt);
//   *calculationHappened = true;
//   break;
// case '+':
//   // printf("%Lf\n",
//   //        getLeftDigits(inputStr, i) + getRightDigits(inputStr, i));
//   ourGcvt((getLeftDigits(inputStr, i, &resultStart) +
//            getRightDigits(inputStr, i, &resultEnd)),
//           resultGcvt, 8);
//   printf("Add:%s\n", resultGcvt);
//   *calculationHappened = true;
//   break;

// if (inputStr[i] == '*') {
//   printf("%Lf\n", getLeftDigits(inputStr, i) * getRightDigits(inputStr,
//   i)); ourGcvt((getLeftDigits(inputStr, i) * getRightDigits(inputStr, i)),
//           tempForGcvt, 8);
//   printf("%s\n", tempForGcvt);
//   calculationHappened = true;
// } else if (inputStr[i] == '/') {
//   printf("%Lf\n", getLeftDigits(inputStr, i) / getRightDigits(inputStr,
//   i)); ourGcvt((getLeftDigits(inputStr, i) / getRightDigits(inputStr, i)),
//           tempForGcvt, 8);
//   printf("%s\n", tempForGcvt);
//   calculationHappened = true;
// } else if (inputStr[i] == '+') {
//   printf("%Lf\n", getLeftDigits(inputStr, i) + getRightDigits(inputStr,
//   i)); ourGcvt((getLeftDigits(inputStr, i) + getRightDigits(inputStr, i)),
//           tempForGcvt, 8);
//   printf("%s\n", tempForGcvt);
//   calculationHappened = true;
// } else if (inputStr[i] == '-') {
//   printf("%Lf\n", getLeftDigits(inputStr, i) - getRightDigits(inputStr,
//   i)); ourGcvt((getLeftDigits(inputStr, i) - getRightDigits(inputStr, i)),
//           tempForGcvt, 8);
//   printf("%s\n", tempForGcvt);
//   calculationHappened = true;
// }

// if (start > -1) {
//   strcpy(left, inputStr);
//   left[start + 1] = '\0';
// } else {
//   left[0] = '\0';
// }
// strcpy(middle, inputStr + start + 1);
// middle[end - start - 1] = '\0';
// strcpy(right, inputStr + end);
// strcpy(inputStr, tempStr);

// int findOrDelDeepestBrackets(char *inputStr, int *startIn, int *endIn,
//                              bool toFind) {  // bool false means to delete
//   int hasError = 0;
//   int i = 0;
//   int start = -69;  // -69 kinda means unitialised, error
//   int end = -69;
//   bool whileBreak = false;
//   while (whileBreak == false) {
//     if (inputStr[i] == '(') {
//       start = i;
//     } else if (inputStr[i] == '\0') {
//       if (start == -69 && end == -69) {
//         hasError = -1;  // no brackets found
//         printf("NO BRACKETS FOUND");
//       } else if (start == -69 || end == -69) {
//         hasError = 1;  // no starting or engding brackets
//         printf("NO STARTING OR ENDING BRACKETS");
//       }
//       whileBreak = true;
//     } else if (inputStr[i] == ')') {
//       end = i;
//       whileBreak = true;
//     }
//     i++;
//   }
//   if (hasError == 0) {
//     if (toFind == true) {  // doing _ acos cos atan tan asin sin etc...
//       *startIn = start;
//       *endIn = end;
//     } else if (toFind == false) {  // deleting brackets instead
//       int oper = checkLeftBracketOper(inputStr, start);
//       if (oper > 0) {
//         char left[MAX_STRING_SIZE] = {0};
//         char middle[MAX_STRING_SIZE] = {0};
//         char right[MAX_STRING_SIZE] = {0};
//         char tempStr[MAX_STRING_SIZE] = {0};
//         threeWaySplit(inputStr, left, middle, right, start, end);
//         if (oper == OPER_MINUS) {
//           if (middle[0] == '~') {  // DELETED PURE MINUS
//             strcpy(tempStr, (char *)middle + 1);
//           } else if (middle[0] != '~') {  // DELETED PURE MINUS
//             strcat(tempStr, "~");
//             strcat(tempStr, middle);
//           }
//           strcpy(middle, tempStr);
//           lrBracketDeletion(left, right);
//           left[strlen(left) - 1] = '\0';
//           recombine(inputStr, left, middle, right);
//         }
//       } else {
//         wholeStrBracketDeletion(inputStr, start, end);
//       }
//     } else {
//       printf("\nDAFAQ\n");
//     }
//   }

//   return hasError;
// }

// long double getLeftDigits(char *inputMid, int operatorPos, int *digitsEnd)
// {
//   char *toMatch = "0123456789~. ";
//   char finalLeftDigit[MAX_STRING_SIZE] = {0};
//   int i = operatorPos - 1;
//   int j = 0;
//   int minusesCount = 0;
//   bool whileBreak = false;
//   if (inputMid[0] == '-') inputMid[0] = '~';  // ugly, but works, dunno why
//   while (whileBreak == false) {
//     if (inputMid[i] == '~') {
//       finalLeftDigit[j] = '-';
//       j++;
//     } else {
//       finalLeftDigit[j] = inputMid[i];
//       j++;
//     }
//     i--;
//     // Break condition:
//     if (i < 0) {
//       whileBreak = true;
//     } else if (inputMid[i] == '\0') {
//       whileBreak = true;
//     } else if (charMatch(toMatch, inputMid[i]) != true) {
//       whileBreak = true;
//     }
//   }
//   if (minusesCount > 1) {
//     printf("A LOT OF MINUSES!");
//   }
//   *digitsEnd = i;
//   reverseString(finalLeftDigit);
//   return strtold(finalLeftDigit, NULL);
// }

// long double getRightDigits(char *inputMid, int operatorPos, int *digitsEnd)
// {
//   char *toMatch = "0123456789~. ";
//   char finalLeftDigit[MAX_STRING_SIZE] = {0};
//   int i = operatorPos + 1;
//   int inputStrLen = strlen(inputMid);
//   int j = 0;
//   int minusesCount = 0;
//   bool whileBreak = false;
//   while (whileBreak == false) {
//     if (inputMid[i] == '~') {
//       finalLeftDigit[j] = '-';
//       j++;
//     } else {
//       finalLeftDigit[j] = inputMid[i];
//       j++;
//     }
//     i++;
//     // Break condition:
//     if (i == inputStrLen) {
//       whileBreak = true;
//     } else if (inputMid[i] == '\0') {
//       whileBreak = true;
//     } else if (charMatch(toMatch, inputMid[i]) != true) {
//       whileBreak = true;
//     }
//   }
//   if (minusesCount > 1) {
//     printf("A LOT OF MINUSES!");
//   }
//   *digitsEnd = i;
//   return strtold(finalLeftDigit, NULL);
// }

// LINEAR SOLVER:
// --------------

// void linearSolver(char *expression, long double expectedAnswer) {
//   long double tempAnswerNum = 0.0L;
//   char tempAnswerStr[MAX_STRING_SIZE] = {0};
//   char localExpression[MAX_STRING_SIZE] = {0};
//   char tempXStr[MAX_STRING_SIZE] = {0};
//   long double tempXNum = TEMPXNUMLINDIA * -1;
//   long counter = 0;
//   do {
//     strcpy(localExpression, expression);
//     tempXNum += 0.01L;
//     sprintfHelper(tempXStr, tempXNum);
//     replaceX(localExpression, tempXStr);
//     // printf("Local expression: %s\n", localExpression);
//     calculate(localExpression, tempAnswerStr);
//     tempAnswerNum = strtold(tempAnswerStr, NULL);
//     counter++;
//     if (counter % 100000 == 0) printf("%.1Lf\n", tempXNum);
//   } while (fabsl(tempAnswerNum - expectedAnswer) > EPS &&
//            tempXNum < TEMPXNUMLINDIA);
//   printf("Possible answer: %s\n", tempXStr);
// }

// ---------------------------------------------------------
// HOMYAK:
// UI.C
// ---------------------------------------------------------

// printf("x:%Lf y:%Lf\n", graphDots[i].x, graphDots[i].y);

// printf("in:%s out:%s\n", tempDoubleInputStr,
// tempGraphOutputStr);
// printf("LF:%Lf\n", (long double)screenWidth / 2);

// printf("xx:%Lf yy:%Lf\n",
//        (float)screenWidth / 2 + (graphDots[i].x * 0.00015),
//        (float)screenHeight / 2 - 30 + (graphDots[i].y * 0.00015));

// ClearBackground(GetColor(GuiGetStyle(DEFAULT, 10)));
// GuiSetFont(font);

// Font font = LoadFontEx("homespun.ttf", 16, 0, 0);

// void drawNinePixelsGrid(Vector2 position, Color color) {
//   position.x = position.x + 0;
//   position.y = position.y + 0;
//   DrawPixelV(position, RED);
//   position.x = position.x + 50;
//   position.y = position.y + 0;
//   DrawPixelV(position, RED);
//   position.x = position.x + -50;
//   position.y = position.y + 0;
//   DrawPixelV(position, RED);
//   position.x = position.x + 0;
//   position.y = position.y + -50;
//   DrawPixelV(position, RED);
//   position.x = position.x + 0;
//   position.y = position.y + 50;
//   DrawPixelV(position, RED);
//   position.x = position.x + 50;
//   position.y = position.y + 50;
//   DrawPixelV(position, RED);
//   position.x = position.x + -50;
//   position.y = position.y + 50;
//   DrawPixelV(position, RED);
//   position.x = position.x + -50;
//   position.y = position.y + -50;
//   DrawPixelV(position, RED);
//   position.x = position.x + 50;
//   position.y = position.y + -50;
//   DrawPixelV(position, RED);
// };

// GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

// #define RAYGUI_CUSTOM_ICONS     // It requires providing gui_icons.h in the
// same directory #include "gui_icons.h"          // External icons data
// provided, it can be generated with rGuiIcons tool

// chekcbox:
// ---------

// // GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
// forceSquaredChecked = GuiCheckBox((Rectangle){25, 108, 15, 15}, "FORCE
// CHECK!",
//                                   forceSquaredChecked);

// 3dshit:
// -------

// verh:

// Camera3D camera = {0};
// camera.position = (Vector3){0.0f, 10.0f, 10.0f};  // Camera position
// camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at
// point camera.up = (Vector3){0.0f, 1.0f,
//                       0.0f};  // Camera up vector (rotation towards target)
// camera.fovy = 45.0f;          // Camera field-of-view Y
// camera.projection = CAMERA_PERSPECTIVE;

// Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

// niz:

// BeginMode3D(camera);
// // if (campos < 10) {
// //   campos += 1.0;
// // } else {
// //   campos -= 10;
// // }
// camera.position = (Vector3){-5.0f, campos, campos};  // Camera position
// SetCameraMode(camera, CAMERA_ORBITAL);
// DrawCube(cubePosition, 8.0f, 4.0f, 4.0f, colorPickerValue);
// DrawCubeWires(
//     cubePosition, 2.0f, 2.0f, 2.0f,
//     CLITERAL(Color){rand() % 10, rand() % 255, rand() % 255, rand() %
//     255});
// EndMode3D();

// 1-2-3 left right:
// --------

// GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
// // GuiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
// if (GuiSpinner((Rectangle){25, 135, 125, 30}, NULL, &spinner001Value, 0,
//                100, spinnerEditMode))
//   spinnerEditMode = !spinnerEditMode;
// if (GuiValueBox((Rectangle){25, 175, 125, 30}, NULL, &valueBox002Value,
// 0,
//                 100, valueBoxEditMode))
//   valueBoxEditMode = !valueBoxEditMode;

// groupbox:
// ---------
// GuiGroupBox((Rectangle){25, 310, 125, 150}, "STATES");
// // GuiLock();
// GuiSetState(STATE_NORMAL);

// Savefile:
// ---------
// GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
// if (GuiButton((Rectangle){25, 255, 125, 30},
//               GuiIconText(ICON_FILE_SAVE, "Save File")))
//   showTextInputBox = true;

// debilnie knopki:
// ----------------

//     GuiSetState(STATE_FOCUSED);
//     if (GuiButton((Rectangle){aboba, aboba, aboba, aboba}, "FOCUSED")) {
//     }
//     GuiSetState(STATE_PRESSED);
//     if (GuiButton((Rectangle){30, 390, 115, 30}, "#15#PRESSED")) {
//     }
//     GuiSetState(STATE_DISABLED);
//     if (GuiButton((Rectangle){30, 425, 115, 30}, "DISABLED")) {
//     }
//     GuiSetState(STATE_NORMAL);
//     // GuiUnlock();

// combo box:
// ----------

// comboBoxActive = GuiComboBox((Rectangle){25, 470, 125, 30},
//                              "ONE;TWO;THREE;FOUR", comboBoxActive);

// dropdown:
// ---------

// NOTE: GuiDropdownBox must draw after any other control that can be
// covered on unfolding
// GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
// if (GuiDropdownBox((Rectangle){25, 65, 125, 30},
//                    "#01#ONE;#02#TWO;#03#THREE;#04#FOUR",
//                    &dropdownBox001Active, dropDown001EditMode))
//   dropDown001EditMode = !dropDown001EditMode;

// GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
// if (GuiDropdownBox((Rectangle){25, 25, 125, 30}, "ONE;TWO;THREE",
//                    &dropdownBox000Active, dropDown000EditMode))
//   dropDown000EditMode = !dropDown000EditMode;

// vsjakaja huina:
// ---------------

// Second GUI column
// listViewActive =
//     GuiListView((Rectangle){165, 25, 140, 140},
//                 "Charmander;Bulbasaur;#18#Squirtel;Pikachu;Eevee;Pidgey",
//                 &listViewScrollIndex, listViewActive);
// listViewExActive = GuiListViewEx((Rectangle){165, 180, 140, 200},
//                                  listViewExList, 8, &listViewExFocus,
//                                  &listViewExScrollIndex,
//                                  listViewExActive);

// toggleGroupActive =
//     GuiToggleGroup((Rectangle){165, 400, 140, 25},
//                    "#1#ONE\n#3#TWO\n#8#THREE\n#23#", toggleGroupActive);

// Third GUI column // NO iT's still the second one
// if (GuiTextBoxMulti((Rectangle){320, 25, 225, 140}, multiTextBoxText, 256,
//                     multiTextBoxEditMode))
//   multiTextBoxEditMode = !multiTextBoxEditMode;

// sliderValue = GuiSlider((Rectangle){355, 400, 165, 20}, "TEST",
//                         TextFormat("%2.2f", (float)sliderValue),
//                         sliderValue, -50, 100);
// sliderBarValue = GuiSliderBar((Rectangle){320, 430, 200, 20}, NULL,
//                               TextFormat("%i", (int)sliderBarValue),
//                               sliderBarValue, 0, 100);
// progressValue = GuiProgressBar((Rectangle){320, 460, 200, 20}, NULL, NULL,
//                                progressValue, 0, 1);
// alphaValue =
//     GuiColorBarAlpha((Rectangle){320, 490, 200, 30}, NULL, alphaValue);

// Color Picker:
// -------------

// colorPickerValue =
//     GuiColorPicker((Rectangle){320, 185, 196, 192}, NULL,
//     colorPickerValue);

// Strange panel info:
// -------------------

// GuiPanel((Rectangle){560, 25 + 180, 100, 160}, "Panel Info");

//  Hui poimi, text file:
//  ---------------------
// if (showTextInputBox) {
//   DrawRectangle(0, 0, screenWidth, screenHeight,
//                 Fade(RAYWHITE, 0.8f));
//   int result = GuiTextInputBox(
//       (Rectangle){(float)screenWidth / 2 - 120,
//                   (float)screenHeight / 2 - 60, 240, 140},
//       "Save", GuiIconText(ICON_FILE_SAVE, "Save file as..."), "Ok;Cancel",
//       textInput, 255, NULL);

//   if (result == 1) {
//     // TODO: Validate textInput value and save

//     strcpy(textInputFileName, textInput);
//   }

//   if ((result == 0) || (result == 1) || (result == 2)) {
//     showTextInputBox = false;
//     strcpy(textInput, "\0");
//   }
// }

//  Hui poimi, text file verh:
//  --------------------------

// if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) showTextInputBox =
// true;

// if (IsFileDropped()) {
//   FilePathList droppedFiles = LoadDroppedFiles();

//   if ((droppedFiles.count > 0) &&
//       IsFileExtension(droppedFiles.paths[0], ".rgs"))
//     GuiLoadStyle(droppedFiles.paths[0]);

//   UnloadDroppedFiles(droppedFiles);  // Clear internal buffers
// }

// vars:
// -----

// int listViewScrollIndex = 0;
// int listViewActive = -1;

// int listViewExScrollIndex = 0;
// int listViewExActive = 2;
// int listViewExFocus = -1;
// const char *listViewExList[8] = {"This", "is",      "a",        "list
// view",
//                                  "with", "disable", "elements",
//                                  "amazing!"};

// char multiTextBoxText[256] = "Multi text box";
// bool multiTextBoxEditMode = false;

// char textInput[256] = {0};
// bool showTextInputBox = false;

// char textInputFileName[256] = {0};

// drop down
//     if (dropDown000EditMode || dropDown001EditMode)
//   GuiLock();
// else if (!dropDown000EditMode && !dropDown001EditMode)
//   GuiUnlock();
//   // GuiDisable();

// bool forceSquaredChecked = false;

// float alphaValue = 0.5f;

// int comboBoxActive = 1;

// int toggleGroupActive = 0;

// double campos = 0.0;

// Vector2 viewScroll = {0, 0};

// int dropdownBox000Active = 0;
// bool dropDown000EditMode = false;

// int dropdownBox001Active = 0;
// bool dropDown001EditMode = false;

// int sliderValue = 50;
// int sliderBarValue = 60;
// float progressValue = 0.4f;

// int spinner001Value = 0;
// bool spinnerEditMode = false;

// int valueBox002Value = 0;
// bool valueBoxEditMode = false;

// if (IsKeyPressed(KEY_SPACE)) PlaySound(fxWav); // gachi space

//  *   TEST CONTROLS:
//  *       - GuiDropdownBox()
//  *       - GuiCheckBox()
//  *       - GuiSpinner()
//  *       - GuiValueBox()
//  *       - GuiTextBox()
//  *       - GuiButton()
//  *       - GuiComboBox()
//  *       - GuiListView()
//  *       - GuiToggleGroup()
//  *       - GuiTextBoxMulti()
//  *       - GuiColorPicker()
//  *       - GuiSlider()
//  *       - GuiSliderBar()
//  *       - GuiProgressBar()
//  *       - GuiColorBarAlpha()
//  *       - GuiScrollPanel()

// moi knopki
//     : -- -- -- -- -- -

// // Calc buttons:
// // -------------
// // TO LOOP:

// if (GuiButton((Rectangle){MARGIN, MARGINPOS, MARGIN, MARGIN}, "+")) {
//   aboba += 10;
//   PlaySound(fxWav);
//   strcpy(inputBoxText, "COLLEGE BOY");
// }
// if (GuiButton((Rectangle){MARGIN, MARGINPOS + MARGIN, MARGIN, MARGIN},
// "-"))
// {
//   aboba += 10;
//   PlaySound(fx2Wav);
//   strcpy(inputBoxText, "COLLEGE BOY");
// }
// if (GuiButton((Rectangle){MARGIN * 2, MARGINPOS, MARGIN, MARGIN}, "*")) {
//   aboba += 10;
//   PlaySound(fx2Wav);
//   strcpy(inputBoxText, "COLLEGE BOY");
// }
// if (GuiButton((Rectangle){MARGIN * 2, MARGINPOS + MARGIN, MARGIN, MARGIN},
//               "/")) {
//   aboba += 10;
//   PlaySound(fxWav);
//   strcpy(inputBoxText, "COLLEGE BOY");
// }
// if (GuiButton((Rectangle){MARGIN * 3, MARGINPOS, MARGIN, MARGIN}, "%")) {
//   aboba += 10;
//   PlaySound(fxWav);
//   strcpy(inputBoxText, "COLLEGE BOY");
// }
// if (GuiButton((Rectangle){MARGIN * 3, MARGINPOS + MARGIN, MARGIN, MARGIN},
//               "pow")) {
//   aboba += 10;
//   PlaySound(fxWav);
//   strcpy(inputBoxText, "COLLEGE BOY");
// }

// OUTPUTBOX:
// --------
// GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
// GuiSetState(STATE_FOCUSED);
// GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
// GuiTextBox(
//     (Rectangle){screenWidth - (screenWidth - 42),
//                 screenHeight - (screenHeight - 50), 996, 38},
//     outputText, 512, false);

//     GuiGrid(
// (Rectangle){screenWidth - (screenWidth - 40),
//             screenHeight - (screenHeight - 90), 1000, 400},
// "aboba", 100, 4);

// prev dimensions:
// ----------------
//     if (GuiTextBox((Rectangle){screenWidth - (screenWidth -
//     42),
//                            screenHeight - 120, 996, 38},
//                inputBoxText, 512, textBoxEditMode)) {
//   textBoxEditMode = !textBoxEditMode;
// }

//     GuiGroupBox((Rectangle){screenWidth - (screenWidth - 38),
//             screenHeight - (screenHeight - 40), 1005,
//             screenHeight - 118},
// "SmartCalc");

//   if (GuiButton((Rectangle){screenWidth - (screenWidth - 42),
//                           screenHeight - 148, 38, 26},
//               "=")) {
//   equalsPressed(inputBoxText, outputText, &justCalculated);
// }