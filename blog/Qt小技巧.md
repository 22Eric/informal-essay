#### 1. 几行代码用时

```c++
#include <QElapsedTimer>  //头文件
QElapsedTimer time;
time.start();
...
...
int milsec = time.elapsed();

//花费milsec毫秒的时间
```

## 2.qobject_cast可能引发的错误

```c++
QRabbitMQ.obj:-1: error: LNK2019: 无法解析的外部符号 "public: static struct QMetaObject const QAmqpQueue::staticMetaObject" (?staticMetaObject@QAmqpQueue@@2UQMetaObject@@B)，函数 "private: void __cdecl QRabbitMQ::queueDeclared(void)" (?queueDeclared@QRabbitMQ@@AEAAXXZ) 中引用了该符号
```

改成static_cast

## 3. mysql小技巧

```mysql

// 在对应的表中增加字段，显示出记录何时创建
ALTER TABLE your_table_name
ADD COLUMN created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP;

// 在对应的表中增加字段，显示出记录何时修改
ALTER TABLE your_table_name
ADD COLUMN updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP;

```

不需要使用代码进行update时间了，会自动记录。
