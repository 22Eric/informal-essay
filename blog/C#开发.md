## 1. C# 简介

​	C#是一种通用的，类型安全的面向对象编程语言。

### 1.1 面向对象

​	C#实现了丰富的面向对象范式，包括封装、继承和多态。这点与C++一样。

​	不同的是，C#拥有统一的类型系统，其中的所有类型都共享一个公共的基类，qt大部分类型也共享公共基类，而C++没有。

#### 类与接口

​	在传统面向对象范式中，唯一的类型就是类。然而C#还有其他几种类型，其中之一是接口（interface）。接口与类相似，但它仅仅描述成员。而实现接口的类型将实现接口定义的这些成员。接口可以有多个实现。

#### 属性、方法和事件

​	C#中函数不仅包括了方法，除此之外还有属性、事件及其他的形式。（纯粹的面向对象中，所有的函数都是方法）

​	C#使用委托（delegate）将函数作为值传递给其他函数或者从其他函数中返回。

### 1.2 类型安全性

​	C#是一种**类型安全**（type-safe）的语言。例如，C#不允许将字符串类型作为整数类型进行处理。

​	更具体地说，C#支持**静态类型化**（static typing），即在编译时会执行安全性检查。此外，在运行时也会同样执行类型安全性检查。

​	C#允许部分代码通过dynamic关键字来动态定义指定类型。然而，C#在大多数情况下仍然是一门静态类型化语言。

​	C#还是一门**强类型语言（**strongly typed language），因为它的类型规则（不论是静态还是运行时）非常严格。例如，不能用一个浮点类型的参数来调用一个接受整数类型参数的函数，必须显式将这个浮点数转换为整数。这可以防止编码错误。

### 1.3 内存管理

C#依靠运行时来实现自动内存管理。

C#并未抛弃指针，只是在大多数编程任务中是不需要使用指针的。仍然可以在标记为**unsafe的程序块内使用指针**并进行显式内存分配。

### 1.4 C#和CLR

​	**CLR（Common Language Runtime，公共语言运行时）**。CLR和语言无关。开发者可以使用多种语言，例如C#、F#、Visual Basic.NET，以及托管C++来构建应用程序。

​	C#也会将代码编译为托管代码。托管代码以 中间语言（**IL**）的形式表示。 CLR通常会在执行前，将IL转换为机器（例如x86或x64）原生代码，称为即时（Just-In-Time, JIT）编译。

### 1.5 C#版本特性

#### 1.5.1  C# 7.0新特性

- 数字字面量的改进

```c#
int a = 1_000_000; //与1000000相同
var b = 0b1010_1011_1100; //二进制字面量可以使用0b前缀进行标识
```

- 输出变量及参数忽略

```c#
bool successful = int.TryParse("123",out int result);//result可以直接在这一行定义。ref标识也可以这么做
```

​	当调用含有多个out参数的方法时，可以使用**下划线字符忽略不关心的参数**。

```c#
MyFunc(out_,out_,out int x,out_);
```

- 模式变量（is）

  is运算符可以自然地引入变量，称为模式变量。

​	switch语句同样支持模式，因此我们不仅可以选择常量还可以选择类型。可以使用when子句来指定一个判断条件；或是直接选择null。

- 局部方法

​	局部方法是声明在其他函数内部的方法。局部方法仅仅在其包含函数内可见，它们可以像Lambda表达式那样捕获局部变量。

- 结构器

  构造器一般接受一系列值（作为参数）并将其赋值给字段，而解构器则正相反，它将字段反向赋值给变量。

- 元组（tuple）

```c#
 (int raw, int col) = GetFilePos();
 Console.WriteLine($"Raw:{raw}, Col:{col}");
```

- throw表达式

  throw既可以做语句，也可以作为表达式。

#### 1.5.2 C# 6.0新特性

- null条件访问运算符

  ```c#
  List<string>? list = null;
  int? count = list?.Count; // list 为 null → count = null（注意返回值是可空类型）
  ```

- 表达式体函数

  以Lambda表达式的形式书写仅仅包含一个表达式的方法、属性、运算符以及索引器。

  ```c#
  public int Func1(int x) => x * 2;
  public string Func2() => "asdasdasd";
  ```

- 属性初始化器

  ```c#
  public DateTime? CreatedTime { get; set; } = DateTime.Now; //支持只读属性
  ```

- 索引初始化器

  ```c#
  var dict = new Dictionary<int, string>
  {
   [3] = "One",
   [5] = "Three"
  };
  ```

- 字符串插值 ($)

  ```c#
  string s = $"[Info] 连接字符串: {ConnectionString}";
  ```

- 异常过滤器

​	可以在catch块上再添加一个条件。

```
 catch(Exception ex) when(3 > 1)
 {
 		//...
 }
```

- using static

​	引入一个类型的所有静态成员，这样就可以不用书写类型而直接使用这些成员.

```c#
using static System.Console;
WriteLine("asdasdasd");
```

- nameof 运算符

  返回变量、类型或者其他符号的名称。

#### 1.5.3 C# 5.0新特性

​	C# 5.0最大的新特性是通过两个关键字，async和await，支持异步功能。

#### 1.5.4 C# 4.0新特性

- 动态绑定

​	动态绑定将绑定过程（解析类型与成员的过程）从编译时推迟到运行时.

- 可选参数

​	可选参数允许函数指定参数的默认值，这样调用者就可以省略一些参数，而命名参数则允许函数的调用者按名字而非按位置指定参数。

#### 1.5.5 C# 3.0新特性

​	C# 3.0增加的特性主要集中在语言集成查询（Language Integrated Query, **LINQ**）上。

- var关键字

  允许在声明语句中省略变量类型，然后由编译器推断其类型。

- 对象初始化器

  允许在调用构造器之后以内联的方式设置属性，从而简化对象的构造过程。对象初始化器不仅支持命名类型也支持匿名类型。

- Lambda表达式
- 扩展方法

​	可以在**不修改类型定义的情况下使用新的方法扩展现有类型**，使静态方法变得像实例方法一样。LINQ表达式的查询运算符就是使用扩展方法实现的

- 表达式树

​	表达式树是赋值给一种特殊类型Expression<TDelegate>的Lambda表达式的DOM（文档对象模型，Document Object Model）模型。表达式树使LINQ查询能够远程执行（例如在数据库服务器上），因为它们可以在运行时进行转换和翻译（例如变成SQL语句）。

- 自动化属性（get; set;）

## 2. C#语言基础

### 2.1 类型基础

#### 2.1.1 值类型与引用类型

​	所有的C#类型可以分为以下几类：值类型、引用类型、泛型参数、指针类型。

​	**值类型包含大多数的内置类型**（具体包括所有数值类型、char类型和bool类型）以及自定义的struct类型和enum类型。

​	**引用类型包含所有的类、数组、委托和接口类型**。（这其中包括了预定义的**string类型**。）

### 2.2 数值类型

#### 2.2.1 数值后缀

​	**后缀F和M是最有用的**，并应该在指定**float**或**decimal**字面量时使用

#### 2.2.2 整数运算溢出检查运算符

​	checked运算符的作用是：在运行时当**整数类型表达式**或语句**超过**相应类型的**算术限制时**不再默默地溢出，而是**抛出OverflowException**。对double、float、decimal无效。

​	在Visual Studio中，可以在“Advanced Build Settings”中设置）来默认使程序中所有表达式都进行算术溢出检查

#### 2.2.3 特殊的float和double值

| 特殊值 | double类型常量          | float类型常量          |
| ------ | ----------------------- | ---------------------- |
| NaN    | double.NaN              | float.Nan              |
| 正无穷 | double.PositiveInfinity | float.PositiveInfinity |
| 负无穷 | double.NegativeInfinity | float.NegativeInfinity |
| -0     | -0.0                    | -0.0f                  |

​	非零值除以零的结果是无穷大。

​	零除以零或无穷大减去无穷大的结果是NaN。

​	一个NaN的值永远也不等于其他的值，甚至不等于其他的NaN值。必须使用float.IsNaN或double.IsNaN方法来判断一个值是否为NaN。

### 2.3 布尔类型运算符

#### 2.3.1 条件运算符

​	不同于C和C++, &和|运算符在用于布尔表达式时执行布尔比较（**非短路计算**）。而&和|运算符仅在用于数值运算时才执行位运算。

```c#
bool A() { Console.WriteLine("A"); return false; }
bool B() { Console.WriteLine("B"); return true; }

A() & B();   // 输出：A 然后 B，结果 false
A() && B();  // 输出：A，结果 false（B 未被调用）
1 & 2; 		 //这个就是按位计算
```

