本文包含C++11、14、17对于多线程方面的支持。主要基于《C++并发编程实战（第二版）》

## 第2章 线程管控

### 2.1 线程的基本管控

每个C++程序至少包含一个线程，那就是主线程。

#### 2.1.1 发起线程

**任何可调用类型都适用于std::thread**。（这里的可调用类型又称为可调用对象，可调用对象包含：函数指针、函数对象（又叫仿函数）、lambda等。详情见《C++复习》）

**将函数对象传递给std::thread的构造函数时**，要注意防范 “C++最麻烦的解释“，意思是：**针对存在二隐形的C++语句，只要它有可能被解释称函数声明，编译器就肯定将其解释为函数声明。**

```c++
thread my_thread(background_task());   //会被解释成函数声明

thread my_thread((background_task()));//正确写法
thread my_thread{background_task()}; //正确写法。列表初始化写法
thread my_thread([](){
   .... 
});                                 //正确写法。lambda表达式写法
```

#### 2.1.2 等待线程完成

通过调用join()函数实现

#### 2.1.3 在出现异常的情况下等待

通常，若要分离线程，在线程启动后调用detach()即可。然而，若要等待线程结束，则需小心地选择执行代码的位置来调用join()。原因是，如果线程启动后有异常抛出，而join()尚未执行，则该join()调用会被略过。

以下是用标准的RAII的手法，确保新线程结束，之后当前线程才退出。

```c++
class thread_guard {
	thread& t;
public:
	explicit thread_guard(thread &t_):t(t_){}
	~thread_guard()
	{
		if (t.joinable())
		{
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

struct func {
	int& i;
	func(int &i_):i(i_){}
	void operator()()
	{

	}
};


void f()
{
	int some_loacl_state = 0;
	func my_func(some_loacl_state);
	thread t(my_func);
	thread_guard g(t);
    ...
	
}
```

当f()正常或者异常退出时，f()中的局部对象会被销毁，g首先被销毁，会调用thread_guard的析构函数，这时调用join函数。可以确保新线程结束，之后当前线程才退出。

**拷贝构造和拷贝赋值运算符都需要delete**。因为所产生的新对象的生存周期有可能超过了与之关联的线程。在销毁原对象和新对象时，分别发生两次析构，将重复调用join()。

#### 2.1.4在后台运行线程

**detach()和join()的前置要求一样，必须是joinable() == true;**

当用户需要打开或使用多个仅细微不同的文件时，可以由一个程序的多个detach()的线程完成要求。这些线程之前互不影响。

### 2.2 向线程函数传递参数

**线程具有内部存储空间**，参数会按照默认方式先**复制**到该处，新创建的执行线程才能直接访问他们。然后，这些**副本**被当成**临时变量**，以**右值**的形式传给新线程上的可调用对象。

将类的成员函数设定为线程函数。

```c++
class X{
public: 
	void do_lengthy_work();

};
X my_x;
std::thread t(&X::do_lengthy_work,&my_x);
```

先说明函数属于哪个类，再说明是哪个对象。

**可以使用std::ref()或者std::move()。向线程函数传递引用或者右值。**

### 2.3 移交线程归属权

std::thread支持移动操作的意义是，函数可以便捷地向外部转移线程的归属权。

以下类确保了在离开其对象所在的作用域前，确保线程已经完结。

```c++
class scoped_thread
{
	std::thread t;
public:
	explicit scoped_thread(thread t_) : t(std::move(t_))
	{
		if (!t.joinable())
		{
			throw logic_error("NO thread");
		}
	}
	~scoped_thread()
	{
		t.join();
	}
	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
};

struct func;
void f()
{
	int some_local_state;
	scoped_thread t{ thread(func(some_local_state)) };
	do_something_in_current_thread();
}
```

### 2.4 在运行时选择线程数量

标准库的std::thread::hardware_concurrency()函数，它的返回值表示程序在各次运行中可真正并发的线程数量。

std::thread::hardware_concurrency()返回值记为hardware_thread；

若信息无法获取，该函数返回0。

**线程最大数量** = 元素总量 / 每个线程处理元素的最低限量

**实际线程数量** = min( hardware_thread != 0 ? hardware_thread ：2 ，线程最大数量)

**每个线程实际分担的元素数量** = 目标区间的长度 / 实际线程数量

### 2.5 识别线程

线程ID的两种获取方法：1.  t.get_id()  ,其中t是thread对象

​										  2.  当前线程的ID：std::this_thread::get_id()

