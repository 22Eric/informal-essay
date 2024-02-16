## 7.类

### 7.1定义抽象数据类型

#### 7.1.2

- 定义成员函数
- 引入this
- 引入const成员函数
- 类作用域和成员函数
- 在类外部定义的成员函数
- 定义一个返回this对象的函数

#### 7.1.4构造函数

- 合成的默认构造函数

  当类没有显示定义构造函数时，编译器会定义一个默认构造函数，我们称之为合成的默认构造函数。

  如果类包含有内置类型或者复合类型的成员，则只有当这些成员函数都被赋予类内的初始值时，这个类才适合于使用合成的默认构造函数。

  我们可以使用= default 来要求编译器生成构造函数。

  ```c++
  Sales_data() = default;
  ```

- 构造函数的初始化列表

  如果不能使用类内的初始值，则所有构造函数都应该显示地初始化每个内置类型的成员。

### 7.2访问控制与封装

出于统一编程风格的考虑，我们希望定义的类的所有成员是public时，使用struct；反之则使用class。

#### 7.2.1友元

类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元(friend)。

一般来说我们会在类开始或结束的位置集中声明友元。友元的声明仅仅指定了访问的权限，而非一个通常意义上的函数声明。如果我们希望类的用户能够调用某个友元函数，那么**我们就必须在友元声明之外再专门对函数进行一次声明**。

### 7.3类的其他特性

#### 7.3.1类成员再探

1. 定义一个类型成员

2. 令成员作为内联函数

3. 重载成员函数

4. 可变数据成员

   作用：可以在定义为const的函数里面修改可变数据成员

   用法：在成员变量前面加mutable关键字

   限制：可变数据成员永远不能是const

5. 类数据成员的初始值

   ```c++
   class Window_Mgr{
   private:
   	vectot<Screen> screens{Screen(24,80,'')};
   
   };
   ```

#### 7.3.2返回*this的成员函数

this是指针，(*this)代表了这个类

**函数的返回类型是引用，则函数返回的是对象本身。返回值则是这个对象的别名。**

1. 从const成员函数返回*this

   一个const成员函数如果以引用的形式返回*this，那么它的返回类型将是一个常量引用。

2. 基于const的重载

   **函数可以基于其是否为const进行重载**

#### 7.3.3类类型

每个类定义了唯一的类型。即使两个类的成员列表完全一致，它们也是不同的类型。

#### 7.3.4友元再探

1. 类之间的友元关系

   如果一个类指定了友元类，那么**友元的成员函数可以访问此类包括非公有成员在内的所有成员。**

   **友元关系不存在传递性。**

2. 令成员函数作为友元

   可以令一个类的成员函数作为另一个类的友元。如此做，我们必须指出该成员函数来自哪个类。

3. 函数重载和友元

   尽管重载函数的名字相同，但仍然是两个不同的函数。分别声明为友元才能分别使用。

4. 友元声明和作用域

   **友元声明仅仅只改变访问权限，不是一个真正的声明，对作用域无影响。**

### 7.5构造函数再探

#### 7.5.1构造函数的初始值列表

如果一个构造函数为所有的参数都提供了默认实参，则它实际意义上也定义了默认构造函数。

#### 7.5.2委托构造函数

构造函数可以委托其他的构造函数完成构造。我们称之为委托构造函数。委托构造函数通过函数初始值列表构建。

#### 7.5.3默认构造函数的作用

在实际中，如果定义了其他构造函数，那么最好也提供一个默认构造函数

#### 7.5.4隐式的类类型转换

- 如果**构造函数只接收一个实参**，则它实际上定义了转换为此类类型的隐式转换机制。**我们把这种构造函数称作转换构造函数**

- **编译器只会自动隐式执行一步类型转换**，如果隐式的使用了两种转换规则，则会报错。

- **在构造函数声明为explicit加以阻止隐式转换**。当我们用explicit关键字声明构造函数时，它将只能以直接初始化的形式使用。而且，编译器将不会在自动转换过程中使用该构造函数。

#### 7.5.5聚合类

- 聚合类的特征：所有成员都是public（一般用struct定义聚合类）,没有定义任何构造函数，没有类内初始值，没有基类没有虚函数。

- 特殊的初始化语法形式：

  ```C++
  //vail.ival = 0,vail.s = string("Anna");  //一般写法
  Data vail = {'0',"Anna"};                 //特殊写法
  ```

### 7.6类的静态成员

- 声明静态成员

  通过在成员的声明之前加上关键字static。静态成员函数不能声明成const，也不能在static函数体内使用this指针。

- 使用类的静态成员

- 定义静态成员函数

  和一般成员函数一样，我们在类内部声明静态成员函数，在类外部定义静态成员函数。但当在类外部定义静态成员函数时，不能重复static关键字。**只在声明处使用static关键字**。

- 静态成员的类内初始化

  即使一个常量静态数据成员在类内部被初始化了，通常情况下也应该在类的外部定义一下该成员。如果在类内部提供了一个初始值，则成员定义不能再指定一个初始值了。

  ```c++
  //类内部
  static constexpr int period = 30;
  
  //类外部
  constexpr int Account::period;
  ```

- 静态成员能用于某些场景，而普通成员不行

  当一个类声明之后，我们只知道这个类是存在的，但具体实现未知。**对于这个类在声明之后定义之前是一个不完全类型。**

  静态成员对象可以是不完全类型。

  指针成员对象可以是不完全类型。

  普通对象不能是不完全类型。

------

## 8.C++标准库

### 8.1IO类

基本IO类型：iostream，fstream，sstream

#### 8.1.1IO对象无拷贝赋值

我们不能拷贝或者对IO对象赋值。因此我们也不能将形参和返回类型设置为流类型。进行IO操作的函数通常以引用的方式传递和返回流。

#### 8.1.2条件状态

IO操作一个与生俱来的问题是可能发生错误。IO类定义了一些函数和标志来帮助我们访问和操作流的条件状态。

|   strm::iostate   | strm是一种IO类型（例如iostream）iostate是一种机器相关的类型，提供了表达条件状态的完整功能 |
| :---------------: | :----------------------------------------------------------: |
|    strm:badbit    |                       用来指出流已崩溃                       |
|   strm:failbit    |                   用来指出一个IO操作失败了                   |
|    strm:eofbit    |                   用来指出流达到了文件结束                   |
|   strm:goodbit    |            用来指出流未处于错误状态。此值保证为零            |
|      s.eof()      |                若流s的eofbit置位，则返回true                 |
|     s.fail()      |           若流s的filebit或者badbit置位，则返回true           |
|      s.bad()      |                若流s的badbit置位，则返回true                 |
|     s.good()      |                若流s处于有效状态，则返回true                 |
|     s.clear()     |   将流s中所有条件状态复位，将流的状态设置为有效，返回void    |
|  s.clear(flags)   | 根据给定的flags标志位，将流s对应条件状态复位。flags的类型为strm::iostate，返回void |
|    s.rdstate()    |        返回流s当前条件状态，返回值类型为strm::iostate        |
| s.setstate(flags) | 根据给定的flags标志位，将流s对应条件状态置位。flags的类型为strm::iostate，返回void |

确定一个流对象的状态的最简单的方法是将它作为一个条件来使用。

- 查询流的状态
- 管理条件状态

```c++
auto old_state = cin.rdstate();    //记住cin的状态
cin.clear();                       //使cin有效
process_input(cin);				   //使用cin
cin.setstate(old_state);           //将cin置为原有状态


//复位fialbit和badbit，保持其他标志位不变
cin.clear(cin.rdstate() & ~cin.failbit & ~cinbadbit);
```

#### 8.1.3管理输出缓冲

**每个输出流都管理一个缓冲区，用来保存程序读写的数据**。有了缓冲机制，操作系统就可以将程序的多个输出操作组合为单一的设备写操作可以带来很大的性能提升。

- 刷新输出缓冲区

  ```c++
  cout << "hi!" << endl;     //输出hi和一个换行，然后刷新输出缓冲区
  cout << "hi!" << ends;     //输出hi和一个空字符，然后刷新输出缓冲区
  cout << "hi!" << flush;     //输出hi，然后刷新输出缓冲区
  ```

- unitbuf操纵符

  如果想在每次输出操作后都刷新缓冲区，我们可以使用unitbuf操纵符。它告诉流在接下来的每次写操作之后都进行一次flush操作。而nounitbuf操纵符则重置流，使其恢复使用正常的系统管理的缓冲刷新机制。

  ```c++
  cout << unitbuf;       //所有输出操作后都会立即刷新缓冲区
  //他们中间的任何输出都立即刷新，无缓冲
  cout << nounitbuf;    //回到正常的缓冲方式
  ```

- 关联输入和输出流

  当输入流和输出流被关联起来时，任何从输入流读取数据的操作都会先刷新关联的输出流。标准库将cin和cout关联。这意味着在在读取之前一定会先存放。**交互式系统通常应关联输入流和输出流**。

  ```c++
  cin.tie(&cout);      //举例说明怎样关联，实际上已经关联
  cin.tie(nullptr);    //举例说明怎样取消关联
  ```


### 8.2文件输入和输出

头文件fstream定义了三个类型来支持文件IO：ifstream从一个给定文件读取数据，ofstream向一个给定文件写入数据，以及fstream可以读写给定文件。在17.5.3中，将介绍如何对同一个文件流既读又写。

|      fstream fstrm;      | 创建一个未绑定的文件流。fstream是头文件fstream中定义的一个类型 |
| :----------------------: | :----------------------------------------------------------: |
|    fstream fstrm(s);     | 创建一个fstream，并打开名为s的文件。s可以是string类型，或者是一个指向C风格字符串的指针。这些构造函数都是explicit的。默认文件模式mode依赖于fstream的类型 |
| fstream fstream(s,mode); |         与前一个构造函数类似，但按照指定mode打开文件         |
|      fstrm.open(s)       | 打开名为s的文件，并将文件与fstrm绑定。s可以是一个string或一个指向C风格字符串的指针。默认的文件mode依赖于fstream的类型。返回void。 |
|     fstream.close()      |               关闭与fstrm绑定的文件。返回void                |
|     fstrm.is_open()      | 返回一个bool值，指出与fstrm关联的文件是否成功打开且尚未关闭  |

#### 8.2.1使用文件流对象

创建文件流对象时，我们可以提供文件名（可选）。如果提供了一个文件名，则open会自动被调用。

```c++
ifstream in(file);       //构造一个ifstream并打开给定文件
ofstream out;			 //输出文件流未关联到任何文件
```

- 用fstream代替iostream&

  **在要求使用基类对象的地方，我们可以用继承类型的对象来代替。**所以，我们可以用fstream代替iostream&。

- 成员函数open和close

- 自动构造和析构

  当一个fstream对象被销毁时，close会自动被调用。

#### 8.2.2文件模式

每个流都有一个关联的文件模式，用来指出如何使用文件。

|   in   |       以只读的方式打开       |
| :----: | :--------------------------: |
|  out   |        以写的方式打开        |
|  app   | 每次写操作前均定位到文件末尾 |
|  ate   |      打开文件后立即定位      |
| trunc  |           截断文件           |
| binary |     以二进制的方式进行IO     |

- 以out模式打开文件会丢弃已有数据

  保留被ofstream打开的文件中已有数据的唯一方法是显示指定app或in模式

- 每次调用open时都会确定文件模式

```c++
ofstream out;                         //未指定文件打开模式
out.open("scratchpad");               //模式隐含设置为输和截断
out.close();                          //关闭out,以便我们将其使用于其他文件
out.open("precious",ofstream::app);   //模式设置为输出和追加
out.close();
```

在每次打开文件时，都要设置文件模式，可能时显示地设置，也可能是隐式的设置。当程序未指定模式时，就使用默认值。

### 8.3string流

sstream头文件定义了三个类型来支持内存IO，ostringstream可以向string写入数据，istringstream从string读取数据，stringstream既可以从string读数据也可以向string写数据，就像string是一个IO流一样。

|  sstream strm;   | strm是一个未绑定的stringstream对象。sstream是头文件sstream中定义的一个类型 |
| :--------------: | :----------------------------------------------------------: |
| sstream strm(s); | strm是一个sstream对象，保存string s的一个拷贝。此构造函数是explicit的。 |
|    strm.str()    |                 返回strm所保存的string的拷贝                 |
|   strm.str(s)    |               将string s拷贝到strm中。返回void               |

#### 8.3.1使用istringstream

当我们的某些工作是对某行文本进行处理，而一些其他工作是处理行内的单个单词时，通常可以使用istringstream

#### 8.3.2使用ostringstream

当我们逐步构造输出，希望最后一起打印时，ostringstream是很有用的。

------

## 9.顺序容器

### 9.1顺序容器概述

|    vector    | 可变大小的数组。支持快速随机访问。在尾部之外的位置插入或删除元素可能很慢 |
| :----------: | :----------------------------------------------------------: |
|    deque     |   双端队列。支持快速随机访问。在头尾位置插入/删除速度很快    |
|     list     | 双向链表。只支持双向顺序访问。在list中任何位置进行插入/删除操作速度都很快 |
| forward_list | 单向链表。只支持单向顺序访问。在链表的任何位置进行插入/删除操作速度都很快 |
|    array     |      固定大小数组。支持快速随机访问。不能添加或删除元素      |
|    string    | 与vector相似的容器，但专门用于保存字符。随机访问快。在尾部插入/删除速度快 |

通常，使用vector是最好的选择，除非有很好的理由选择其他容器。

forward_list的设计目标是达到与最好的手写单向链表数据结构相当的性能。因此forward_list没有size操作。

### 9.2容器库概览

在本节中介绍的操作是对所有容器都适用。

|        类型别名        |                                                             |
| :--------------------: | :---------------------------------------------------------: |
|        iterator        |                   此容器类型的迭代器类型                    |
|     const_iterator     |          可以读取元素，但不能修改元素的迭代器类型           |
|       size_type        |   无符号整数类型，足够保证此种容器类型最大可能容器的大小    |
|    difference_type     |        带符号整数类型，足够存储两个迭代器之间的距离         |
|       value_type       |                          元素类型                           |
|       reference        |            元素的左值类型；与value_type&含义相同            |
|    const_reference     |        元素的const左值类型（即，const value_type&）         |
|      **构造函数**      |                                                             |
|          C c;          |                  默认构造函数，构造空容器                   |
|       C c1(c2);        |                       构造c2的拷贝c1                        |
|       C c(b,e);        | 构造c，将迭代器b和e指定的范围内的元素拷贝到c（array不支持） |
|     C c{a,b,c...};     |                       **列表初始化c**                       |
|     **赋值与swap**     |                                                             |
|        c1 = c2;        |                将c1中的元素替换为c2中的元素                 |
|    c1 = {a,b,c...};    |        将c1中的元素替换为列表中元素（不适用于array）        |
|       a.swap(b);       |                       交换a和b的元素                        |
|       swap(a,b);       |                交换a和b的元素（与上式等价）                 |
|        **大小**        |                                                             |
|        c.size()        |              c中元素的数目(不支持forward_list)              |
|      c.max_size()      |                    c可保存的最大元素数目                    |
|       c.empty()        |          若c中存储了元素，返回false，否则返回true           |
|   **添加/删除元素**    |       不适用于array，在不同容器中这些操作的接口都不同       |
|     c.insert(args)     |                    将args中的元素拷贝进c                    |
|    c.emplace(inits)    |                 使用inits构造一个c中的元素                  |
|     c.erase(args)      |                     删除args指定的元素                      |
|       c.clear()        |                  删除c中所有元素，返回void                  |
|     **关系运算符**     |                                                             |
|         ==，!=         |              所有容器都支持相等（不等）运算符               |
|       <,<=,>,>=        |              关系运算符（无序关联容器不支持）               |
|     **获取迭代器**     |                                                             |
|   c.begin(),c.end()    |           返回指向c的首元素和尾后元素位置的迭代器           |
|  c.cbegin(),c.cend()   |                     返回const_iterator                      |
|   反向容器的额外成员   |                     不支持forward_list                      |
|    reverse_iterator    |                   按逆序寻址元素的迭代器                    |
| const_reverse_iterator |                  不能修改元素的逆序迭代器                   |
|  c.rbegin(),c.rend()   |          返回指向c的尾元素和首元素之前位置的迭代器          |
| c.crbegin(),c.crend()  |                 返回const_reverse_iterator                  |

#### 9.2.1迭代器

- 迭代器范围

  迭代器的范围概念是标准库的基础

- 使用**左闭合范围**蕴含的编程假定

  假定begin()和end()构成一个合法的迭代器范围，则

  1. 如果begin和end相等，则范围为空
  2. 如果begin和end不等，则范围至少包含一个元素，并且begin指向第一个元素
  3. 我们可以对begin递增若干次，使得begin==end

#### 9.2.2容器类型成员

#### 9.2.3begin和end成员

当不需要写访问时，应使用cbegin()和cend()。

#### 9.2.4容器定义和初始化

- 将一个容器初始化为另一个容器的拷贝

  有两种方法：1.直接拷贝整个容器；2.拷贝一个迭代器指定的元素范围

  当一个容器初始化为另一个容器的拷贝时，两个容器类型和元素类型都必须相同。

- 列表初始化

- 与顺序容器大小相关的构造函数（array除外）

  ```c++
  vector<int> a(10,-1);    //10个int元素，每个都是-1
  ```

  关联容器不支持这样构造。

- 标准库array具有固定的大小

  ```c++
  array<int,42>;    //类型为：保存42个int的数组
  ```

#### 9.2.5赋值和swap

| seq.assign(b,e) | 将seq中的元素替换为迭代器b和e所指向范围的元素 |
| :-------------: | :-------------------------------------------: |
| seq.assign(il)  |    将seq中的元素替换为初始化列表il中的元素    |
| seq.assign(n,t) |       将seq中的元素替换为n个值为t的元素       |

由于其旧元素被替换，因此传递给assign的迭代器不能指向调用assign的容器。

除array外，swap不对任何元素进行拷贝、删除或者插入操作，因此可以保证在常数时间内完成。**除string外，指向容器的迭代器。引用和指针在swap操作之后都不会失效**。统一使用非成员版本的swap是一个好习惯。

#### 9.2.6容器大小操作

#### 9.2.7关系运算符

每个容器类型都支持相等运算符（==和!=）；除了无序关联容器外的所有容器都支持关系运算符（>,>=,<,<=）。

只有当其元素类型也定义了相应的比较运算符时，我们才可以使用关系运算符来比较两个容器。

### 9.3顺序容器操作

#### 9.3.1向顺序容器添加元素

|    c.push_back(t)    |            在c的尾部创建一个值为t的元素。返回void            |
| :------------------: | :----------------------------------------------------------: |
| c.emplace_back(args) |        在c的尾部创建一个由args创建的元素。返回void。         |
|   c.push_front(t)    |            在c的头部创建一个值为t的元素。返回void            |
| c.emplace_back(args) |        在c的头部创建一个由args创建的元素。返回void。         |
|    c.insert(p,t)     | 在迭代器p指向的元素之前创建一个值为t的元素。返回指向新添加元素的迭代器。 |
|  c.emplace(p,args)   | 在迭代器p指向的元素之前创建一个由args创建的元素。返回指向新添加元素的迭代器。 |
|   c.insert(p,n,t)    | 在迭代器p指向的元素之前创建n个值为t的元素。返回指向新添加的第一个元素的迭代器。若n为0，则返回p |
|   c.insert(p,b,e)    | 将迭代器b和e指定的范围内的元素插入到迭代器p指向的元素之前。b和e不能指向c中元素。返回指向新添加的第一个元素的迭代器。若范围为空，则返回p |
|    c.insert(p,il)    | il是一个花括号包围的元素值列表。将这些给定值插入到迭代器p指向的元素之前。返回指向新田间的第一个元素的迭代器。若列表为空，则返回p |

**向一个vector，string，deque插入元素会使所有指向容器的迭代器、引用和指针失效。**

- 使用push_back

  除了array和forward_list之外，每个顺序容器（包括string）都支持push_back.

  **当我们将一个对象插入到容器时，我们插入的是这个对象的拷贝而不是这个元素本身**

- 使用push_front

  list、forward_list和deque容器支持push_front操作。

  注意deque提供了随机访问元素的能力，但它提供了vector没有的push_front。

  ps:forward_list支持push_front不支持push_back。是否说明forward_list是一个反向的单链表。

- 在容器的特定位置添加元素

  将元素插入到vector、deque和string中的任何位置都是合法的。然而，这可能很耗时。

- 插入范围内的元素

- 使用insert的返回值

  通过使用insert的返回值，可以在容器的一个特定位置反复插入元素。

- 使用emplace操作

  emplace函数在容器中直接构造函数。而push_back和insert是将已有对象的拷贝插入容器中。

  传递给emplace函数的参数必须与元素类型的构造函数相匹配。

#### 9.3.2访问元素

**at和下标操作只适用于string、vector、deque、array。**

| c.back()  |         返回c中尾元素的引用。若c为空，函数行为未定义         |
| :-------: | :----------------------------------------------------------: |
| c.front() |         返回c中首元素的引用。若c为空，函数行为未定义         |
|   c[n]    | 返回c中下标为n的元素的引用，n是一个无符号整数。若n>c.size()，则函数行为未定义 |
|  c.at(n)  | 返回下标为n的元素的引用。如果下标越界，则抛出out_of_range异常 |

对一个空容器调用back和front，就像使用一个越界的下标一样，是一个严重的程序设计错误。

- 访问成员函数返回的是引用
- 下标操作和安全的随机访问

#### 9.3.3删除元素

**这些操作会改变容器大小，所以不适用于array。**