### 2.4 字符串和字符

​	C#的char（System.Char类型的别名）类型表示一个Unicode字符并占用两个字节

#### 2.4.1 字符串类型

​	string类型是引用类型而不是值类型。但是它的相等运算符却遵守值类型的语义。

​	原意字符串字面量要加**@**前缀，它不支持转义字符。

### 2.5 数组

#### 2.5.1 默认数组元素初始化

​	创建数组时其元素总会用默认值初始化。类型的默认值是按位取0的内存表示的值。

​	数组元素的类型是值类型还是引用类型对其性能有重要的影响。**若元素类型是值类型，每个元素的值将作为数组的一部分进行分配**。若Point是类，创建数组则仅仅分配了1000个**空引用**。

### 2.6 变量和参数

#### 2.6.1 栈和堆

- 栈

  栈是存储局部变量和参数的内存块。

- 堆

​	堆是保存对象（例如引用类型的实例）的内存块。新创建的对象会分配在堆上并返回其引用。C#中无法像C++那样显式删除对象。未引用的对象最终将被垃圾回收器回收。

​	静态字段也会存储在堆上。与分配在堆上的对象（可以被垃圾回收）不同，这些变量一直存活直至应用程序域结束。

#### 2.6.2 明确赋值

​	C#强制执行明确赋值策略。实践中这意味着在unsafe上下文之外无法访问未初始化的内存。

明确赋值有三种含义：

- 局部变量在读取之前必须赋值。
- 调用方法时必须提供函数的实际参数（除非标记为可选参数）。
- 运行时将自动初始化其他变量（例如字段和数组元素）。

#### 2.6.3 默认值

​	所有类型的实例都有默认值。预定义类型的默认值是按位取0的内存表示的值。

| 类型               | 默认值 |
| ------------------ | ------ |
| 所有引用类型       | null   |
| 所有数字和枚举类型 | 0      |
| char类型           | '\0'   |
| bool类型           | false  |

​	default关键字可用于获得任意类型的默认值。

​	自定义值类型（例如struct）的默认值等同于每一个字段都取其默认值。

#### 2.6.4 参数

​	使用ref和out修饰符可以控制参数的传递方式。

| 参数修饰符 | 传递类型 | 必须明确赋值的变量 |
| ---------- | -------- | ------------------ |
| 无         | 值传递   | 传入               |
| ref        | 引用传递 | 传入               |
| out        | 引用传递 | 传出               |

- 值传递参数、ref传递

  默认情况下，C#中的**参数默认按值传递**。

```c#
class Foo { public int X; }

void Modify(Foo f) {
    f.X = 10;         // 修改对象的内部状态 => 调用方可见
}

void Reassign(Foo f) {
    f = new Foo { X = 20 }; // 只改变局部引用，调用方的引用不变
}

void ReassignRef(ref Foo f) {
    f = new Foo { X = 30 }; // 使用 ref，调用方的引用也会指向新对象
}
```

​	**类对象是引用（相当于是C++的指针，存储的是地址）**，按值传递的时候，把地址复制了一份，**修改对象的内部状态 => 调用方可见**。

​	**ref 传递（相当于加了一个C++的引用**，**指的的别名**）。加了ref之后，内部和外部相当于一个东西。

- out修饰符

​	out参数和ref参数类似，但在以下几点上不同：· 不需要在传入函数之前进行赋值。· 必须在函数结束之前赋值。out修饰符通常用于获得方法的多个返回值。

​	从C# 7开始，允许在调用含有out参数的方法时直接声明变量。

​	当调用含有多个out参数的方法时，若我们并非关注所有参数的值，那么可以使用下划线来“丢弃”那些不感兴趣的参数。（out_）

- 按引用传递的含义
  按引用传递参数是为现存变量的存储位置起了一个别名而不是创建一个新的存储位置。

-  params修饰符

​	**params参数修饰符**只能修饰方法中的最后一个参数，它能够**使方法接受任意数量的指定类型参数**。参数类型必须声明为数组。也**可以将普通的数组提供给params参数**。

```c#
static int Sum(params int[] numbers)
{
    int total = 0;
    foreach (var num in numbers)
    {
        total += num;
    }
    return total;
}
```

- 可选参数

  从C# 4.0开始，方法、构造器和索引器中都可以声明可选参数。只要在参数声明中提供默认值，这个参数就是可选参数。

​	可选参数的默认值必须由常量表达式或者无参数的值类型构造器指定，可选参数不能标记为ref或者out。

​	必填参数必须在可选参数方法声明和调用之前出现（params参数例外，它总是最后出现。

- 命名参数

  除了用位置确定参数外，还可以用名称来确定参数。

```c#
  private void Foo(int x, int y)
  {
      int z = x + y;
  }

 Foo(y: 1, x: 2);//命名参数
```

​	**命名参数在和可选参数混合使用时特别有效**.

```c#
 private static void Bar(int a = 0, int b = 0, int c = 0)
 {
     //...
 }
 Bar(c: 3);
```

### 2.7 表达式和运算符

​	**表达式本质上是值**。最简单的表达式是常量和变量。表达式能够用运算符进行转换和组合。运算符用一个或多个输入操作数来输出一个新的表达式

### 2.8 null运算符

#### 2.8.1 null合并运算符（??）

​	null合并运算符写作`??`。它的意思是“如果操作数不是null则结果为操作数，否则结果为一个默认的值.

```c#
 string? s = null;
 string s2 = s ?? "default"; //s不是null就按s的值，s为null就按??后面的来
```

#### 2.8.2 null条件运算符(?.)

​	当运算符的左侧为null的时候，该表达式的运算结果也是null而不会抛出异常。

### 2.9 语句

#### 2.9.1 带有模式的switch语句

​	每一个case子句都指定了一种需要匹配的类型和一个变量（模式变量），如果类型匹配成功就对变量赋值。和常量不同，对于类型的使用并没有任何限制。还可以使用when关键字对case进行预测。

```c#
private static void Test(object x)
{
    switch (x)
    {
        case int a:
            Console.WriteLine($"x = {x}");
            break;

        case string s:
            Console.WriteLine(s);
            break;

        case bool b when b == true:
            Console.WriteLine("asdasdas");
            break;
    }
}
```

## 3. 在C#中创建类型

### 3.1 类

​	在class关键字之前：类特性（Attribute）和类修饰符。非嵌套的类修饰符有：public、internal、abstract、sealed、static、unsafe和partial。

​	紧接YourClassName：泛型参数、唯一基类与多个接口。

​	在花括号内：类成员（方法、属性、索引器、事件、字段、构造器、重载运算符、嵌套类型和终结器）。

#### 3.1.1 字段

​	字段（field）是类或结构体中的变量成员。字段直接存储数据，没有 get 或 set 访问器。

```c#
class A
{
    string count;
}
```

- 字段初始化

​	字段不一定要初始化。没有初始化的字段均为默认值（0、\0、null、false）。字段初始化逻辑在构造器之前运行。

#### 3.1.2 方法

- 表达式体方法

  表达式体方法也可以用void作为返回类型。

```c#
private int Foo(int x) => x * 2;
private void Foo(string s) => Console.WriteLine(s);
```

- 按值传递和按引用传递

​	方法重载的时候，值传递和引用传递被认为是不同的。因此，Foo(int)和Foo(ref int)或Foo(out int)可以同时出现在一个类中。但Foo(ref int)和Foo(out int)不能同时出现在一个类中。

- 局部方法

​	C# 7允许在一个方法中定义另一个方法。

​	局部方法不能用static修饰。如果父方法是静态的，那么局部方法也是隐式静态的。

#### 3.1.3 实例构造器

​	构造器执行类或结构体的初始化代码。也就是C++中的构造函数。

- 重载构造器

  类或者结构体可以重载构造器。为了避免重复代码，**构造器可以用this关键字调用另一个构造器**。	

```c#
public class Wine
{
  public decimal Price;
  public int Year;

  public Wine(decimal price) => Price = price;

  public Wine(decimal price, int year) : this(price) => Year = year;
}
```

​	当构造器调用另一个构造器时，被调用的构造器先执行。还可以向另一个构造器传递表达式。

```c#
public Wine(decimal price, DateTime dateTime) : this(price, dateTime.Year)
{
}
```

-  隐式无参数构造器

​	C#编译器会自动为没有显式定义构造器的类生成无参数公有构造器。但是，一旦显式定义了至少一个构造器，系统就不再自动生成无参数的构造器。

- 构造器和字段的初始化顺序

