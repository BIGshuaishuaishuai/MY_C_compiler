#ifndef __CODETRAN_HPP__
#define __CODETRAN_HPP__
#include <string>
#include <map>
#include <stack>
#include "node.hpp"
#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Verifier.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

using namespace llvm;
// using namespace node;

static LLVMContext Context;

class CodeBlock{
public:
    BasicBlock *codeblock;
    CodeBlock *prev;
    CodeBlock *next;
    std::map<std::string, Value*> local_vars;
    CodeBlock() : codeblock(NULL),prev(NULL),next(NULL){}
};

// This class is a list of the CodeBlocks
class CodeContext{
private:
    CodeBlock* head_block;
    CodeBlock* tail_block;
    Function* mainfunction;

public:
    Module *module;
    IRBuilder<> builder;
    std::map<std::string, Value*> global_vars;
    std::map<std::string, CodeBlock*> func_table;
    std::map<std::string, Value*>& cur_vars;

    int opnums;
    int fors;
    int blocks;
    CodeContext(): module(new Module("main",Context)),head_block(NULL),tail_block(NULL),mainfunction(NULL),builder(IRBuilder<>(Context)),cur_vars(global_vars),opnums(0),fors(0),blocks(0) {}
    void CreateContext(node::Root* root);
    GenericValue runCode();
    CodeBlock* HeadBlock(){return head_block;}
    CodeBlock* TailBlock(){return tail_block;}
    std::map<std::string , Value*>& localvars() { return cur_vars; }
    void InsBlock(CodeBlock* new_block){
        if (head_block == NULL){
            head_block = new_block;
            tail_block = new_block;
        }
        else {
            new_block->prev = tail_block;
            new_block->next = NULL;
            tail_block->next = new_block;
            tail_block = new_block;
        }
    }
    void RmHeadBlock(){
        if (head_block != NULL){
            auto tmp = head_block;
            head_block = head_block->next;
            if (tmp != NULL)free(tmp);
        }
        else{
            printf("No head! The Context is empty");
            exit(1);
        }
    }
    void RmTailBlock(){
        if (tail_block != NULL){
            auto tmp = tail_block;
            auto prev = tail_block->prev;
            if (prev == NULL) head_block = NULL;
            else prev->next = tmp->next;
            tail_block = prev;
            if (tmp != NULL)free(tmp);
        }
        else{
            printf("No tail! The Context is empty");
            exit(1);
        }
    }
      
};

#endif