| c.pop_back()  |    删除c中尾元素。若c为空，则函数行为未定义。函数返回void    |
| :-----------: | :----------------------------------------------------------: |
| c.pop_front() |    删除c中首元素。若c为空，则函数行为未定义。函数返回void    |
|  c.erase(p)   | 删除迭代器p所指定的元素，返回一个指向被删元素之后元素的迭代器，若p指向尾元素，则返回尾后元素迭代器。若p是尾后迭代器，则函数行为未定义 |
| c.erase(b,e)  | 删除迭代器b和e所指定范围内的元素。返回一个指向最后一个被删除元素之后元素的迭代器，若e本身就是尾后迭代器，则函数也返回尾后迭代器 |
|   c.clear()   |                 删除c中的所有元素，返回void                  |

forward_list有特殊版本的erase。

forward_list不支持pop_back**;vector和string不支持pop_front。**

**删除deque中除首尾位置之外的任何元素都会使所有迭代器、引用、指针失效。指向vector和string中删除位置之后的迭代器、引用、指针都会失效。**

- pop_front和pop_back成员函数

  **用process(b)，可以保存b迭代器所指向元素的拷贝。**

- 从容器内部删除一个元素

- 删除多个元素

- 特殊的forward_list操作

  |   lst.before_begin()    | 返回指向链表首元素之前不存在的元素的迭代器(首前迭代器)。此迭代器不能解引用。 |
  | :---------------------: | :----------------------------------------------------------: |
  |   lst.cbefore_begin()   |            cbefore_begin()返回一个const_iterator             |
  |  lst.insert_after(p,t)  | 在迭代器p之后的位置插入元素。t是一个对象。返回一个指向最后一个插入元素的迭代器。 |
  | lst.insert_after(p,n,t) |      在迭代器p之后的位置插入元素。t是一个对象，n是数量       |
  | lst.insert_after(p,b,e) | b和e是表示范围的一对迭代器。返回一个指向最后一个插入元素的迭代器。如果范围为空，则返回p。若p为尾后迭代器则函数行为未定义。 |
  | lst.insert_after(p,il)  | il是一个花括号列表。返回一个指向最后一个插入元素的迭代器。如果范围为空，则返回p。若p为尾后迭代器则函数行为未定义。 |
  |  emplace_after(p,args)  | 使用args在p指定的位置之后创建一个元素。返回一个指向这个新元素的迭代器。若p为尾后迭代器则函数行为未定义。 |
  |   lst.erase_after(p)    |                 删除p指向的位置之后的元素。                  |
  |  lst.erase_after(b,e)   | 删除b之后直到e（不包含e）指向的位置的元素。若不存在这样的元素，则返回尾后迭代器。若p指向lst的尾元素或者是一个尾后迭代器，则函数行为未定义 |

#### 9.3.5改变容器大小

|  c.resize(n)  | 调整c的大小为n个元素。若n<c.size(),则多出的元素被丢弃。若必须添加新元素，对新元素进行初始化 |
| :-----------: | :----------------------------------------------------------: |
| c.resize(n,t) |     调整c的大小为n个元素。任何新添加的元素都被初始化为t      |

如果resize()缩小容器，则指向被删除元素的迭代器、引用、指针都会失效。**对vector，string，deque进行resize()可能导致迭代器、指针和引用失效。**

array不可改变大小，不适用于resize()

**resize只能改变size的大小，不能改变capacity的大小。**

#### 9.3.6容器操作可能使迭代器失效

vector，string，deque必须保证每次改变容器的操作之后都正确地重新定位迭代器。

- 编写改变容器的循环程序

- 不要保存end返回的迭代器

  如果在一个循环中插入/删除deque、string、vector中的元素，不要缓存end返回的迭代器。这时，在每次循环中都重新调用end是个好的选择。

### 9.4vector对象是如何增长的

一般情况下，vector和string会分配比新控件需求更大的控件。容器预留这些控件作为备用，可用来保存更多的新元素。这种分配策略通常来说性能表现也足够好——虽然vector在每次重新分配内存控件时都要移动所有元素，但使用此策略后，其扩张操作通常比list和deque还要快。

- 管理容量的成员函数

  **shrink_to_fit仅适用于vector、string、deque。**

  **capacity和reserve仅适用于vector和string。**

  | c.shrink_to_fit() |             请将capacity()减少为与size()相同大小             |
  | :---------------: | :----------------------------------------------------------: |
  |   c.capacity()    |          不重新分配内存空间的话，c可以保存躲到元素           |
  |   c.reserve(n)    | 分配至少能容纳n个元素的内存空间，如果n<c.size(),则什么也不做 |

  reverse并不改变容器中元素的数量，它仅影响vector预先分配多大的内存空间。

- capacity和size

  每个vector实现都可以选择自己的内存分配策略。但是必须遵守的一条原则是：只有当迫不得已时才可以分配新的内存空间。

### 9.5额外的string操作

#### 9.5.1构造string的其他方法

**n、len2、pos2都是无符号值**

|     string s(cp,n)     | s是cp指向的数组中前n个字符的拷贝。此数组至少应该包含n个字符  |
| :--------------------: | :----------------------------------------------------------: |
|   string s(s2,pos2)    | s是string s2从下标pos2开始的字符拷贝。若pos2>s.size()，构造函数的行为未定义 |
| string s(s2,pos2,len2) | s是string s2从下标pos2开始len2个字符的拷贝。若pos2>s.size()，构造函数的行为未定义。不管len2的值是多少，构造函数至多拷贝s2.size()-pos2个字符。 |
|    s.substr(pos,n)     | 返回一个string，包含s中从pos开始的n个字符的拷贝。pos的默认值是0。n的默认值是s.size()-pos，即拷贝从pos开始的所有字符。 |

#### 9.5.2改变string的其他方法

append，replace。

append和push_back的区别：append不能加单个字符，push_back可以加单个字符。

​													append可以加字符串，push_back不能加字符串。

​													append可以配合迭代器使用，push_back不能配合迭代器使用。

#### 9.5.3string搜索操作

|       s.find(args)        |          查找s中args第一次出现的位置          |
| :-----------------------: | :-------------------------------------------: |
|       s.rfind(args)       |         查找s中args最后一次出现的位置         |
|   s.find_first_of(args)   |  在s中查找args中任何一个字符第一次出现的位置  |
|   s.find_last_of(args)    | 在s中查找args中任何一个字符最后一次出现的位置 |
| s.find_first_not_of(args) |        在s中查找第一个不在args中的字符        |
| s.find_last_not_of(args)  |       在s中查找最后一个不在args中的字符       |

**args必须是以下形式之一**

|  c,pos   |            从s中位置pos开始查找字符c。pos默认是0             |
| :------: | :----------------------------------------------------------: |
|  s2,pos  |           从s中位置pos开始查找字符串s2。pos默认是0           |
|  cp,pos  | 从s中位置pos开始查找指针cp指向的以空字符为结尾的C风格字符串。pos默认是0 |
| cp,pos,n | 从s中位置pos开始查找指针cp指向的数组的前n个字符。pos和n无默认值 |

string的find类函数，返回一个string::size_type类型，表示匹配的下标。如果返回失败，则返回一个string::npos。

#### 9.5.4compare函数

标准可以提供了一组compare函数，这些函数与C标准库的strcmp函数很相似。

**s.compare()的几种参数形式**

|         s2         |                          比较s和s2                           |
| :----------------: | :----------------------------------------------------------: |
|     pos1,n1,s2     |            将s中从pos1开始的n1个字符与s2进行比较             |
| pos1,n1,s2,pos2,n2 | 将s中从pos1开始的n1个字符与s2中从pos2开始的n2个字符进行比较  |
|         cp         |            比较s与cp指向的以空字符结尾的字符数组             |
|     pos1,n1,cp     | 将s中从pos1开始的n1个字符与cp指向的以空字符结尾的字符数组进行比较 |
|   pos1,n1,cp,n2    | 将s中从pos1开始的n1个字符与指针cp指向的地址开始的n2个字符进行比较 |

#### 9.5.5数值转换

p是size_t指针，用来保存s中第一个非数值字符的下标。p默认为0，即函数不保存下标

| to_string(val) |                   |
| :------------: | :---------------: |
|  stoi(s,p,b)   |                   |
|  stol(s,p,b)   |                   |
|  stoul(s,p,b)  | 返回unsigned long |
|  stoll(s,p,b)  |                   |
| stoull(s,p,b)  |                   |
|   stof(s,p)    |                   |
|   stod(s,p)    |                   |
|   stold(s,p)   |                   |

### 9.6容器适配器

适配器是标准库的一个通用概念。容器、迭代器和函数都有适配器。本质上，适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。例如，stack适配器接受一个顺序容器，使得这个容器操作起来像一个stack一样。

**所有容器适配器都支持的操作和类型**

|   size_type    |          一种类型，足以保存当前类型的最大对象的大小          |
| :------------: | :----------------------------------------------------------: |
|   value_type   |                           元素类型                           |
| container_type |                   实现适配器的底层容器类型                   |
|      A a;      |                   创建一个名为a的空适配器                    |
|    A a(c);     |          创建一个名为a的适配器，带有一个容器c的拷贝          |
|   关系运算符   | 每个适配器都支持所有关系运算符：==,!=,<,<=,>和>=。这些运算符返回底层容器的比较结果 |
|   a.empty()    |           若a包含任何元素，返回false，否则返回true           |
|    a.size()    |                      返回a中的元素数目                       |
|   swap(a,b)    | 交换a和b的内容，a和b必须有相同类型，包括底层容器类型也必须相同 |
|   a.swap(b)    |                          与上面相同                          |

- 定义一个适配器

  每个适配器都定义两个构造函数：默认构造函数创建一个空对象，接受一个容器的构造函数拷贝该容器来初始化适配器。

  假设deq是一个deque<int>我们可以用deq来初始化一个新的stack，如下所示：

  ```c++
  stack<int> stk(deq);
  ```

  默认情况下，stack和queue是基于deque实现的，priority_queue是在vector之上实现的。我们可以在创建一个适配器时将一个命名的顺序容器作为第二个类型参数，来重载默认容器类型。

  ```c++
  //在vector上实现的空栈
  stack<string,vector<string>> str_stk;
  //str_stk2在vector上实现，初始化时保存svec的拷贝
  stack<string,vector<string>> str_stk2(svec);
  ```

- 栈适配器

  栈默认基于deque实现，也可以在list或vector之上实现

  |   s.pop()    |          删除栈顶元素，但不返回该元素值          |
  | :----------: | :----------------------------------------------: |
  | s.push(item) | 创建一个新元素压入栈顶，该元素通过拷贝或移动item |
  | s.push(args) |    创建一个新元素压入栈顶，该元素通过args构造    |
  |   s.top()    |          返回栈顶元素，但不将元素弹出栈          |

  每个容器适配器都基于底层容器类型的操作定义了自己的特殊操作。我们只可以使用适配器操作，而不能使用底层容器类型的操作。

- 队列适配器

  |     q.pop()     | 返回queue的首元素或priority_queue的最高优先级的元素，但不返回该元素 |
  | :-------------: | :----------------------------------------------------------: |
  |    q.front()    |              返回首元素或尾元素，但不删除此元素              |
  |    q.back()     |                        只适用于queue                         |
  |     q.top()     |  返回最高优先级元素，但不删除该元素，只适用于priority_queue  |
  |  q.push(item)   | 在queue末尾或priority_queue中的恰当位置创建一个元素其值为item |
  | q.emplace(args) |  在queue末尾或priority_queue中的恰当位置由args创建一个元素   |

  priority_queue是一个优先级队列。默认情况下，标准库在元素类型上使用<运算符来确定相对优先级。我们可以重载<来使其完成我们需要的内容。

------

## 10泛型算法

### 10.1概述

大多数算法都定义在头文件 algorithm 中。标准库还在头文件 numeric 中定义了一组数值泛型算法。

一般情况下，这些算法并不直接操纵容器，而是遍历由两个迭代器指定的一个元素范围来进行操作。

```
int val = 32;   //我们想要查找的值
auto result = find(vec.cbegin(),vec.end(),val);
```

ps:泛型算法本身不会执行迭代器的操作，它们运行于迭代器之上，执行迭代器的操作。**泛型算法永远不会改变底层容器的大小**。

### 10.2初识泛型算法

#### 10.2.1只读算法

1. 例子：find，accumulate(在头文件numeric中)，equal
2. 算法和元素类型：accumulate将第三个参数作为求和的起点，这蕴含着一个编程假定：将元素的类型加到和的类型上的操作必须是可行的。
3. 操作两个序列的算法：equal

```c++
//对vec中的元素求和，和的初值是0
int sum = accumulate(vec.cbegin(),vec.end(),0);   //三个参数

//accumulate中的第三个参数的类型定义了函数中使用哪个加法运算符
string sum = accumulate(v.cbegin,v.end(),string(""));
string sum = accumulate(v.cbebin,v.end(),"");  //错误


//equal的第三个参数是第二个序列的起始迭代器
equal(v1.cbegin(),v1.cend(),v2.cbegin());
```

ps：字符串字面值的类型是const char * ,没有定义“+”运算。

 那些和equal一样只接受一个单一的迭代器来表示第二个序列的算法，都假定第二个序列至少与第一个序列一样长。

#### 10.2.2写容器元素的算法

1. 算法不检查写操作

   向目的位置迭代器写入数据的算法假定目的位置足够大，能容纳要写入的元素。

2. 介绍back_inserter

   一种保证有足够空间来容纳输出数据的方法是使用插入迭代器。它定义在头文件 iterator 中。通常情况我们通过迭代器向容器元素赋值时，值被赋予迭代器指向的元素。**而当我们使用插入迭代器赋值时，一个与赋值元素相等的元素被添加到容器中。**

3. 拷贝算法

   copy，也是一个接受一个单一的迭代器来表示第二个序列的算法。所以我们需要手动使得s2的长度大于等于s1。copy返回一个新的s2的尾后迭代器。

```c++
vector<int> vec;
fill_n(back_inserter(vec),10,0);   //添加10个元素到vec中，并将10个元素都重置为0
```

#### 10.2.3重排容器元素的算法

sort，使用容器的<运算符实现排序。

- 消除重复单词

  假定一个vector数组里面存放单词，设计算法来消除重复单词。

  ```c++
  void eliDups(vector<string>& words)
  {
  	sort(words.begin(),words.end());
      //unique重排输入范围，使得每个单词只出现一次
      auto end_unique = unique(words.begin(),words.end());
      words.erase(end_unique,words.end());
  }
  ```

### 10.3定制操作

#### 10.3.1向算法传递函数

​		使用谓词，见**谓词**

#### 10.3.2lambda表达式

1. 定义：一个lambda表达式表示一个可调用的代码单元，我们**可以将其理解为一个未命名的内联函数**。

2. 形式：一个返回类型，一个参数列表、一个函数体。lambada表达式可以定义在函数体内部。

   capture list是一个lambda所在函数中定义的局部变量的列表（通常为空），parameter list表示参数列表。**我们可以忽略参数列表和返回类型，但必须包括捕获列表和函数体**。

3. 作用：解决二元谓词只有两个参数的局限性。

4. **如果lambda表达式的函数体包含任何单一return语句之外的内容，且未指定返回类型，则返回void。**如果lambda表达式的函数体只包含return语句，且未指定返回类型，则根据代码自动推断返回类型。

5. **lambda表达式不能有默认参数**

6. lambda表达式的捕获列表用来**捕获包含lambda所在的函数的本地变量**(局部非static变量)，不捕获不能使用。一个lambda可以直接使用定义在当前函数之外的名字。例如:cout,cin

```c++
//lambda表达式格式：
[capture list](parameter list) -> return type{function body};

auto f = []{ return 42;};    //此例中我们定义了一个可调用对象f，它不接受参数
cout << f() << endl;        //lambda表达式调用和普通函数调用一样
```

- 调用find_if

  使用此lambda，我们就可以查找第一个长度大于等于sz的元素。

  ```c++
  //find_if返回一个迭代器，接受一个一元谓词
  auto wc = find_if(words.begin(),words.end(),
  				 [sz](const string &a)
  				 {return a.size() >= sz;});
  
  ```

- for_each算法

  ```c++
  for_each(wc,words.end(),
           [&](const string &s)
           {cout << s;}        
  );
  ```

#### 10.3.3lambda的捕获和返回

当定义一个lambda时，编译器生成一个与lambda对应的新的（未命名）类类型。

1. 值捕获

   **值捕获不能修改捕获后的变量**，类似于加了个const。

2. 引用捕获

   当以引用方式捕获一个变量时，必须保证在lambda执行时变量是存在的。事实上，**在一般的函数传参时可以用const引用避免这个问题，但是lambda不支持使用const引用**。**所以我们应该尽量避免使用引用捕获和指针捕获。**

3. 隐式捕获

   我们在捕获列表中写一个&或者=，告诉编译器采用的捕获方式。&表示引用捕获，=表示值捕获。

   混用显示捕获和隐式捕获时，**先写隐式捕获**，表示默认捕获方式，**再写显示捕获**，表示某个特定的参数的捕获方式。

```c++
//只写一个=表示所有该函数下的局部变量都使用值捕获，&同理
wc = find_if(words.begin(),words.end(),
			[=](const string &s)
			{return s.size() >= sz;}
);


//混用隐式捕获和显示捕获

for_each(words.begin(),words.end(),
         [&,c](const string &s)
         {os << s << c;}        
);
```

- 可变lambda

  默认情况下，对于值被拷贝的变量，lambda不会改变拷贝的变量。如果想要改变一个被捕获的变量的值，就必须在参数列表首加上关键字mutable。因此，可变lambda可以省略参数列表。

```c++
void fun()
{
	size_t v1 = 42;
	auto f = [v1](){return ++v1};   //错误，不能直接更改值，编译器报错
    v1 = 0;
    auto j = f(); 
}



void fun2()
{
	size_t v1 = 42;
	auto f = [v1]() mutable {return ++v1};  //v1在这个语句已经被捕获
    v1 = 0;
    auto j = f();  //j为43
    auto k = f();  //k为44
}


void fun3()
{
    size_t v1 = 42;
	auto f = [&v1](){return ++v1};
    v1 = 0;
    auto j = f();  //j为1
    auto k = f();  //k为2
}
```

注意：使用可变lambda时，在第一次写下lambda表达式组成的语句时，就已经捕获了变量，这个变量类似与静态变量，在多次使用可调用变量f后，return的值连续的改变。

- 指定lambda返回类型

  指定的lambda返回类型**必须**使用尾置返回（见C++复习6.3）

#### 10.3.4参数绑定

- 标准库bind函数

  我们可以使用bind函数来解决向check_size传递一个长度参数的问题。**即解决算法接受的是一元谓词的问题**。

  bind函数定义在头文件**functional**中。可以将bind函数看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。

  ```c++
  auto newCallable = bind(callable,arg_list);
  ```

  其中，newCallable本身是一个可调用对象，arg_list是一个逗号分隔的参数列表，对应给定的callable的参数。即，当我们调用newCallable时，newCallable会调用callable，并传递给它arg_list中的参数。

  arg_list中的参数可能包含_n的名字，其中n是一个整数。例如__1为newCallable的第一个参数。

- 绑定check_size的sz参数

  作为一个简单的例子，我们将使用bind生成一个调用check_size的对象，如下所示，它用一个定值作为其大小参数来调用check_list。在本例中 6 也可以用占位符_2代替。chek_list有多少参数都可以用占位符替代。

  ```c++
  //check_list是一个接受两个参数的函数
  bool check_list(const string &s,string::size_type sz)
  {
  	return s.size() >= sz;
  }
  
  //check6是一个可调用对象，接受一个string类型的参数
  //并用此string和值6来调用check_list
  auto check6 = bind(check_list,_1,6);
  
  //调用check6来完成check_list的调用
  string s = "sdasdasd";
  bool b1 = check6(s,6);
  ```

  使用bind，我们可以将lambda版本的find_if调用改成使用check_list版本

  ```c++
  //lambda版本
  auto wc = find_if(words.begin(),words.end(),
  				 [sz](const string &a)
  				 {return a.size() >= sz;});
  //check_list版本
  
  auto wc = find_if(words.begin(),words.end(),
                   bind(check_list,_1,sz));
  ```

- 使用placeholders名字

  名字_n都定义在命名空间**placeholders**下，而这个命名空间又定义在**std**下。这**两个命名空间都要using**。

  ```c++
  using namespace std::placeholders;
  ```

- bind的参数

  ```c++
  auto g = bind(check_list,_2,_1);       //一般不这么写，违反直觉
  g(6,"dasdasdsa");                      //_2对应check_list的第二个参数,类型为string::size_type
  ```

- 用bind重排参数序列

  ```c++
  //根据上面“bind的参数”实现
  //下面两个相同
  sort(words.begin(),words.end(),isShroter);
  sort(words.begin(),words.end(),bind(isShroter,_1,_2));
  //下面一个和上面两个相反
  sort(words.begin(),words.end(),bind(isShroter,_2,_1));
  ```

- 绑定引用参数

  当使用lambda表达式时，我们可以轻易的按引用捕获，来捕获参数的引用来完成工作。

  但使用bind绑定引用参数时，不可简单的替换，而是要使用标准库**ref**函数。

  ```c++
  //使用lambda表达式完成的工作
  for_each(words.begin(),words.end(),
           [&,c](const string &s)
           {os << s << c;}        
  );
  
  //使用下面两段来完成上面一段的工作
  //print函数
  ostream& print(ostream &os,const string &s,char c)
  {
      return os << s << c;
  }
  //含ref的bind
  for_each(words.begin(),words.end(),
           bind(print,ref(os),_1,'')
  );
  ```

### 10.4再探迭代器