​	字段的初始化按声明的先后顺序，在构造器之前执行。

- 非公有构造器

​	构造器不一定都是公有的。通常，定义非公有的构造器的原因是为了通过一个静态方法调用来控制类实例的创建。

```c#
public class Class1
{
    private Class1()//在 C# 中，类的成员（字段、属性、方法等）如果不指定访问修饰符，默认访问级别是 private。
    {
    }

    public static void Create()
    {
        //
    }
}
```

- 解构器

​	C# 7引入了解构器模式。解构器将字段反向赋值给若干变量。解构方法的名字必须为Deconstruct，并且拥有一个或多个out参数。

```c#
 public void Deconstruct(out decimal price, out int year)
 {
     price = Price;
     year = Year;
 }


  Wine wine = new Wine(50.0m, 1990);
  (decimal price, int year) = wine;	//解构器调用方法，或者直接调用也可以
```

#### 3.1.4 对象初始化器

```c#
dbItem = new Repository.Model.TbParameterModel()
{
    PartType = parameter.PartType,
    PointName = parameter.PointName
};//这种方式就叫对象初始化器。 

//等价于下面的写法
var tbParmModel = new TbParameterModel();
tbParmModel.PartType = parameter.PartType;
tbParmModel.PointName = parameter.PointName;
```

#### 3.1.5 属性

​	从外表看来，属性（Property）和字段很类似，但是属性内部像方法一样含有逻辑。属性比字段多出了get/set代码块。

​	尽管访问属性和字段的方式是相同的，但不同之处在于，属性在获取和设置值的时候给实现者提供了完全的控制能力。这种控制能力使实现者可以选择任意的内部表示形式，而无须将属性的内部细节暴露给用户。

​	**在实际应用中，为了提高封装性会更倾向于使用公有属性，而不是公有字段**

​	通常属性会用一个专门的后台字段来存储其所代表的数据，但属性也可以从其他数据计算得来。

- 表达式属性

```c#
  public decimal StdDown
  {
      get => 2.0 * StdValue;
      set => StdValue = value/2;
  }
```

- 自动属性(get;set;)

- 属性初始化器

  ```c#
  public DateTime? CreatedTime { get; set; } = DateTime.Now;
  ```

  因为这个是初始化器，所以可以设置只读属性的初始化值。

#### 3.1.6 索引器

- 索引器的实现

​	编写索引器首先要定义一个名为this的属性，并将参数定义放在一对方括号中。

```c#
public class Class1
{
    private string[] words = "hello world".Split();

    public string this[int wordnum]
    {
        get => words[wordnum];
        set => words[wordnum] = value;
    }
}

Class1 class1 = new Class1();
Console.WriteLine(class1[0]); // 输出 "hello"
```

​	一个类型可以定义多个参数类型不同的索引器，一个索引器也可以包含多个参数。例子里面是一个参数。

​	如果省略set访问器，则索引器就是只读的，并且可以使用C# 6的表达式语法来简化定义。

#### 3.1.7 常量

​	常量是一种值永远不会改变的静态字段。常量会在编译时静态赋值，编译器会在常量使用点上直接替换该值（类似于C++的宏）。

​	常量用关键字const声明，并且必须用值初始化。

​	常量在使用时比起static readonly字段有着更多的限制，不仅能够使用的类型有限，而且初始化字段的语句含义也不同。其他的不同之处还有常量是在编译时进行赋值的。

​	未来可能发生的变化的任何值从定义上都不是常量，因此不应当表示为常量。

#### 3.1.8 静态类

​	类可以标记为static，表明它必须只能够由static成员组成，并不能够派生子类。System.Console和System.Math类就是静态类的最好示例。

#### 3.1.9 终结器

​	终结器（Finalizer）是只能够在类中使用的方法。该方法在垃圾回收器回收未引用的对象占用的内存前调用。终结器的语法是类型的名称加上～前缀。类似于C++中的析构函数。

#### 3.1.10 分部类型和方法

​	分部类型（Partial type）允许一个类型分开进行定义，典型的做法是分开在多个文件中。

​	分部类型使用的常见场景是从其他源文件自动生成分部类（例如从Visual Studio模板或设计器），而这些类仍然需要额外手动编写方法。

```c#
partial class Class1   //partial是必须的 
{
    //....
}

partial class Class1
{
    //....
}
```

​	编译器并不保证分部类型声明中各个组成部分之间的字段初始化顺序。

​	分部类型可以包含分部方法（partial method）。这些方法能够令自动生成的分部类型为手动编写的代码提供自定义钩子（hook）。

​	分部方法由两部分组成：定义和实现。定义一般由代码生成器生成，而实现一般由手动编写。如果没有提供方法的实现，分部方法的定义会被编译器清除（调用它的代码部分也一样）。这样，自动生成的代码既可以提供钩子又不必担心代码过于臃肿。分部方法返回值类型必须是void，且默认是private的。

#### 3.1.11 nameof运算符

​	nameof运算符返回任意符号的字符串名称（类型、成员、变量等）。

```c#
int count = 3;
Console.WriteLine($"name = {nameof(count)}");
```

### 3.2 继承

​	类可以通过继承另一个类来对自身进行扩展或定制。继承类可以重用其所有功能而无须重新构建。**类只能继承自唯一的类，但是可以被多个类继承**，从而形成了类的层次。

​	注意：**C#不支持多继承。但可以实现多个接口**，达到类似于多继承的效果。

```c#
public class MyClass : BaseClass, IInterface1, IInterface2  // 继承一个类，实现多个接口
```

#### 3.2.1 多态

​	引用是多态的。意味着x类型的变量可以指向x子类的对象。（x类型变量在C#里面是引用类型，类似与C++里面的指针）。

​	**C# 的 ref 参数：类似于 C++ 的引用（&）。**

​	**C# 的引用类型：可以类比为 C++ 的指针**。

#### 3.2.2 类型转换和引用转换

​	对象引用可以：· 隐式向上转换为基类的引用；· 显式向下转换为子类的引用。

​	向上转换总是能够成功，而向下转换只有在对象的类型符合要求时才能成功。

```c#
//Asset是基类，Stock是子类
Stock msft = new Stock();
Asset a = msft;                          // Upcast
Stock s = (Stock)a;                      // Downcast
Console.WriteLine (s.SharesOwned);       // <No error>
Console.WriteLine (s == a);              // True
Console.WriteLine (s == msft);           // True
```

- as运算符

​	as运算符在向下类型转换出错时返回null（而不是抛出异常）。

```c#
Asset a = new Asset();
Stock s = a as Stock;        // s is null; no exception thrown
```

​	as运算符不能用来实现自定义转换（请参见4.14节），也不能用于数值的转换。

- is运算符

​	is运算符检查引用的转换是否能够成功。不能用于自定义类型转换和数值转换。

```c#
if (a is Stock s && s.SharesOwned > 100000)
  Console.WriteLine ("Wealthy");
else
  s = new Stock();    // s is in scope

Console.WriteLine (s.SharesOwned);  // Still in scope。 这个时候s仍然有效
```

#### 3.2.3 虚函数成员

​	方法、属性、索引器和事件都可以声明为virtual。

​	子类通过override修饰符重写虚方法。

#### 3.2.4 抽象类和抽象成员

​	声明为抽象（abstract）的类不能够实例化，只有抽象类的具体实现子类才能实例化。

​	抽象类中可以定义抽象成员，抽象成员和虚成员相似，只不过抽象成员不提供默认的实现。

​	**抽象和接口的区别**：接口压根不是类，抽象类是类。 一个类可以实现多个接口，但只能继承一个类。 抽象类是类，因此内部可以有实现，接口内部不写实现

#### 3.2.5 隐藏继承成员

​	基类和子类可能定义相同的成员，例如

```c#
public class A       { public int Counter = 1; }
public class B : A  { public new int Counter = 2; }
```

​	B的引用（在编译时）绑定到B.Counter有时需要故意隐藏一个成员。此时可以在子类的成员上中使用new修饰符。new修饰符仅用于阻止编译器发出警告。

​	C#在不同上下文中的new关键字拥有完全不同的含义。特别注意new运算符和new修饰符是不同的。

#### 3.2.6 密封函数和类

​	重写的函数成员可以使用**sealed**关键字密封其实现，**防止其他的子类再次重写**。

​	可以在类中使用sealed修饰符来密封整个类，这会隐式地密封类中所有的虚函数。密封类比密封函数成员更常见。

#### 3.2.7 base关键字

​	base关键字和this关键字很相似。

​	它有两个重要目的：· 从子类访问重写的基类函数成员· 调用基类的构造器

