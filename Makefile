OBJS=actions.o ast.o check.o ecc.tab.o errors.o generator.o defgen.o indent.o lex.yy.o main.o
DEPS=globals.h version.h
TEST_MODULES=$(wildcard tests/*.cpp)
TEST_OBJS=$(TEST_MODULES:.cpp=.o)
TEST_TARGETS=ast.o
CXXFLAGS+=--std=c++11 -g 
INC=-I. -I/usr/include/cppunit

ifdef COVERAGE
LIBS += -lgcov
CXXFLAGS += -fprofile-arcs -ftest-coverage -O0 -fno-inline -ggdb
endif

ecc: $(OBJS) $(DEPS)
	g++ $(OBJS) $(CXXFLAGS) $(INC) -o $@

-include $(OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)
-include $(TEST_TARGETS:.o=.d)

test: $(TEST_OBJS) $(TEST_TARGETS)
	g++ $(TEST_OBJS) $(TEST_TARGETS) $(LIBS) $(CXXFLAGS) $(INC) -lcppunit -o $@

coverage: test
	./test
	cd cov; lcov --capture --output-file app.info -b $(CURDIR) --directory $(CURDIR)
	cd cov; lcov --remove app.info "/usr*" -o app.info
	cd cov; lcov --remove app.info "tests*" -o app.info
	cd cov; genhtml app.info
	xdg-open cov/index.html &


ecc.tab.cpp: ecc.y
	bison -d ecc.y -o ecc.tab.cpp
	mv ecc.tab.hpp ecc.tab.h

lex.yy.cpp: ecc.l
	flex -o lex.yy.cpp ecc.l

%.o : %.cpp
	g++ -c $*.cpp $(CXXFLAGS) $(INC) -o $@
	g++ -c $*.cpp -MM $(CXXFLAGS) $(INC) > $*.d

clean:
	rm -f *.o *~ *tab* lex.yy.* a.out ecc *.d tests/*.o test