除了为每个容器定义的迭代器之外，标准库在头文件 iterator 中还定义了额外的几种迭代器。包括以下几种：

1. 插入迭代器；2.流迭代器；3.反向迭代器；4.移动迭代器。

#### 10.4.1插入迭代器

插入器是一种**迭代器适配器**。

|    it = t     | 在it指定的当前位置插入值t。假定c是it绑定的容器，依赖于插入迭代器的不同种类，此赋值会分别调用c.push_back(t)、c.push_front(t)或c.insert(t,p)，其中p为传递 给inserter的迭代器位置 |
| :-----------: | :----------------------------------------------------------: |
| *it,++it,it++ |    这些操作虽然存在，但不会对it做任何事。每个操作都返回it    |

插入器的三种类型

| back_inserter  |                创建一个使用push_back的迭代器                 |
| :------------: | :----------------------------------------------------------: |
| front_inserter |                创建一个使用push_front的迭代器                |
|    inserter    | 创建一个使用inserter的迭代器。此函数接受两个参数，这个参数必须是一个指向给定容器的迭代器。元素将被插入到给定迭代器所表示的元素之前。 |

只有在容器支持push_back(push_front)，才能使用back_inserter(front_inserter)。



```c++
list<int> lst = {1,2,3,4};
list<int> lst2,lst3;

//代码完成后lst2和lst顺序相反
copy(lst.begin(),lst.end(),front_inserter(lst2));

//代码完成后lst3和lst顺序相同
copy(lst.begin(),lst.end(),inserter(lst3,lst3.begin()));
```

#### 10.4.2iostream迭代器

虽然iostream类型不是迭代器，但是标准库定义了可以用于这些IO对象的迭代器。istream_iterator读取输入流。ostream_iterator向一个输出流写入数据。通过使用流迭代器，我们可以用泛型算法从流对象读取数据以及向其写入数据。

- istream_iterator操作

  ```c++
  //从cin流和从文件中读取int
  istream_iterator<int> int_it(cin);
  istream_iterator<int> int_eof;
  ifstream in("afile");
  istream_iterator<string> str_it(in);
  
  while(in_it != int_eof)
  {
      vec.push_back(*in_it++);
  }
  ```

  istream_iterator操作

  | istream_iterator<T> in(is); |                 in从输入流is读取类型为T的值                  |
  | :-------------------------: | :----------------------------------------------------------: |
  |  istream_iterator<T> end;   |    读取类型为T的值的istream_iterator迭代器，表示尾后位置     |
  |         in1 == in2          | in1和in2必须读取相同的数据类型。如果他们都是尾后迭代器，或绑定到相同的输入，则两者相等 |
  |         in1 != in2          |                                                              |
  |             *in             |                     返回从流中读取的数值                     |
  |           in->mem           |                     与(*in).mem含义相同                      |
  |          ++in,in++          | 使用元素类型所指定的>>运算符从输入流中读取下一个值。与往常一样，前置版本返回一个指向递增后迭代器的引用，后置版本返回旧值。 |


- 使用算法操作流迭代器

  10.5.1会看到如何分辨哪些算法可以用于流迭代器

- istream_iterator允许使用懒惰求值

  istream_iterator绑定到一个流上面时，标准库不保证迭代器立即从流读取数据。保证的是，当我们第一次解引用迭代器之前，从流中读取数据的操作已经完成了

- ostream_iterator操作

  **创建一个ostream_iterator时，我们可以提供（第二个参数），它是一个C风格字符串，在输出每个元素后都会打印此字符串。**

  C风格字符串：字符串字面值常量，或指向以空字符为结尾的字符数组的指针。

  **ostream_iterator必须绑定到一个指定的流。**

  |  ostream_iterator<T> out(os);  |                out将类型T的值写入到输出流os中                |
  | :----------------------------: | :----------------------------------------------------------: |
  | ostream_iterator<T> out(os,d); | out将类型T的值写入到输出流os中，每个值后面都输出一个d。d指向一个空字符结尾的字符数组 |
  |           out = val            | 用<<运算符将val写入到out所绑定的ostream中。val的类型必须与out可写的类型相同 |
  |        *out,++out,out++        |  这些运算符是存在的，但不对out做任何事。每个运算符都返回out  |

  ```c++
  ostream_iterator<int> out_iter(cout,"");
  
  //第一种写法
  for(auto e : vec)
  {
  	*out_iter++ = e;
  }
  cout << endl;
  
  //第二种写法，与上面的写法，作用相同
  for(auto e : vec)
  {
  	out_iter = e;
  }
  cout << endl;
  
  //第三种写法，不使用循环
  copy(vec.begin(),vec.end(),out_iter);
  cout << endl;
  ```

  第一种写法中，流迭代器的使用与其他迭代器的使用保持一致，因此推荐使用第一种写法。

- 使用流迭代器处理类类型

  一个例子：

  ```c++
  istream_iterator<Sales_item> item_iter(cin),eof;
  ostream_iterator<Sales_item> out_iter(cout,"\n");
  //将第一笔交易记录在sum中，并读取下一条记录
  Sales_item sum = *item_iter++;
  while(item_iter != eof)
  {
      if(item_iter->isbn() == sum.isbn())
      {
  		sum += *item_iter++;
      }
      else{
  		out_iter = sum;
          sum = *item_iter++;
      }
  }
  out_iter = sum;
  ```

#### 10.4.3反向迭代器

递增一个反向迭代器（++it）会移动到前一个元素；递减一个反向迭代器（--it）会移动到后一个元素；

- 反向迭代器需要递减运算符

  **我们只能从既支持++又支持--的迭代器来定义反向迭代器**。所以，forward_list和流迭代器不能创建反向迭代器。

- 反向迭代器和其他迭代器的关系

  ```c++
  //一个字符串分割算法，正向的迭代器
  string s = "15881,dasdqw,wqwew,4555,hiuguih,qwer";
  auto temp1 = s.begin();
  auto temp2 = find(temp1,s.end(),',');
  vector<string> v;
  while(temp2 != s.end())
  {
      v.push_back(string(temp1,temp2));
      temp1 = temp2+1;
      temp2 = find(temp1,s.end(),',');
  }
  v.push_back(string(temp1,s.end()));
  
  for(auto i : v)
      cout << i << endl;
  
  //反向迭代器
  
  auto rcomma = find(s.crbegin(),s.crend(),',');
  cout << string(s.crbegin(),rcomma);   //会输出rewq,即反向输出
  ```

  我们可以使用reverse_iterator的**base成员函数完成反向迭代器到正向迭代器的转换。**

  ```c++
  cout << string(rcomma.base(),s.end());  //这时正常输出qwer
  ```

  反向迭代器的目的是保存元素范围，而这些范围是不对成的，这导致一个重要结果：**当我们从一个普通迭代器初始化一个反向迭代器，或是给一个反向迭代器赋值时，结果迭代器与赋值迭代器指向的不是相同元素而是相邻元素。**

### 10.5泛型算法结构

算法所要求的迭代器的操作可以分为5个迭代器类别。每个算法都会对它的每个迭代器参数指明须提供哪类迭代器。

|   输入迭代器   |    只读，不写；单遍扫描，只能递增    |
| :------------: | :----------------------------------: |
|   输出迭代器   |    只写，不读；单遍扫面，只能递增    |
|   前向迭代器   |      可读写；多遍扫描，只能递增      |
|   双向迭代器   |     可读写；多遍扫描，可递增递减     |
| 随机访问迭代器 | 可读写，多遍扫描，支持全部迭代器运算 |

#### 10.5.1 5类迭代器

- 输入迭代器：可以读取序列中的元素。必须支持
  1. ==，!=
  2. ++
  3. *(解引用)，解引用只会出现在赋值运算符的右侧
  4. ->

- 输出迭代器：只写不读元素。必须支持
  1. ++
  2. *

- 前向迭代器：可以读写元素。

  算法replace要求前向迭代器。forward_list上的迭代器是前向迭代器。

- 双向迭代器

  算法reverse要求双向迭代器。除了forward_list之外，其他标准库都提供符合双向携带其要求的迭代器。

- 随机访问迭代器。支持双向迭代器的所有操作，**此外还支持**：
  1. <，<=，>，>=
  2. +，+=，-，-=
  3. 减法运算符，得到两个迭代器的距离
  4. 下标运算符

#### 10.5.2算法形参模式

大多数算法具有如下4种形式之一：

​	**alg(beg，end，other args)；**

​	**alg(beg，end，dest，other args)；**

​	**alg(beg，end，beg2，other args)；**

​	**alg(beg，end，beg2，end2，other args)；**

- 接受单个目标迭代器的算法

  dest参数是一个表示算法可以写入的目的位置的迭代器。算法假定：按其需要写入数据，不管写入多少个元素都是安全的。

  **常见情况是dest被绑定到一个插入迭代器或是一个ostream_iterator中。**

  向输出迭代器写入数据的算法都假定目标空间足够容纳写入的数据。

- 接受第二个输入序列的算法

#### 10.5.3算法命名规范

- 一些算法使用重载形式传递一个谓词

- _if版本的算法

  接受一个元素值的算法通常都有另一个不重名的（不是重载）版本。该版本接受一个谓词代替元素值。接受谓词参数的算法都有附加的 _if 前缀。例如find和find_if。

  ```c++
  find(beg,end,val);
  find_if(beg,end,pred);  //查找第一个令pred为真的元素
  ```

- 区分拷贝元素的版本和不拷贝的版本

  **默认情况下，重排元素的算法将重排之后的元素写回给定的输入序列中**。这些算法还提供 _copy 的版本，将元素写道一个指定的输出位置。

  ```c++
  reverse(beg,end);
  reverse_copy(beg,end,dest);     //将元素按逆序拷贝到dest
  ```

### 10.6特定容器算法

对于链表来说，通用版本的算法可以适用，但代价太高。因此，**对于链表来说，应优先使用成员函数的算法而不是通用算法。**

list和forward_list成员函数版本的算法，**这些操作都返回void**

|   lst.merge(lst2)    | 将来自lst2的元素合并入lst。lst和lst2都必须是有序的。元素将从lst2中删除。在合并之后,lst2变为空。默认调用<运算符 |
| :------------------: | :----------------------------------------------------------: |
| lst.merge(lst2,comp) | 将来自lst2的元素合并入lst。lst和lst2都必须是有序的。元素将从lst2中删除。在合并之后,lst2变为空。调用comp完成比较 |
|   lst.remove(val)    |              调用erase删除掉与给定值相等的元素               |
| lst.remove_if(pred)  |               调用erase删除掉使谓词为真的元素                |
|    lst.reverse()     |                                                              |
|      lst.sort()      |                                                              |
|    lst.sort(comp)    |               使用给定比较操作（comp）排序元素               |
|     lst.unique()     |           调用erase删除同一个值的连续拷贝。使用==            |
|   lst.unique(pred)   |     调用erase删除同一个值的连续拷贝。使用二元谓词(pred)      |

- splice成员

  链表定义了splice算法。此算法使链表数据结构所特有的，所以不需要通用版本。

  

  lst是list类型，flst是forward_list

  **lst.splice(args)或flst.splice_after(args)**

  |  (p，lst2)   | p是一个指向lst元素的迭代器，或一个指向flst首前位置的迭代器。函数将lst2的所有元素移动到lst中p之前的位置，或是flst中p之后的位置。将元素从lst2中删除。lst2类型必须与lst或flst相同，且不能是同一个链表 |
  | :----------: | :----------------------------------------------------------: |
  | (p,lst2,p2)  | p2是一个指向lst2中位置的有效迭代器。将p2指向的元素移动到lst中，或者将p2之后的元素移动到flst中。lst2可以是与lst和flst相同的链表 |
  | (p,lst2,b,e) | b和e必须指向lst2中的有效范围。lst2可以是与lst和flst相同的链表.但p不能指向给定范围的元素。 |

- 链表特有的操作会改变容器

  前文提到，泛型算法通用版本不会改变底层的容器，而链表的特有操作会改变底层容器。

------

## 11关联容器

类型map和multimap定义在头文件map中；set和multiset定义在头文件set中；无序容器则定义在头文件unordered_map和unordered_set中。

关联容器类型：

| 按关键字有序保存元素 |                                       |
| :------------------: | :-----------------------------------: |
|         map          |       关联数组；保存关键字-值对       |
|         set          |   关键字即值，即只保存关键字的容器    |
|       multimap       |         关键字可重复出现的map         |
|       multiset       |         关键字可重复出现的set         |
|     **无序集合**     |                                       |
|    unordered_map     |          用哈希函数组织的map          |
|    unordered_set     |          用哈希函数组织的set          |
|  unordered_multimap  | 哈希函数组织的map。关键字可以重复出现 |
|  unordered_multiset  | 哈希函数组织的set。关键字可以重复出现 |

### 11.1使用关联容器

map类型通常被称为关联数组

- 使用map
- 使用set

### 11.2关联容器概述

关联容器支持9.2节中介绍的普通容器操作，不支持顺序容器的位置相关的操作。

#### 11.2.1定义关联容器

- 初始化multimap或multiset

#### 11.2.2关键字类型的要求

**对于有序容器——map、multimap、set、multiset，关键字类型必须定义元素比较的方法。**默认情况下，标准库使用关键字类型的<运算符来比较两个关键字。

- 有序容器的关键字类型

  在实际编程中，重要的是，如果一个类型定义了“行为正常”的<运算符，则它可以用作关键字类型。

- 使用关键字类型的比较函数

```c++
bool compareIsbn(const Sales_data &lhs,const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}


multiset<Sales_data,decltype(compareIsbn)*> bookstore(compareIsbn);
```

#### 11.2.3 pair类型

在介绍关联容器操作之前，需要先了解名为pair的标准库类型，它定义在头文件utility中。

pair上的操作

|     pair<T1,T2> p;      | p是一个pair，两个类型分别为T1，T2的成员都进行了值初始化（3.3.1节） |
| :---------------------: | :----------------------------------------------------------: |
|  pair<T1,T2> p(v1,v2)   | p是一个成员类型为T1，T2的pair；first和second成员分别用v1,v2来初始化 |
| pair<T1,T2> p = {v1,v2} |                          与上面等价                          |
|    make_pair(v1,v2)     |  返回一个用v1,v2初始化的pair。pair类型从v1,v2的类型推断出来  |
|         p.first         |              返回p的名为first的（公有）数据成员              |
|        p.second         |             返回p的名为second的（公有）数据成员              |
|       p1 relop p2       |             关系运算符（<,>,<=,>=）按字典序定义              |
|        p1 == p2         |                                                              |
|        p1 != p2         |                                                              |

- 创建pair对象的函数

  ```c++
  //当我们需要返回一个pair时，以下是几种方法
  
  return {v.back(),v.back.size()}; //列表初始化
  
  return pair<string,int>(v.back(),v.back().size());
  
  return make_pair(v.back(),v.back().size());
  ```

### 11.3关联容器操作

关联容器额外的类型别名

|  key_type   |                    此容器类型的关键字类型                    |
| :---------: | :----------------------------------------------------------: |
| mapped_type |          每个关键字关联的类型；只适用于map(所有map)          |
| value_type  | 对于set,与key_type相同。对于map,为pair<const key_type,mapped_type> |

#### 11.3.1关联容器迭代器

**当解引用一个关联容器迭代器时，我们会得到一个类型为容器的value_type的值的引用**。**对map而言，value_type是一个pair类型，其first成员保存const关键字，second成员保存值。**

- set的迭代器是const的

- 遍历关联容器

- 关联容器和算法

  **我们通常不对关联容器使用泛型算法。可以使用关联容器定义的成员函数的算法来进行操作。**

#### 11.3.2添加元素

使用关联容器的insert成员。insert有两个版本，分别接受一对迭代器，和一个初始化列表。

```
set2.insert(ivec.begin(),ivec.end());
set2.insert({1,2,5,3,7});
```

- 向map中添加元素

  **对一个map进行insert操作时，必须记住元素类型是pair。**

  关联容器的insert操作：

  |    c.insert(v)    |                v是一个value_type类型的对象。                 |
  | :---------------: | :----------------------------------------------------------: |
  |  c.emplace(args)  |                     args用来构造一个元素                     |
  |   c.insert(b,e)   |                         函数返回void                         |
  |   c.insert(il)    |                                                              |
  |   c.insert(p,v)   | 类似于insert(v)，但用p给出一个指示，指出从哪里开始搜索新元素应该存储的位置 |
  | c.emplace(p,args) | 类似于emplace(args)，但用p给出一个指示，指出从哪里开始搜索新元素应该存储的位置 |

  insert和emplace对于map和set来说，只有当元素的关键字不在c中才插入（构造）。

- 检测insert的返回值

  **insert(或emplace)返回的值依赖于容器类型和参数**。**对于不包含重复关键字的容器，添加单一元素的insert返回一个pair**，告诉我们插入是否成功。pair的first成员是一个迭代器，指向具有给定关键字的元素；second成员是bool，指出是否成功插入。

- 展开递增语句

- 向multiset和multimap添加元素

  **对于允许重复关键字的容器，接受单个元素的insert(或emplace)操作返回一个指向新元素的迭代器。**

#### 11.3.3删除元素

从关联容器中删除元素：

|  c.erase(k)  | 从c中删除每一个关键字为k的元素。返回一个size_type值，指出删除元素的数量 |
| :----------: | :----------------------------------------------------------: |
|  c.erase(p)  | 从c中删除迭代器p指定的元素。p必须指向c中一个真实元素，不能等于c.end()。返回一个指向p之后元素的迭代器，若p指向c中的尾元素，则返回c.end()。 |
| c.erase(b,e) |                 删除b到e范围内的元素。返回e                  |

#### 11.3.4map的下标操作

- 使用下标操作的返回值

  对一个map进行下标操作时，会获得一个mapped_type对象。当解引用一个map迭代器时，会得到一个value_type对象。

#### 11.3.5访问元素

在一个关联容器中查找元素的操作：

**lower_bound和upper_bound不适用于无序容器；**

下标和at操作只适用于非const的map和unordered_map

|    c.find(k)     | 返回一个迭代器，指向第一个关键字为k的元素，若k不在容器中，则返回尾后迭代器 |
| :--------------: | :----------------------------------------------------------: |
|    c.count(k)    | 返回关键字等于k的元素的数量。对于不允许重复关键字的容器，返回值永远时0或1 |
| c.lower_bound(k) |        返回一个迭代器，指向第一个关键字不小于k的元素         |
| c.upper_bound(k) |         返回一个迭代器，指向第一个关键字大于k的元素          |
| c.equal_range(k) | 返回一个迭代器pair，表示关键字等于k的元素的范围。若k不存在，pair的两个成员均等于c.end() |

- 对map使用find代替下标操作

- 在multimap或multiset中查找元素

  如果multimap或multiset中有**多个元素具有给定的关键字**，则这些元素在容器中会**相邻存储。**

- 一种不同的，面向迭代器的解决方法

  lower_bound返回的迭代器可能指向第一个具有给定关键字的元素，也可能不指向。**如果关键字不在容器中，lower_bound会返回第一个安全插入点。**

  如果lower_bound和upper_bound返回相同的迭代器，则给定的关键字不在容器中。

- equal_range函数

  此函数接受一个关键字，返回一个迭代器pair，若关键字不存在，则两个迭代器都指向关键字可以插入的位置。

### 11.4无序容器

如果关键字类型固有就是无序的，或者性能测试发现问题可以用哈希技术解决，就可以用无序容器。

- 使用无序容器

  无序容器除了哈希管理操作之外，无序容器还提供了与有序容器相同的操作(find、insert等)。因此通常可以用一个无序容器替换有序容器，反之也可以。

- 管理桶

  无序容器管理操作：

  |        桶接口         |                                                              |
  | :-------------------: | :----------------------------------------------------------: |
  |   c.bucket_count()    |                      正在使用的桶的数目                      |
  | c.max_bucket_count()  |                  容器能容纳的最多的桶的数目                  |
  |   c.bucket_size(n)    |                    第n个桶中有多少个元素                     |
  |      c.bucket(k)      |                  关键字为k的元素在哪个桶中                   |
  |      **桶迭代**       |                                                              |
  |    local_iterator     |               可以用来访问桶中元素的迭代器类型               |
  | const_local_iterator  |                     桶迭代器的const版本                      |
  |  c.begin(n),c.end(n)  |                桶n的首元素迭代器和尾后迭代器                 |
  | c.cbegin(n),c.cend(n) |         与前两个函数类似，但返回const_local_iterator         |
  |     **哈希策略**      |                                                              |
  |   c.local_factor()    |              每个桶的平均元素数量，返回local值               |
  |  c.max_load_factor()  | c试图维护平均桶的大小，返回float值。c会在需要时添加新的桶，以使得load_factor <= max_load_factor |
  |      c.rehash(n)      | 重组存储，使得bucket_count >= n 且bucket_count > size/max_load_factor |
  |     c.reserve(n)      |          重组存储，使得c可以保存n个元素且不必rehash          |

- 无序容器对关键字类型的要求

  默认情况下，无序容器使用==运算符来比较元素，它们还使用一个hash<key_type>类型的对象来生成每一个元素的hash值。

  我们不能直接定义关键字类型为自定义类类型的无序容器。与容器不同，不能直接使用哈希模板，而必须提供我们自己的hash模板版本。

------

## 12动态内存

### 12.1动态内存与智能指针

新的标准库提供了两种智能指针类型来管理动态对象。这两种智能指针的区别在于管理底层指针的方式：s**hared_ptr允许多个指针指向同一对象；unique_ptr则独占所指向的对象**。标准库还定义了一个**名为weak_ptr的伴随类**，它是一种**弱引用**，**指向shared_ptr所管理的对象**。这三种类型都定义在**头文件memory**中。