```c#
public class House : Asset
{
  ...
  public override decimal Liability => base.Liability + Mortgage;
}
```

#### 3.2.8 构造器和继承

​	子类必须声明自己的构造器。派生类可以访问基类的构造器，但是并非自动继承。

​	base关键字和this关键字很像，但base关键字调用的是基类的构造器。

​	基类的构造器总是先执行，这保证了基类的初始化发生在子类特定的初始化之前。

- 隐式调用基类的无参数构造器

​	如果子类的构造器省略base关键字，那么基类的无参数构造器将被隐式调用。

​	**无参构造器可以被自动继承，有参的就需要使用base**

- 构造器和字段初始化的顺序

✅ 静态优先（仅执行一次）：基类静态（字段→构造） → 子类静态（字段→构造）

✅ 实例随后（每次创建都执行）：基类实例字段 → 基类构造 → 子类实例字段 → 子类构造

#### 3.2.9 重载和解析

​	继承对方法的重载有着特殊的影响。以声明的类型为优先匹配。

```c#
static void Foo (Asset a) { }
static void Foo (House h) { }

Asset a = new House (...);
Foo(a);                          // Calls Foo(Asset)
```

​	如果把Asset类转换为dynamic（见第4章），则会在运行时决定调用哪个重载。这样就会基于对象的实际类型进行选择。

```c#
Asset a = new House (...);
Foo ((dynamic)a);    // Calls Foo(House)
```

### 3.3 object类型

​	object类型（System.Object）是所有类型的最终基类。任何类型都可以向上转换为object类型。

​	object是引用类型，承载了类的优点。尽管如此，int等值类型也可以和object类型相互转换并加入栈中。

#### 3.3.1 装箱和拆箱

​	装箱是将值类型实例转换为引用类型实例的行为。引用类型可以是object类或接口。

​	拆箱操作刚好相反，它把object类型转换成原始的值类型。拆箱需要显式类型转换。

​	**数组和泛型的变量只能支持引用转换，不能支持装箱转换。**

#### 3.3.2 GetType方法和typeof运算符

​	有两个基本方法可以获得System.Type对象：**在类型实例上调用GetType方法（运行时计算）**；**在类型名称上使用typeof运算符（编译时计算）**。

​	System.Type拥有诸多属性，例如类型的名称、程序集、基类型等属性。

​	System.Type同时还是运行时反射模型的访问入口。

### 3.4 结构体

​	结构体和类相似，不同之处在于：· **结构体是值类型，而类是引用类型**。· **结构体不支持继承**（除了隐式派生自object类型，或更精确地说，是派生自System. ValueType）。

​	结构体隐式包含一个无法重写的无参数构造器，将字段按位置为0

​	定义结构体的构造器时，必须显式为每一个字段赋值。

### 3.5 访问权限修饰符

​	与C++相同的是，有public、private、protected。

​	不同的是，C#增加了interal和protected interal。

​	interal：仅可以在程序集内访问，或供友元程序集访问。这是非嵌套类型的默认可访问性。

#### 3.5.1 友元程序集

​	在一些高级的场景中，添加System.Runtime.CompilerServices.InternalsVisibleTo程序集特性就可以将internal成员提供给其他的友元程序集访问。例如单元测试中。

```c#
[assembly: InternalsVisibleTo ("Friend")]
```

#### 3.5.2 可访问性封顶

​	  类型的可访问性是它内部声明成员可访问性的封顶。

#### 3.5.3 访问权限修饰符的限制

​	**当重写基类的函数时，重写函数的可访问性必须一致**。子类可以比基类的访问权限低，但不能比基类的访问权限高。

### 3.6 接口

​	接口和类相似，但接口只为成员提供定义而不提供实现。**接口的成员都是隐式抽象的**。相反，类可以包含抽象的成员和有具体实现的成员。

​	**一个类（或者结构体）可以实现多个接口。而一个类只能够继承一个类，结构体则完全不支持继承**（只能从System.ValueType派生。

​	**接口成员总是隐式public的**，并且不能用访问权限修饰符声明。

#### 3.6.1  扩展接口

​	接口可以从其他接口派生。

```c#
public interface IUndoable                { void Undo(); }
public interface IRedoable : IUndoable { void Redo(); }
```

​	IRedoable“继承”了IUndoable接口的所有成员。换言之，实现IRedoable的类型也必须实现IUndoable的成员。

#### 3.6.2 显式接口实现

​	当实现多个接口时，有时会出现成员签名的冲突。显式实现接口成员可以解决冲突。

```c#
public interface ITestInterface1
{
    void TestMethod();
}

public interface ITestInterface2
{
    void TestMethod();
}

public class TestClass : ITestInterface1, ITestInterface2
{
    void ITestInterface1.TestMethod()
    {
        // Implementation for ITestInterface1
    }

    void ITestInterface2.TestMethod()
    {
        // Implementation for ITestInterface2
    }
}
```

​	另一个使用显式实现接口成员的原因是隐藏那些高度定制化的或对类的正常使用干扰很大的接口成员。

#### 3.6.3  虚方法实现接口成员

​	默认情况下，隐式实现的接口成员是密封的。为了重写，必须在基类中将其标识为virtual或者abstract。

​	**显式实现的接口成员不能标识为virtual**，也不能实现通常意义的重写，但是它可以通过再次显式实现接口来提供新实现，这相当于“**重新实现**”。

​	virtual方法和abstract方法的区别：

​		**virtual方法：可以有自己的实现，子类可以不重写。**

​		**abstract方法：不能自己实现，子类必须重写。只能存在于abstract类中。**

​	另外：abstract类中的方法可以是抽象的（abstract）、虚拟的（virtual）、普通的。

#### 3.6.4 在子类中重新实现接口

​	继承（inheritance）**：类的继承是传递的**（transitive）。如果 A 继承 B，B 继承 C，那么 A 自动继承 C 的所有成员（字段、方法等）。继承关系可以一层层传递下去。

​	接口实现（interface implementation）：**接口实现不传递**。如果 A 实现接口 I，B 继承 A，那么 B 不会自动实现 I，除非 B 也显式声明实现 I。

### 3.7 枚举类型

​	枚举类型是一种特殊的值类型，可以在枚举类型中定义一组命名的数值常量。

​	编译器还支持显式指定部分枚举成员。没有指定的枚举成员，在最后一个显式指定的值基础上递增。

#### 3.7.1 枚举类型转换

​	枚举类型的实例可以与它对应的整数值相互显式转换。

​	在枚举表达式中，编译器会特殊对待数值字面量0。它不需要进行显式转换。

​	对0进行特殊对待的原因有两个：· 第一个枚举成员经常作为默认值。· 在合并枚举类型中，0表示无标志。

#### 3.7.2 标志枚举类型

​	枚举类型的成员可以合并。为了避免混淆，合并枚举类型的成员要显式指定值，典型的值为2的幂次。

```c#
[Flags]
public enum BorderSides
{
  None=0,
  Left=1, Right=2, Top=4, Bottom=8,
  LeftRight = Left | Right,
  TopBottom = Top  | Bottom,
  All        = LeftRight | TopBottom
}
```

#### 3.7.3 枚举运算符

```c#
=    ==    ! =    <    >     <=    > =    +    -    ^  &  |    ～
+=    -=    ++  --    sizeof
```

​	位运算符、算术运算符和比较运算符都返回对应整数值的运算结果。枚举类型和整数类型之间可以做加法，但两个枚举类型之间不能做加法

### 3.8 嵌套类型

​	嵌套类型（nested type）是声明在另一个类型内部的类型。

```c#
public class TopLevel
  {
    public class Nested { }                  // Nested class  嵌套类型
    public enum Color { Red, Blue, Tan }     // Nested enum   嵌套类型
  }
```

​	从外层类以外访问嵌套类型，需要使用外层类名称进行限定（就像访问静态成员一样）。

```
TopLevel.Color color = TopLevel.Color.Red;
```

​	使用嵌套类型的原因应当是利用它较强的访问控制能力，或者是因为嵌套的类型必须访问外层类型的私有成员。

### 3.9 泛型

​	 C#的泛型和C++的模板是相似的概念，但它们的工作方法不同。

#### 3.9.1 泛型类型

​	泛型类型中声明的类型参数（占位符类型）需要由泛型类型的消费者（即提供类型参数的一方）填充。

```c#
public class Stack<T> 
{
  int position;
  T[] data = new T[100];
  public void Push (T obj)  => data[position++] = obj;
  public T Pop()            => data[--position];
}

var stack = new Stack<int> ();
stack.Push (5);
stack.Push (10);
int x = stack.Pop();          // x is 10
int y = stack.Pop();          // y is 5
```

