all: parser

parser: parser.cpp CodeTran.cpp main.cpp lexer.cpp
	g++ -o $@ `llvm-config --libs core jit native --cxxflags --ldflags` *.cpp

lexer.cpp: lexer.l parser.hpp
	lex -o $@ $^

parser.hpp: parser.cpp

parser.cpp: parser.y
	bison -d -o $@ $^
    
	
clean:
	rm parser.cpp parser.hpp parser tokens.cpp