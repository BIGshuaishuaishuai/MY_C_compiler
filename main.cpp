#include <iostream>
#include "CodeTran.hpp"
#include "node.hpp"

using namespace std;

extern int yyparse();
extern NBlock* programBlock;

int main(int argc, char **argv)
{
    yyparse();
    std::cout << programBlock << std::endl;

    CodeGenContext context;
    context.generateCode(*programBlock);
    context.runCode();
    
    return 0;
}