all: parser

parser: parser.cpp CodeTran.cpp main.cpp lexer.cpp
	g++ -o $@ `llvm-config-14 --libs core native --cxxflags --ldflags` *.cpp

parser.hpp: parser.cpp

lexer.cpp: lexer.l
	lex -o $@ $^

parser.cpp: parser.y
	bison -d -o $@ $^

clean:
	rm parser.cpp parser.hpp parser tokens.cpp