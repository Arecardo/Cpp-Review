# C++ STL 标准模板库基础整理

STL内容虽然看起来很多，单独成书都不是问题（《STL源码剖析》），但从实际使用状况来看，我认为只需要知道以下几点就可以了：

- 怎么用？

    各种STL基本的增删改查怎么使用。每种容器都提供了很多操作，但实际增删改查我们通常只需要掌握透彻一种方式即可。有些功能只是出于通用性考虑才存在的，但对于相应的STL这些操作完全可以忽略。所以我对STL使用的看法是，不需要花太多时间去了解所有功能，只要掌握最基本的即可，要把精力放在对需求的了解并选择适合的数据结构。

- 怎么实现？

    本身STL就是封装了我们常用的数据结构，所以最先需要了解每种数据结构的特性。而且了解实现方式对我们能够准确、高效使用STL打下了基础。

- 如何避免错误？

    在第二阶段了解了STL的实现之后，我们已经可以很清楚地知道他们底层使用的是什么数据结构以及该数据结构做什么操作比较高效。但还有一点需要注意的就是怎么才能用对他们，避免一些未知的错误，比如迭代器失效问题。

- STL六大部件：

    - 容器（Container）：[cppreference](https://zh.cppreference.com/w/cpp/container)
    - 分配器（Allocators）
    - 算法（Algorithms）：[cppreference](https://zh.cppreference.com/w/cpp/algorithm)
    - 迭代器（Iterators）
    - 适配器（Adapters）
    - 仿函数（Functors）

- 常用的容器

    - 顺序容器 - 顺序容器实现能按顺序访问的数据结构。
        - **array**：静态的连续数组
        - **vector**：动态的连续数组（string本质上是以字符作为元素的vector特化版本；不存在0字符结尾这个概念，能装入'\0'这种数据。）
        - **list**：双向链表
        - **forward_list**：单链表
        - **deque**：双端队列

    - 容器适配器 - 容器适配器提供顺序容器的不同接口。（底层一般用list或deque实现）
        - **stack**：栈（LIFO 数据结构）
        - **queue**：队列（FIFO 数据结构）
        - **priority_queue**：默认最大堆

    - 关联容器 - 关联容器实现能快速查找（ O(log n) 复杂度）的数据结构。（底层数据结构为红黑树），有序
        - **set**：唯一键的集合，按照键排序
        - **map**：键值对的集合，按照键排序，键是唯一的
        - multiset
        - multimap

    - 无序关联容器 - 无序关联容器提供能快速查找（均摊 O(1) ，最坏情况 O(n) 的复杂度）的无序（哈希）数据结构。
        - **unordered_set**：唯一键的集合，按照键生成散列
        - unordered_multiset
        - **unordered_map**：键值对的集合，按照键生成散列，键是唯一的
        - unordered_multimap

**string**

**vector**

用法：

        定义：
            vector<T> vec;

        插入元素：
            vec.push_back(element);
            vec.insert(iterator, element);

        删除元素：
            vec.pop_back();
            vec.erase(iterator);

        修改元素：
            vec[position] = element;

        遍历容器：
            for(auto it = vec.begin(); it != vec.end(); ++it) {......}

        其他：
            vec.empty();    //判断是否空
            vec.size();    // 实际元素
            vec.capacity();    // 容器容量
            vec.begin();    // 获得首迭代器
            vec.end();    // 获得尾迭代器
            vec.clear();    // 清空

实现：

[模拟Vector实现](https://github.com/linw7/Skill-Tree/blob/master/code/my_vector.cpp)

- 线性表，数组实现。
    - 支持随机访问。
    
    - 插入删除操作需要大量移动数据。

- 需要连续的物理存储空间。

- 每当大小不够时，重新分配内存（*2），并复制原内容。

错误避免：

[迭代器失效](https://github.com/linw7/Skill-Tree/blob/master/code/vector_iterator.cpp)

- 插入元素
    - 尾后插入：size < capacity时，首迭代器不失效尾迭代实现（未重新分配空间），size == capacity时，所有迭代器均失效（需要重新分配空间）。
    
    - 中间插入：size < capacity时，首迭代器不失效但插入元素之后所有迭代器失效，size == capacity时，所有迭代器均失效。

- 删除元素
    - 尾后删除：只有尾迭代失效。
    
    - 中间删除：删除位置之后所有迭代失效。

**map**

用法：

        定义：
            map<T_key, T_value> mymap;

        插入元素：
            mymap.insert(pair<T_key, T_value>(key, value));    // 同key不插入
            mymap.insert(map<T_key, T_value>::value_type(key, value));    // 同key不插入
            mymap[key] = value;    // 同key覆盖

        删除元素：
            mymap.erase(key);    // 按值删
            mymap.erase(iterator);    // 按迭代器删

        修改元素：
            mymap[key] = new_value;

        遍历容器：
              for(auto it = mymap.begin(); it != mymap.end(); ++it) {
                cout << it->first << " => " << it->second << '\n';
              }

实现：

[RBTree实现](https://github.com/linw7/Skill-Tree/tree/master/code/RBTree)

- 树状结构，RBTree实现。
    - 插入删除不需要数据复制。
    
    - 操作复杂度仅跟树高有关。

- RBTree本身也是二叉排序树的一种，key值有序，且唯一。
    - 必须保证key可排序。

基于红黑树实现的map结构（实际上是map, set, multimap，multiset底层均是红黑树），不仅增删数据时不需要移动数据，其所有操作都可以在O(logn)时间范围内完成。另外，基于红黑树的map在通过迭代器遍历时，得到的是key按序排列后的结果，这点特性在很多操作中非常方便。

面试时候现场写红黑树代码的概率几乎为0，但是红黑树一些基本概念还是需要掌握的。

1. 它是二叉排序树（继承二叉排序树特显）：
    - 若左子树不空，则左子树上所有结点的值均小于或等于它的根结点的值。

    - 若右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值。

    - 左、右子树也分别为二叉排序树。

2. 它满足如下几点要求：
    - 树中所有节点非红即黑。

    - 根节点必为黑节点。

    - 红节点的子节点必为黑（黑节点子节点可为黑）。

    - 从根到NULL的任何路径上黑结点数相同。

3. 查找时间一定可以控制在O(logn)。

4. 红黑树的节点定义如下：
    ```C++
    enum Color {
        RED = 0,
        BLACK = 1
    };
    struct RBTreeNode {
        struct RBTreeNode*left, *right, *parent;
        int key;
        int data;
        Color color;
    };
    ```
所以对红黑树的操作需要满足两点：1.满足二叉排序树的要求；2.满足红黑树自身要求。通常在找到节点通过和根节点比较找到插入位置之后，还需要结合红黑树自身限制条件对子树进行左旋和右旋。

相比于AVL树，红黑树平衡性要稍微差一些，不过创建红黑树时所需的旋转操作也会少很多。相比于最简单的BST，BST最差情况下查找的时间复杂度会上升至O(n)，而红黑树最坏情况下查找效率依旧是O(logn)。所以说红黑树之所以能够在STL及Linux内核中被广泛应用就是因为其折中了两种方案，既减少了树高，又减少了建树时旋转的次数。

从红黑树的定义来看，红黑树从根到NULL的每条路径拥有相同的黑节点数（假设为n），所以最短的路径长度为n（全为黑节点情况）。因为红节点不能连续出现，所以路径最长的情况就是插入最多的红色节点，在黑节点数一致的情况下，最可观的情况就是黑红黑红排列......最长路径不会大于2n，这里路径长就是树高。


**set**
