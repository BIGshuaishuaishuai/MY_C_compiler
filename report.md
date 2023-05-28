<div class="cover" style="page-break-after:always;font-family:方正公文仿宋;width:100%;height:100%;border:none;margin: 0 auto;text-align:center;">
    <div style="width:60%;margin: 0 auto;height:0;padding-bottom:10%;">
        </br></br></br></br></br></br>
        <img src="https://gitee.com/Keldos-Li/picture/raw/master/img/%E6%A0%A1%E5%90%8D-%E9%BB%91%E8%89%B2.svg" alt="校名" style="width:70%;"/>
    </div>
    </br></br></br>
    </br></br></br></br></br></br></br>
    <span style="font-family:华文黑体Bold;text-align:center;font-size:16pt;margin: 10pt auto;line-height:30pt;">本科实验报告</span>
    </br>
</br></br></br>
    <table style="border:none;text-align:center;width:72%;font-family:仿宋;font-size:14px; margin: 0 auto;">
    <tbody style="font-family:方正公文仿宋;font-size:12pt;">
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">课程名称</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 编译原理</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">姓　　名</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">郑昊伦 朱靖彦 李天烨</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">学　　院</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">计算机科学与技术学院</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">专　　业</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">计算机科学与技术</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">学　　号</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">3200102570 3200104165 </td>     </tr>
      <tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">指导教师</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;text-align:center;font-family:华文仿宋">冯雁</td>     </tr>
    </tbody>              
    </table>
</br></br>
			<span style="font-family:华文黑体Bold;text-align:center;font-size:12pt;margin: 10pt auto;line-height:30pt;">2023 年 5 月 28 日</span>
</div>

# 浙江大学操作系统实验报告

项目名称：MY C Compiler

## 一、实验基本信息

### 实验要求
实现某语言的编译器；用Lex开发该语言的词法分析器，用YACC开发该语言的语法分析，并生成语法树和中间代码，最终生成目标代码（ARM或RISC-V）。语言可以是类C或者类PASCAL或者某个自定义语言，词法和语法要自己定义。

### 实验环境
* Linux 
* GCC
* Bison 
* Flex 
* llvm

### 成员分工

朱靖彦：

郑昊伦：

李天烨：

## 二、实验效果

本次实验我们实现了一个类C编译器，支持了以下功能：
* 函数的声明以及调用
* 变量的定义
* C语言基本语句，包括`for, if-else, while, switch-case`等等
* 基本的算术运算和逻辑运算，运算类型详见词法分析
* 数组和指针的使用
* 编译器忽略注释

## 三、词法分析

词法分析部分利用lex(flex)完成。lex是一个用于生成词法分析器的工具。它可以将输入的正则表达式转换为一个有限状态机，然后再根据这个有限状态机生成对应的词法分析器程序。

lex的基本语法如下，用`%%`来分割三个部分：

```lex
definition
%%
rules
%%
user's code
```

lex提供了一些用于辅助解析词法的变量和函数，常用的有：
*  yylineno    行号
*  yytext      当前的token
*  yyleng      当前token的长度
*  yylex       整个lexer的函数
*  yylval      用于保存token的值

在本次实验中，我们定义如下的规则来解析词法，lex将根据下面的正则表达式自动生成DFA进行解析，其中包含的运算和关键词与C语言的词法一致。部分token含有语义值，通过yylval进行传递。`definition`和`user's code`部分较为简单，基本没有内容，这里不详细展开了。

```lex
"("     { return LP; }
")"     { return RP; }
"{"     { return LC; }
"}"     { return RC; }
"["     { return LB; }
"]"     { return RB; }
"+"     { return PLUS; }
"-"     { return SUB; }
"*"     { return MULT; }
"/"     { return DIV; }
"%"     { return MOD; }
"<<"    { return SHL; }
">>"    { return SHR; }
"<"     { return LT; }
"=="    { return EQ; }
">"     { return GT; }
">="    { return GE; }
"<="    { return LE; }
"!="    { return NE; }
"="     { return EQU; }
"+="	{ return ADDEQ; }
"-="	{ return SUBEQ; }
"*="	{ return MULEQ; }
"/="	{ return DIVEQ; }
"%="	{ return MODEQ; }
"<<="   { return SHLEQ; }
">>="   { return SHREQ; }
"!"     { return NOT; }
"~"     { return BNOT; }
"&&"    { return AND; }
"&"     { return BAND; }
"||"    { return OR; }
"|"     { return BOR; }
"return"    { return RETURN; }
"if"        { return IF; }
"else"      { return ELSE; }
"do"        { return DO; }
"while"     { return WHILE; }
"for"       { return FOR; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"switch"	{ return SWITCH; }
"case"		{ return CASE; }
"default"	{ return DEFAULT; }
"ptr"       { return PTR; }
"array"     { return ARRAY; }
","     { return COMMA; }
";"     { return SEMI; }
":"     { return COLON; }
" " | \t | \n { ; }
"//".*  { ; }       // 这里可以忽略注释
"int"|"char"|"float"|"void" { yylval.type = new std::string(yytext, yyleng); return TYPE; }
[0-9]+                      { yylval.ival = atoi(yytext); return INT; } 
[A-Za-z_][0-9A-Za-z_]*      { yylval.sval = new std::string(yytext, yyleng); return ID; }
[0-9]+\.[0-9]+              { yylval.fval = atof(yytext); return FLOAT; }
\'.\'                       { yylval.cval = yytext[1]; return CHAR; }
.       { printf("Lex Error at Line %d: Illegal lex %s.\n", yylineno, yytext); }
```

其中有关变量类型的定义，我们用含有语义值的token(TYPE)表示一个变量类型的token，并将其语义值以string的形式传递到parser阶段具体分析其类型。

## 四、语法分析及抽象语法树的构建

## 五、语义分析

## 六、代码生成和代码优化

## 七、测试