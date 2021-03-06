# CH6 Functions

## Basics

1. 一个函数的调用（calling a function）做了两件事情：

    - 用实参（Arguments）初始化函数的形参（Parameters）。
    - 主调函数（calling function）的执行被暂时中断，被调函数（called function）开始执行。

2. 当一个函数结束时，使用return语句有两个作用：

    - 返回return语句中的值（如果有的话）
    - 将控制权从被调函数交还给主调函数。

3. 函数的形参列表可以为空

    ```c++
    void f1(){ }
    void f2(void){ }
    ```
4. 局部对象（local objects）

    - 作用域（scope）：一个名字的作用域是程序文本的一部分，名字在其中可见。
    - 生命周期（lifetime）：是程序执行过程中该对象存在的时间。
    - 局部变量（local variable）
    - 自动对象（automatic object）：块执行期间的对象，当块的执行结束后自动对象就被销毁。
    - 局部静态变量（local static object）：这种对象在函数第一次执行经过对象定义语句后被初始化，直到程序终止才销毁。

5. 函数声明和分离式编译

    - 函数声明可以省略形参，但是为了更好理解函数的功能通常会把形参也写上。
    - 函数的三要素（返回类型、函数名和形参）描述了函数的接口，说明了调用了该函数所需的全部信息。
    - 一般在头文件中声明函数，然后在独立的源文件中定义函数，在main.cpp中#include头文件，编译的时候同时编译main.cpp和函数源文件。
    - 这样做的好处是，当我们需要改动函数的时候，我们不需要重新编译main.cpp，而是只需要编译函数源文件即可。
    - 随后，把几个编译单元链接起来即可。

## 参数传递

1. 传值调用和引用调用

    函数参数的传递分为三种，由函数的形参来决定：

    - 传值调用：`fun(int a)`
    - 引用调用：`fun(int &a)`

    两者的差别在于，在传值调用的时候，相当于是在函数的作用域内创建了变量，并把外部的变量拷贝给这个变量（假设外部变量是b，那么执行`int a = b`），因为改变参数不会影响外部的变量。而引用调用则会执行`int &a = b`，这样a只是b的一个别名，而不是一个变量，因此改变它也会影响外部变量。

    值得一提的是有一种特殊形参，叫做

    - 指针形参：`fun(int *a)`

    指针形参实际上是传值调用的一种，但是它比较特殊。首先假设外部变量是 `int *b = &c`，那么在调用函数的时候，实际执行是 `int *a = b`。那么首先，a作为一个指针，它的保存的是一个变量的地址，那么在我们改变a指向别的变量的时候，并不会影响到b指向c。但是我们可以通过a指向c的地址，来改变c的值。因此指针形参实际上是可以改变外部的值的，而且往往会有不可预知的错误。因此C++ Primer建议使用引用类型的形参替代指针。

    我们可以看到，传值调用实际上是对实参的拷贝。而在遇到占用内存比较大的对象，或者有些类根本不支持拷贝操作的时候，我们需要使用引用传值。

    另外引用调用还可以被用来返回多个结果。

2. const形参和实参

- 复习一下const

    如果形参是const时，情况就会变得比较复杂。首先需要了解const在拷贝时，顶层const（top-level const）和底层const（low-level const）规则。这边可以查阅const关键字。

    顶层const（top-level const）指的是，变量本身是const的。底层const（low-level const）一般在指针中会比较常见，指的是指针指向的值不能被修改。比如：

    ```c++
    const int i = 42; // 顶层const，i本身不可变
    const int* const p = &i; //第一个const是底层const，表明这个指针指向的变量不可变，第二个const是顶层const，p这个指针只能指向i而不能被修改成指向别的变量。
    ```

    现在来看看拷贝。在把const变量拷贝给普通变量的过程中，顶层const会被忽略。现在来看例子：

    ```c++
    const int i = 42; // 顶层const，i本身不可变
    int j = i; // ok：顶层const被忽略

    int* const p1 = &j; //顶层const
    *p1 = 1; // ok：通过p1更改j的值是被允许的
    int* p2 = p1; // ok：顶层const被忽略

    //另外，复习一下指针const
    const int* p3 = &j; // ok：底层const，虽然p3把j申明成不可改变，但是实际上j是可以改变的，只是我们不能通过p3来改变j的值。
    ```

