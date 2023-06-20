# MYC compile

## 使用环境
该项目实现了一个简单的类`C`语言编译器，使用`flex,bison和llvm`完成编写，并使用`clang`进行最后可执行文件的编译。

* OS：Linux
* flex
* bison
* llvm：10.0.0.1
* clang

配置环境有两种方法：

1. 直接手动安装所有的依赖项
2. 我们将必要的`llvm`等组件封装到了`d1msh1mm32/ccompiler:1.0`的`docker`镜像中，所以只需要安装好·，使用 `docker`拉取该镜像。详细方法可以查看`docker/readme.md`文件

## 编译方法

1. 进入`src`文件夹，使用`make`工具编译，即可生成可执行文件`parser`
2. 运行可执行文件`parser`。通过`./parser xx.c`编译`.c`文件，生成文件`example.bc`，该文件为二进制文件，可以通过llvm的命令执行。同时，命令行中会打印出对应的llvm IR代码，以供参阅。
3. 输入`lli example.bc`即可运行二进制文件`example.bc`
4. 为了查看其输出，可以使用`echo $?`

## 文件结构

```shell
.
├── MY_C Compiler.pptx
├── docker
│   ├── MY_C_compiler.tar.gz
│   ├── dockerfile
│   └── readme.md
├── readme.md
├── report.md
├── src
│   ├── CodeTran.cpp
│   ├── CodeTran.hpp
│   ├── Makefile
│   ├── example.bc
│   ├── lex_test
│   │   ├── lex_test
│   │   ├── lex_test.cpp
│   │   ├── test
│   │   ├── test.txt
│   │   └── testl.l
│   ├── lexer.l
│   ├── main.cpp
│   ├── node.hpp
│   ├── parser.y
│   ├── test_0.c
│   ├── test_1.c
│   ├── test_2.c
│   └── test_3.c
└── tmp.md
```