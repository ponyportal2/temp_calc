UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
	SYSFLAG=-D LINUX
	BUILD=./build/
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	LEAK=CK_FORK=no leaks -quiet -atExit --
	SYSFLAG=-D APPLE
	BUILD=./build/
endif

CFLAGS=-Wall -Werror -Wextra
GFLAGS=-fprofile-arcs -ftest-coverage
SOURCES= ./my_libs/*.c view.c controller.c logic_model.c
HEADERS= ./my_libs/*.h view.h controller.h logic_model.h
SOURCESGCOVNOTESTCHECK = ./my_libs/*.c controller.c logic_model.c
SOURCESGCOV= ./my_libs/*.c controller.c logic_model.c test_check.c
HEADERSGCOV= ./my_libs/*.h controller.h logic_model.h
MEME_ON=-DCALC_MEME
MEME_OFF=
# -----------------

all: styleforce build

build: clean ${SOURCES} ${HEADERS}
	# -mv c.wav c.doc
	-mv c.doc c.wav 
	g++ libraylib_big_sur.a ${SOURCES} -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags` -o SmartCalc ${MEME_OFF} -DMAC -DGUI_TEXTBOX_EXTENDED_IMPLEMENTATION
	-mkdir ../build/
	mv SmartCalc ../build/SmartCalc
	-cp a.wav c.doc c.wav dark.rgs readme.html a.jpg ../build/

buildwin: clean
	-mv c.wav c.doc
	g++ ./my_libs/*.c ui.c s21_the_calc.c libraylib_wingw64_12_2_0.a -lwinmm -lopengl32 -lgdi32 -std=c99 -o SmartCalc.exe -DWIN -DGUI_TEXTBOX_EXTENDED_IMPLEMENTATION
	-mkdir ../build/
	mv SmartCalc.exe ../build/SmartCalc.exe
	-cp a.wav c.doc c.wav dark.rgs readme.html a.jpg ../build/

rebuild: clean all

clean: styleforce
	rm -rf *.gc* *.log *.out *.out.dSYM *.input *.output *.dSYM *.tgz
	rm -rf SmartCalc test_check test_check.c s21_the_calc.a report log.xml
	rm -rf *.o *.test .test.c *.gcda *.gcno *.info *.exe ../build/

# install: build // BACKUP
# 	@mkdir -p /Users/$(shell whoami)/VasSmartCalc
# 	@cp -r ../build/ /Users/$(shell whoami)/VasSmartCalc
# 	@cp -r /Users/$(shell whoami)/VasSmartCalc/VasSmartCalc.app ~/Desktop/
# 	rm -rf *.cfg *.out *.tgz *.o *.a *.gcda *.gcno *.info report ../build/ *build

install: build
	-@mkdir -p ~/Desktop/VasSmartCalc/
	-@cp -r ../build/* ~/Desktop/VasSmartCalc/
	rm -rf *.cfg *.out *.exe *.tgz *.o *.gcda *.gcno *.info report ../build/ *build s21_the_calc.a
	~/Desktop/VasSmartCalc/SmartCalc

installwin: uninstallwin buildwin
	-@mkdir -p 'C:/VasSmartCalc'
	-@cp -r ../build/* 'C:/VasSmartCalc'
	rm -rf *.cfg *.out *.exe *.tgz *.o *.gcda *.gcno *.info report ../build/ *build s21_the_calc.a

uninstall:
	@rm -rf ~/Desktop/VasSmartCalc/

uninstallwin:
	@rm -rf 'C:/VasSmartCalc'

dist: clean
	-tar -czf "SmartCalcDist.tgz" *.c *.h *.a *.rgs *.py *.cfg *.doc *.wav *.jpg *.check Makefile readme.html ./my_libs/*.c ./my_libs/*.h ./extras/*.h ./extras/*.jpg ./icons/*.h ./icons/*.png ./icons/*.rgi

dvi:
	open readme.html

test: clean ${SOURCESGCOVNOTESTCHECK} ${HEADERSGCOV}
	checkmk clean_mode=1 calcTest.check > test_check.c
	gcc $(SYSFLAG) ${SOURCESGCOV} $(LFLAGS) $(GFLAGS) -g -o test_check
	./test_check

gcov_report:
	checkmk clean_mode=1 calcTest.check > test_check.c
	gcc $(SYSFLAG) ${SOURCESGCOV} $(LFLAGS) $(GFLAGS) -g -o test_check
	./test_check > test.log
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

style:
	clang-format -n -style=Google ${SOURCES}

styleforce:
	clang-format -i -style=Google ${SOURCES}

# -----------------

uitest: build
	../build/SmartCalc

uitestwin: buildwin
	../build/SmartCalc.exe

# -----------------

# mytest: s21_the_calc.a
# 	gcc $(SYSFLAG) $(CFLAGS) s21_the_calc.c ./my_libs/*.c mytest.c $(LFLAGS) -g
# 	# -cppcheck ${SOURCES}
# 	-clang-format -i -style=Google ${SOURCES}
# 	# -python3 cpplint.py --extensions=c ${SOURCES}
# 	./a.out

# mytestleak: s21_the_calc.a
# 	gcc $(SYSFLAG) $(CFLAGS) s21_the_calc.a mytest.c $(LFLAGS) -g
# 	-cppcheck ${SOURCES}
# 	-clang-format -i -style=Google ${SOURCES}
# 	-python3 cpplint.py --extensions=c ${SOURCES}
# 	-leaks -quiet -atExit -- ./a.out > test.log
# 	grep -e "0 total leaked bytes" -e "nodes malloced" -e "leaks Report Version" -v test.log

meme:
	-mv c.doc c.wav
	g++ ./my_libs/*.c ui.c s21_the_calc.c libraylib.a -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags` -o SmartCalc -DMEME -DMAC -DGUI_TEXTBOX_EXTENDED_IMPLEMENTATION
	./SmartCalc

# s21_the_calc.a: clean
# 	gcc $(SYSFLAG) $(CFLAGS) -c s21_the_calc.c ./my_libs/*.c
# 	ar rc s21_the_calc.a *.o
# 	ranlib s21_the_calc.a
# 	rm -f *.o