​	技术上，我们称Stack<T>是开放类型，称Stack<int>是封闭类型。

#### 3.9.2 泛型方法

​	泛型方法在方法的签名中声明类型参数。

```c#
static void Swap<T>  (ref T a, ref T b)
{
  T temp = a;
  a = b;
  b = temp;
}
```

​	通常**调用泛型方法不需要提供类型参数**。如果有二义性，则可以用下面的方式调用泛型方法

```c#
Swap<int>  (ref x, ref y);
```

#### 3.9.3 声明类型参数

​	可以在声明类、结构体、接口、委托（见第4章）和方法时引入类型参数（用尖括号标出）。其他的结构，如属性，虽不能引入类型参数，但可以使用类型参数。

​	习惯上，如果泛型类型和泛型方法只有一个类型参数，且参数的含义明确，那么一般将其命名为T。当使用多个类型参数时，每一个类型参数都使用T作为前缀，后面跟一个更具描述性的名称。

#### 3.9.4 泛型的默认值

​	default关键字可用于获取泛型类型参数的默认值。引用类型的默认值为null，而值类型的默认值是将值类型的所有字段按位设置为0的值。

#### 3.9.5 泛型的约束

​	默认情况下，类型参数可以由任何类型来替换。在类型参数上应用约束，可以将类型参数定义为指定的类型参数。

```c#
where T : base-class    // Base-class constraint
where T : interface     // Interface constraint
where T : class         // Reference-type constraint
where T : struct        // Value-type constraint (excludes Nullable types)
where T : new()         // Parameterless constructor constraint
where U : T             // Naked type constraint
```

#### 3.9.6 继承泛型类型

​	泛型类和非泛型类一样都可以派生子类。并且子类中仍可以令基类中类型参数保持开放。

```c#
class Stack<T>                        {...}
class SpecialStack<T>  : Stack<T>  {...}
```

​	子类也可以用具体的类型来封闭泛型参数。子类型还可以引入新的类型参数。

#### 3.9.7 自引用泛型声明

​	一个类型可以使用自身类型作为具体类型来封闭类型参数。

```c#
public interface IEquatable<T>  { bool Equals (T obj); }

public class Balloon : IEquatable<Balloon>
{
  public string Color { get; set; }
  public int CC { get; set; }
  public bool Equals (Balloon b)
  {
    if (b == null) return false;
    return b.Color == Color && b.CC == CC;
  }
}
```

#### 3.9.8 静态数据

​	静态数据对于每一个封闭的类型来说都是唯一的。（不同的封闭类型，那当然是不同的）

```c#
public class A<T>
{
    private int Foo<T>(T x) => (int)(object)x;      //常见做法，先转成object再转成想要的类型
}
```

#### 3.9.9 协变

​	假定A可以转换为B，如果X<A>可以转换为X<B>那么称X有一个协变类型参数。

​	 由于C#有协变（covariance）和逆变（contravariance）的概念，所以“**可转换”意味着可以通过隐式引用转换进行类型转换**，例如，A是B的子类或者A实现B。而数值转换、装箱转换和自定义转换是不包含在内的。

- 可变性不是自动的

​	为了保证静态类的安全性，泛型类型参数不是自动协变的。

```
Stack<Bear>  bears = new Stack<Bear> ();
Stack<Animal>  animals = bears;              // Compile-time error，编译报错，不能自动协变，即使Bear继承自Animal
```

- 数组

​	由于历史原因，数组类型支持协变。这说明如果B是A的子类，则B[]可以转换为A[]（A和B都是引用类型）。

- 声明协变类型参数

​	C# 4.0中，**在接口和委托的类型参数上指定out修饰符可将其声明为协变参数**。和数组不同，这个修饰符保证了协变类型参数是完全类型安全的。

```c#
public interface IPoppable<out T>  { T Pop(); }//加个out指定为协变参数

var bears = new Stack<Bear> ();
bears.Push (new Bear());
// Bears implements IPoppable<Bear> . We can convert to IPoppable<Animal> :
IPoppable<Animal>  animals = bears;   // Legal
Animal a = animals.Pop();
```

​	接口中的协变或逆变都是常见的，在接口中同时支持协变和逆变是很少见的。

​	不管是类型参数还是数组，**协变（和逆变）仅仅对于引用转换有效**，而对装箱转换无效

#### 3.9.10 逆变

​	如果X<A>允许引用类型转换为X<B>，则类型X具有协变类型参数。而逆变的转换方向正好相反，即从X<B>转换到X<A>。它仅在类型参数出现在输入位置上，并用**in修饰符标记**才行得通

​	**实现协变**：允许泛型的引用类型在运行过程中**向上转换**（指的是变成成基类），且该泛型类型只能用于返回处。`基类引用 = 子类引用;// 泛型上下文，协变后（加out修饰符），赋值操作合法`

​	**实现逆变**：允许泛型的引用类型在运行过程中**向下转换**（指的是变成子类），且该泛型类型只能用于输入处。`子类引用 = 基类引用;// 泛型上下文，逆变后（加in修饰符），赋值操作合法`

​	默认情况下是不变的。**泛型的子类引用不能变成基类引用，基类引用也不能变成子类引用**。注意：在没有泛型的时候，子类引用可以变成基类引用。

​	没有泛型时：SubClass 可以直接赋值给 BaseClass（多态性），因为 SubClass 是 BaseClass 的子类。

​	有泛型时，默认不变：Generic<SubClass> 不能赋值给 Generic<BaseClass>，即使 SubClass 继承 BaseClass。

​	以上均指引用类型之间的转换，不包括拆箱与装箱。

#### 3.9.11 C#泛型和C++模板对比

​	C#的泛型和C++的模板在应用上很相似，但是它们的工作原理却大不相同。两者都发生了生产者和消费者的关联，且生产者的占位符将被消费者填充。但是在**C#泛型**中，**生产者的类型（开放类型如List<T> ）可以编译到程序库中（如mscorlib.dll）。这是因为生产者和消费者进行关联生成封闭类型是在运行时发生的**。而**C++模板中，这一关联是在编译时进行的**。这意味着C++不能将模板库部署为．dll，它们只存在于源代码中。这令动态语法检查难以实现，更不用说即时创建或参数化类型了。

## 4. C#的高级特性

### 4.1 委托

​	委托（delegate）是一种知道如何调用方法的对象。它定义了方法的返回类型和参数类型。

```c#
delegate int Transformer (int x);

class Test
{
  static void Main()
  {
    Transformer t = Square;             // Create delegate instance
    //或者这么写     Transformer t = new Transformer (Square);
    int result = t(3);                  // Invoke delegate
    Console.WriteLine (result);         // 9
  }
  static int Square (int x) => x * x;
}
```

​	Transformer兼容任何返回类型为int并有一个int类型的参数的方法。

​	调用者调用委托，而委托调用目标方法。这种间接调用方式可以将调用者和目标方法解耦。

​	委托和回调（callback）类似。一般指捕获类似C函数指针的结构。

#### 4.1.1 用委托书写插件方法

​	委托变量可以在运行时指定一个目标方法，这个特性可用于编写插件方法。

```c#
public delegate int Transformer (int x);

class Util
{
  public static void Transform (int[] values, Transformer t)
  {
    for (int i = 0; i < values.Length; i++)
      values[i] = t (values[i]);
  }
}

class Test
{
  static void Main()
  {
    int[] values = { 1, 2, 3 };
    Util.Transform (values, Square);   // Hook in the Square method
    foreach (int i in values)
      Console.Write (i + "  ");        // 1    4    9
  }

  static int Square (int x) => x * x;
}
```

#### 4.1.2 多播委托

​	所有的委托实例都拥有多播能力。这意味着一个委托实例可以引用一个目标方法，也可以引用一组目标方法。**委托可以使用+和+=运算符联结多个委托实例。**

```c#
SomeDelegate d = SomeMethod1;
d += SomeMethod2;
```

​	委托会按照添加的顺序依次触发。

​	委托是不可变的，因此调用+=和-=的实质是创建一个新的委托实例，并把它赋值给已有变量。

​	如果一个多播委托拥有非void的返回类型，则调用者将从最后一个触发的方法接收返回值。前面的方法仍然调用，但是返回值都会被丢弃。大部分调用多播委托的情况都会返回void类型。