#### 12.1.1shard_ptr类

类似于vector，智能指针也是模板。

```c++
shared_ptr<string> p1;
shared_ptr<list<int>> p2;
```

默认初始化的智能指针中保存着一个空指针。

**shared_ptr和unique_ptr都支持的操作：**

| shared_ptr<T> sp; |              空智能指针，可以指向类型为T的对象               |
| :---------------: | :----------------------------------------------------------: |
| unique_ptr<T> up; |                                                              |
|         p         |        将p用作一个条件判断，若p指向一个对象，则为true        |
|        *p         |                                                              |
|      p->mem       |                                                              |
|      p.get()      | 返回p中保存的指针。要小心使用，若智能指针释放了其对象，返回的指针所指向的对象也消失了。 |
|     swap(p,q)     |                       交换p和q中的指针                       |
|     p.swap(q)     |                                                              |

**shared_ptr独有的操作**

| make_shared<T>(args) | 返回一个shared_ptr，指向一个动态分配的类型为T的对象。使用args初始化此对象 |
| :------------------: | :----------------------------------------------------------: |
|  shared_ptr<T> p(q)  | p是shared_ptr q的拷贝；此操作会递增q中的计数器，q中的指针必须能转换为T* |
|        p = q         | p和q都是shared_ptr，所保存的指针都必须能相互转换。此操作会递减p的引用计数，递增q的引用计数。若p的引用计数变为0，则将其管理的原内存释放 |
|      p.unique()      |          若p.use_count()为1，返回true;否则返回false          |
|    p.use_count()     |    返回与p共享对象的智能指针数量；可能很慢，主要用于调试     |

- make_shared函数

  最安全的分配和使用内存的方法是调用一个名为make_shared的标准库函数。此函数返回一个shared_ptr。

- shared_ptr的拷贝和赋值

- shared_ptr自动销毁所管理的对象

- shared_ptr还会自动释放相关联的内存

- 使用了动态生存期的资源的类

  **程序使用动态内存处于以下三种原因之一：**

  1. 程序不知道自己需要使用多少对象
  2. 程序不知道所需对象的准确类型
  3. 程序需要在多个对象之间共享数据

#### 12.1.2直接管理内存

- 使用new动态分配和初始化对象

- 动态分配的const对象

  合法。也必须初始化动态分配的const对象。返回的是一个const对象的指针。

- 内存耗尽

  ```c++
  int *p1 = new int;            //如果分配失败，new抛出std::bad_alloc
  int *p2 = new (nothrow) int;  //如果分配失败，new返回一个空指针
  ```

- 释放动态内存

- 指针值和delete

  我们传递给delete的指针必须指向动态分配的内存，或者是一个空指针。释放一块并非由new分配的内存，或者将相同指针值释放多次，行为是未定义的。

- 动态对象的生存期直到被释放时为止

- delete之后重置指针值

  **在delete之后，指针就变成了空悬指针。**如果我们需要保留指针，可以在delete之后将nullptr赋予指针，这样就清楚的指出指针不指向任何对象。

- 这只提供了有限的保护

  在实际系统中，查找指向相同内存的所有指针是异常困难的。

#### 12.1.3shared_ptr和new结合使用

我们可以用new的返回值来初始化智能指。但智能指针的构造函数是explicit。因此，我们不能将一个内置指针隐式转换成一个智能指针，**必须使用直接初始化形式来初始化一个智能指针。**

```c++
shared_ptr<int> p1 = new int(1024);  //错误，这是将int*隐式转换为智能指针
shared_ptr<int> p2(new int(1024));   //正确，这是直接初始化
```

**定义和改变shared_ptr的其他方法**

|  shared_ptr<T> p(q)   | p管理内置指针q所指向的对象，q必须指向new分配的内存，且能够转换成T*类型 |
| :-------------------: | :----------------------------------------------------------: |
|  shared_ptr<T> p(u)   |       p从unique_ptr u那里接管了对象的所有权；将u置为空       |
| shared_ptr<T> p(q,d)  | p从内置指针q那里接管了对象的所有权，p将使用可调用对象d来代替delete |
| shared_ptr<T> p(p2,d) |          p是p2的拷贝。p将用可调用对象d来带起delete           |
|       p.reset()       | 若p是唯一指向其对象的shared_ptr,reset会释放此对象。将p置为空。 |
|      p.reset(q)       |           若传递了可选的参数内置指针q，会令p指向q            |
|      p.rest(q,d)      |        若传递了参数d，将会调用d而不是delete来释放q。         |

- 不要混合使用普通指针和智能指针

- 也不要使用get初始化另一个智能指针或为智能指针赋值

  get函数是为了这样一种情况设计的，我们需要向不能使用智能指针的代码传递一个内置指针。**使用get返回的指针的代码不能delete此指针。**

#### 12.1.4智能指针和异常

- 智能指针和哑类

- 使用我们自己的释放操作

  ```c++
  //end_connection是一个删除器
  void end_connection(connection *p){disconnection(*p);}  //disconnection是一个已有的函数
  
  void f(destination &d /*其他参数*/)
  {
  	connection c = connect(&d);
  	shared_ptr<connection> p(&c,end_connection);
  }
  
  ```

  注意：**智能指针陷阱：**

  1. **不使用相同的内置指针值初始化（或reset）多个智能指针。**
  2. **不delete get()返回的指针。**
  3. **不使用get()初始化或reset另一个智能指针。**
  4. **如果使用get()返回的指针，记住当最后一个对应的智能指针销毁后，这个指针就无效了。**
  5. **如果使用智能指针管理的资源不是new分配的内存，记住传递给它一个删除器**。

#### 12.1.5 unique_ptr

unique_ptr和shared_ptr一样，必须使用直接初始化。

**unique_ptr操作：**

|  unique_ptr<T> u1;   | 空unique_ptr，可以指向类型为T的对象。u1会使用delete来释放它的指针 |
| :------------------: | :----------------------------------------------------------: |
| unique_ptr<T,D> u2;  | 空unique_ptr，u2会使用一个类型为D的可调用对象来释放它的指针  |
| unique_ptr<T,D> u(d) |  空unique_ptr，指向类型为T的对象，用类型D的对象d代替delete   |
|     u = nullptr      |                  释放u指向的对象，将u置为空                  |
|     u.release()      |          u放弃对指针的控制权，返回指针，并将u置为空          |
|      u.reset()       |                **释放u指向的对象**，将u置为空                |
|      u.reset(q)      |       释放u指向的对象,提供了内置指针q，令u指向这个对象       |
|   u.reset(nullptr)   |                                                              |

- 传递unique_ptr参数和返回unique_ptr

  **不能拷贝unique_ptr的规则有一个例外，我们可以拷贝或赋值一个将要被销毁的unique_ptr。最常见的例子是从函数返回一个unique_ptr。**在此种情况下，编译器会执行一种特殊的拷贝，我们将在13.6.2节介绍。

- 向unique_ptr传递删除器

  如下所示**向unique_ptr传递删除器和向shared_ptr传递删除器格式不同**：

  ```c++
  void f(destination &d /*其他参数*/)
  {
  	connection c = connect(&d);
  	unique_ptr<connection,decltype(end_connection)*> p(&c,end_connection);
  }
  ```

#### 12.1.6 weak_ptr

weak_ptr是一种不控制所指向对象生存期的智能指针。它指向一个由shared_ptr管理的对象。将weak_ptr绑定到一个shared_ptr不会改变shared_ptr的计数。**一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放。即使有weak_ptr指向对象，对象依然会被释放。**

|   weak_ptr<T> w   |               空weak_ptr可以指向类型为T的对象                |
| :---------------: | :----------------------------------------------------------: |
| weak_ptr<T> w(sp) | 与shared_ptr sp指向相同对象的weak_ptr。T必须能够转换为sp所指向的类型 |
|       w = p       |   p可以是一个shared_ptr或一个weak_ptr。赋值后w与p共享对象    |
|     w.reset()     |                          将w置为空                           |
|   w.use_count()   |                  与w共享的shared_ptr的数量                   |
|    w.expired()    |         若w.use_count()为0，返回true，否则返回false          |
|     w.lock()      | 如果expired为true，返回一个空shared_ptr；否则返回一个指向w对象的shared_ptr |

由于对象可能不存在，我们不能直接使用weak_ptr访问对象，而必须调用lock。

```c++
if(shared_ptr<int> np = wp.lock())
{
	...
}
```

### 12.2动态数组

#### 12.1.1new和数组

- 分配一个数组会得到一个元素类型的指针

  虽然我们通常称new T[]分配的内存为“动态数组”，但这种叫法某种程度上有些误导。当用new分配一个数组时，我们并未得到一个数组类型的对象，而是得到一个数组元素类型的指针。

  由于分配的内存不是一个数组类型，就不能使用begin,end函数（是类似于begin(),end()的函数，3.5.3），也不饿能用范围for循环来处理动态数组中的元素。

- 初始化动态分配对象的数组

  ```c++
  int *pia3 = new int[10]();                       //正确
  int *pia3 = new int[10]{};                       //正确
  int *pia3 = new int[10](1,2,3,4,5,6,7,8,9,10);   //错误
  int *pia3 = new int[10]{1,2,3,4,5,6,7,8,9,10};   //正确
  string *psa3 = new string[10]{"a","b","c","d","e","f","g","h","i","j"}; //正确
  ```

  **建议：多用花括号初始化。**

- 动态分配一个空数组是合法的

- 释放动态数组

  delete [] p;

- 智能指针和动态数组

  标准库提供了一个可以管理new分配的数组的unique_ptr版本：

  ```c++
  unique<int[]> up(new int[10]);
  up.release();  //自动用delete[]销毁其指针
  ```

  指向数组的unique_ptr：

  指向数组的unique_ptr不支持成员访问运算符（点和箭头运算符）

  |  unique_ptr<T[]> u   |     u可以指向一个动态分配的数组，数组元素类型为T      |
  | :------------------: | :---------------------------------------------------: |
  | unique_ptr<T[]> u(p) | u指向内置指针p所指向的动态分配的数组。p必须能转换成T* |
  |         u[i]         |   返回u用用的数组中位置i处的对象。u必须指向一个数组   |

#### 12.2.2allocator类

new有一些灵活性上的局限，其中一方面表现在它将内存分配和对象构造组合在了一起。类似的delete也一样。

**当分配一大块内存时，我们通常计划在这块内存上按需构造对象。在此情况下，我们希望内存分配和对象构造分离。**

- allocator类

  标准库allocator类定义在头文件memory中，它帮助我们将内存分配和对象构造分离。

  标准库allocator类及其算法：

  |   allocator<T> a    | 定义了一个名为a的allocator对象，它可以为类型为T的对象分配内存 |
  | :-----------------: | :----------------------------------------------------------: |
  |    a.allocate(n)    |      分配一段原始的、未构造的内存，保存n个类型为T的对象      |
  |  a.deallocate(p,n)  | 释放从T*指针p中地址开始的内存，这块内存保存了n个类型为T的对象；p必须是一个先前有allocate返回的指针，且n必须是p创建时所要求的大小。在调用deallocate之前，用户必须对每个在这块内存中创建的对象调用destroy |
  | a.construct(p,args) | p必须是一个类型为T *的指针，指向一块原始内存；args被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象 |
  |    a.destroy(p)     | p必须是一个类型为T *的指针，此算法对p指向的对象执行析构函数  |

- allocator分配为构造的内存

  **allocator分配的内存是未构造的。**在新标准库中，construct成员函数接受一个指针和零个或多个额外参数，在给定位置构造一个元素。额外参数用来初始化构造的对象。

  ```c++
  auto q = p;  //q指向最后构造函数之后的位置
  alloc.construct(q++);            //*q为空字符串
  alloc.construct(q++，10，'c');   //*q为cccccccccc
  alloc.construct(q++,"hi");      //*q为hi
  ```

  为了使用allocate返回的内存，我们必须使用construct构造对象，使用未构造的内存，其行为是未定义的。

  **我们只能对真正构造了的元素进行destroy操作。**

- 拷贝和填充未初始化内存的算法

  alloctor算法：

  这些函数在给定目的位置创建元素，而不是由系统分配内存给它们。

  | uninitialized_copy(b,e,b2)  | 从迭代器b到e指出的输入范围中拷贝元素到迭代器b2指向的未构造的原始内存中。b2指向的内存必须足够大，能容纳输入序列中元素的拷贝 |
  | :-------------------------: | :----------------------------------------------------------: |
  | uninitialized_copy(b,n,b2)  |                                                              |
  |  uninitialized_fill(b,e,t)  | 从迭代器b和e指定的原始内存范围中创建对象，对象的值均为t的拷贝 |
  | uninitialized_fill_n(b,n,t) |                                                              |

  



























## 13拷贝控制

### 13.1拷贝、赋值和销毁

#### 13.1.1拷贝构造函数

拷贝构造函数的第一个参数必须是引用类型。拷贝构造函数在几种情况下都会被隐式地使用，因此拷贝构造函数通常不应该是explicit。

- 合成拷贝构造函数

  与合成默认构造函数不同，不管有没有定义自己的拷贝构造函数，编译器都会给我们合成一个拷贝构造函数。

- 拷贝初始化

  拷贝初始化不仅在我们用=定义变量时会发生，在下列情况下也会发生：

  1. 将一个对象作为实参传递给一个非引用类型的形参
  2. 从一个返回类型为非引用类型的函数返回一个对象
  3. 用花括号列表初始化一个数组中的元素或一个聚合类中的成员。

- 参数和返回值

- 拷贝初始化的限制

  ```c++
  //假定一个explicit的构造函数来进行类型转换
  vector<int> v1(10);    //正确，直接初始化
  vector<int> v2 = 10;   //错误，接受大小参数的构造函数是explicit
  
  void f(vector<int>);   //f的参数进行拷贝初始化
  f(10);                 //错误，不能用一个explicit的构造函数拷贝一个实参
  f(vector<int>(10));    //正确，从一个int直接构造一个临时vector
  ```

- 编译器可以绕过拷贝构造函数

#### 13.1.2 拷贝赋值运算符

- 重载赋值运算符

  赋值运算符通常应该返回一个指向其左侧运算对象的引用。

- 合成拷贝赋值运算符

  合成拷贝赋值运算符返回一个指向其左侧运算对象的引用。

#### 13.1.3析构函数

- 析构函数完成什么工作

  隐式销毁一个内置指针类型的成员不会delete它所指向的对象

- 什么时候会调用析构函数

  当指向一个对象的指针或引用离开作用域时，析构函数不会被执行。

- 合成析构函数

  类似拷贝构造函数和拷贝赋值运算符，对于某些类，合成析构函数被用来阻止该类型的对象被销毁。如果不是这种情况，合成析构函数的函数体就为空。

#### 13.1.4 三/五法则

- 需要析构函数的类也需要拷贝和赋值操作

- 需要拷贝操作的类也需要赋值操作，反之亦然

#### 13.1.5使用=default

我们智能对具有合成版本的成员函数使用=default。即，默认构造函数或者拷贝控制成员。

#### 13.1.6阻止拷贝

大多数类应该定义默认构造函数、拷贝构造函数和拷贝赋值运算符，无论是显示的还是隐式的。

- 定义删除的函数

  在新标准下，我们可以通过将**拷贝构造函数**和**拷贝赋值运算符定义为删除的函数来阻止拷贝**。

  ```c++
  struct NoCopy{
      NoCopy() = default;
      NoCopy(const NoCopy&) = delete;
      NoCopy& operator=(const NoCopy&) = delete;
      ~NoCopy() = default;
  };
  ```

  与default不同的是，=delete可以对任何函数进行指定。

- 析构函数不能是删除的成员

  对于析构函数已删除的类型，不能定义该类型的变量或释放指向该类型动态分配对象的指针。

- 合成的拷贝控制成员可能是删除的

  **本质上，当不可能拷贝、赋值、销毁类的成员时，类的合成拷贝控制成员就被定义为删除的**

- private拷贝控制

  希望阻止拷贝的类应该使用=delete，而不是private。

### 13.2拷贝控制和资源管理

#### 13.2.1行为像值的类

行为像值的类需要：——big three

1. 定义一个拷贝构造函数
2. 定义一个析构函数
3. 定义一个拷贝赋值运算符

- 类值拷贝赋值运算符

  编写**赋值运算符**时，记住以下两点

  1. **如果将一个对象赋予它自身，赋值运算符必须能正常工作**
  2. **大多数赋值运算符组合了析构函数和拷贝构造函数的工作**

#### 13.2.2定义行为像指针的类

### 13.3交换操作

管理资源的类通常还定义一个名为swap的函数。对于那些与重排元素的算法一起使用的类，定义swap时非常重要的。这类算法在需要交换两个元素时会调用swap。

- 编写我们自己的swap函数

- swap函数应该调用swap，而不是std::swap

- 在赋值运算符中使用swap

  定义swap的类通常用swap来定义它们的赋值运算符。这些运算符使用了名为**拷贝并交换**的技术。这种计数将**左侧运算对象与右侧运算对象的一个副本进行交换**。

  这种方法是”异常“安全的，且能正确处理自赋值。

### 13.4拷贝控制实例 

拷贝赋值运算符通常执行拷贝构造函数和析构函数中也要做的工作。这种情况下，公共的工作应该放在private的工具函数中完成。

### 13.5动态内存管理类

### 13.6对象移动

很多情况下，都会发生对象拷贝，在其中某种情况下，对象拷贝后就立即被销毁了。在这种情况下，移动而非拷贝对象会大幅度提升性能。

标准库容器、string、和shared_ptr类既支持移动也支持拷贝。IO类和unique_ptr可以移动但不能拷贝。

#### 13.6.1右值引用

为了支持移动操作，新标准引用了一种新的引用类型——右值引用。所谓右值引用就是必须绑定到右值的引用。我们通过&&来获得右值引用。**右值引用的一个重要特质，只能绑定到一个即将销毁的对象。**

- 左值持久；右值短暂

  右值引用指向将要被销毁的对象。因此，我们可以从绑定到右值引用的对象“窃取”状态。

- 变量是左值

- 标准库move函数

  我们可以通过**调用名为move的函数来获得绑定到左值上的右值引用**。此函数定义在头文件utility中。**调用move就意味着承诺；除了对rr1赋值或销毁它之外，我们将不在使用它。**

  ```c++
  int &&rr3 = std::move(rr1);
  ```
  
  调用move的代码应当直接使用std::move，而不是move。
  
  **我们可以销毁一个移后源对象，也可以赋予它新值，但不能使用一个移后源对象的值。**

#### 13.6.2移动构造函数和移动赋值运算符

移动构造函数和移动赋值运算符，这两个成员类似对应的拷贝操作，但它们从给定对象“窃取”资源而不是拷贝资源。

```c++
StrVec::StrVec(StrVec &&s) noexpext    //移动操作不应抛出任何异常
: elements(s.elements),first_free(s.first_free),cap(s.cap)   //将this的元素构造，
{
	s.elements = s.first_free = s.caps = nullptr;          //释放s
}
```

- 移动操作、标准库容器和异常

  不抛出异常的移动构造函数和移动赋值运算符必须标记为noexcept。

- 移动赋值运算符

- 移后源对象必须可析构

  从一个对象移动数据并不会销毁此对象，但有时在移动操作完成后，源对象会被销毁。因此，**当我们编写移动操作时，必须确保以后源对象进入一个可析构的状态**。上面的例子中把移后源对象赋值为nullptr。

- 合成的移动操作

  只有当一个类没有定义任何自己版本的拷贝控制成员，且类的每个非static数据成员都可以移动时，编译器才会为它合成移动构造函数或移动赋值运算符。

  **定义了一个移动构造函数或移动赋值运算符的类必须也定义自己的拷贝构造操作。否则，这些成员默认地被定义为删除的。**

- **移动右值，拷贝左值**
- **但如果没有移动构造函数，右值也被拷贝**。

- 拷贝并交换赋值运算符和移动操作

  ```c++
  class HasPtr{
  public:
      HasPtr(HasPtr &&p) noexpext : ps(p.ps),i(p.i){p.ps = 0;}
      HasPtr(const HasPtr &p) : ps(p.ps),i(p.i),use(p.use){ ++*use; }
      HasPtr& operator=(HasPtr rhs)
      {
  		swap(*this,rhs);
          return *this;
      }
  };
  ```

  因此rhs是非引用类型，当调用=函数时，就是需要进行拷贝初始化。现在有两个函数，拷贝构造函数，移动构造函数都可以完成拷贝初始化的工作。就看调用=函数的参数和这两个函数哪个更匹配。

  ```c++
  hp = hp2;                    //这时调用拷贝构造函数
  hp = std::move(hp2);         //这时调用移动构造函数
  ```

  等于一个=函数完成了拷贝赋值运算符和移动赋值运算符的操作。

  **一般来说，如果一个类定义了任意一个拷贝操作，它就该定义所有五个操作（拷贝构造，拷贝赋值，移动构造，移动赋值，析构）。**

- 移动迭代器

  移动迭代器是一种适配器。一个移动迭代器通过改变给定迭代器的解引用运算符的行为来适配此迭代器。**移动迭代器的解引用操作生成一个右值引用。**

  ```c++
  //使用普通迭代器重新分配空间
  void Str::reallocate()
  {
  	auto newcapacity = size() ? 2*size() : 1;
      auto newdata = alloc.allocate(newcapacity);
      auto dest = newdata;
      auto elem = elements;
      for(size_t i = 0;i != size();++i)
      {
          alloc.construct(dest++,std::move(*elem++));
      }
      free();
      elements = newdata;
      first_free = dest;
      cap = elements + newcapacity;
  }
  
  //使用移动迭代器重新分配空间
  void Str::reallocate()
  {
  	auto newcapacity = size() ? 2*size() : 1;
      auto first = alloc.allocate(newcapacity);
      auto last = uninitialized_copy(make_move_iterator(begin()),
                                    make_move_iterator(end()),
                                    first);
      free();
      elements = first;
      first_free = last;
      cap = elements + newcapacity;
  }
  ```