**C++标准库允许我们随意的判断两个线程ID**,包括 == 、!= 、<= 、>=等。

**线程ID可以作为有序关联容器和无序关联容器的key。**

std::thread::id常被用于识别线程，识别线程之间的区别，以判断它是否要执行某项操作。



## 第3章 在线程间共享数据

### 3.1 线程间数据共享的问题

多线程共享数据的问题多由数据改动引发。

**不变量**是一个针对特定数据的断言，该断言总是成立的。例如“双向链表的每个结点都有链接上下结点的指针”。

改动线程间的共享数据，可能导致的最简单的问题是破坏不变量。

#### 3.1.1 条件竞争

**诱发恶性条件竞争的典型场景是，要完成一项操作，却需要改动两份或多分不同的数据。**

#### 3.1.2 防止恶性条件竞争

有以下三种方法防止恶性条件竞争：

1. 采取保护措施包装数据结构，确保不变量被破坏时，中间状态只对执行改动的线程可见（最常用）
2. **无锁编程**（不常用）：修改数据结构的设计及其不变量，由一连串不可拆分的改动完成数据变更，每个改动都维持不变量不被破坏。
3. **软件事务内存（STM）**（C++暂未直接支持）：把需要执行的数据读写操作视为一个完整序列，先用事务日志存储记录，再把序列当成单一步骤提交运行。

### 3.2 用互斥保护共享数据

访问一个数据结构前，先所锁住与数据相关的互斥，访问结束后，再解锁互斥。

#### 3.2.1 在C++中使用互斥

C++标准库提供了类模板 std::lock_gurad<> ，针对互斥类融合实现了RAII手法：**在构造时给互斥加锁，在析构时解锁**。

```c++
list<int> some_list;
mutex some_mutex;

void add_to_list(int new_value)
{
    lock_guard<mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

void list_contains(int value_to_find)
{
    lock_guard<mutex> guard(some_mutex);
    return find(some_list.begin(),some_list.end(),value_to_find) != some_list.end();
}
```

C++17引入了类模板参数推导，因此

```
lock_guard<mutex> guard(some_mutex); 
```

 可以简化成

```
lock_guard guard(some_mutex);
```

C++17还引入了scoped_lock，它是增强版的lock_guard。因此可以写成

```
scoped_lock guard(some_mutex);
```

本例采用全局变量，但更常用的是，**将互斥与受保护的数据组成一个类**。

#### 3.2.2 组织和编排代码以保护共享数据

**不管成员函数通过什么形式向调用者返回指针或者引用，指向受保护的共享数据，就会危及到共享数据安全。**

我们需要检查以下两种情况：

1. 检查成员函数，防止向调用者传出指针或引用。
2. 若成员函数在内部调用了其他函数，也不得向其他函数传递指针或引用。

#### 3.2.3 发现接口固有的条件竞争

尽管运用了互斥或其他方法保护共享数据，条件竞争依然无法避免。接口之间可能会产生条件竞争。

以下的例子说明了这一点。

```c++
stack<int> s;//假设stack是我们自己写的一个普通的栈容器
if(!s.empty())
{
    const int value = s.top();
    s.pop();
    do_something(value);
}
```

在单线程下，不会产生问题。但在多线程之下，empty()和pop()之间就会产生条件竞争。如果在empty()之后，pop()之前，另外一个线程执行了pop()。可能会导致本来的pop()失败。top()和pop()之间也会产生类似的问题。

若将top()和pop()合起来，组成一个新的函数，再在新函数内互斥呢？我们假定**新pop()**函数的定义是：返回栈顶元素的值，并从栈上将其移除。那么有可能返回不成功，但是移除成功了。会导致数据丢失。

若用异常来处理，会比较臃肿和麻烦。以下有三种方法可以解决这个问题。

1. **传入引用**

   **借一个外部变量以引用的形式接受栈容器弹出的元素。**这样**新pop()**函数就不会产生返回不成功、溢出成功了这种情况了。

2. 提供不抛出异常的拷贝构造函数，或不抛出异常的移动构造函数

3. 返回指针，指向弹出的元素

   **推荐返回智能指针。**

可以方法1和方法2一起使用，或者方法1和方法3一起使用。以下是一个线程安全的栈容器类的定义。