```c#
public delegate void ProgressReporter(int percentComplete);

public class Util
{
    public static void HardWork(ProgressReporter p)
    {
        for (int i = 0; i < 10; i++)
        {
            p(i * 10);                                // Invoke delegate
            System.Threading.Thread.Sleep(100);       // Simulate hard work
        }
    }
}

internal class Test
{
    private static void Main()
    {
        ProgressReporter p = WriteProgressToConsole;
        p += WriteProgressToFile;
        Util.HardWork(p);
    }

    private static void WriteProgressToConsole(int percentComplete)
      => Console.WriteLine(percentComplete);

    private static void WriteProgressToFile(int percentComplete)
      => System.IO.File.WriteAllText("progress.txt",
                                          percentComplete.ToString());
}
```

#### 4.1.3 实例目标方法和静态目标方法

​	当你将一个实例方法（非静态方法）赋值给委托对象时，委托不仅保存方法的引用（即方法在内存中的地址），还需要保存该方法所属的实例对象的引用。

#### 4.1.4 泛型委托类型	

​	委托类型可以包含泛型类型参数。

```c#
public delegate T Transformer<T>  (T arg);

public class Util
{
  public static void Transform<T>  (T[] values, Transformer<T>  t)
  {
    for (int i = 0; i < values.Length; i++)
      values[i] = t (values[i]);
  }
}

class Test
{
  static void Main()
  {
    int[] values = { 1, 2, 3 };
    Util.Transform (values, Square);       // Hook in Square
    foreach (int i in values)
      Console.Write (i + "  ");             // 1    4    9
  }
  static int Square (int x) => x * x;
}
```

#### 4.1.5 Func和Action委托

​	System命名空间下系统已经定义好了一些泛型委托Func和Action委托。

​	**Func是有返回值的委托。Action是无返回值的委托。**

```c#
// 以下三种写法效果是一样的

//1.自定义委托
public delegate void ABCD(string message, int a);
ABCD aBCD = PrintMessage;

//2.使用Action或Func
private static Action<string, int> action = PrintMessage;
									//1和2两种写法都需要自定义PrintMessage函数

//3.使用Action或Func + lambda。 更推荐使用这种方法。
private static Action<string,int> action = (message,a) => Console.WriteLine(message+a);
```

#### 4.1.6 委托和接口

​	能用委托解决的问题，都可以用接口解决。如果以下一个或多个条件成立，委托可能是比接口更好的选择：· 接口内仅定义了一个方法· 需要多播能力· 订阅者需要多次实现接口。

#### 4.1.7 委托的兼容性

- 类型的兼容性

​	即使签名相似，委托类型也互不兼容。

- 参数的兼容性

​	委托也可以有比它的目标方法参数类型更具体的参数类型，这称为逆变。

- 返回类型的兼容性

​	委托的目标方法可能返回比委托声明的返回值类型更加特定的返回值类型，这称为协变。

```c#
delegate object ObjectRetriever(); //声明更基础，称为协变

class Test
{
  static void Main()
  {
    ObjectRetriever o = new ObjectRetriever (RetrieveString);
    object result = o();
    Console.WriteLine (result);       // hello
  }
  static string RetrieveString() => "hello";
}
```

- 泛型委托类型的参数协变

​	定义一个泛型委托类型，参考如下的准则。

​	**将只用于返回值类型的类型参数标记为协变（out）。**

​	**将只用于参数的任意类型参数标记为逆变（in）**。

```c#
internal class Test
{
    private static void Main()
    {
        action = action2;//一个逆变的例子
    }

    private static Action<string> action = (message) => Console.WriteLine(message);

    private static Action<object> action2 = (message) => 						Console.WriteLine(message.ToString());
}
```

​	**协变和逆变主要在泛型上下文中才有意义**。基本的继承，不属于泛型上下文，谈不上协变和逆变。

### 4.2 事件

​	事件是一种使用有限的委托功能实现广播者/订阅者模型的结构。使用事件的主要目的在于保证订阅者之间不互相影响。

​	声明事件最简单的方法是在委托成员的前面加上event关键字。

```c#
public delegate void PriceChangedHandler (decimal oldPrice,
                                            decimal newPrice);
public class Stock
{
  string symbol;
  decimal price;

  public Stock (string symbol) { this.symbol = symbol; }

  public event PriceChangedHandler PriceChanged;

    public decimal Price
  {
    get { return price; }
    set
    {
      if (price == value) return;       // Exit if nothing has changed
      decimal oldPrice = price;
      price = value;
      if (PriceChanged != null)             // If invocation list not
        PriceChanged (oldPrice, price);      // empty, fire event.
    }
  }
}
```

​	本例中，如果将event关键字去掉，PriceChanged就变成了普通的委托字段。有几个坏处：**委托支持直接赋值**，所以以前+=的订阅者可能会被覆盖掉（**而事件只支持+=，不支持=**）；PriceChanged可能会被直接置为null；**委托可能会被手动调用来广播，模拟触发（事件不能直接手动调用）**。

#### 4.2.1 标准事件模式

```c#
using System;

public class PriceChangedEventArgs : EventArgs //EventArgs是为事件传递信息的基类
{
  public readonly decimal LastPrice;
  public readonly decimal NewPrice;
  public PriceChangedEventArgs (decimal lastPrice, decimal newPrice)
  {
    LastPrice = lastPrice; NewPrice = newPrice;
  }
}

public class Stock
{
  string symbol;
  decimal price;

  public Stock (string symbol) {this.symbol = symbol; }

    //EventHandler就帮我们定义了委托，不需要再写 public delegate void PriceChangedHandler 				(decimal oldPrice,decimal newPrice);
  public event EventHandler<PriceChangedEventArgs>  PriceChanged;

  protected virtual void OnPriceChanged (PriceChangedEventArgs e)
  {
    PriceChanged? .Invoke (this, e);
  }

  public decimal Price
  {
    get { return price; }
    set
    {
      if (price == value) return;
      decimal oldPrice = price;
      price = value;
      OnPriceChanged (new PriceChangedEventArgs (oldPrice, price));
    }
  }
}

class Test
{
  static void Main()
  {
    Stock stock = new Stock ("THPW");
    stock.Price = 27.10M;
    // Register with the PriceChanged event
    stock.PriceChanged += stock_PriceChanged;
    stock.Price = 31.59M;
  }

  static void stock_PriceChanged (object sender, PriceChangedEventArgs e)
  {
    if ((e.NewPrice - e.LastPrice) / e.LastPrice > 0.1M)
      Console.WriteLine ("Alert, 10% stock price increase! ");
  }
}
```

​	对于事件来说，一般更推荐使用EventArgs的子类来传递信息。

​	EventHandler还有无泛型版本，一般只用于：不传递自定义参数，只传递事件触发信号。

#### 4.2.2 事件的修饰符

​	和方法类似，事件可以是虚的（virtual）、可以重写（overridden）、可以是抽象的（abstract）或者密封的（sealed），当然也可以是静态的。

### 4.3 Lambda表达式

​	Lambda表达式是一种可以替代委托实例的匿名方法。

#### 4.3.1 显式指定Lambda参数的类型

​	编译器通常可以根据上下文推断出Lambda表达式的类型，但是当无法推断的时候则必须显式指定每一个参数的类型。

```c#
//下面三种写法效果相同
Bar ((int x) => Foo (x));

Bar<int>  (x =>  Foo (x));     // Specify type parameter for Bar

Bar<int>  (Foo);              // As above, but with method group
```

#### 4.3.2 捕获外部变量

​	Lambda表达式可以引用方法内定义的局部变量和方法的参数。

​	捕获的变量会在真正调用委托时赋值，而不是在捕获时赋值。

​	**Lambda表达式**也可以更新捕获的变量的值。**效果相当于隐式的ref传参**

```c#
int seed = 0;
Func<int>  natural = () =>  seed++;
Console.WriteLine (natural());             // 0
Console.WriteLine (natural());             // 1
Console.WriteLine (seed);                   // 2
```

​	**当捕获for循环的迭代变量时，C#会认为该变量是在循环体外定义的**。而这意味着同一次变量在每一次迭代都被捕获了，因此程序输出333而非012。lambda表达式捕获变量 i 的引用，而不是值。循环结束后 i 为 3，所有lambda都输出 3。

```c#
Action[] actions = new Action[3];

for (int i = 0; i < 3; i++)
    actions[i] = () => Console.Write(i);

foreach (Action a in actions) a();      // 333
```

#### 4.3.3 Lambda表达式和局部方法的对比

