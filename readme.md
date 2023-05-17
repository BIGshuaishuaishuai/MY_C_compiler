# MYC compile

参考资料：
* 南京大学编译原理实验文档  
* 学长代码：https://github.com/LittleJohnKhan/SPL-Complier 
* 使用Flex Bison 和LLVM编写自己的编译器  http://www.cppblog.com/woaidongmao/archive/2009/11/11/100693.aspx


## 测试环境
1. Linux version 5.10.16.3-microsoft-standard-WSL2 (oe-user@oe-host) (x86_64-msft-linux-gcc (GCC) 9.3.0, GNU ld (GNU Binutils) 2.34.0.20200220)
2. flex 2.6.4
3. bison (GNU Bison) 3.5.1

## lexer和parser部分

这部分要求通过词法和语法分析，生成抽象语法树AST。

要求通过标准输出打印程序的运行结果。对于那些包含词法或者语法错误的输入文件，只要输出相关的词法或语法有误的信息即可。在这种情况下，注意不要输出任何与语法树有关的内容。要求输出的信息包括错误类型、出错的行号以及说明文字，其格式为：

```shell
Error type [错误类型] at Line [行号]: [说明文字].
```

错误类型包括：A.词法错误    B.语法错误

对于那些没有任何词法或语法错误的输入文件，你的程序需要将构造好的语法树按照先序遍历的方式打印每一个结点的信息，这些信息包括：

pass

选做内容：
1. 识别八进制和十六进制
2. 识别指数形式的浮点数
3. 识别并过滤注释