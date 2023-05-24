%prec是Bison中的一个指令，用于指定优先级和结合性。它可以用来解决文法中存在二义性的问题。

当存在多个产生式可以匹配同一个输入时，Bison会使用“最长前缀匹配”规则来选择产生式。如果仍然存在歧义，可以使用%prec指令来指定优先级和结合性。

%prec指令的语法如下：

```
%token TOKEN_NAME
%left TOKEN_NAME
%right TOKEN_NAME
%nonassoc TOKEN_NAME
%prec TOKEN_NAME
```

其中，%left、%right和%nonassoc用于指定运算符的结合性，%prec用于指定优先级。

在Bison中，%prec指令可以用于产生式右侧的终结符或非终结符。例如：

```
expr: expr '+' expr %prec ADD_PREC
     | expr '-' expr
     | term
     ;

term: term '*' term %prec MUL_PREC
     | term '/' term
     | factor
     ;

factor: '(' expr ')'
      | NUMBER
      ;
```

在上面的例子中，%prec指令用于指定加法和乘法的优先级。ADD_PREC和MUL_PREC是自定义的优先级名称。

如果不使用%prec指令，Bison会使用默认的优先级和结合性规则。默认情况下，所有左结合的运算符具有相同的优先级，所有右结合的运算符具有相同的优先级，所有非结合运算符具有相同的优先级。

以下是一些关于%prec的链接：

- https://www.gnu.org/software/bison/manual/html_node/Precedence.html
- https://www.ibm.com/docs/en/zos/2.4.0?topic=direct-use-prec-directive-clarify-ambiguities
- https://www.cs.utah.edu/~zachary/isp/tutorials/bison/bison_7.html



bksy.zju.edu.cn 
9.10 推免整体节点
19级的竞赛变动
计算机学院推荐免试研究生工作实施办法
