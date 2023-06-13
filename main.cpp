#include <iostream>
#include "CodeTran.hpp"


using namespace std;

extern int yyparse();
extern node::Root* root;
extern FILE *yyin;
extern int yyparse(void);
int main(int argc, char **argv)
{
    std::cout << string("[") + string(argv[1])+string(" starts]")<< std::endl;
    
    yyin = fopen(argv[1],"r");
    if (yyin){
        std::cout<<"[Parser starts]"<<std::endl;
        yyparse(); 
    }

    std::cout<<"[paerser done]"<<std::endl;

    CodeContext codecontext;
    codecontext.CreateContext(root);
    // context.runCode();
    verifyModule(*(codecontext.module));
    
    return 0;
}