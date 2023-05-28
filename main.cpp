#include <iostream>
#include "CodeTran.hpp"
#include "node.hpp"

using namespace std;

extern int yyparse();
extern Root* root;

int main(int argc, char **argv)
{
    yyparse();
    std::cout << root << std::endl;

    CodeContext context;
    context.generateCode(*root);
    context.runCode();
    
    return 0;
}