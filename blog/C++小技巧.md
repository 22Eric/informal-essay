记录作者在刷leetcode时碰到的一些标准库函数、算法的用法。

1.标准库函数erase

单词的意思为“擦除”。作用就是擦除容器内的一部分内容。(string不是容器也可使用)

顺序容器erase的用法：(string也是这么用)

```C++
vector<int> v(12,2);  //v中有12个元素每个都是2
v.erase(迭代器1，迭代器2);   
```

注意：erase使用**左闭右开区间**进行擦除，擦除迭代器1的内容，不擦除迭代器2的内容。

关联容器中也有erase，遇到时补充。

2.substr函数

适用于string。作用是截取字符串的一部分。

```c++
string s = "dsasdsdsdasda";
string s1 = s.substr(index,num);
```

注意：idnex是起始下标，num表示要截取的数量

3.标准库函数reverse函数

单词的意思是"翻转"。作用是将容器的内容进行翻转

顺序容器reverse的用法（string可用）

```c++
string s = "sdeedwede";
string rev = reverse(迭代器1,迭代器2);
```

注意：reverse使用左闭右开区间进行翻转，迭代器2指向的内容不参与翻转。

4.C++中string和int相互转换

```c++
//string转int
string s = "q2323dscs";
int i = s.atoi(s.c_str());

//int转string
int i = 6;
string s = to_string(i);
```

5.整型的范围

```
INT_MAX
INT_MIN     //可以直接用
```

6.动态规划待填坑

7.函数名 和 decltype(函数名)  的区别

8.静态成员变量，在类中是声明，需要在类外定义。

9.size_type类型

vector<int>::size_type实际上是一种unsigned类型。

```c++
vector<int>::size_type i = 5;
unsigned int j = 5;

cout << i-6 << endl;         //是4294967295
cout << j-6 << endl;         //也是4294967295，而不是-1

cout << int(i-6) << endl;   //这样才是-1
cout << int(j-6) << endl;   //这样才是-1
```

10.函数的参数接受可调用对象。

可调用对象是函数时，分为全局函数和类成员函数。

全局函数可以直接传入函数指针。

类成员函数，需要表明函数是哪个类的，也需要表明函数属于哪个对象（假设调用的函数也属于这个类，则省略属于哪个对象，改为this指针）

