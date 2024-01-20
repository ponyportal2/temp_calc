# -----------------
CFLAGS=-Wall -Werror -Wextra -Wno-narrowing
CFLAGSLITE=
GCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest
SOURCES=controller.cc view.cc logic_model.cc vaslib.cc
HEADERS=controller.h view.h logic_model.h vaslib.h
SOURCESLITE=controller.cc logic_model.cc vaslib.cc
HEADERSLITE=controller.h logic_model.h vaslib.h
MEME_ON=-DCALC_MEME
MEME_OFF=
OUTPUT_ON=-DCALC_WITH_OUTPUT
OUTPUT_OFF=
REPORTDIR=./gcovreport/
# -----------------
all: styleforce build

push: clean styleforce
	git add .
	git commit -m "next"
	git push origin develop

build: clean ${SOURCES} ${HEADERS}
	g++ ${CFLAGSLITE} libraylib_big_sur.a ${SOURCES} -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags` -o SmartCalc ${OUTPUT_OFF} ${MEME_OFF} -DMAC -DGUI_TEXTBOX_EXTENDED_IMPLEMENTATION
	-mkdir ../build/
	mv SmartCalc ../build/SmartCalc
	-cp a.wav c.wav readme.html a.jpg ../build/

output: clean ${SOURCES} ${HEADERS}
	g++ -Wall -Wextra libraylib_big_sur.a ${SOURCES} -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags` -o SmartCalc ${OUTPUT_ON} ${MEME_OFF} -DMAC -DGUI_TEXTBOX_EXTENDED_IMPLEMENTATION
	-mkdir ../build/
	mv SmartCalc ../build/SmartCalc
	-cp a.wav c.wav readme.html a.jpg ../build/

meme: clean ${SOURCES} ${HEADERS}
	g++ -Wall -Wextra libraylib_big_sur.a ${SOURCES} -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags` -o SmartCalc ${OUTPUT_OFF} ${MEME_ON} -DMAC -DGUI_TEXTBOX_EXTENDED_IMPLEMENTATION
	-mkdir ../build/
	mv SmartCalc ../build/SmartCalc
	-cp a.wav c.wav readme.html a.jpg ../build/
	
test: clean $(SOURCESLITE) ${HEADERSLITE} test_main.cc
	g++ $(CFLAGSLITE) $(SOURCESLITE) ${OUTPUT_OFF} test_main.cc $(GTESTFLAGS) -o the_test
	./the_test

gcov_report: clean $(SOURCESLITE) ${HEADERSLITE} test_main.cc
	gcc --coverage ${SOURCESLITE} test_main.cc -o gcov_report -lgtest -lstdc++
	./gcov_report
	gcovr -r . --html --html-details -o ./report/index.html
	open ./report/index.html

rebuild: clean all

clean: styleforce
	rm -rf *.gc* *.log *.out *.out.dSYM *.input *.output *.dSYM *.tgz
	rm -rf SmartCalc test_check test_check.c s21_the_calc.a log.xml
	rm -rf *.o *.test .test.c *.gcda *.gcno *.info *.exe ../build/
	rm -rf gcov_report

install: build
	-@mkdir -p ~/Desktop/VasSmartCalc/
	-@cp -r ../build/* ~/Desktop/VasSmartCalc/
	rm -rf *.cfg *.out *.exe *.tgz *.o *.gcda *.gcno *.info report ../build/ *build s21_the_calc.a
	~/Desktop/VasSmartCalc/SmartCalc

uninstall:
	@rm -rf ~/Desktop/VasSmartCalc/

dist: clean
	-tar -czf "VasSmartCalc.tgz" *

dvi:
	open readme.html

style:
	clang-format -n -style=Google ${SOURCES} ${HEADERS}

styleforce:
	clang-format -i -style=Google ${SOURCES} ${HEADERS}

# -----------------

uitest: build
	../build/SmartCalc

memetest: meme
	../build/SmartCalc

outputtest: output
	../build/SmartCalc