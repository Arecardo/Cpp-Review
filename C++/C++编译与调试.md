# C++ 编译与调试

参考：

- [编程语言(C/C++)](https://github.com/linw7/Skill-Tree/blob/master/%E7%BC%96%E7%A8%8B%E8%AF%AD%E8%A8%80C%2B%2B.md#other)

## C++ 源码（Source Code）->机器码（Machine Code）

综合来讲，一个C++程序从源码被编译成能被机器读懂的机器码，需要经历以下几个步骤：

1. 预处理（Preprocessor）

    - 展开所有的宏定义，完成字符常量替换。

    - 处理条件编译语句，通过是否具有某个宏来决定过滤掉哪些代码。

    - 处理#include指令，将被包含的文件插入到该指令所在位置。

    - 过滤掉所有注释语句。

    - 添加行号和文件名标识。

    - 保留所有#pragma编译器指令。

2. 编译（Complier）

    - 词法分析。

    - 语法分析。

    - 语义分析。

    - 中间语言生成。

    - 目标代码生成与优化。

    这一步结束后会生成.obj文件（一个或多个translation units）

3. 链接（Linker）

4. 装载（Loader）

