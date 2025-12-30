# make c++ easier about our projects
## why create this git?
* **A:** **Dont** do the same things any more

## Everybody can use this lib， how to use it？
```markdown
you must add all header file in `include directory` and `src/xxx/*.hpp`  
you also need link the `xxx.lib/xxx.so` which you will use
**Wait a mimute !!!! 🚀🚀🚀🚀🚀🚀🚀🚀** 
some parts(e.g. `src/yaml_parser/parse_yaml.hpp`) of libs need 3rd lib like `OpenCV`, you should write your own `CMakeLists.txt` and add them first.
```

## `##` in Macro
```markdown
1. 令牌拼接运算符 `##`
- 语法：`A##B` → 预处理器会把两个令牌（标识符）拼接为一个新的标识符；
- 示例：`s_##name + name=log_dir → 生成 s_log_dir；FLAGS_##name → 生成 FLAGS_log_dir`；
- 核心作用：为每个参数生成唯一的变量名，避免冲突。
2. 字符串化运算符 `#`
- 语法：`#A` → 预处理器会把标识符 A 直接转为字符串常量 `"A"`；
- 示例：`#name + name=log_dir` → 生成 `"log_dir"`；
- 核心作用：把参数名转为命令行可识别的字符串。
```

## write in the last
<!-- > 通过这个项目的编写，我学习了编译器的预处理和链接器的链接的功能。  
> 举个例子：
> 当第三个人使用我的库的时候，他们只需要安装相关的第三方库，将我的头文件和库链接上就可以使用。  
> 这其中的原理是编译好的库中存有一个`符号引用表`，由于`#include`的作用只是文本替换，所以库中没有你在编写时的相对头文件路径信息，而头文件只是提供给编译器用来提供声明使用的，具体链接时用来到库的`符号引用表`中进行查找对应的实现。如果没有对应实现则会提示`undifined reference`的链接错误。 -->
```markdown
通过这个项目的编写，我深入理解了编译器预处理阶段的文本替换特性，以及链接器的符号解析与绑定机制。  
举个例子：  
当第三方开发者使用我编译好的库时，只需先安装项目依赖的第三方库（如 OpenCV），再将我的头文件目录加入编译路径、链接我的库文件，即可正常调用接口。这一过程的核心原理是：  
* `预处理阶段:` `#include` 的本质是纯文本替换，仅将头文件内容嵌入当前源码，因此编译生成的库文件中不会保留编写时的头文件相对路径信息；
* `编译阶段:` 头文件的作用是向编译器提供函数 / 类的声明（如 `Jimn_Jhn::parse_yaml()` 的接口定义），确保调用代码的语法和类型匹配，让编译过程顺利完成；
* `链接阶段:` 编译好的库文件中包含「符号表」（存储 “符号名→二进制实现地址” 的键值对），链接器会根据头文件声明的符号名，到库的符号表中查找对应的实现地址并完成绑定。
若符号表中无匹配的实现（如漏链接依赖库、符号名不匹配），则会抛出 `undefined reference`（未定义引用）链接错误。
```