#### 13.6.3右值引用和成员函数

**一般来说，拷贝构造函数的参数是const的左值引用，移动构造函数的参数是非const的右值引用。**一般的成员函数也可以同时提供拷贝和移动版本，与上面的方法相同。

- 右值和左值引用成员函数

  在函数的**参数列表**后面加一个**&表示只能用于左值**，**&&表示只能用于右值**。

- 重载和引用函数

  **引用限定符可以区分重载函数版本。**

  **如果一个成员函数有引用限定符（&，&&），则具有相同参数列表的所有版本都必须具有引用限定符。**

------

## 14重载运算与类型转换

### 14.1基本概念

- 直接调用一个重载的运算符函数

- 某些运算符不应该被重载

  我们一般不重载逗号运算符、取地址运算符、逻辑与、逻辑或运算符。

- 使用与内置类型一致的含义
- 赋值和复合赋值运算符
- 选择作为成员或非成员函数
  1. =，下标[]，->必须是成员。
  2. 复合赋值一般是成员，但也可以不是成员。
  3. 递增、递减、解引用必须是成员。
  4. **算数、相等性、关系和位运算符等**，具有对称性的运算符必须是**非成员**。

### 14.2输入和输出运算符

#### 14.2.1重载输出运算符

**通常情况下，输出运算符的第一个形参是一个非常量ostream对象的引用。**

- 输出运算符尽量减少格式化操作

  输出运算符主要负责打印对象的内容而非控制格式，输出运算符不应该打印换行符。

- 输入输出运算符必须是非成员函数版本

#### 14.2.2重载输入运算符

**通常情况下，输入运算符的第一个形参是运算符将要读取的流的引用。第二个形参是将要读到的（非常量）对象的引用**。

**输入运算符必须处理输入可能失败的情况，而输出运算符不需要。**

- 输入时的错误

  当读取操作发生错误时，输入运算符应该负责从错误中恢复。

### 14.3算数和关系运算符

**通常情况下，算数和关系运算符定义成非成员函数以允许对左侧或者右侧的运算对象进行转换。**

如果类同时定义了算术运算符和相关的复合赋值运算符，则通常情况下应该使用复合赋值来实现算数运算符。

#### 14.3.1相等运算符

#### 14.3.2关系运算符

如果存在唯一一种逻辑可靠的<定义，则应该考虑为这个类定义<运算符。如果类同时还包含==，则当且仅当<的定义和==产生的结果一致时才定义<运算符。

### 14.4赋值运算符

**赋值运算符必须定义为成员函数。**应该返回左侧运算对象的引用。

### 14.5下标运算符

如果一个类包含下标运算符，则它通常会定义两个版本：一个返回普通引用，另一个时类的常量成员并且返回常量引用。

### 14.6递增和递减运算符

定义递增和递减运算符的类应该同时定义前置版本和后置版本。这些运算符通常被定义为类的成员。

- 定义前置递增/递减运算符

  为了与内置版本保持一致，前置运算符应该返回递增或递减后对象的引用。

- 区分前置和后置运算符

  为了区分，后置版本接受一个额外的（不被使用）int类型的形参。因为我们不会用到int形参，而无需为其命名。这种方法，在C++设计模式Prototype中也有体现。

  为了与内置版本保持一致，后置运算符应该返回对象的原值，返回的形式是一个值而非引用。

### 14.7成员访问运算符

- 对箭头运算符（->）返回值的限定

  **重载的箭头运算符必须返回类的指针或自定义了箭头运算符的某个类的对象。**

### 14.8函数调用运算符 “（）”

如果类定义了调用运算符，我们称该类的对象为**函数对象**。

- 含有状态的函数对象类

  **函数对象常常作为泛型算法的实参。**

#### 14.8.1lambda是函数对象

- 表示lambda及相应捕获行为的类

#### 14.8.2标准库定义的函数对象

|       算术       |        关系         |       逻辑        |
| :--------------: | :-----------------: | :---------------: |
|    plus<Type>    |   equal_to<type>    | logical_and<Type> |
|   minus<Type>    | not_equal_to<Type>  | logical_or<Type>  |
| multiplies<Type> |    greater<Type>    | logical_not<Type> |
|  divides<Type>   | greater_equal<Type> |                   |
|  modulus<Type>   |     less<Type>      |                   |
|   negate<Type>   |  less_equal<Type>   |                   |

- 在算法中使用标准库函数对象

  表示运算符的函数对象类常用来替换算法中的默认运算符。比较两个无关的指针会产生未定义的行为。但我们可以使用一个标准库函数对象来实现该目的。

  ```c++
  vector<string *> nameTable;
  
  //下面是错误用法
  sort(nameTable.begin(),nameTable.end(),
      [](string *a,string *b){retrun a < b;}
      );
  
  //下面是正确用法
  sort(nameTable.begin(),nameTable.end(),
       less<string *>
      );
  ```

  关联容器默认使用less<key_type>对元素进行排序。因此我们可以在map中使用指针作为关键字而无须直接声明less。

#### 14.8.3可调用对象与function

C++中有几种可调用的对象：函数、指针、lambda表达式、bind创建的对象以及重载了函数调用对象的类。

- 不同类型可能具有相同的调用形式

  调用形式：int(int,int)    这是一种调用形式，参数是int,int，返回值是int。

  我们可以使用function，来把这些调用形式一致的可调用对象放在一起，建立函数表。

- 标准库function类型

  function定义在头文件functional中。

  |     function<T> f;      | f是用来存储可调用对象的空function，这些可调用对象的调用形式应该与函数类型T相同（即T是retType(args)） |
  | :---------------------: | :----------------------------------------------------------: |
  | function<T> f(nullpter) |                   显示的构造一个空function                   |
  |   function<T> f(obj)    |                 在f中存储可调用对象obj的脚本                 |
  |            f            |      将f作为条件，当f含有一个可调用对象时为真；否则为假      |
  |         f(args)         |                  调用f中的对象，参数时args                   |

  定义为function<T>的成员的类型

  |     result_type      |             该function类型的可调用对象返回的类型             |
  | :------------------: | :----------------------------------------------------------: |
  |    argument_type     | 当T有一个或两个实参时定位的类型。如果T只有一个实参，则argument_type是该类型的同义词 |
  | first_argument_type  |         当T有一个或两个实参时定位的类型。T有两个实参         |
  | second_argument_type |                                                              |

  function是一个模板，当我们创建一个具体的function类型时我们必须提供**调用形式**。

  ```c++
  map<string,function<int(int,int)>> binops = {
  	{"+",add},                                //add是个函数
      {"-",std::minus<int>},                    //minus是个标准库函数对象
      {"/",divide()},                           //divide是个函数对象
      {"*",[](int i,int j){return i * j;}}      //lambda表达式
      {"%",mod}                                 //mod是一个名了名的lambda表达式
  };
  ```

- 重载的函数与function

  我们不能直接将重载函数的名字存入function类型的对象中。会有二义性的问题。

  有两种方式解决这个问题，1.函数指针   2.lambda表达式

  ```c++
  //函数指针来消除二义性
  int (*fp)(int,int) = add;
  binops.insert({"+",fp});
  
  //lambda来消除二义性
  binops.insert({"+",[](int a,int b){return add(a,b);}});
  ```

### 14.9重载、类型转换与运算符

转换构造函数和类型转换运算符共同定义了**类类型转换**，这样的转换有时候也被称为**用户定义的类型转换**。

#### 14.9.1类型转换运算符

类型转换运算符是一种特殊的成员函数。形式：

```c++
operator type() const;
```

- 定义含有类型转换运算符的类


- 类型转换运算符可能产生意外结果


- 显示的类型转换运算符

  形式：

  ```c++
  explicit operator type() const;
  ```

- 转换为bool

  向bool的类型转换通常用在条件部分，因此operator bool一般定义成explicit的。

#### 14.9.2避免有二义性的类型转换

对于某个给定的类来说，最好之定义最多一个与算术类型有关的转换规则。

- 实参匹配和相同的类型转化

- 二义性与转换目标为内置类型的多重类型转换

  当我们使用两个用户定义的类型转换时，如果转换函数之前或之后存在标准类型转换，则标准类型转换将决定最佳匹配到底是哪一个。

- 重载函数与转换构造函数
- 重载函数与用户定义的类型转换

#### 14.9.3函数匹配与重载运算符

表达式中运算符的候选函数集应该包括成员函数，也应该包括非成员函数。

如果我们对同一个类既提供了转换目标是算术类型的类型转换，也提供了重载的运算符，则将会遇到充值该运算符与内置运算符的二义性问题。

------

## 15.面向对象程序设计

### 15.1OOP:概述

面向对象程序设计的核心思想是数据抽象、继承、动态绑定。

- 继承

- 动态绑定

  在C++语言中，当我们使用基类的引用（或指针）调用一个虚函数时将发生动态绑定。

### 15.2定义基类和派生类

#### 15.2.1定义基类

基类通常应该定义一个虚析构函数。

- 成员函数和继承

  如果基类的一个函数声明为虚函数，则该函数在其派生类中也隐式的声明为虚函数。

- 访问控制与继承

#### 15.2.2定义派生类

- 派生类中的虚函数

  派生类经常（但也可以不）覆盖它继承的虚函数。如果派生类没有覆盖（重写override）其基类中的某个虚函数，则该虚函数的行为类似于其他的普通成员，派生类会直接继承其在基类中的版本。

- 派生类对象及派生类向基类的类型转换

  需要基类指针（或引用）的地方可以用派生类的指针（或引用）

  在派生类对象中含有其基类对应的组成部分，这一事实是继承的关键所在。

- 派生类构造函数

  **每个类控制它自己的成员初始化过程。**

  ```c++
  //Bulk_qutoe由Quote派生而来
  //下面是Bulk_qutoe的构造函数
  Bulk_qutoe(const string &book,double p ,
  		   size_t qty, double disc) :
  		Quote(book,p),min_qty(qty),discount(disc){}
  ```

  首先初始化基类部分，然后按照声明的顺序一次初始化派生类的成员。

- 派生类使用基类的成员

  **派生类的作用域嵌套在基类的作用域之中。**派生类使用派生类成员和使用基类成员的方法一样。

- 继承与静态成员

  如果基类定义了一个静态成员，则在整个继承体系中只存在该成员的唯一定义。

- 派生类的声明

  派生类的声明和其他类一样。包含类型但是不包含它的派生列表。

- 被用作基类的类

  如果想将某个类用作基类，则该类必须已定义而非仅仅声明。

- 防止继承的发生

  在类名后面加final:

  ```c++
  class NoDerived final {.......};
  ```

#### 15.2.3类型转换与继承

理解基类和派生类之间的类型转换是理解C++语言面向对象变成的关键所在。

**智能指针也支持派生类向基类的类型转换**。**基类的指针可以指向派生类的对象。**

- 静态类型与动态类型

  基类的指针或引用的静态类型可能与其动态类型不一致。比如：静态类型是基类的指针，而动态类型是派生类的指针。

- 不存在从基类向派生类的隐式类型转换

- 在对象之间不存在类型转换

  派生类向基类的类型转换指的是指针（引用）转换，而对象不能转换。

  派生类对象为一个基类对象初始化或赋值时，实际上调用基类的构造函数，而基类的构造函数的参数是指针或引用。因此，派生类对象为一个基类对象初始化或赋值，不是对象之间的类型转换。

  **当我们用一个派生类对象为一个基类对象初始化或赋值时**，只有该派生类对象的基类部分会被拷贝、移动、赋值，它的派生类部分会被忽略掉。

### 15.3虚函数

- 对虚函数的调用可能在运行时才被解析

  当且仅当对通过指针或引用调用虚函数是，才会在运行时解析该调用，也只有在这种情况下对象的动态类型才有可能与静态类型不同。

- 派生类中的虚函数

  一个派生类的函数如果覆盖了某个继承而来的虚函数，则它的参数类型必须与被它覆盖的基类函数完全一致。

  返回类型也必须和基类函数匹配。但该规则有一个例外，当类的虚函数返回类型是类本身的指针或引用时，该规则无效。也就是说基类的该虚函数可以返回基类的指针或引用，派生类的该虚函数可以返回派生类的指针或引用。

- final和override说明符

  我们使用override说明符来说明派生类中的虚函数。

- 虚函数与默认实参

  如果虚函数使用默认实参，则基类和派生类中定义的默认实参最好一致。

- 回避虚函数的机制

  在某些情况下，我们希望对虚函数的调用不要动态绑定，而是强迫其执行虚函数的某个特定版本。使用作用域运算符实现这一目的：

  ```c++
  double undisconnected = base->Quote::net_price(42);
  ```

  通常情况下，只有成员函数（或友元）中的代码才需要使用作用域运算符来回避虚函数机制。

### 15.4抽象基类

- 纯虚函数

  书写=0就可以将一个虚函数说明为纯虚函数。

- 含有纯虚函数的类是抽象基类

  我们**不能直接创建一个抽象基类的对象**。

- 派生类构造函数只初始化它的直接基类

  在Quote的继承体系中增加Disc_quote类是重构的一个典型实例。重构负责重新设计类的体系以便将操作和/或数据从一个类移动到另一个类中。

### 15.5访问控制和继承

protected还有一条重要性质：**派生类的成员或者友元只能通过派生类对象来访问基类的受保护成员。派生类对于一个基类对象中的受保护成员没有任何访问特权。**

- 公有、私有和受保护继承

- 派生类向基类转换的可访问性

  只有当D公有的继承B时，用户代码才能使用派生类向基类的转换。

  一般来说，基类将其接口成员设计为公开的，将派生类需要访问的部分设计为受保护的，将只能自己及友元使用的部分设计为私有的。

- 友元和继承

  友元关系不能传递，友元的关系也不能继承。（朋友的朋友不是我的朋友，朋友的儿子不是我的朋友，也不是我儿子的朋友）

- 改变个别成员的可访问性

  有时我们需要改变派生类继承的某个名字的可访问性。通过使用using声明：

  ```c++
  class Dericed : public Base{
  public:
      using Base::size;        //假定Base中的size是protected的 
  private:
      using Base:n;            //假定Base中的n是public的
  };
  ```

  **派生类只能为那些它可以访问的名字提供using声明。**

- 默认的继承保护级别

  class关键字定义的派生类是私有继承的，struct关键字定义的派生类的关键字是公有继承的。

### 15.6继承中的类作用域

派生类的作用域嵌套在基类的作用域中。如果一个名字在派生类的作用域内无法正确解析，则编译器将继续在外层的基类中寻找该名字的定义。

- 在编译时进行名字查找

- 名字冲突与继承

  **派生类的成员对象将隐藏同名的基类成员对象。**

- 通过作用域运算符来使用隐藏的成员

  除了覆盖继承而来的虚函数之外，派生类最好不要重用其他定义在基类的名字。

- 一如往常，名字查找先于类型检查

  和其他作用域一样，如果派生类的成员函数（或对象）与基类的某个成员函数（或对象）同名，则派生类将在其作用域内隐藏该基类成员。**即使派生类成员和基类成员的形参列表不一致，基类成员也会被要隐藏掉。**

- 虚函数与作用域

- 覆盖重载的函数

  可以为重载的成员提供一条using声明，这样我们就无需覆盖基类的每一个重载版本了。using声明语句指定一个名字而不指定形参列表，所以一条基类成员函数的using声明语句就可以把函数的所有重载实例添加到派生类作用域中。此时派生类只需要定义其特有的函数就可以了，无须为继承而来的其他函数重新定义。

### 15.7拷贝函数与拷贝控制

#### 15.7.1虚析构函数

如果基类的析构函数不是虚函数，则delete一个指向派生类对象的基类将产生未定义的行为。

之前介绍过一个重要的经验准则，如果一个类需要析构函数，则它也同样需要拷贝构造和拷贝赋值运算符，最好同时还有移动构造和移动赋值运算符。**基类的析构函数是一个重要的例外**，因为基类的析构函数是虚函数，该析构函数为了称为虚函数而令内容为空，这时我们就无法推断出基类是否需要拷贝构造或拷贝赋值运算符了。

**虚析构函数将阻止合成移动操作。**

#### 15.7.2合成拷贝控制与继承

- 派生类中删除的拷贝控制与基类的关系

- 移动操作和继承

  我们可以用=default来显示的构造合成移动构造函数。一旦定义了自己的移动操作，那么它必须同时显示的定义拷贝操作。

#### 15.7.3派生类的拷贝控制成员

**与派生类的构造函数类似，派生类的拷贝构造和拷贝赋值和移动构造和移动赋值必须也要拷贝和移动基类部分的成员。**

- 定义派生类的拷贝或移动构造函数

  ```c++
  //D类中的拷贝构造和移动构造函数
  D(const D &d) : Base(d){...}
  D(D &&d) : Base(d){...}
  ```

- 派生类赋值运算符

  ```c++
  D& D::operator=(const D &rhs)
  {	
      Base::operator=(rhs);
      ...
      return *this;
  }
  ```

- 派生类析构函数

  这个与上面几个不同，只需要析构自己分配的资源。会自动调用基类的析构函数对基类部分进行析构。

- 在构造函数和析构函数中调用虚函数

  因为先构造基类部分，再构造派生类的其他部分。先析构派生类的其他部分，再析构基类部分。

  所以，**如果构造函数或析构函数调用了某个虚函数，则我们应该执行与构造函数或析构函数所属类型相对应的版本。**

#### 15.7.4继承的构造函数

**派生类可以“继承”直接基类的构造函数**。**不能继承基类的默认、拷贝、移动构造函数**。

使用方法：

```c++
class Bulk_quote : public Disc_quote{
public:
    using Disc_quote::Disc_quote;
};//如果派生类中含有自己的数据成员，则被默认初始化。

//与上面等价
class Bulk_quote : public Disc_quote{
public:
    Bulk_quote(const string &book,double price,
              size_t qty,double disc) :
    		Disc_quote(book,price,qty,disc){}
};
```

- 继承的构造函数的特点

  **和普通成员的using声明不一样的是，构造函数的using声明不会改变该构造函数的访问级别。也不会改变是否是constexpr和explicit。**

  无论是通过using声明继承，还是正常“继承”。**“继承”的构造函数会改变默认实参。**如果一个基类的构造函数含有两个参数，其中一个是默认实参。通过using声明，派生类将得到两个构造函数，其中接受一个参数，另一个接受两个参数。

### 15.8容器和继承

当派生类对象被赋值给基类对象时，其中的派生类部分将被“切掉”，因此容器和存在继承关系的类型无法兼容。

- 在容器中放置（智能）指针而非对象

------

## 16模板与泛型编程

### 16.1定义模板

#### 16.1.1函数模板

在模板定义中，模板参数列表不能为空。

- 实例化函数模板

  当我们调用一个函数模板时，编译器（通常）用函数实参来为我们推断模板实参。

- 模板类型参数

  例如：T

  ```c++
  template<typename T>
  ```

- 非类型模板参数

  **一个非类型模板参数表示一个值而非一个类型**。当一个模板被实例化时，非类型参数被一个用户提供的或编译器推断的值所替代。**这些值必须是常量表达式。**非类型参数可以是以一个指向对象或函数指针或（左值）引用。**绑定到指针或引用的非类型参数的实参必须具有静态的生存期。（static）**
  
  ```c++
  template<unsigned N,unsigned M>
  int compare(const char (&p1)[N],const char (&p2)[M])
  {
      return strcmp(p1,p2);
  }
  
  
  compare("hi","world");   //实例化后，N是3，M是6
  ```

- inline和constexpr的函数模板

  函数模板可以声明为inline或constexpr。

  ```c++
  template<class T>
  inline T min(const T&,const T&);
  ```

- 编写类型无关的代码

  **泛型代码的两个重要原则**：

  1. **模板中的函数参数是const的引用**
  2. **函数体中的条件判断仅使用<比较运算**

​		模板程序应该尽量减少对实参类型的要求

- 模板编译

  只有当实例化出一个模板的特定版本是，编译器才会生成代码。

  **函数模板和类模板成员函数的定义通常放在头文件。**

- 大多数编译错误在实例化期间报告

#### 16.1.2类模板

类模板是用来生成类的蓝图的。与函数模板不同的是，编译器不能为类模板推断模板参数类型。我们必须在尖括号（< >）中提供额外信息。

- 定义类模板

- 实例化类模板

  一个类模板的每个实例都形成一个**独立的类**。类与类之间没有任何关系。

- 在模板作用域中引用模板类型

- 类模板的成员函数

  与其他任何类相同，成员函数可以在类内定义，也可以在类外定义。且在类内定义的成员函数隐式地被声明为inline。

- 类模板成员函数的实例化

  **默认情况下，对于一个实例化了的类模板，其成员只有在使用时才被实例化。**

- 在类代码内简化模板类名的使用

  **当我们使用类模板类型时必须提供模板实参**。但**有一个例外**，在类模板自己的作用域中，我们可以直接使用模板名而不提供实参。

- 在类模板外使用类模板名

  当我们在类模板外定义其成员时，必须记住，我们并不在类的作用域中，直到遇到类名才表示进入类的作用域。

  ```c++
  template<class T>
  BlobPtr<T> BlobPtr<T>::operator++(int)   //在写返回值时，不在类的作用域，不能简写
  {
      BlobPtr ret = *this;                 //在写函数体内部时，在类的作用域，可以简写
      ++*this;
      return ret;
  }
  ```