```c++
struct empty_stack : std:exception
{
    const char* what() const throw();
}

template<typename T>
class threadsafe_stack
{
private:
    stack<T> data;
    mutable mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack &other)
    {
        lock_guard<mutex> lock(other.m);
        data = other.data;//这里为了能够互锁，没有采用初始化列表
    }
    threadsafe_stack& operator=(const threadsafe_stack &) = delete;
    void push(T new_value)
    {
        lock_guard<mutex> lock(other.m);
        data.push_back(std::move(new_value));
    }
    shared_ptr<T> pop()//方法3
    {
        lock_guard<mutex> lock(other.m);
        if(data.empty()) throw empty_stack();
        shared_ptr<T> const res(make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T &value)//方法1
    {
        lock_guard<mutex> lock(other.m);
        if(data.empty()) throw empty_stack();
        value = data.pop();
        data.pop();
    }
    bool empty() const
    {
        lock_guard<mutex> lock(other.m);
        return data.empty();
    }
}
```

#### 3.2.4 死锁：问题和解决方法

**防范死锁的通常建议是，始终按相同顺序对两个互斥加锁。**但针对两个相同的实例，若两个线程都通过一个函数在他们之间交换数据，则第一个线程先锁的内容，是第二个线程后锁的内容，这样就会产生死锁。

**C++提供了std::lock()函数，可以同时锁住多个互斥，而没有发生死锁的风险。**解决了上述问题。

调用方式：

```c++
if(&lhs == &rhs)
    return ;       //不能缺少判断，因为不能两次加锁同一个对象
std::lock(lhs.m,rhs.m);
lock_guard<mutex> lock_a(lhs.m,std::adopt_lock);
lock_guard<mutex> lock_b(rhs.m,std::adopt_lock);
```

std::adopt_lock对象指明了互斥已被锁住，lock_guard就不会再次加锁了。

**lock()函数是“全员共同成败”，即要么全部锁住，要么全部不锁。**

C++17可将上述代码优化为：

```c++
if(&lhs == &rhs)
    return ;       //不能缺少判断，因为不能两次加锁同一个对象
scoped_lock guard(lhs.m,rhs.m);   
```

#### 3.2.5 防范死锁的补充标准

防范死锁的两个**基本标准**是：

1. 按相同顺序对两个互斥加锁
2. 同一时间的多个互斥应该使用lock()，或scoped_lock()来加锁

**按层级加锁**，本质上就是一种按相同顺序加锁。C++标准库没有直接支持按层级加锁，所以我们需要自己写一个层级加锁的类：hierarchical_mutex

```c++
class hierarchical_mutex
{
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long const previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;
    
    void check_for_hierarchy_violation()
    {
        if(this_thread_hierarchy_value <= hierarchy_value)
        {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update_hierarchy_value()
    {
        previous_hierarchy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }
    
public:
    explicit hierarchical_mutex(unsigned long value):
    	hierarchy_value(value),
    	previous_hierarchy_value(0){}
    void lock()
    {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }
    void unlock()
    {
        if(this_thread_hierarchy_value != hierarchy_value)//实现按顺序解锁
           throw std::logic_error("mutex hierarchy violated");
        this_thread_hierarchy_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }
    bool try_lock()
    {
        check_for_hierarchy_violation();
        if(!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
};

thread_local unsigned long
    hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);
```

#### 3.2.6 运用std::unique_lock<>灵活加锁

**std::unique_lock对象不一定始终占有与之关联的互斥**，**因此**它相较于lock_guard**更加灵活**。

它的第二个参数可以传入std::adopt_lock实例，表明此unique_lock对象管理互斥上的锁；也可以传入std::defer_lock实例，使互斥在完成构造时处于无锁状态。

因为更加灵活，所以相较于lock_guard会造成轻微的性能损失。所以一般不需要灵活性的工作采用lock_guard，需要灵活性的工作，例如延时加锁，采用unique_lock。

#### 3.2.7 在不同作用域之间转移互斥归属权

unique_lock对象不一定始终占有与之关联的互斥，所以采用unique_lock实例**转移**互斥归属权。转移左值，必须显示的使用std::move函数；转移右值，转移会自动发生。

### 3.3 保护共享数据的其他工具

一种极端但常见的情况是，为了并发访问，共享数据仅需在初始化过程中收到保护。这时，使用互斥就不是最佳方案了。

#### 3.3.1 在初始化过程中保护共享数据

使用互斥也可实现在初始化过成功保护共享数据，但效率不高在此不展示。我们使用std::once_falg和std::call_once()实现。以下是一个例子。

