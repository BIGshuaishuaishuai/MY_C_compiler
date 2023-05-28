#include <string>
#include <map>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/PassManager.h>
#include <llvm/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/ModuleProvider.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

class node;

class CodeBlock{
public:
    BasicBlock *codeblock;
    CodeBlock *prev;
    CodeBlock *next;
    std::map<std::string, Value*> local_vars;
};

// This class is a list of the CodeBlocks
class CodeContext{
private:
    CodeBlock* head_block;
    CodeBlock* tail_block;
    Function* mainfunction;
public:
    Module *module;
    CodeContext(): module(Module("main")) {}
    void CreateContext(node* root);
    GenericValue RunCode();
    CodeBlock* HeadBlock(){return head_block;}
    CodeBlock* TailBlock(){return tail_block;}
    std::map<std::string , Value*>& localvars() { return tail_block->local_vars; }
    void InsBlock(CodeBlock* new_block){
        new_block->prev = tail_block;
        new_block->next = NULL;
        tail_block->next = new_block;
        tail_block = new_block;
    }
    void RmHeadBlock(){
        if (head_block != NULL){
            tmp = head_block;
            head_block = head_block->next;
            free(tmp);
        }
        else{
            printf("No head! The Context is empty");
            exit(1)
        }
    }
    void RmTailBlock(){
        if (tail_block != NULL){
            tmp = tail_block;
            tail_block = head_block->prev;
            free(tmp);
        }
        else{
            printf("No tail! The Context is empty");
            exit(1)
        }
    }
      
};