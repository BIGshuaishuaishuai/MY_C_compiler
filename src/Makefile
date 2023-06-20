all: parser

parser: parser.cpp CodeTran.cpp main.cpp lexer.cpp
	clang++ -o parser `llvm-config --cxxflags --ldflags --system-libs --libs all` -w -lffi -lLLVM *.cpp

parser.hpp: parser.cpp

lexer.cpp: lexer.l
	lex -o $@ $^

parser.cpp: parser.y
	bison -d -o $@ $^

clean:
	rm parser.cpp parser.hpp parser lexer.cpp *.o 