```c++
std::shared_ptr<some_resource> resource_ptr;
std::once_flag resource_flag;
void init_resource()
{
    resource_ptr.reset(new some_resource);
}
void foo()
{
    std::call_once(resource_flag,init_resource);
    resource_ptr->do_somthing();
}
```

call_once()函数和thread一样接收**可调用对象**，因此传参数的方式也一样。上面的例子中init_resource()是全局函数，因此可以直接调用。如果init_resource()是类成员函数，那么就要表明它属于哪个类，以及它属于哪个对象（如果foo()函数也是该类成员函数的话，省略这一项，改为this指针）。

#### 3.3.2 保护甚少更新的数据结构

**std::mutex不支持并发访问。**

C++17提供了两种新的互斥，std::shared_mutex，std::shared_timed_mutex。一般采用std::shared_mutex，但C++14中只有std::shared_timed_mutex。这两种新的互斥支持并发访问。

使用共享锁（读锁）和排他锁（写锁）实现并发时的性能以及安全要求。

```c++
//以下std::shared_mutex可用std::shared_timed_mutex代替
std::shared_lock<std::shared_mutex>     //共享锁
    
std::unique_lock<std::shared_mutex>    //排他锁
std::lock_guard<std::shared_mutex>     //排他锁
```

共享锁（读锁）：读的时候，其他线程可以读，也可以写。当被写时，本身阻塞。

排他锁（写锁）：写的时候，其他线程不能读，也不能写.。

#### 3.3.3 递归加锁

**std::mutex不支持多次加锁。**

C++标准库提供了std::recursive_mutex，允许多次加锁。我们必须先释放全部的锁之后，才可以让另一个线程锁住互斥。

需要用到递归锁的情况，可以改变结构，用普通的std::mutex完成会更好。



## 第4章 并发操作的同步

### 4.1 等待事件或等待其他条件

#### 4.1.1 凭借条件变量等待条件成立

C++标准库提供了条件变量的两种实现：std::condition_variable和std::condition_variable_any。后者更加灵活，但开销更大，所以一般优先采用前者。**前者仅限于与std::mutex一起使用**。

#### 4.1.2 利用条件变量构建线程安全的队列

以下是一个线程安全的类定义：

```c++
#include <iostream>
#include<condition_variable>
#include <thread>
#include<mutex>
#include<queue>
using namespace std;

template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue(){}
	threadsafe_queue(threadsafe_queue const& other)
	{
		lock_guard<mutex> lk(other.mut);
		data_queue = other.data_queue;
	}
    threadsafe_queue& operator=(threadsafe_queue const&) = delete;
	void push(T new_value)
	{
		lock_guard<mutex> lk(mut);
		data_queue.push(new_value);
		data_cond.notify_one(); //只响应一个
	}
	void wait_and_pop(T& value)
	{
		unique_lock<mutex> lk(mut);
		data_cond.wait(lk,[this]() { return !data_queue.empty(); });
		value = data_queue.front();
		data_queue.pop();
	}
	std::shared_ptr<T> wait_and_pop()
	{
		unique_lock<mutex> lk(mut);
		data_cond.wait(lk, [this]() { return !data_queue.empty(); });
		shared_ptr<T> res(make_shared<T>(data_queue.front()));
		data_queue.pop();
		return  res;
	}
	bool try_pop(T& value)
	{
		lock_guard<mutex> lk(mut);
		if (data_queue.empty())
			return false;
		value = data_queue.front();
		data_queue.pop();
		return true;
	}
	shared_ptr<T> try_pop()
	{
		lock_guard<mutex> lk(mut);
		if (data_queue.empty())
			return shared_ptr<T>();
		shared_ptr<T> res(make_shared<T>(data_queue.front()));
		data_queue.pop();
		return  res;
	}
	bool empty() const
	{
		lock_guard<mutex> lk(mut);
		return data_queue.empty();
	}
};
```

**条件变量也适用于多个线程都在等待同一个目标时间的情况。**若要全部响应，则可以改成`data_cond.notify_all();`。但是由条件变量构建的队列，只要达成条件，就一定会响应。如果我们需要响应一次之后，不再响应呢？这时用到future是更好的选择。

### 4.2 使用future等待一次性事件发生

C++标准库中有两种future。shared_future和unique_future。**只要目标事件发生，shared_future关联的所有实例都会同时就绪，并且，它们都可以访问与该目标事件关联的任何数据。**

#### 4.2.1 从后台任务返回值