- 类模板和友元

  当一个类包含一个友元声明时，类与友元各自是否是模板是相互无关的。如果一个类模板包含一个非模板友元，则友元被授权访问所有模板实例。如果友元自身是模板，类可以授权给所有友元实例，也可以只授权给特定实例。

- 一对一友好关系

- 通用和特定的模板友好关系

- 令模板自己的类型参数成为友元

- 模板类型别名

  模板的一个实例和其他非模板类一样，可以用typedef来引用实例化的类。

  ```c++
  template Blob<string> StrBlob;
  ```

  但不能使用typedef来引用未实例化的模板类。新标准允许我们为类模板定义一个类型别名：

  ```c++
  template<class T> using twin = pari<T,unsigned>;
  twin<string> authors;             //authors是一个pair<string,unsigned>
  ```

- 类模板的static成员

  类模板可以声明static成员，**类模板的每个实例都有一个独有的static成员**。

  类似任何其他成员函数，一个static成员函数只有在使用时才会被实例化。

#### 16.1.3模板参数

- 模板参数与作用域

- 模板声明

  模板声明必须包含模板参数

- 使用类的类型成员

  默认情况下，C++语言假定通过作用域运算符访问的名字不是类型。因此，如果我们希望使用一个模板类型参数的类型成员，就必须显示的告诉编译器该名字是一个类型。

  ```c++
  template<typename T>
  typename T::value_type top(const T &c)
  {
  	if(c.empty())
          return c.back();
     	else
          return typename T::value_type();
  }
  ```

  当我们希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能不能使用class。

- 默认模板实参

- 模板默认实参与类模板

  无论何时使用一个类模板，我们都必须在模板名之后加<>。

  ```c++
  Numbers<> average_precision;          //这个类模板有默认实参，因此可以不在<>加参数
  ```

#### 16.1.4成员模板

一个类可以包含本身是模板的成员函数。这种成员被称为成员模板。**成员模板不能是虚函数。**

- 普通（非模板）类的成员模板
- 类模板的成员模板
- 实例化与成员模板

#### 16.1.5控制实例化

在大系统中，在多个文件中实例化相同模板的额外开销可能非常严重。在新标准中，我们可以通过显示实例化来避免这种开销。

一个显示实例化具有如下形式：

```c++
extern template 声明;    //实例化声明
template 定义;           //实例化定义
```

- 实例化定义会实例化所有成员

  在一个类模板的实例化定义中，所用类型必须能用于模板的所有成员函数。

#### 16.1.6效率与灵活性

- 在运行时绑定删除器

  shared_ptr可能采用这种方式绑定。shared_ptr不是将删除器直接保存为一个成员。使得用户重载删除器更方便。

- 在编译时绑定删除器

  unique_ptr可能采用这种方式绑定。unique_ptr将删除器直接保存为一个成员。这样避免了间接调用删除器时的运行时的开销。

### 16.2模板实参判断

#### 16.2.1类型转换与模板类型参数

对于模板实例化来说，编译器通常不会对实参进行类型转换，而是生成一个新的模板实例。

与往常一样，顶层const无论在形参还是在实参中都会被忽略掉。

**将实参传递给带模板类型的函数形参时，能够自动应用的类型转换只有const转换（底层const）及数组到指针的转换。**

- 使用相同模板参数类型的函数形参


- 正常类型转换应用于普通函数实参

  如果函数参数类型不是模板参数，则对实参进行正常的类型转换。

#### 16.2.2函数模板显示实参

- 指定显示模板实参

  在下面的例子中，没有任何函数实参的类型可用来推断T1的类型。每次调用sum时使用者必须为T1提供一个**显示模板实参**。

  ```c++
  template<typename T1,typename T2,typename T3>
  T1 sum(T2,T3);                   //这是一个函数的声明
  
  auto val3 = sum<long long>(i,lng);  //T1是long long ,T2、T3由函数实参推断而来
  auto val2 = sum<long long,int,long>(i,long);  //T1、T2、T3都由显示模板实参指定，顺序由模板参数的顺序决定
  ```

- 正常类型转换应用于显示指定的实参

  对于用普通类型定义的函数参数，允许进行正常的类型转换，出于同样的原因，对于模板类型参数已经显示指定了函数实参，也进行正常的类型转换。

#### 16.2.3尾置返回类型与类型转换

#### 16.2.4函数指针和实参推断

当我们用一个函数模板初始化一个函数指针或为一个函数指针赋值时，编译器使用指针的类型来推断模板实参。

```c++
template<typename T>
int compare(const &T,const T&);

int(*pf1)(const int&,const int&) = compare;   //pf1指向compare的int实例
```

#### 16.2.5模板实参推断和引用

- 从左值引用函数参数推断类型

  ```c++
  template<typename T> void f1(T &);   //实参必须是左值
  
  int i = 5;
  const int j =6;
  f1(i);     //T推断为int 
  f1(j);     //和平常不同的是，T参数推断为const int
  
  template<typename T> void f2(const T &);   //实参可以是右值
  int i = 5;
  const int j =6;
  f2(i);          //T推断为int    
  f2(j);          //T推断为int
  ```

  **当函数参数是const T&时，T就不会是个const**

- 从右值引用函数参数推断类型

  推断过程类似于左值引用的推断过程。

  ```c++
  template<typename T> void f3(T &&);
  int i = 5;
  f3(5);   
  f3(i);                //编译器推断T的类型为int&
  f3(std::move(i));     //T为int
  ```
  
- 引用折叠和右值引用参数

  **如果一个函数参数是指向模板参数类型的右值引用，则可以传递给它任意类型的实参。如果将一个左值传递给这样的参数，则函数参数被实例化为一个普通的左值引用。**

- 编写接受右值引用参数的模板函数

  ```c++
  //f3的定义
  template<typename T> void f3(T &&)
  {
  	T t = val; 
      ...
  }
  ```

  当T接受一个左值时，推断T是引用类型(例如：int&)。此时，val是t的别名。

  当T接受一个右值时，推断T是非引用类型（例如：int）。此时，t是val的拷贝。

#### 16.2.6 理解std::move

虽然不必理解move就可以使用它，但理解std::move是为了巩固对模板的理解和使用。

- std::move是如何定义的

  ```c++
  //标准库定义：
  template<typename T>
  typename remove_reference<T>::type && move(T &&t)
  {
      return static_cast<typename remove_reference<T>::type &&>(t);
  }
  ```

- std::move是如何工作的

- 从一个左值static_cast到一个右值引用是允许的

#### 16.2.7转发

某些函数需要将其一个或多个实参连同类型不变的转发给其他函数。在此情况下，我们需要保持被转发实参的所有性质，包括实参类型是否是const的以及实参是左值还是右值。

- 定义能保持类型信息的函数参数

  通过将一个函数参数定义为一个指向模板类型参数的右值引用，我们可以保持其对应实参的所有类型信息。而使用引用参数（无论左值右值）使得我们可以保持const属性，因为在引用类型中的const是底层的。

  ```c++
  template<typename F,typename T1,typename T2>
  void flip2(F f,T1 &&t1,T2 &&t2)
  {
      f(t2,t1);
  }
  ```

  **如果一个函数参数是指向模板类型参数的右值引用，它对应的实参的const属性和左值/右值属性将得到保持**。

  **函数参数和任何其他变量一样，都是左值表达式。**

- 在调用中使用std:forward保持类型信息

  我们可以使用名为forward的新标准库设施来传递flip2的参数，**它能保持原始参数的类型。定义在头文件utility中**。

  **forward必须通过显示模板实参来调用，forward返回该显示实参类型的右值引用。**

  **与std::move相同，对std::forward不使用using声明是一个好主意**。

  ```c++
  //上面flip2存在下面的问题：
  void g(int &&i,int &j)
  {
      ...
  }
  flip2(g,i,42);   //错误，不能从左值实例化int&
  //虽然42是右值，但我们传递给g的将是flip2中名为t2的参数，由于函数参数都是左值表达式，
  //所以，flip2中对g的调用将传递给g的右值引用参数一个左值。与我们设想不符
  
  
  //解决了上述问题，flip3中对g的调用会传递给g的右值引用参数一个右值。
  template<typename F,typename T1,typename T2>
  void flip3(F f,T1 &&t1,T2 &&t2)
  {
      f(std::forward<T2>(t2),std::forward<T1>(t1));
  }
  ```

### 16.3重载与模板

函数匹配规则会在一下几个方面受到影响：

1. 对于一个调用，其候选函数包括所有模板实参推断成功的函数模板实例

2. 候选的函数模板总是可行的，因为模板实参推断会排除任何不可行的模板

3. 与往常一样，可行函数（模板与非模板）按类型转换来排序。当然，可以用于函数模板调用的类型转换是非常有限的（16.2.1节）

4. 与往常一样，如果恰有一个函数提供比任何其他函数都更好的匹配，则选择此函数。但是如果有多个函数提供同样好的匹配则：

   —如果同样好的函数中只有一个是非模板函数，则选择此函数

   —如果同样好的函数中没有非模板函数，而是有多个函数模板，且其中一个模板比其他模板更特例化，则选择此模板

   —否则，此调用有歧义。

- 编写重载模板
- 多个可行模板
- 非模板和模板重载
- 重载模板和类型转换
- 缺少声明可能导致程序行为异常

### 16.4可变参数模板

可变数目的参数被称为参数包。存在两种参数包：**模板参数包**，表示零个或多个模板参数；**函数参数包**，表示零个或多个函数参数。

```c++
//Args表示一个模板参数包，rest表示一个函数参数包
template <typename T, typename... Args> //也可以使用class...
void foo(const T &t, const Args &... rest);
```

- sizeof...运算符

  当我们需要知道包中有多少元素时，可以使用sizeof...运算符。格式为：sizeof...(Args)。或sizeof...(rest)。

#### 16.4.1编写可变参数函数模板

**当定义可变参数版本的print时，非可变参数版本的声明必须在作用域中。否则，可变参数版本会无限递归。**

#### 16.4.2包扩展

对于一个参数包，除了获取其大小之外，我们能对它做的唯一事情就是**扩展**它。当扩展一个包时，我们提供用于每个扩展元素的迷失。扩展一个包就是把他分解为构成的元素，对每个元素应用模式，获得扩展之后的列表。我们通过在模式右边放一个省略号来触发扩展操作。

```c++
//这个必须有，避免无限递归
template<typename T>
ostream& print1(ostream &os,const T &t)
{
    return os << t;
}


template <typename T, typename... Args>
ostream& print1(ostream &os,const T &t,const Args&... rest)
{
    os << t << ",";
    return print1(os, rest...);
}
```

- 理解包扩展

  ```c++
  template<typename T>
  string debug_rep(const T &t)
  {
      ostringstream ret;
      ret << t;
      return ret.str();
  }
  
  template<typename... Args>
  ostream& errorMsg(ostream &os,const Args& ... rest)
  {
      return print1(os, debug_rep(rest)...);
  }
  
  
  errorMsg(cerr,s,i,6,"other"); //与下面的代码相当
  
  print1(cerr, debug_rep(s), debug_rep(i), debug_rep(6), debug_rep("other"));
  ```

  扩展中的模式会独立地运用于保重的每个元素。

#### 16.4.3转发参数包

在新标准下，我们可以使用可变参数模板与forward机制来编写函数，**实现将其实参不变地传给其他函数**。

例如：

```c++
template<typename... Args>
void fun(Args &&... args)
{
    work(std::forward<Args>(args)...);
}
```

### 16.5模板特例化

- 定义函数模板特例化

  当我们已经定义了函数模板，**有些时候，通用函数模板对特定类型是不合适的，我们可以使用模板特例化。**

  ```c++
  template<>
  int compare(const char* const &p1,const char* const &p1)
  {
      return strcmp(p1, p2);
  }
  ```

- 函数重载与模板特例化

  **特例化的本质是实例化一个模板，而非重载它。因此，特例化不影响函数匹配。**

- 类模板特例化
- 类模板部分特例化
- 特例化成员而不是类

------

## 17.标准库特殊设置

### 17.1tuple类型

tuple是类似pair的模板。每个pair的成员类型都不相同，但每个pair都恰好有两个成员。不同tuple类型的成员类型也不相同，但**一个tuple可以有任意数量的成员**。每个确定的tuple类型的成员数目都是固定的，但一个tuple类型的成员数目可以与另一个tuple类型不同。

tuple支持的操作：

|        tuple<T1,T2,...,Tn> t;        | t是一个tuple，成员数是n，第i个成员的类型为Ti。所有成员都进行值初始化 |
| :----------------------------------: | :----------------------------------------------------------: |
| tuple<T1,T2,...,Tn> t(v1,v2,...,vn); |   每个成员都用相对应的vi进行初始化。此构造函数时explicit的   |
|       make_tuple(v1,v2,..,vn)        | 返回一个用给定初始值初始化的tuple。tuple的类型从初始值的类型推断 |
|               t1 == t2               | 当两个tuple具有相同数量的成员且成员对应相等时两个tuple相等。使用成员的==运算符来完成。一旦发现不等，则剩下的成员不比较 |
|               t1 != t2               |                                                              |
|             t1 relop t2              | tuple的关系运算使用字典序。两个tuple必须具有相同数量的成员。使用<运算符比较t1和t2的对应成员 |
|              get<i>(t)               | 返回t的第i个数据成员的引用。如果t是一个左值，结果是一个左值引用。否则，结果是一个右值引用。tuple的所有成员都是public的 |
|     tuple_size<typleType>::value     | 一个类模板，可以通过一个tuple类型来初始化。它有一个名为value的public constexpr static数据成员。类型为size_t，表示给定tuple类型中成员的数量 |
|   tuple_element<i,typleType>::type   | 一个类模板，可以通过一个整型常量和一个tuple类型来初始化。它有一个名为type的public成员，表示给定tuple类型中指定成员的类型。 |

**我们可以将tuple看作一个快速而随意的数据结构。**

#### 17.1.1定义和初始化tuple

tuple的构造函数是explicit的。因此我们必须使用直接初始化，而不是拷贝初始化。

```c++
tuple<size_t, size_t, size_t> threeD = {1, 2, 3};   //错误，拷贝初始化
tuple<size_t, size_t, size_t> threeD{1, 2, 3};      //正确，直接初始化，也是列表初始化
tuple<size_t, size_t, size_t> threeD(1, 2, 3);      //正确，直接初始化
```

- 访问tuple的成员

  使用名为get的标准库函数。例如：get<0>(item);

  如果不知道一个tuple的准确信息，可以用两个辅助类模板来查询typle成员的数量和类型。

  ```c++
  typedef decltype(item) trans;
  size_t sz = tuple_size<trans>::value;
  tuple_element<1, trans>::type cnt = get<1>(item);
  ```

- 关系和相等运算符

  tuple的关系和相等运算符的行为类似于容器的对应操作。

  **由于tuple定义了一个<和==运算符，我们可以将tuple序列传递给算法，并且可以在无序容器中将tuple作为关键字类型**。

#### 17.1.2使用tuple返回多个值

- 返回tuple的函数
- 使用函数返回的tuple

### 17.2bitset类型

标准库定义了bitset类，使得位运算更为容易，并且能够处理超过最长整型类型大小的位集合。bitset类定义在头文件bitset中。

#### 17.2.1定义和初始化bitset

bitset类是一个类模板，它类似于array类，具有固定的大小。定义一个bitset时，需要声明它包含多少个二进制位，其中编号为0开始的二进制位被称为低位，编号到31结束的二进制位被称为高位。

初始化bitset方法：

|          bitset<n> b;          |        b有n位；每一位均为0。此构造函数是一个constexpr        |
| :----------------------------: | :----------------------------------------------------------: |
|        bitset<n> b(u);         | b是unsigned long long值u的低n位的拷贝。如果n大于unsigned long long的大小，则b中超出unsigned long long的高位被置为0。此构造函数是一个constexpr |
| bitset<n> b(s,pos,m,zero,one); | b是string s从位置pos开始m个字符的拷贝。s只能包含字符zero或one；如果s包含任何其他字符，构造函数会抛出invalid_argument异常。字符在b中分别保存为zero和one。pos默认为0，m默认为string::npos，zero默认为‘0’，one默认为‘1’ |
| bitsrt<n> b(cp,pos,m,zero,one) | 与上一个构造函数相同，但从cp指向的字符数组中拷贝字符。如果未提供m，则cp必须指向一个C风格字符串。如果提供了m，则从cp开始必须至少有m个zero或one字符。 |

- 用unsigned值初始化bitset

  当我们使用一个整型值来初始化bitset时，此值将会被转换成unsigned long long类型并被当作位模式来处理。

  ```c++
  //bitvec1比初始值小；初始值中的高位被丢弃
  bitset<13> bitvec1(0xbeef);
  //bitvec1比初始值大；它的高位置为0
  bitset<20> bitvec2(0xbeef);
  ```

- 从一个string初始化bitset

  **string的下标编号习惯与bitset正好相反；string中下标最大的字符用来初始化bitset中的低位。**

#### 17.2.2bitset操作

bitset操作定义了多种检测或设置一个或多个二进制位的方法。bitset类还支持在4.8节介绍的位运算符。这些运算符用于bitset对象的含义与内置运算符用于unsigned运算对象相同。

bitset操作：

|        b.any()        |                  b中是否存在置位的二进制位                   |
| :-------------------: | :----------------------------------------------------------: |
|        b.all()        |                    b中的所有位都置位了吗                     |
|       b.none()        |                  b中不存在置位的二进制位吗                   |
|       b.count()       |                        b中置位的位数                         |
|       b.size()        |               一个constexpr函数，返回b中的位数               |
|      b.test(pos)      |       若pos位置的位是置位的，则返回true，否则返回false       |
|     b.set(pos,v)      | 将位置pos处的位设置位bool值v。v默认是true。如果未传递实参，则将b中所有位置位 |
|        b.set()        |                                                              |
|     b.reset(pos)      |          将位置pos处的位的状态或改变b中每一位的状态          |
|       b.rest()        |                                                              |
|      b.flip(pos)      |         改变位置pos处的位的状态或改变b中每一位的状态         |
|       b.flip()        |                                                              |
|        b[pos]         | 访问b中位置pos处的位。如果b是const的，则当该位置位时b[pos]返回一个bool值true，否则返回false |
|     b.to_ulong()      | 返回一个unsigned long的值，其位模式与b相同。如果b中位模式不能放入指定的结果类型，则抛出一个overflow_error异常 |
|     b.to_ullong()     |        与上面相同。返回的是一个unsigned long long的值        |
| b.to_string(zero,one) | 返回一个string，表示b中的位模式。zero和one的默认值分别是0和1，用来表示b中的0和1。 |
|        os << b        |          将b中二进制位打印为字符0或1，打印到流os。           |
|        is >> b        | 从is读取字符到b。当下个字符不是0或1时，或是已经读入b.size()个位时，读取过程停止。 |

### 17.3正则表达式

介绍C++正则表达式（RE库），RE库定义在头文件regex中。包含多个组件：

|      regex      |                   表示有一个正则表达式的类                   |
| :-------------: | :----------------------------------------------------------: |
|   regex_match   |              将一个字符序列与一个正则表达式匹配              |
|  regex_serach   |              寻找第一个与正则表达式匹配的子序列              |
|  regex_replace  |                使用给定格式替换一个正则表达式                |
| sregex_iterator | 迭代器适配器，调用regex_serach来遍历一个string中所有匹配的子串 |
|     smatch      |               容器类，保存在string中的搜索结果               |
|   ssub_match    |                 string中匹配的子表达式的结果                 |

regex_search和regex_match的参数：

注意：这些操作返回bool值，指出是否找到匹配

| (seq,m,r,mft) | 在字符序列seq中查找regex对象r中的正则表达式。seq可以是一个string、表示范围的一对迭代器以及一个指向空字符结尾的字符数组的直至额 |
| :-----------: | :----------------------------------------------------------: |
|  (seq,r,mft)  | m是一个match对象，用于保存匹配结果的相关细节。m和seq必须具有兼容的类型。 |
|               | mft是一个可选的regex_constants::match_flag_type值。后面会描述这些值。 |

#### 17.3.1使用正则表达式库

默认情况下，regex使用的正则表达式语言是ECMAScript。在ECMAScript中，模式[[:alpha:]]匹配任意字母，**符号+表示我们希望“一个或多个”匹配；符号*表示我们希望“零个或多个”匹配。**  

[^c]ei。表示前面不是c，后面接一个ei。

```c++
string pattern("[^c]ei");
pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
regex r(pattern);
smatch results;
string test_str = "receipt freind theif receive";
if(regex_search(test_str,results,r))
cout << results.str() << endl;
```

