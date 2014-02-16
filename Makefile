OBJS=actions.o ast.o check.o ecc.tab.o errors.o generator.o defgen.o indent.o lex.yy.o main.o
DEPS=globals.h version.h
CXXFLAGS+=--std=c++11 -g

ecc: $(OBJS) $(DEPS)
	g++ $(OBJS) $(CXXFLAGS) -o ecc

ecc.tab.c: ecc.y
	bison -d ecc.y

lex.yy.c: ecc.l
	flex ecc.l

lex.yy.o: lex.yy.c 
	g++ -c lex.yy.c -o lex.yy.o $(CXXFLAGS)

ecc.tab.o: ecc.tab.c ecc.tab.h
	g++ -c ecc.tab.c -o ecc.tab.o $(CXXFLAGS)

clean:
	rm -f *.o *~ *tab* lex.yy.* a.out ecc