只要不急需线程运算的值，就可以使用std::async()按**异步**的方式启动任务。**std::async()获取future对象**。若要用到这个值，只需要在future对象上调用get()，当前函数会被阻塞，直到future准备妥当并返回该值。std::async(）函数接收**可调用对象**。

与thread不同的是，thread对象内部有存储空间，而async()内部没有存储空间。

按默认情况下，std::async(）的实现会自行决定：等待future时，是启动新线程，还是同步执行任务。也可以通过（等待get或wait函数才执行任务函数）std::launch::deferred或（直接执行任务函数）std::launch::async指定。

#### 4.2.2 关联future实例和任务

std::packaged_task<>连结了future对象与可调用对象。**std::packaged_task<>对象在执行任务时，会调用关联的可调用对象，把返回值保存为future的内部数据，并令future准备就绪。**

std::packaged_task<>的参数是**函数签名**。

std::packaged_task<>具有成员函数get_future()，它返回std::future<>实例。该future的特化类型取决于函数签名所指定的返回值。

std::packaged_task<>对象是可调用对象。有三种使用方式。

1. 直接调用
2. 将其包装在std::function对象内，当作线程函数传递给std::thread对象
3. 传递给需要可调用对象的函数

#### 4.2.3 创建std::promise

std::promise<T>给出了一种异步求值的方法，某个std::future<T>对象与结果关联，能延后读出需要求取的值。可实现下面的工作机制：**等待数据的线程在future上阻塞，而提供数据的线程利用相配的promise设定相关联的值，使future准备就绪。**

#### 4.2.4 将异常保存到future中

1. 若经由std::async()调用的函数抛出异常，则会被保存到future中，带起本该设定的值。
2. std::packaged_task类似，调用get()得到该异常
3. std::promise如果想要保存异常，应调用成员函数set_exception()。使用std::make_exception_ptr()直接保存新异常，而不触发抛出的行为，更为简单，优先采用；也可以使用std::current_exception()用于捕获抛出的异常。

#### 4.2.5 多个线程一起等待

std::shared_future实现多个线程一起等待。**一般来说，可以向每个线程传递std::shared_future对象的副本，它们为各线程独自所有，并被视作局部变量。**

future和promise都具备成员函数valid()，用于判别异步状态是否有效。

构造std::shared_future的方法：

1. 用一个右值的future

   ```c++
   std::promise<int> p;
   std::future<int> f(p.get_future());
   
   std::shared_future<int> sf(std::move(f));
   ```

2. 用promise对象调用get_future

   ```c++
   std::promise<int> p;
   std::shared_future<int> sf(p.get_future());
   ```

3. 用share()直接构造

   ```
   std::promise<int> p;
   auto sf = p.get_future().share();
   ```

### 4.3 限时等待

有两种超时机制可供选用：一是迟延超时（**_for**），线程根据指定的时长而继续等待；二是绝对超时(**_until**)，在某特定时间点来临之前，线程一直等待。

#### 4.3.1 时钟类

1. 系统时钟类，std::chrono::system_clock
2. 恒稳时钟类，std::chrono::steady_lock
3. 高精度时钟类，std::chrono::high_resolution_clock

#### 4.3.2 时长类

std::chrono::duration<>是标准库中最简单的时间部件。具有两个模板参数，前者指明采用何种类型表示计时单元的数量，后者是一个分数，设定该时长类的每一个即使单元代表多少秒。例如`std::chrono::duration<double,std::ratio<1,1000>>`

#### 4.3.3 时间点类

时间点由类模板std::chrono::time_point<>的实例表示，它的第一个模板参数指明所参考的时钟，第二个模板参数指明计时单元（std::chrono::duration<>的特化）。时间点是一个时间跨度，始于一个称为时钟纪元的特定时刻，终于该时间点本身。跨度的值表示某具体时长的倍数。

#### 4.3.4 接收超时时限的函数

std::this_thread::sleep_for()和std::this_thread::sleep_until()。它们的功能就像简单的闹钟：线程采用sleep_for()按指定的时长休眠，或采用sleep_until()休眠直到指定时刻为止。

C++标准库中接受超时时限的函数

|                         类/名字空间                          |                             函数                             |                            返回值                            |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|                   std::this_thread名字空间                   |     sleep_for(duration)          sleep_until(time_point)     |                              无                              |
| std::condition_variable或std::condition_variable_any或 wait_for(lock,duration)或wait_until(lock,time_point) | std::cv_status::timeout或std::cv_status::no_timeout或wait_for(lock,duration,predicate)或wait_until(lock,time_point,predicate) |                 Bool----被唤醒时断言的返回值                 |
| std::timed_mutex,std::recursive_timed_mutex或std::shared_timed_mutex |      try_lock_for(duration)或try_lock_until(time_point)      |        Bool-----若获取了锁，则返回true，否则返回false        |
|                   std::shared_timed_mutex                    | try_lock_shared_for(duartion)或try_lock_shared_until(time_point) |        Bool-----若获取了锁，则返回true，否则返回false        |
| std::unique_lock<TimedLockable> unique_lock(lockable,duration) 或unique_lock(lockable,time_point) |      try_lock_for(duration)或try_lock_until(time_point)      | 无----如果在新构建的对象上获取了锁，那么owns_lock()返回true，否则返回false。Bool-----若获取了锁，则返回true，否则返回false |
| std::shared_lock<SharedTimeLockable> shared_lock(lockable,duration)或 shared_lock(lockable,time_point) |      try_lock_for(duration)或try_lock_until(time_point)      | 无----如果在新构建的对象上获取了锁，那么owns_lock()返回true，否则返回false。Bool-----若获取了锁，则返回true，否则返回false |
|    std::future<ValueType>或std::shared_future<ValueType>     |          wait_for(duartion)或wait_until(time_point)          | 如果等待超时则返回std::future_status::timeout如果future已就绪则返回std::future_status::ready如果future上的函数按推迟方式执行，且尚未开始执行，则返回std::future_status::deferred |

### 4.4 运用同步操作简化代码

一种简化代码的途径是：在并发实战中使用非常贴近函数式编程风格。

#### 4.4.1 利用future进行函数式编程

1. 函数式编程风格的快速排序

   ```c++
   //关于splice和partition函数，请查看《C++复习》和《常用算法概览》
   template<typename T>
   list<T> sequential_quick_sort(list<T> input)
   {
   	if (input.empty() || input.size() == 1)
   		return input;
   
   	list<T> result;
   	result.splice(result.begin(), input, input.begin());
   	const T &flag = *result.begin();
   	auto divide_point = std::partition(input.begin(), input.end(), [&](const T &t) {
   		return t < flag;
   		});
   	list<T> low_part;
   	low_part.splice(low_part.end(), input,input.begin(), divide_point);
   	auto new_low = sequential_quick_sort(std::move(low_part));
   	auto new_high = sequential_quick_sort(std::move(input));
   	result.splice(result.begin(), new_low);
   	result.splice(result.end(), new_high);
   	return result;
   }
   ```

2.函数式编程风格的并行快速排序

```c++
template<typename T>
list<T> sequential_quick_sort(list<T> input)
{
	if (input.empty() || input.size() == 1)
		return input;

	list<T> result;
	result.splice(result.begin(), input, input.begin());
	const T &flag = *result.begin();
	auto divide_point =  std::partition(input.begin(), input.end(), [&](const T &t) {
		return t < flag;
		});
	list<T> low_part;
	low_part.splice(low_part.end(), input,input.begin(), divide_point);
	auto new_low(std::async(&sequential_quick_sort<T>, std::move(low_part)));
	auto new_high(std::async(&sequential_quick_sort<T>, std::move(input)));
	result.splice(result.begin(), new_low.get());
	result.splice(result.end(), new_high.get());
	return result;
}
```

#### 4.4.2 使用消息传递进行同步（CSP）

角色模型：系统中含有一些分散的角色，它们各自在独立线程上运行，它们彼此收发消息以执行手上的任务，还直接通过消息传递状态，但除此之外，它们之间没有共享数据。

## 第6章 设计基于锁的并发数据结构

### 6.1 并发设计的内涵

设计数据时必须深思熟虑，力求实现真正的并发访问。

### 6.2 基于锁的并发数据结构

#### 6.2.1 采用锁实现线程安全的栈容器

#### 6.2.2 采用锁和条件变量实现线程安全的队列容器

见4.1.2中代码。假定在数据压入队列的过程中，有多个线程同时在等待，我们可以将data_cond.notify()改为data.cond.notify_all()。这样就会唤醒全体线程，但要大大增加开销：它们绝大多数还是会发现队列依然为空，只好重新休眠。第二种处理方式是，倘若有异常抛出，则在wait_and_pop()中再次调用notify_one()，从而再唤醒另一线程，让它去获取存储的值。第三种处理方式是，将std::shared_ptr<>的初始化语句移动到push()的调用处。









