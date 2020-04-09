# Interview Review
准备面试的时候看面经做题目什么的，积累的面试题。

资料：
- [面试知识点总结](http://harlon.org/2018/07/23/interview/#jump11)
- [后台开发核心知识](https://github.com/linw7/Skill-Tree)


## C/C++

### C++内存管理

#### C++内存分布

参考： [Harlon's Blog: C/C++内存布局策略详解](http://harlon.org/2018/04/21/cpluscplusmemory/)

C 中的内存布局： ![pic](pics/c-memory.png)

一个C++程序可以分为（自上往下）:
- **栈**
- **堆**：堆又分为new分配的存储区和malloc分配的内存块，new分配的存储区会在程序结束之后，系统会帮助我们清理；
- **全局/静态存储区**：在C++中，不再区分数据段和BSS段，未初始化和初始化的全局/静态变量都会存储在这里，并且初始化为0；
- **常量存储区**
- **代码段**

#### 栈内存和堆内存的区别，优缺点
堆：
> 堆是动态内存分配区，向高地址增长，堆中分配内存和释放内存需要调用malloc/new或free/delete。

栈：
> 栈和堆一般相邻，但沿着相反方向增长。当栈指针和堆指针相等就说明堆栈内存耗尽。栈中保存的是局部变量和每次函数调用时的信息。每次函数调用返回地址，一些调用者环境信息（比如寄存器）都被存放在栈中。然后新调用的函数就会在栈中为他们的自动或者临时变量分配内存空间，这就是C中递归函数调用的过程。每次递归函数调用自己，新的堆栈就会被创建，这样新的变量集合就不会被其他函数实例的变量集合影响了。

#### 堆内存：malloc和new，free和delete
- `malloc`和`free`是标准库函数，支持覆盖；`new`和`delete`是运算符，并且支持重载；
- `malloc`仅仅分配内存空间，`free`仅仅回收内存空间，不具备调用构造函数和析构函数的功能，用`malloc`函数分配存储类的对象存在风险；`new`的`delete`除了分配回收功能外，还能调用构造函数和析构函数。
- `malloc`返回的是`void`类型的指针，必须进行类型转换，而`new`和`delete`返回的是具体类型指针。

### 基础

#### NULL与nullptr
#### 深浅拷贝
#### static和const

### 函数

#### inline，inline函数和普通函数、宏定义，和virtual能一起使用吗

### 面向对象 OOP

#### 多态的理解
#### 虚函数
#### 析构函数为什么要是虚函数

### STL
### C++ 11 新特性

## Data Structure and Algorithm

### 高级结构
#### 红黑树的特点和优点

## Operating System
## Linux System Programming
## Linux Kernel
## Network
## Design Pattern
## System Design
## Distributed System
## Version Control