​	C# 7中的局部方法（请参见1.8.1.4节）和Lambda表达式的相应功能是重叠的，而局部方法拥有以下三个优势。· 局部方法无须使用奇怪的技巧就可以实现递归（调用自己）。· 局部方法避免了定义杂乱的委托类型。· 局部方法的开销更小。

​	局部方法更加高效，因为它不需要间接使用委托。换言之，当间接使用到委托的时候，Lambda表达式通常会显得更加简洁和清晰。

### 4.4 匿名方法

​	匿名方法类似于Lambda表达式，但是没有以下的特性：· 隐式类型的参数；· 表达式语法（匿名方法必须是一个语句块）；· 在赋值给Expression<T>时将其编译为表达式树的能力。

​	匿名方法的写法是在delegate关键字后面跟上参数的声明（可选)。

```c#
//匿名方法写法
Transformer sqr = delegate (int x) {return x * x; };

//lambda写法，效果相同
Transformer sqr = (int x) => {return x * x; };
//或者
Transformer sqr = x  => x * x;
```

​	匿名方法和Lambda表达式捕获外部变量的方式是完全一样的。就是隐式的ref捕获。

### 4.5 try语句和异常

​	try语句是为了处理错误或者执行清理代码而定义的语句块。try语句块后面必须跟catch语句块或者finally语句块，或者两者都有。

#### 4.5.1 catch子句

​	catch子句定义捕获哪些类型的异常，这些异常应当是System.Exception或者其子类。

​	从C# 6.0开始，可以在catch子句中添加when子句来指定异常筛选器。

```c#
catch (WebException ex) when (ex.Status == WebExceptionStatus.Timeout)
{
  ...
}
```

#### 4.5.2 finally块

​	无论代码是否抛出异常，也无论try程序块是否完全执行，finally程序块总会执行。**通常，finally块用于执行清理工作**。

​	using语句提供了一种在finally块中调用IDisposable接口对象的Dispose方法的优雅方式。

```c#
//下面两种写法等价
using (StreamReader reader = File.OpenText ("file.txt"))
{
  ...
}

{
  StreamReader reader = File.OpenText ("file.txt");
  try
  {
    ...
  }
  finally
  {
    if (reader ! = null)
      ((IDisposable)reader).Dispose();
  }
}
```

#### 4.5.3 抛出异常

-  throw表达式（C# 7)

​	在C# 7之前，throw永远是一个语句，而现在它也可以以表达式的形式出现在表达式函数中。

```c#
public string Foo() => throw new NotImplementedException();
```

-  重新抛出异常

```c#
try {  ...  }
catch (Exception ex)
{
  // Log error
  ...
  throw;            // Rethrow same exception
}
```

​	重新抛出异常可用于需要记录错误但是并不将异常隐藏的情形，也可以在异常超出处理范围的情况下放弃对异常进行处理。

#### 4.5.4 System.Exception的关键属性

​	System.Exception类的最重要的属性有下面几个：

- StackTrace：表示一个异常从起源到catch块的所有调用方法的字符串。

- Message：描述异常的字符串。

- InnerException：导致外部异常的内部异常（如果有的话）。而内部异常本身也可以有另外一个InnerException。

  所有的C#异常都是运行时异常，没有和Java对等的编译时检查异常

### 4.6 可枚举类型和迭代器

#### 4.6.1 可枚举类型

​	枚举器（Enumerator）是一个只读的且只能在值序列上前移的游标。枚举器实现下面的接口之一：· System.Collections.IEnumerator· System.Collections.Generic.IEnumerator<T>。

#### 4.6.2 集合的初始化器

```c#
using System.Collections.Generic;
//1.List初始化方式
List<int>  list = new List<int>  {1, 2, 3};

//2.字典类型的两种初始化方式，不能混用
var dict = new Dictionary<int, string> ()
{
  { 5, "five" },
  { 10, "ten" }
};

var dict = new Dictionary<int, string> ()
{
  [3] = "three",
  [10] = "ten"
};
```

#### 4.6.3 迭代器

​	迭代器（iterator）是指使用 yield return 或 yield break 的方法、属性或者索引器，它返回 IEnumerable<T> 或 IEnumerator<T>，允许逐个生成序列元素，实现延迟求值。

```c#
class Test
{
    static void Main()
    {
        foreach (int fib in Fibs(6))
            Console.Write (fib + "  ");
    }
    static IEnumerable<int>  Fibs (int fibCount)
    {
        for (int i = 0, prevFib = 1, curFib = 1; i < fibCount; i++)
        {
            yield return prevFib;  //每一遍的for，都会往IEnumerable<int>里面生产一个新的元素
            int newFib = prevFib+curFib;
            prevFib = curFib;
            curFib = newFib;
        }
    }
}
```

​	迭代器适合大数据或动态生成场景。

#### 4.6.4 迭代器语义

- yield break语句

​	yield break语句表明迭代器块不再返回更多的元素而是提前退出。

​	迭代器语句块中使用return语句是非法的，应当使用yield break。

- 迭代器和try/catch/finally语句块

​	yield return语句不能出现在带catch子句的try语句块中，yield return语句也不能出现在catch或者finally语句块中。但是可以在只带有finally块的try语句块中使用yield语句。

#### 4.6.5 组合序列

​	迭代器有高度可组合性。

```c#
using System;
using System.Collections.Generic;

class Test
{
  static void Main()
  {
    foreach (int fib in EvenNumbersOnly (Fibs(6)))
      Console.WriteLine (fib);
  }
  static IEnumerable<int>  Fibs (int fibCount)
  {
    for (int i = 0, prevFib = 1, curFib = 1; i < fibCount; i++)
    {
      yield return prevFib;
      int newFib = prevFib+curFib;
      prevFib = curFib;
      curFib = newFib;
    }
  }

  //只输出偶数斐波那契数列：
  static IEnumerable<int>  EvenNumbersOnly (IEnumerable<int>  sequence)
  {
    foreach (int x in sequence)
      if ((x % 2) == 0)
        yield return x;
  }
}
```

### 4.7 可空类型

​	可空类型是由数据类型后加一个“? ”。表示可以为null。**T？的默认值为null。**

#### 4.7.1 Nullable<T>结构体

​	T？会翻译为System.Nullable<T>，二者等价。

#### 4.7.2 隐式和显式的可空对象转换

​	**从T到T？的转换是隐式的而反之则是显式的**。显式强制转换与直接调用可空对象的Value属性实质上是等价的。

#### 4.7.3 装箱拆箱可空值

​	如果T？是装箱的，那么堆中的装箱值包含的是T，而不是T?。这种优化方式是可行的，因为装箱值已经是一个可以赋值为null的引用类型了。

​	C#允许通过as运算符对一个可空类型进行拆箱。如果强制转换出错，那么结果为null

```c#
object o = "string";
int? x = o as int? ;
Console.WriteLine (x.HasValue);    // False
```

#### 4.7.4 运算符优先级提升

​	混合使用可空或不可空类型是可行的，这是因为T与T？之间存在着隐式转换机制。

```c#
int? a = null;
int b = 2;
int? c = a + b;    // c is null - equivalent to a + (int? )b
```

#### 4.7.5 在bool？上使用&和|运算符

​	这是可空布尔值（bool?）的三值逻辑运算。null 表示未知，运算遵循三值逻辑规则。
​	|（或）：如果任一操作数为 true，结果为 true；如果都为 false 或 null，结果为 null（未知）。
​	&（与）：如果任一操作数为 false，结果为 false；如果都为 true，结果为 true；否则 null（未知）。

```c#
bool? n = null;
bool? f = false;
bool? t = true;
Console.WriteLine (n | n);     // (null)
Console.WriteLine (n | f);     // (null)
Console.WriteLine (n | t);     // True
Console.WriteLine (n & n);     // (null)
Console.WriteLine (n & f);     // False
Console.WriteLine (n & t);     // (null)
```

### 4.8 扩展方法

​	扩展方法允许在现有类型上扩展新的方法而无须修改原始类型的定义。**扩展方法是静态类的静态方法，而其中的第一个参数需要用this修饰符修饰，且第一个参数的类型就是需要扩展的类型。**

```c#
public static class StringExtensions
{
    //第一个参数this string 标识了是要扩展string
    public static bool IsNullOrEmpty(this string str)
    {
        return string.IsNullOrEmpty(str);
    }
}

// 使用
string s = null;
bool result = s.IsNullOrEmpty();  // 看起来像实例方法
```

#### 4.8.1 扩展方法链

```c#
public static class StringHelper
{
  public static string Pluralize (this string s) {...}
  public static string Capitalize (this string s) {...}
}

//使用扩展方法链的方式调用 
string x = "sausage".Pluralize().Capitalize();  
```