- 指定regex对象的选项

  当我们定义一个regex或是对一个regex对象用assign为其赋予新值时，可以指定一些标志来影响regex如何操作。下表中提供了6个标志指出编写正则表达式所用的语言。默认为ECMAScript标志，从而regex会使用ECMA-262规范。

  |   regex r(re)   | re表示一个正则表达式，它可以时一个string、一个表示字符范围的迭代器对、一个指向空字符结尾的字符数组的指针、一个字符指针和一个计数器或是一个花括号包围的字符列表。 |
  | :-------------: | :----------------------------------------------------------: |
  |  regex r(re,f)  | f是指出对象如何处理的标志。f通过下面的表格列出的值来设置。如果未指定f，其默认值未ECMAScript |
  |    r1 == re     | 将r1中的正则表达式替换为re。re表示一个正则表达式，它可以是另一个regex对象、一个string、一个指向空字符结尾的字符数组的指针或是一个花括号包围的字符列表 |
  | r1.assign(re.f) | 与使用赋值运算符（=）效果相同，可选的标志f也与regex的构造函数对应的参数含义相同 |
  | r.mark_count()  |               r中子表达式的数目（17.3.3介绍）                |
  |    r.flags()    |                        返回r的标志集                         |

  定义regex时指定的标志:

  |   icase    |     在匹配过程中忽略大小写     |
  | :--------: | :----------------------------: |
  |   nosubs   |      不保存匹配的子表达式      |
  |  optimize  |     执行速度优先于构造速度     |
  | ECMAScript |     使用ECMA-262指定的语法     |
  |   basic    | 使用POSIX基本的正则表达式语法  |
  |  extended  | 使用POSIX扩展的正则表达式语法  |
  |    awk     |  使用POSIX版本的awk语言的语法  |
  |    grep    | 使用POSIX版本的grep语言的语法  |
  |   egrep    | 使用POSIX版本的egrep语言的语法 |

  例子：

  ```c++
  //   \\. 表示 .
  regex r("[[:alpha:]]+\\.(cpp|cxx|cc)$",regex::icase);
  ```

  因为 . 是正则表达式的特殊字符。所以使用\去掉特殊含义。又由于\在C++中有特殊含义，再用一个\去除其特殊含义。

