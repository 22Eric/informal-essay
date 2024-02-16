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