- 复习好了const，我们来看一下const参数拷贝调用。

    ```c++
    void fun(const int j){ } // 可以读j，但是不能修改j
    // fun(int j) { } //单独使用没有问题，但是和上面的fun一起就会报错，重复定义

    main(){
        int a = 1;
        const int b = 1;

        fun(a);
        fun(b); // 都是可以的，拷贝的时候顶层const会被忽略
    }
    ```

    上面的代码定义了两个`fun()`，一个是const拷贝传参，一个是普通的拷贝传参。`main   ()`中定义了一个a为普通`int`变量，b为`const int`变量。调用`fun(a)`和`fun(b) `都没有问题。

    唯一的问题是两个`fun()`不能同时定义，否则会报错。因为顶层const被忽略的机制，我  们无法区分出我们传递参数时具体想要选择哪一个函数，因此就出现了重复定义的错误。

- 再来看一下const指针或引用调用

    通过上上节const复习，我们知道底层const变量可以通过普通变量来定义，但是反过来不行。也就是说，一个指针/引用可以申明它所指向的变量是不变的，但是这个被指向的变量不需要是不变的。但是反过来，一个普通指针/引用不能指向/引用const变量。

    这样就为我们函数的引用/指针调用提供了便利。举一个例子，我们需要通过引用调用来节省函数的内存开销，但是我们又不希望在函数中意外地改变这个变量的值。因此我们可以这么写：

    ```c++
    string i = "abc";
    const string j = "def";

    void fun(const string &a) { }

    fun(i);
    fun(j);
    ```

    这样，字符串`i`被传入`fun()`中作为`a`正常使用，但是我们不能在`fun()`中改变`a`的值。const字符串`j`被传入`fun()`中作为`a`正常使用，在外部和函数内部都不能改变`j`的值。

- 我们需要尽可能地使用const引用

    如果你是这样定义你的函数的：

    ```c++
    void fun1(string &a) { fun2(a) }
    void fun2(const string &a) { }
    ```

    那么根据引用和常量引用的规则，会出现一些问题：
        
        [1] `const string`类型的变量将无法被传入fun1。
        [2] `const string &`类型的别名也无法被传入fun2。
        [3] 类似于`fun1("abc")`这样的调用也无法实现，因为不能把字面值（literal）赋值给一个别名。
        [4] 对于嵌套函数，如fun1中嵌套了fun2,那么a是不能被传入fun2的。

- 数组Array形参

    array比较特殊，因为不允许`=`复制，我们通常是传指向array第一个地址的指针给函数，或者使用引用。

    最好可以定义成这样：

    ```c++
    void fun(const int[10]) { }
    ```

    在调用的时候，`fun()`只检查传进来的参数是否是`const int*`。

    ```c++
    int i = 0, j[2] = {0, 1};

    fun(&i); // ok：&i是int*
    fun(j); // ok：j会被当作是指向j[0]的指针
    ```

    当然，使用标准库的函数的定义方法也是可以的。类似于`sort(a.begin(), a.end())`。

- `main`函数如何处理命令行选项

    ```c++
    int main(int argc, char **argv[]) { ... }
    ```
    `argv`指向`char*`，是一个数组，数组里面是一系列指针指向一系列字符串。第一个整数`argc`代表了`argv`的长度。

    比如

    ```shell
    prog -d -o ofile data0
    ```

    那么

    ```c++
    argc = 5;
    
    argv[0] = "prog"; //argv[0]也可能指向空字符串
    argv[1] = "-d";
    argv[2] = "-o";
    argv[3] = "ofile";
    argv[4] = "data0";
    argv[5] = 0;
    ```

- 多个参数传递（不固定个数）

    一种方法是使用STL的`initializer_list<T>`模板类。

## 返回类型和return语句

    - 无返回值的函数
    - 有反回值的函数