#### 4.8.2 二义性与解析

- 命名空间


​	只有包含扩展方法的类在作用域内时（一般通过导入其所在的命名空间）我们才能够访问扩展方法。

- 扩展方法与实例方法


​	**任何兼容的实例方法的优先级总是高于扩展方法。**

-  扩展方法与扩展方法


​	如果两个扩展方法签名相同，则扩展方法必须作为一个普通的静态方法调用才能进行区分。当然，如果其中一个扩展方法具有更具体的参数，那么更具体参数的方法优先级更高。

### 4.9 匿名类型

​	匿名类型是一个由编译器临时创建来存储一组值的简单类。如果需要创建一个匿名类型，则可以使用new关键字，后面加上对象初始化器，指定该类型包含的属性和值。

```c#
var dude = new { Name = "Bob", Age = 23 };
```

​	在同一个程序集内声明的两个匿名类型实例，如果它们的元素名称和类型是相同的，那么它们在内部就是相同的类型。匿名类型重写了Equals方法方法从而能够执行比较运算。

​	匿名类型主要用于编写LINQ查询。

### 4.10 元组（C# 7）

​	和匿名类型一样，元组（tuple）也是存储一组值的便捷方式。元**组的主要目的是不使用out参数而从方法中返回多个值**（这是匿名类型做不到的）。

​	C# 7的元组几乎可以做到匿名类型做到的任何事情，甚至更多。而它的**缺点**之一**是命名元素的运行时类型擦除**，我们接下来会进行介绍。

```c#
var bob = ("Bob", 23);    // Allow compiler to infer the element types

Console.WriteLine (bob.Item1);    // Bob
Console.WriteLine (bob.Item2);    // 23
```

​	**元组是值类型**，并且它是可变（可读可写）的元素

​	和匿名类型不同，我们可以将每一个元素的类型列在括号中，来显式指定元组的类型。

```c#
(string, int) bob  = ("Bob", 23);   // var is not compulsory with tuples!
```

​	元组和泛型配合默契，泛型中可以使用元组。

```c#
Task<(string, int)>
Dictionary<(string, int), Uri>
IEnumerable<(int ID, string Name)>     // See below for naming elements
```

#### 4.10.1 元组元素命名

```c#
//第一种命名方式
var tuple = (Name:"Bob", Age:23);
Console.WriteLine (tuple.Name);      // Bob
Console.WriteLine (tuple.Age);       // 23

//第二种命名方式     
static (string Name, int Age) GetPerson() => ("Bob", 23);   
```

### 4.11 特性

​	特性（Attribute）是一种将自定义信息添加到代码元素（程序集、类型、成员、返回值、参数和泛型类型参数）的扩展机制。

#### 4.11.1 特性类

​	特性是通过直接或者间接继承抽象类System.Attribute的方式定义的。按照惯例，所有特性类型都以Attribute结尾。C#能够识别这个后缀并允许在为成员附加特性时忽略该后缀

#### 4.11.2 命名和位置特性参数

```c#
[XmlElement ("Customer", Namespace="http://oreilly.com")]
public class CustomerEntity { ... }
```

​	特性参数分为两类：位置参数和命名参数。在前一个例子中，第一个参数是命名参数，第二个参数是位置参数。位置参数对应于特性类型的公有构造器的参数；命名参数则对应于该特性类型的公有字段或者公有属性。

#### 4.11.3 特性的目标

​	在不显式指定的情况下，特性的目标就是它后面紧跟的代码元素，并且一般是类型或者类型的成员。然而，也可以将特性附加在程序集上。这就要求显式指定特性的目标了。

#### 4.11.4 指定多个特性

​	一个代码元素可以指定多个特性。特性可以列在同一对方括号中（用逗号分隔），或者分隔在多对方括号中，当然也可以是两种形式的结合。

### 4.12 调用者信息特性

​	从C# 5开始，可以在可选参数上添加三种调用者信息中的一种，它们可以让编译器从调用者源代码获取参数的默认值。

-  [CallerMemberName]：表示调用者的成员名称

-  [CallerFilePath]：表示调用者的源代码文件的路径

- [CallerLineNumber]：表示调用者源代码文件的行号

```c#
using System;
using System.Runtime.CompilerServices;

class Program
{
  static void Main() => Foo();
  static void Foo (
    [CallerMemberName] string memberName = null,
    [CallerFilePath] string filePath = null,
    [CallerLineNumber] int lineNumber = 0)
  {
    Console.WriteLine (memberName);
    Console.WriteLine (filePath);
    Console.WriteLine (lineNumber);
  }
}

//假设我们的程序位于c:\source\test\Program.cs。则输出结果是：
Main
c:\source\test\Program.cs
6
```

### 4.13 动态绑定

​	动态绑定将绑定（binding）（即解析类型、成员和操作的过程）从编译时延迟到运行时。

```c#
dynamic d = ...
d.Quack();
```

​	dynamic类型类似于object，即一种同样不具备描述性的类型。但区别是动态类型能够在编译时在不知道它存在的情况下使用它。动态对象是基于其运行时类型而非它的编译时类型进行绑定的。

### 4.14 运算符重载

​	运算符可以通过重载以更自然的语法操作自定义类型。运算符重载最适合实现那种表示基元数据类型的结构体。例如：自定义的数值类型。

```c#
public struct Note
{
  int value;
  public Note (int semitonesFromA) { value = semitonesFromA; }
  public static Note operator + (Note x, int semitones)
  {
    return new Note (x.value + semitones);
  }
}
```

### 4.15 预处理指令

​	预处理指令向编译器提供关于一段代码的附加信息。最常用的预处理指令是条件指令，它提供了一种控制某一块代码编译与否的方法

```c#
#define DEBUG
class MyClass
{
  int x;
  void Foo()
  {
    #if DEBUG
    Console.WriteLine ("Testing: x = {0}", x);
    #endif
  }
  ...
}
```

## 5. 框架基础

### 5.1 字符串与文本处理

#### 5.1.1 字符

​	一个char字符占用16个二进制位，这足以表示基本多文种平面（Basic Multilingual Plane）中的所有Unicode字符。

#### 5.1.2 字符串

​	C#中的string（== System.String）是一个不可变的（不可修改）的字符序列。

- 字符串内搜索

​	在字符串内执行搜索的最简单方法是StartsWith、EndsWith和Contains，这些方法均返回true或false。

​	indexOf：它返回指定字符或者字符串的首次出现的位置（-1则表示该子字符串不存在）。

- 字符串处理

​	**string是不可变的**，因此**所有“处理”字符串的方法都会返回一个新的字符串**，而原始的字符串则不受影响。

​	Substring方法可以提取部分字符串。

​	Insert和Remove在特定的位置插入或者删除一些字符。

​	PadLeft和PadRight会用特定的字符（如果未指定则使用空格）将字符串填充为指定的长度。

​	TrimStart和TrimEnd会从字符串的开始或结尾删除指定的字符，Trim则是从开始和结尾执行删除操作。这些方法默认会删除空白字符（包括空格、制表符、换行和这些字符的Unicode变体）。

​	Replace会替换字符串中所有（非重叠的）特定字符或子字符串。	

​	ToUpper和ToLower会返回与输入字符串相对应的**大写和小写**字符串。默认情况下，它会受用户当前语言设置的影响；**ToUpperInvariant和ToLowerInvariant则总是应用英语字母表规则**。

### 5.2 日期和时间

#### 5.2.1 TimeSpan

​	如果希望指定一个单位时间间隔，例如分钟、小时等，那么静态方法From..．更方便:

```c#
public static TimeSpan FromDays (double value);
public static TimeSpan FromHours (double value);
public static TimeSpan FromMinutes (double value);
public static TimeSpan FromSeconds (double value);
public static TimeSpan FromMilliseconds (double value);
```

​	TimeSpan的默认值是TimeSpan.Zero。

#### 5.2.2 DateTime和DateTimeOffset

​	DateTimeOffset和DateTime的功能类似。但是它主要的特点是存储了UTC的偏移量，这允许在进行不同时区的时间值比较时也能得到有效的结果。

​	**如果没有时区的改变，使用DateTime**

​	DateTimeOffset和DateTime具有类似的构造器，其区别是DateTimeOffset还需要指定一个TimeSpan类型的UTC偏移量

```c#
    public DateTimeOffset (int year, int month, int day,
                            int hour, int minute, int second,
                            TimeSpan offset);

    public DateTimeOffset (int year, int month, int day,
                            int hour, int minute, int second, int millisecond,
                            TimeSpan offset);
```







