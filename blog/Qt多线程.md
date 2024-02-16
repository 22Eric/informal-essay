### 1. 简介QThread

Qt通过QThread实现多线程。

#### 1.1 public函数

Public Functions

|                            | [QThread](qthread.html#QThread)(QObject **parent* = nullptr) |
| -------------------------- | ------------------------------------------------------------ |
| virtual                    | [~QThread](qthread.html#dtor.QThread)()                      |
| QAbstractEventDispatcher * | [eventDispatcher](qthread.html#eventDispatcher)() const      |
| void                       | [exit](qthread.html#exit)(int *returnCode* = 0)              |
| bool                       | [isFinished](qthread.html#isFinished)() const                |
| bool                       | [isInterruptionRequested](qthread.html#isInterruptionRequested)() const |
| bool                       | [isRunning](qthread.html#isRunning)() const                  |
| int                        | [loopLevel](qthread.html#loopLevel)() const                  |
| QThread::Priority          | [priority](qthread.html#priority)() const                    |
| void                       | [requestInterruption](qthread.html#requestInterruption)()    |
| void                       | [setEventDispatcher](qthread.html#setEventDispatcher)(QAbstractEventDispatcher **eventDispatcher*) |
| void                       | [setPriority](qthread.html#setPriority)(QThread::Priority *priority*) |
| void                       | [setStackSize](qthread.html#setStackSize)(uint *stackSize*)  |
| uint                       | [stackSize](qthread.html#stackSize)() const                  |
| bool                       | [wait](qthread.html#wait)(unsigned long *time* = ULONG_MAX)  |

#### 1.2 重载的public函数

Reimplemented Public Functions

| virtual bool | [event](qthread.html#event)(QEvent **event*) override |
| ------------ | ----------------------------------------------------- |
|              |                                                       |

#### 1.3 槽

Public Slots

| void | [quit](qthread.html#quit)()                                  |
| ---- | ------------------------------------------------------------ |
| void | [start](qthread.html#start)(QThread::Priority *priority* = InheritPriority) |
| void | [terminate](qthread.html#terminate)()                        |

#### 1.4 信号

Signals

| void | [finished](qthread.html#finished)() |
| ---- | ----------------------------------- |
| void | [started](qthread.html#started)()   |

#### 1.5 静态public成员

Static Public Members



| QThread *  | [create](qthread.html#create)(Function &&*f*, Args &&... *args*) |
| ---------- | ------------------------------------------------------------ |
| QThread *  | [create](qthread.html#create-1)(Function &&*f*)              |
| QThread *  | [currentThread](qthread.html#currentThread)()                |
| Qt::HANDLE | [currentThreadId](qthread.html#currentThreadId)()            |
| int        | [idealThreadCount](qthread.html#idealThreadCount)()          |
| void       | [msleep](qthread.html#msleep)(unsigned long *msecs*)         |
| void       | [sleep](qthread.html#sleep)(unsigned long *secs*)            |
| void       | [usleep](qthread.html#usleep)(unsigned long *usecs*)         |
| void       | [yieldCurrentThread](qthread.html#yieldCurrentThread)()      |

#### 1.6 protected函数

Protected Functions



| int          | [exec](qthread.html#exec)() |
| ------------ | --------------------------- |
| virtual void | [run](qthread.html#run)()   |

#### 1.7静态protected成员

Static Protected Members



| void | [setTerminationEnabled](qthread.html#setTerminationEnabled)(bool *enabled* = true) |
| ---- | ------------------------------------------------------------ |
|      |                                                              |



### 2. 常用QThread成员

#### 2.1 start

通过调用run(）开始线程的执行。操作系统将根据优先级参数调度线程。如果线程已在运行，则此函数不执行任何操作。

#### 2.2 run

线程的起点。调用start（）后，新创建的线程调用此函数。默认实现只调用exec（）。
您可以重新实现此功能以便于高级线程管理。从该方法返回将结束线程的执行。、

一般来说，我们需要**重写**run函数，来完成需求。

#### 2.3 信号和槽

子线程和其他线程之间的通讯由信号和槽实现。一般来说connect函数写在主线程中。

### 3. demo

#### 方法1：创建多个子线程并在子线程的run函数内完成操作。

目录：C:\Chengshan\MultithreadingTest1

用途：主线程实现数据的显示，有三个子线程，作用分别是生成随机数、使用冒泡排序、使用快速排序。

#### 方法2：创建多个子线程，创建多个任务类对象，用任务类对象在子线程内完成操作

目录：C:\Chengshan\MultithreadingTest2

用途：主线程实现数据的显示，有三个子线程，作用分别是生成随机数、使用冒泡排序、使用快速排序。

比较：1.方法1中只能用信号和槽完成子线程和其他线程的信息交互。方法2中信息的传入更加简单。

​			2.方法2使用了任务类对象。可以将多个任务方便的由一个子线程处理，更加灵活。

注意：任务类对象因为要move到子线程中，因此初始化的时候不能设置其父对象。

#### 方法3：方法1的线程池版本。创建多个任务类对象，将任务类对象放入线程池中

注意：任务类构造函数中需设置自动delete。



