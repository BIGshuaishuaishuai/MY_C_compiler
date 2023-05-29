#include <iostream>
#include "CodeTran.hpp"


using namespace std;

extern int yyparse();
extern node::Root* root;

int main(int argc, char **argv)
{
    std::cout << "[main starts]"<< std::endl;
    yyparse(); 
    std::cout<<"[paerser done]"<<std::endl;

    CodeContext codecontext;
    codecontext.CreateContext(root);
    // context.runCode();
    
    return 0;
}