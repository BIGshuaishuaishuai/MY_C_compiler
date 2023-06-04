# MYC compile

## 使用环境
该项目实现了一个简单的类`C`语言编译器，使用`flex,bison和llvm`完成编写，并使用`clang`进行最后可执行文件的编译，并将必要的`llvm`等组件封装到了`d1msh1mm32/ccompiler:1.0`的`docker`镜像中，所以只需要安装好·，使用 `docker`拉取该镜像，使用`make`工具编译，即可生成可执行文件`parser`:

```shell
$ docker pull d1msh1mm32/ccompiler
$ docker run -idt --name compiler_env d1msh1mm32/ccompiler:1.0 
# cd MY_C_compiler
# make 
# parser test_0.c
```

即可生成`test_0.c`编译生成的`llvm`机器码
## 文件结构

```shell
.
|-- CodeTran.cpp
|-- CodeTran.hpp
|-- CodeTran.o
|-- Makefile
|-- lexer.cpp
|-- lexer.l
|-- lexer.o
|-- main.cpp
|-- node.hpp
|-- parser
|-- parser.cpp
|-- parser.hpp
|-- parser.o
|-- parser.y
|-- readme.md
|-- report.md
|-- test_0.c
`-- test_1.c
```