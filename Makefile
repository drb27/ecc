OBJS=actions.o ast.o check.o ecc.tab.o errors.o generator.o defgen.o indent.o lex.yy.o main.o warning.o
DEPS=globals.h version.h
CXXFLAGS+=--std=c++11 -g

ecc: $(OBJS) $(DEPS)
	g++ $(OBJS) $(CXXFLAGS) -o ecc

-include $(OBJS:.o=.d)

ecc.tab.cpp: ecc.y
	bison -d ecc.y -o ecc.tab.cpp
	mv ecc.tab.hpp ecc.tab.h

lex.yy.cpp: ecc.l
	flex -o lex.yy.cpp ecc.l

%.o : %.cpp
	g++ -c $*.cpp $(CXXFLAGS)
	g++ -c $*.cpp -MM $(XCCFLAGS) > $*.d

clean:
	rm -f *.o *~ *tab* lex.yy.* a.out ecc *.d