- 指定或使用正则表达式时的错误

  **一个正则表达式的语法是否正确是在运行时解析的。**
  
  正则表达式错误类型：
  
  定义在regex和regex_constants::error_type中
  
  |  error_collate   |                无效的元素校对请求                |
  | :--------------: | :----------------------------------------------: |
  |   error_ctype    |                   无效的字符类                   |
  |   error_escape   |          无效的转义字符或无效的尾置转义          |
  |  error_backref   |                  无效的向后引用                  |
  |   error_brack    |                不匹配的方括号 [ ]                |
  |   error_brack    |                不匹配的花括号 { }                |
  |   error_paren    |                不匹配的小括号 ( )                |
  |  error_badbarce  |                  {}中无效的范围                  |
  |   error_range    |           无效的字符范围（例如[z-a]）            |
  |   error_space    |          内存不足，无法处理此正则表达式          |
  | error_badrepeat  | 重复字符（*、？、+或{ ）之前没有有效的正则表达式 |
  | error_complexity |                要求的匹配过于复杂                |
  |   error_stack    |             栈空间不足，需要重新分配             |
  
  正则表达式的编译是一个非常慢的过程，因此避免创建不必要的正则表达式。

- 正则表达式类和输入类型序列

  正则表达式库类：

  | 如果输入序列类型 |              则使用正则表达式               |
  | :--------------: | :-----------------------------------------: |
  |      string      |   regex,smatch,ssub_match,sregex_iterator   |
  |   const char *   |   regex,cmatch,csub_match,cregex_iterator   |
  |     wstring      | wregex,wsmatch,wssub_match,wsregex_iterator |
  | const wchar_t *  | wregex,wcmatch,wcsub_match,wcregex_iterator |

#### 17.3.2匹配与Regex迭代器类型

17.3.1中我们查找”i在e之前，除非在c之后“规则的单词，它只打印输入序列中第一个匹配的单词。我们可以使用sregex_iterator来**获得所有匹配。**

sregex_iterator操作：

当然，它也适用于上表中的其他iterator。例如：cregex_iterator等

| sregex_iterator it(b,e,r); | 一个sregex_iterator，遍历迭代器b和e范围的string，它调用sregex_search(b,e,r)将it定义到输入中第一个匹配的位置 |
| :------------------------: | :----------------------------------------------------------: |
|    sregex_iterator end;    |                 sregex_iterator 的尾后迭代器                 |
|            *it             | 根据最后一个调用regex_search的结果，返回一个search对象的引用或一个指向smatch对象的指针 |
|            it->            |                                                              |
|            ++it            |                                                              |
|            it++            |                                                              |
|         it1 == it2         |                                                              |
|         it1 != it2         |                                                              |

- 使用sregex_iterator 

  ```c++
  string pattern("[^c]ei");
  string test_str = "receipt freind theif receive";
  pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
  regex r(pattern, regex::icase);
  for(sregex_iterator it(test_str.begin(),test_str.end(),r),end_it ; it != end_it;++it)
  {
      cout << it->str() << endl;
  }
  ```

  其中，end_it也可以改成end。或随便什么名字。它的含义都是尾后迭代器。

#### 17.3.3使用子表达式

#### 17.3.4使用regex_replace

正则表达式替换操作：

|      m.format(dest,fmt,mft)       | 使用格式字符串fmt生成格式化输出，匹配在m中，可选的match_flag_type标志在mft中。第一个版本写入迭代器dest指向的目的位置并接受fmt参数，可以是一个string，也可以是一个指向空字符结尾的字符数组的一对指针。 |
| :-------------------------------: | :----------------------------------------------------------: |
|         m.format(fmt,mft)         | 第二个版本返回一个string，保存输出，并接受fmt参数，可以是一个string，也可以是一个指向空字符结尾的字符数组的指针。mft的默认值为format_default |
| regex_replace(dest,seq,r,fmt,mft) | 将输出写入到迭代器dest指定的位置，并接受一对迭代器表示范围。fmt既可以是一个string，也可以是一个指向空字符结尾的字符数组的指针。且mft的默认值是match_default。 |
|   regex_replace(seq,r,fmt,mft)    | 返回一个string，保存输出，且seq既可以是一个string，也可以是一个指向空字符结尾的字符数组的指针。fmt既可以是一个string，也可以是一个指向空字符结尾的字符数组的指针。且mft的默认值是match_default。 |

### 17.4随机数

定义在头文件random中的随机数库。

随机数库的组成：

| 引擎 |       类型，生成随机unsigned整数序列       |
| :--: | :----------------------------------------: |
| 分布 | 类型，使用引擎返回服从特定概率分布的随机数 |

#### 17.4.1随机数引擎和分布

标准库定义了多个随家属引擎类，区别在于性能和随机性质量不同。每个编译器都会指定其中一个作为default_random_engin类型。此类型一般具有最常用的特性。下标列出了随机数引擎操作：

|      Engine e;      |   默认构造函数；使用该引擎类型默认的种子   |
| :-----------------: | :----------------------------------------: |
|    Engine e(s);     |            使用整型值s作为种子             |
|      e.seed(s)      |          使用种子s重置引擎的状态           |
|       e.min()       |            此引擎可生成的最小值            |
|       e.max()       |                                            |
| Engine::result_type |        此引擎生成的unsigned整型类型        |
|    e.discard(u)     | 将引擎推进u步。u的类型为unsigned long long |

**对于大多数场合，随机数引擎的输出是不能直接使用的**，问题出在生成的对技术的值范围通常与我们需要的不符。

- 分布类型和引擎

  为了得到一个指定范围内的随机数，我们使用一个分布类型的对象

  ```c++
  uniform_int_distribution<unsigned> u(0, 100);
  default_random_engine e;
  for (size_t i = 0; i < 10;++i)
  {
      cout << u(e) << endl;
  }
  ```

  **当我们说随机数发生器时，是指分布对象和引擎的组合。**

- 比较随机数引擎和rand函数

- 引擎生成一个数值序列

  一个给定的随机数发生器一直会生成相同的随机数序列。**一个函数如果定义了局部的随机数发生器，应该将其（包括引擎和分布对象）定义为static的。否则每次调用都会生成相同的序列。**

- 设置随机数发生器种子

  随机数发生器会生成相同的随机数序列这一特性在调试时很有用，但是调式完成后我们希望每次程序运行都生成不同的结果，可以桶过**种子**来达到这一目的。

  **不同的种子生成不同的结果，相同的种子生成相同的结果。**

  一般选择的种子是，调用系统函数time。这个函数定义在头文件ctime中。它返回从一个特定时刻到当前经过了多少秒。函数time接受单个指针参数，它指向用于写入时间的数据结果。如果此指针为空，则函数简单地返回时间：

  ```c++
  default_random_engine e(time(0));  //这种方式只适用于生成种子的间隔为秒级或更长时间的应用
  ```

#### 17.4.2其他随机数分布

- 生成随机实数

  生成随机实数可以使用分布对象uniform_real_distribution类型的对象，并让标准库来处理从随机整数到随机浮点数的映射。

  ```c++
  uniform_real_distribution<double> u(0, 1);
  default_random_engine e(113);
  cout << "这是第一次生成：" << endl;
  for (size_t i = 0; i < 10;++i)
  {
  cout << u(e) << endl;
  }
  ```

  分布类型的操作：

  |  Dist d;  | 默认构造函数；使d准备好被使用。其他构造函数依赖于Dist 的类型。分布类型的构造函数时explicit的 |
  | :-------: | :----------------------------------------------------------: |
  |   d(e)    | 用相同的e连续调用d的话，会根据d的分布式类型生成一个随机数序列，e是一个随机数引擎对象 |
  |  d.min()  |                    返回d(e)能生成的最小值                    |
  |  d.max()  |                    返回d(e)能生成的最大值                    |
  | d.reset() |     重建d的状态，使得随后对d的使用不依赖于d已经生成的值      |

- 使用分布的默认结果类型
- 生成非均匀分布的随机数

### 17.5IO库再探

#### 17.5.1格式化输入与输出

除了条件状态外，每个iostream对象该维护一个格式状态来控制IO如何格式化的细节。格式状态控制格式化的某些方面，如整型值是几进制，浮点值的精度，一个输出元素的宽度等。

- 很多操纵符改变格式状态

- 控制布尔值的格式

  默认情况下，bool值打印出来是0或1。但我们可以使用boolalpha操纵符来覆盖这种格式使其打印true和false。

  注意：**当操纵符改变流的格式状态时，通常改变后的状态对后续所有IO都有效**。因此，我们在不需要boolalpha操纵符时，使用noboolalpha取消之。(其他改变流格式的操纵符也需要取消)

  ```c++
  cout << "默认输出bool值：" << true << "," << false << endl;
  cout << "boolalpha控制输出bool值："<< boolalpha      
  << true << "," << false << endl
  << noboolalpha;
  ```

- 指定整型值的进制

  默认情况下，整型值的输入输出使用十进制。我们可以使用操纵符hex（16进制），oct（8进制），dec（10进制）

  **操纵符hex,oct和dec只影响整型运算对象，浮点值的表示形式不受影响。**

  ```c++
  cout << hex << 15 << ",";
  cout << 100 << ",";         //该成16进制之后，后续都是16进制，使用dec改回十进制
  cout << dec << 100;
  ```

- 在输出中指出进制

  有时候我们希望输出中能指出使用的是几进制。采用showbase可以做到（记得noshowbase）

  ```c++
  cout << showbase;
  cout << hex << 15 << ",";
  cout << 100 << ",";
  cout << dec << 100;
  cout << noshowbase;
  ```

- 控制浮点数格式

  我们可以控制浮点数输出三个种格式：

  1. 以多高精度（多少个数字）打印浮点值
  2. 数值是打印为十六进制、定点十进制还是科学计数法形式
  3. 对于没有小数部分的浮点值是否打印小数点

- 指定打印精度

  **默认情况下，精度会控制打印的数字的总数。浮点值按四舍五入而非截断。**

  我们可以通过调用IO对象的precision成员来改变精度。它是重载的，一个版本接受一个int值，将精度设置为此值；另一个版本不接受参数，返回当前精度值。

  **接受参数的操纵符都定义在头文件iomanip中。**

  定义在iostream中的操纵符：

  *表示默认流状态

  |   boolalpha   |        将true和false输出为字符串         |
  | :-----------: | :--------------------------------------: |
  | * noboolalpha |                                          |
  |   showbase    |        对整型值输出表示进制的前缀        |
  | * noshowbase  |                                          |
  |   showpoint   |          对浮点值总是显示小数点          |
  | * noshowpoint |                                          |
  |    showpos    |              对非负数显示+               |
  |  * noshowpos  |                                          |
  |   uppercase   | 在十六进制值中打印0X,在科学计数法中打印E |
  | * nouppercase | 在十六进制值中打印0x,在科学计数法中打印e |
  |     *dec      |                                          |
  |      hex      |            整型值显示为16进制            |
  |      oct      |            整型值显示为8进制             |
  |     left      |     在值的右侧添加填充字符（左对齐）     |
  |     right     |     在值的左侧添加填充字符（右对齐）     |
  |   internal    |        在符号和值之间添加填充字符        |
  |     fixed     |          浮点值显示为定点十进制          |
  |  scientific   |          浮点值显示为科学计数法          |
  |   hexfloat    |            浮点值显示为16进制            |
  | defaultfloat  |          重置浮点数格式为十进制          |
  |    unitbuf    |          每次输出后都刷新缓冲区          |
  |  * nounitbuf  |                                          |
  |   * skipws    |           输入运算符跳过空白符           |
  |   noskipws    |                                          |
  |     flush     |            刷新ostream缓冲区             |
  |     ends      |    插入空字符，然后刷新ostream缓冲区     |
  |     endl      |                                          |

- 指定浮点数记数法

  除非需要控制浮点数的表示形式，否则由标准库来选择记数法是最好的方式。

- 打印小数点

- 输出补白

  **setw指定下一个数字或字符串值的最小空间。**

  **setw类似于endl，不改变输出流的内部状态。只决定下个输出的大小。**

  ```c++
  int i = -16;
  double d = 3.1415926;
  cout << left;            //设置为左对齐
  cout << setfill('#');    //使用'#'补齐空的部分
  cout << "i:" << setw(12) << i  << endl;
  cout << "d:" << setw(12) << d << endl;
  cout << right;           //返回到默认对齐方式
  cout << setfill(' ');   //返回默认补齐方式
  ```

  **注意:在使用setw后默认是right（右对齐）的，默认空的部分由' '补上**

- 控制输入格式


#### 17.5.2未格式化的输入/输出操作

上面的所有程序都只用过格式化IO操作。输入和输出运算符根据读取或写入的数据类型来格式化他们。

标准库还提供了一组底层操作，支持未格式化IO。这些操作允许我们将一个流当作一个无解释的字节序列来处理。

- 单字节操作

  单字节底层IO操作：

  |   is.get(ch)   | 从istream is中读取下一个字符存入字符ch中。返回is |
  | :------------: | :----------------------------------------------: |
  |   os.put(ch)   |         将字符ch输出到ostream os。返回os         |
  |    is.get()    |           将is的下一个字节作为int返回            |
  | is.putback(ch) |              将字符ch放回is。返回is              |
  |   is.unget()   |           将is向后移动一个字节。返回is           |
  |   is.peek()    |    将下一个字节作为int返回，但不从流中删除它     |

- 将字符放回输入流

- 从输入操作返回的int值

- 多字节操作

  |   is.get(sink,size,delim)   | 从is中读出最多size个字节，并保存在字符数组中。字符数组的起始地址由sink给出。读取过程直到遇到了字符delim或读取了size个字节或遇到文件尾时停止。如果遇到了delim，则将其留在输入流中，不读取出来存入sink |
  | :-------------------------: | :----------------------------------------------------------: |
  | is.getline(sink,size,delim) |       与接受三个参数的get版本类似，但会读取并丢弃delim       |
  |     is.read(sink,size)      |        读取最多size个字节，存入字符数组sink中。返回is        |
  |         is.gcount()         |          返回上一个未格式化读取操作从is读取的字节数          |
  |    os.write(source,size)    |        将字符数组source中的size个字节写入os。返回os。        |
  |    is.ignore(size,delim)    | 读取并忽略最多size个字符，包括delim。于其他未格式化函数不同。ignore由默认参数，size的默认值是1，delim的默认值为文件尾。 |

- 确定读取了多少个字符

#### 17.5.3流随机访问

istream和ostream不支持随机访问。本节只研究fstream和sstream类型

- seek和tell函数

  为了支持随机访问，IO类型维护一个标记来确定下一个读写操作要在哪里进行。它们还提供两个函数：一个函数通过将标记seek到给定位置来重定位它；另一个函数tell告诉我们标记的当前位置。输入和输出版本的处在于名字的后缀是g还是p，g版本表示我们正在获得（读取）数据，而p版本表示我们正在放置（写入）数据。

  seek和tell函数：

  |     tellg()     |                返回一个输入流中标记的当前位置                |
  | :-------------: | :----------------------------------------------------------: |
  |     tellp()     |                返回一个输出流中标记的当前位置                |
  |   seekg(pos)    | 在一个输入流中将标记重定位到给定的绝对地址。pos通常是前一个tellg或tellp返回的值 |
  |   seekp(pos)    | 在一个输出流中将标记重定位到给定的绝对地址。pos通常是前一个tellg或tellp返回的值 |
  | seekg(off,from) | 在一个输入流中将标记定位到from之前或之后off个字符。from可以是下列值之一： |
  | seekp(off,from) |                                                              |
  |                 |                beg，偏移量相对于流开始的位置                 |
  |                 |                cur，便宜量相当于流当前的位置                 |
  |                 |                end，便宜量相当于流结尾的位置                 |

- 只有一个标记

------

## 18.用于大型程序的工具

### 18.1异常处理

#### 18.1.1抛出异常

- 栈展开

  栈展开过程沿着嵌套函数的调用链不断查找，直到找到了与异常匹配的catch语句位置；或者也可能一直没找到匹配的catch，则退出主函数后查找过程终止。

  假设找打了一个匹配的catch子句，则程序进入该子句并执行其中的代码。当执行完这个子句之后，找到与try块关联的最后一个catch子句之后的点，并从这里继续执行。

  **如果一个异常没有被捕获，则它将终止当前的程序。**

- **栈展开过程中对象会被自动销毁**

  我们应该保证对象正确的被销毁

- 析构函数和异常

  **析构函数总是会被执行，但是函数中负责释放资源的代码却可能被跳过。**

- 异常对象

  抛出指针要求在任何对应的处理代码存在的地方，指针所指的对象都必须存在。

#### 18.1.2捕获异常

#### 18.1.3函数try语句块与构造函数

#### 18.1.4noexcept异常说明

#### 18.1.5异常层次类

### 18.2命名空间

多个库将名字放置在全局命名空间中将引发**命名空间污染**。

#### 18.2.1命名空间定义

```c++
namespace cplusplus_primer{
	class Sales_data{};
}
```

命名空间作用域后面无序分号。

- 每个命名空间都是一个作用域

- 命名空间可以是不连续的

  定义多个类型不相关的命名空间应该使用单独的文件分别表示每个类型。

- 定义命名空间成员

  在这个命名空间作用域内，该命名空间成员可以直接使用名字，无需指出其属于哪个作用域。

- 模板特例化

  模板特例化必须定义在原始模板所属的命名空间中。和其他命名空间名字类似，只要我们在命名空间声明了特例化，就能在命名空间外部定义它了。

- 全局命名空间

- 嵌套的命名空间

- 内联命名空间

  内联命名空间和嵌套命名空间不同，内联命名空间的名字可以被外层命名空间直接使用

- 未命名的命名空间

  未命名的命名空间是指关键字namespace后紧跟花括号括起来的一系列声明语句。**未命名的命名空间中定义的变量具有静态的生命周期**：它们在第一次使用前创建，直到程序结束后才销毁。

  和其他命名空间不同，未命名的命名空间仅在特定的文件内部有效，其作用范围不会横跨多个不同的文件。

#### 18.2.2使用命名空间成员

我们可以使用using声明来使用命名空间成员（3.1节）。以下介绍几种其他的方式使用命名空间成员。

- 命名空间的别名

  ```c++
  namespace Qlib = cplusplus_primer::QueryLib;
  ```

  一个命名空间可以由好几个同义词或者别名，所有别名都和命名空间原来的名字等价。

- using声明：扼要概述

  一条using声明语句的有效范围就是它所在的作用域的范围。

- using指示

  以下是一个常见的using指示：

  ```c++
  using namespace std;
  ```

  **对于using指示不作任何特殊控制的话，将重新引入名字冲突问题。**

- using指示与作用域

  **using指示具有将命名空间成员提升到包含命名空间本身和using指示的最近作用域的能力。**

#### 18.2.3类、命名空间与作用域

可以从函数的限定名推断出查找名字时检查作用域的次序，限定名以相反次序指出被查找的作用域。

- 实参相关的查找与类类型形参

  **当我们给函数传递一个类类型的对象（或指针、引用）时，除了在常规的作用域查找之外还会查找实参类所属的命名空间。**

  例如： operator<<(std::cin,s);   //cin是类类型的对象，在其命名空间std中，存在operator<<,所以不需要在operator之前加std::std

- 查找std::move和std::forward

  因为std::move可以接受任意类型的形参，所以当我们自己定义了move函数时，就会产生冲突。为了避免冲突采用std::move的格式。

- 友元声明与实参相关的查找

#### 18.2.4重载与命名空间

- 与实参相关的查找与重载
- 重载与using声明
- 重载与using指示
- 跨越多个using指示的重载

### 18.3多重继承与虚继承

多重继承是指从多个直接基类中产生派生类的能力。多重继承的派生类继承了所有父类的属性。

#### 18.3.1多重继承

- 多重继承的派生类从每个基类中继承状态
- 派生类构造函数初始化所有直接基类

- 继承的构造函数与多重继承

  如果从多个基类中继承了相同的构造函数则程序会产生错误。

  ```c++
  struct Base1{
      Base1() = default;
      Base1(const string &) { cout << "Base1" << endl; }      
      Base1(shared_ptr<int>){}
  };
  
  struct Base2{
      Base2() = default;
      Base2(const string &) { cout << "Base2" << endl; }
      Base2(int){}
  };
  
  struct D2 : public Base1,public Base2
  {
      using Base1::Base1;
      using Base2::Base2;
      //从Base1和Base2中继承的相同的构造函数，我们需要定义自己的版本
      D2(const string &) { cout << "D2" << endl; }   
  };
  ```

- 析构函数与多重继承

- 多重继承的派生类的拷贝与移动操作

  与单继承一样，派生类自己定义的拷贝/移动构造函数和赋值运算符，则必须在完整的对象上执行拷贝/移动或赋值（15.7.2节）

#### 18.3.2类型转换与多个基类

在单继承（这里指只有一个基类）的情况下，派生类的指针或引用能自动转换成一个可访问基类的指针或引用。多个基类的情况与之类似。

- 基于指针类型或引用类型的查找

  **与单继承一样，对象、指针、引用的静态类型决定了我们能够使用哪些成员（15.6）。**

#### 18.3.3多重继承下的类作用域

当一个类拥有多个基类时，有可能出现派生类从两个或更多基类中继承了同名成员的情况。此时，不加前缀限定符直接使用该名字将引发二义性。

#### 18.3.4虚继承

尽管在派生列表中同一个基类只能出现一次，但实际上派生类可以多次继承同一个类。派生类可以通过它的两个直接基类分别继承同一个间接基类，也可以直接继承某个基类，再通过另一个基类再一次间接继承该类。

**默认情况下，派生类多次继承同一个类时，派生类对象会包含多个基类对象部分。C++中通过虚继承解决上述问题。虚继承的目的是令某个类做出声明，承诺愿意共享它的基类。**其中，共享的基类子对象称为虚基类。

虚派生值影响从制定了虚基类的派生类中进一步派生出的类，它不会影响派生类本身。

- 使用虚基类

  使用虚基类的方法是在派生类列表中添加关键字virtual

- 支持向基类的常规类型转换

- 虚基类成员的可见性

#### 18.3.5构造函数与虚继承

**在虚派生中，虚基类是由最底层的派生类初始化的。**一般派生中，派生类只会初始化其直接基类，但虚派生必须由最底层的派生类初始化。

- 虚继承的对象的构造方式


含有虚基类的对象的构造顺序与一般的顺序稍有区别：首先使用提供给最底层派生类构造函数的初始值初始化该对象的虚基类子部分，接下来按照直接基类在派生列表中出现的次序对其进行初始化。

虚基类总是先于非虚基类构造，与它们在继承体系中的次序和位置无关。

- 构造函数与析构函数的次序

  一个类可以有多个虚基类。此时，这些虚的子对象按照它们在派生列表中出现的顺序从左向右依次构造。

------

## 19.特殊工具与技术

### 19.1控制内存分配

#### 19.1.1重载new与delete

重载这两个运算符与重载其他运算符的过程大不相同。首先需要对new表达式和delete表达式的工作机制有更多了解。

当我们使用一条new表达式时：

```c++
string *sp = new string("a value");
string *arr = new string[10];
```

实际执行了三步操作。第一步，new表达式调用一个名为operator new(或operator new[])的标准库函数。该函数分配一块足够大的、原始的、未命名的内存空间以构造这些对象，并为其传入初始值。第三步，对象被分配了空间并构造完成，返回一个指向该对象的指针。

我们可以在全局作用域中定义operator new函数和operator delete函数，也可以将它们定义为成员函数。我们可以使用作用域运算符令new表达式或delete表达式忽略定义在类中的函数，直接执行全局作用域中的版本呢。例如，::new。

- operator new接口和operator delete接口

  标准库定义了operator new和operator delete的8个重载版本：

  ```c++
  //这些版本可能抛出异常
  void *operator new(size_t);
  void *operator new[](size_t);
  void *operator delete(void *) noexcept;
  void *operator delete[](void *) noexcept;
  
  //这些版本不会抛出异常
  void *operator new(size_t,nothrow_t &) noexcept;
  void *operator new[](size_t,nothrow_t &) noexcept;
  void *operator delete(void *,nothrow_t &) noexcept;
  void *operator delete[](void *,nothrow_t &) noexcept;
  ```

  应用程序可以自定义上面函数的任意一个，前提是自定义的版本必须位于全局作用域或者类作用域中。当我们将上述运算符函数定义成类的成员时，它们是隐式静态的。我们无须显示地声明static。

  对于operator new函数或者operator new[]函数来说，它的返回类型必须是void *,第一个形参的类型必须是size_t且该形参不能含有默认实参。当编译器调用operator new时，把存储指定类型对象所需字节数传给size_t形参；当调用operator new[]时，传入函数的则是存储数组中所有元素所需要的空间。

  如果我们想自定义operator new函数，则可以为它提供额外的形参。此时，用到这些自定义函数的new表达式必须使用new的定位形式（12.1.1）将实参传递给新增的形参。我们可以重载绝大部分函数，但下面的函数不能被用户重载：

  ```c++
  void * operator new(size_t,void*);  //这种形式只供标准库使用，不能被用户重新定义
  ```

  对于operator delete函数或者operator delete[]函数来说，它的返回类型必须是void *,第一个形参的类型必须是void *。执行一条delete表达式将调用相应operator函数，并用指向待释放内存的指针来初始化void *对象。

  当我们将operator delete或operator delete[]定义成类的成员时，该函数可以包含另外一个类型为size_t的形参。此时该形参的初始值是第一个形参所指向对象的字节数。size_t形参可用于删除继承体系中的对象。如果一个基类有一个虚析构函数，则传递给operator delete的字节数将因待删除指针所指向对象的动态类型不同而有所区别。而且，实际运行的operator delete函数版本也有对象的动态类型决定。

  **和其他operator函数不同，这两个函数并没有重载new表达式或delete表达式。**实际上，我们根本无法自定义new表达式或delete的行为。**我们提供新的operator new函数和operator delete函数的目的在于改变内存分配的方式，但不能改变new运算符和delete运算符的基本含义。**

- malloc函数与free函数

  我们可以在自己operator new和operator delete函数中使用malloc和free函数来分配内存。

#### 19.1.2定位new表达式

### 19.2运行时类型识别

运行时类型识别由两个运算符实现：

1. typeid运算符，用于返回表达式的类型
2. dynamic_cast运算符，用于将基类的指针或引用安全地转换成派生类的指针或引用。

**这两个运算符特别适用于一下情况：我们想使用基类对象的指针或引用执行某个派生类操作并且该操作不是虚函数。一般来说，尽可能地使用虚函数。假设我们无法使用虚函数，则可以使用一个RTTI运算符**。**使用RTTI必须要加倍小心。

#### 19.2.1 dynamic_cast运算符

dynamic_cast运算符的使用形式如下：

```c++
dynamic_cast<type *>(e);
dynamic_cast<type &>(e);
dynamic_cast<type &&>(e);
```

其中type必须是类类型，通常该类型应该含有虚函数。在第一种形式中e必须是一个有效的指针，在第二种情况下，e必须是一个左值，在第三种情况下，e不能是一个左值。

- 指针类型的dynamic_cast

  ```c++
  if(Derived *dp == dynamic_cast<Derived *>(bp))
  {
  	...
  }
  ```

  我们可以对一个空指针执行dynamic_cast，结果是所需类型的指针。

  在条件部分执行dynamic_cast操作可以确保类型转换和结果检查在同一条表达式中完成。

- 引用类型的dynamic_cast

  ```c++
  try{
  	const Derived &d = dynamic_cast<const Derived &>(b);
      
  }catch(bad_cast) {
  ...
  }
  ```

#### 19.2.2 typeid运算符

为RTTI提供的第二个运算符是typeid运算符，**它允许程序向表达式提问：你的对象是什么类型？**

typeid表达式的形式是 typeid(e)，其中e可以是任意表达式或类型的名字。typeid操作的结果是一个常量对象的引用，该对象的类型是标准库类型type_info或type_info的公有派生类型。type_info定义在头文件typeinfo中，在19.2.4中详细介绍type_info的细节。

typeid运算符可以作用于任意类型的表达式。和**往常一样，顶层const被忽略，如果表达式是一个引用，则typeid返回该引用所引用对象的类型。不过，当typeid作用于数组或者函数时，并不会执行向指针的标准类型转换**。也就是说，如果我们对数组a执行typeid(a)，则所得的结果是数组类型而非指针类型。

- 使用typeid运算符

  ```c++
  Derived *dp = new Derived;
  Base *bp = dp;
  if(typeid(*bp) == typeid(*bp)){
  ...
  }
  if(typeid(*bp) == typeid(Derived)){
  ...
  }			
  ```

  **当typeid作用于指针时，返回的结果时该指针静态编译时的类型。**

#### 19.2.3使用RTTI

在某些情况下RTTI非常有用，比如当我们想为具有继承关系的类实现相等运算符时。

以下是一个例子：

```c++
class Base{
   friend bool operator==(const Base &, const Base &);
public:

protected:
   virtual bool equal(const Base &rhs) const
   {
       //执行比较Base对象的操作
   }
   
};
class Derived : public Base{
public:

protected:
   bool equal(const Base &rhs) const
   {
      auto r = dynamic_cast<const Derived &>(rhs);
       //执行比较两个Derived对象的操作并返回结果
      ...
   }
};

bool operator==(const Base &lhs, const Base &rhs)
{
   return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}
```

#### 19.2.4 type_info类

type_info精确定义根据编译器的不同而有所不同。但规则type_info必须定义在头文件typeinfo中，并且至少提供下表的操作：

|   t1 == t2    | 如果type_info对象t1和t2表示同一种类型，返回true，否则返回false |
| :-----------: | :----------------------------------------------------------: |
|   t1 != t2    |                                                              |
|   t.name()    | 返回一个C风格字符串，表示类型名字的可打印形式。类型名字的生成方式因系统而异 |
| t1.before(t2) |            返回一个bool值，表示t1是否位于t2之前。            |

### 19.3枚举类型

C++包含两种枚举：限定作用域的和不限定作用域的。

```c++
//限定作用域的枚举
enum class open_modes{input,output,append};
//不限定作用域的枚举
enum color{red,yellow,green};
```

- 枚举成员

  默认情况下，枚举值从0开始，依次加1。不过也可以为一个或多个枚举成员指定专门的值。

  枚举成员是const，因此在初始化枚举成员时提供的初始值必须是常量表达式。

- 和类一样枚举也定义新类型

  使用枚举类型：

  ```c++
  om = open_modes::input; 
  ```

- 指定enum的大小

  尽管每个enum都定义了唯一的类型，但实际上enum是由某种整数类型表示的。我们可以在enum的名字后面加上冒号以及我们想在该enum中使用的类型：

  ```c++
  enum intValues : unsigned long long
  {
     a = 255,
     b = 4294967295UL
  };
  ```

- 枚举类型的前置声明


```c++
enum intValues : unsigned long long;        //必须指定成员类型，无默认值
enum class open_modes;                      //由默认值int，可以不指定显示的成员类型
```

- 形参匹配与枚举类型

  要想初始化一个enum对象，必须使用该enum类型的另一个对象或者他的一个枚举类型。因此，即使某个整型值恰好与枚举成员的值相等，它也不能作为函数的enum实参使用。

### 19.4类成员指针

成员指针是指可以指向类的非静态成员的指针。

#### 19.4.1数据成员指针

```c++
//pdata可以指向一个常量（非常量）Screen对象的string成员
const string Screen::*pdata;     
pdata = &Screen::contents;

//使用auto声明成员指针
auto pdata = &Screen::conntents;
```

- 使用数据成员指针

  当我们初始化一个成员指针或为成员指针赋值时，该指针并没有指向任何数据。成员指针（数据成员和成员函数）指定了成员而非成员所属的对象，只有当解引用成员指针时，我们才提供对象的信息。

  ```c++
  Screen myScreen, *pScreen = &myScreen;
  auto s = myScreen.*pdata;   //注意是 .*
  s = pScreen->*pdata;        //注意是->*
  ```

- 返回数据成员指针的函数

  因为数据成员一般情况下是私有的，所有我们通常不能直接获得数据成员的指针。最好是定义一个函数，返回值是指向该成员的指针。

#### 19.4.2成员函数指针

```c++
auto pmf = &Screen::get_cursor;
```

和普通的函数指针类似，如果成员存在重载问题，则我们必须显示地声明函数类型以明确指出我们想要使用的是哪个函数。例如：

```c++
char (Screen::*pmf2)(Screen::pos,Screen::pos)const;
pmf2 = &Screen::get;
```

- 使用成员函数指针

  ```c++
  Screen myScreen, *pScreen = &myScreen;
  char c1 = (pScreen->*pmf);
  char c2 = (myScreen.*pmf2)(0,0);
  ```

- 使用成员指针的类型别名

  使用类型别名或typedef可以使得成员指针更容易理解。

- 成员指针函数表

  对于普通函数指针和指向成员函数的指针来说，一种常见的用法是将其存入一个函数表（14.8.3）中。

```c++
class Screen{
public:
   Screen& home();
   Screen& forward();
   Screen& back();
   Screen& up();
   Screen& down();
   using Action = Screen& (Screen::*)();   //Action是一个成员函数指针
   enum Directions
   {
      HOME,
      FORWARD,
      BACK,
      UP,
      DOWN
   };
   Screen& move(Directions cm)
   {
       //运行this对象中索引值为cm的元素
      return (this->*Menu[cm])();  //Menu[cm]指向一个成员函数
   }  
   
private:
   static Action Menu[];   //函数表
};
//初始化函数表
Screen::Action Screen::Menu[] = {&Screen::home,
                                 &Screen::forward,
                                 &Screen::back,
                                 &Screen::up,
                                 &Screen::down};

Screen myScreen;
myScreen.move(Screen::HOME);   //调用myScreen.home
mySCreen.move(Screen::DOWN);
```

#### 19.4.3将成员函数用作可调用对象

如我们所知，要想通过一个指向成员函数的指针进行函数调用，必须先利用 .* 运算符或 ->*运算符将该指针绑定到特定的对象上。**因此与普通的函数指针不同，成员指针不是一个可调用对象，这样的指针不支持函数调用运算符。**

```c++
auto fp = &string::empty;
find_if(svec.begin(),svec.end(),fp); //错误，find_if算法需要一个可调用对象
```

- 使用function生成一个可调用对象（14.8.3）

  ```c++
  function<bool (const string &)> fcn = &string::empty;
  find_if(svec.begin(),svec.end(),fcn); //正确
  ```

- 使用mem_fn生成一个可调用对象

  mem_fn和function不同的是，mem_fn可以根据成员指针的类型推断可调用对象的类型，而无须用户的显示指定。

  ```c++
  find_if(svec.begin(),svec.end(),mem_fn(&string::empty)); //正确
  ```

- 使用bind生成一个可调用对象

  ```c++
  auot it = find_if(svec.begin(),svec.end(),bind(&string::empty,_1)); //正确
  ```


### 19.5嵌套类

一个类可以定义在另一个类的内部，前者称为嵌套类或嵌套类型。**嵌套类常用于定义作为实现部分的类**。**嵌套类是一个独立的类，与外层类基本没什么关系。**

- 声明一个嵌套类

  ```c++
  class TextQuery{
  public:
  	class QueryResult;
  };
  ```

- 在外层类之外定义一个嵌套类

  和成员函数一样，嵌套类可以在类内声明，类外定义。

  在嵌套类在其外层类之外完成真正的定义之前，它都是一个不完全类型（7.3.3）

- 定义嵌套类的成员

- 嵌套类的静态成员定义

- 嵌套类作用域中的名字查找

  名字查找的一般规则（7.4.1）在嵌套类中同样适用。当然，**因为作用域嵌套，所以会查找嵌套类的外层作用域。**

- 嵌套类和外层类是相互独立的

### 19.6 union: 一种节省空间的类

联合（union）是一种特殊的类。一个uoion可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值。和其他类一样，一个union定义了一种新类型。

类的某些特性对union同样适用，但非所有特性都适用。union不能含有引用类型成员，除此之外，它的成员可以是绝大多数类型。在新标准中，含有构造函数或析构函数的类类型也可以作为union的成员类型。u**nion可以为其成员指定public、protected、private等保护标记。默认情况下，union的成员都是公有的**，这一点和struct相同。

- 定义union

  union提供了一种有效的途径使得我们可以方便地表示一组类型不同的互斥值。例如：

  ```c++
  union Token{
  	char cval;
  	int val;
  	double dval;
  };
  ```

- 使用union类型

  我们可以像显示地初始化聚合类（7.5.5）一样，使用一对花括号内的初始值显示地初始化一个union。

  ```c++
  Token first_token = {'a'};   //初始化cval成员
  Token last_token;            //未初始化的Token对象
  Token *pt = new Token;       //指向一个未初始化的Token对象的指针
  ```

- 匿名union

  匿名union是一个未命名的union，并且在右花括号和分号之间没有任何声明。一旦我们定义了一个匿名union，编译器就自动地为该union创建一个未命名的对象。

  ```c++
  union {
  	char cval;
  	int val;
  	double dval;
  };
  ```

  在匿名union定义的作用域内，该union成员都是可以直接访问的。

  匿名union不能包含受保护的成员或私有成员，也不能定义成员函数。

- 含有类类型成员的union

- 使用类管理union成员

  我们通常把含有类类型成员的union内嵌在另一个类当中。这个类可以管理并控制与union的类类型成员有关的类型转换。下面是一个例子：

  ```c++
  class Token{
  public:
     Token():tok(INT),ival(0){}
     Token(const Token &t) : tok(t.tok) { copyUnion(t); }
     Token &operator=(const Token &);
     ~Token(){if(tok==STR) sval.~string();}
     Token &operator=(const string &);
     Token &operator=(char);
     Token &operator=(int);
     Token &operator=(double);
  private:
     enum
     {
        INT,
        CHAR,
        DBL,
        STR
     } tok;       //tok是这个未命名的枚举类型的一个对象
     union {
        char cval;
        int ival;
        double dval;
        string sval;
     };
     void copyUnion(const Token &);
  };
  //管理判别式并销毁string
  Token& Token::operator=(int i)
  {
     if(tok == STR)
        sval.~string();
     ival = i;
     tok = INT;
     return *this;
  }
  
  
  Token &Token::operator=(const string &s)
  {
     if(tok == STR)
        sval = s;
     else
        new (&sval) string(s);
     tok = STR;
     return *this;
  }
  
  //管理需要拷贝控制的联合成员
  void Token::copyUnion(const Token &t)
  {
     switch (t.tok)
     {
     case Token::INT :
        ival = t.ival;
        break;
     case Token::CHAR :
        cval = t.cval;
        break;
     case Token::DBL :
        dval = t.dval;
        break;
     case Token::STR :
        new (&sval) string(t.sval);
        break;
     }
  }
  
  
  Token &Token::operator=(const Token &t)
  {
     if(tok == STR && t.tok != STR)
        sval.~string();
     if(tok == STR && t.tok == STR)
        sval = t.sval;
     else
        copyUnion(t);
     tok = t.tok;
     return *this;
  }
  ```


### 19.7局部类

类可以定义在某个函数的内部，我们称这样的类为局部类。

局部类的所有成员（包括函数）都必须完整定义在类的内部。因此局部类的作用域与嵌套类相比相差很远。

- 局部类不能使用函数作用域中的变量
- 常规的访问保护规则对局部类同样适用
- 局部类中的名字查找
- 嵌套的局部类

### 19.8固有的不可移植的特性

不可移植的特性是指因机器而异的特性，当我们将含有不可移植特性的程序从一台机器转移到另一台机器上时，通常需要重新编写该程序。例如：算术类型（2.1.1），此外还有位域、volatile、链接指示等不可移植特性。

#### 19.8.1位域

***位域的类型必须是整型或者枚举类型。因为带符号位域的行为是由具体实现决定的，所以在通常情况下我们适用无符号类型保存一个位域。**

```c++
typedef unsigned int Bit;
class File{
	Bit mode:2;
	Bit modified:1;
	Bit prot_owner:3;
	Bit prot_group:3;
	Bit prot_world:3;
public:
	enum modes{READ = 01,WRITE = 02,EXECULTE = 03};
	File &open(modes);
	void close();
	void write();
    bool isRead() const;  //用来检验位域的值
    void setWrite();      //用来设置位域的值
	
};
```

- 使用位域

  ```c++
  void File::write()
  {
     modified = 1;
     // ...
  }
  void File::close()
  {
     if(modified)
     //...保存内容
  }
  File &File::open(File::modes m)
  {
     mode |= READ;
     if(m & WRITE)
     //按照读/写的方式打开文件
     return *this;
  }
  
  int main() {
  
  
  
     getchar();
     return 0;
  }
  ```

#### 19.8.2 volatile限定符

#### 19.8.3链接指示：extern "C"

C++有时需要调用其他语言（主要是C语言）编写的函数。其他语言中的函数名字也必须在C++中进行声明，并且该声明必须指出普通C++函数返回类型和形参列表（这是否是**调用形式**？14.8.3）。C++对其他语言检查其调用的方式与普通C++函数相同，但生成的代码有所区别。C++使用链接指示来指出任意非C++函数所用的语言。

- 声明一个非C++函数

  下面是例子：

  ```c++
  //extern "C" + 普通函数声明
  extern "C" size_t strlen(const char *);
  
  extern "C" {
      int strcmp(const char *,const char *);
      char *strcat(char*,const char *);
  }
  ```

- 链接指示与头文件

  多重声明的形式可以应用于整个头文件：

  ```c++
  extern "C" {
  	#include<string.h>
  }
  ```

- 指向extern "C"函数的指针

  ```c++
  extern "C" void (*pf)(int);
  ```

  指向C函数的指针和指向C++函数的指针是不一样的，不能用来相互赋值。（尽管有的编译器会允许相互赋值，但在严格意义上是非法的）

- 链接指示对整个声明都有效

- 导出C++函数到其他语言

  ```c++
  //calc函数可以被C程序调用
  extern "C" double calc(double dparm){ .... }
  ```

  















