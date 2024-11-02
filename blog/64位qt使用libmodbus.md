## 1.使用libmodbus的原因

Qt自带的QModbusClient是由信号和槽实现的,在一些读写频率较高的场景下,会引发问题。而本文中使用到的libmodbus更快、更稳定



## 2.如何在64位的Qt中使用libmodbus

### 2.1 环境

Windows, qt6.2.4,msvc2019 64bit

### 2.2 下载安装libmodbus

1. 在github中搜索并下载libmodbus。我目前下载的是3.1.10版本

2. 解压后，找到根目录下 /src/win32 文件夹

3. 在这个目录下启动Windows终端（“cmd”），运行`cscript configure.js` 。会生成**config.h**

4. 将**config.h**文件复制到上级目录src中

5. 将src/win32/modbus-9.sln 文件使用vs2019打开

6. 将下图中的debug和win32 改为 release 和x64。

   ![image-20240924093213845](https://s2.loli.net/2024/11/02/qbJARjD4pcirKFg.png)

7. 运行程序，发现有一些link2019的报错。 右击项目，打开属性，在配置属性-链接器-输入-附加依赖项中添加`ws2_32.lib`

   ![image-20240924093521908](https://s2.loli.net/2024/11/02/S13ANqLgF2CXjie.png)

8. 再次运行程序，发现错误减少，有link1120错误。项目右键属性-常规-配置类型，修改为（动态库.dll）

   ![image-20240924093932989](https://s2.loli.net/2024/11/02/3DPAKqZfE5aT6rz.png)

9. 再次运行程序。编译成功，没有错误，此时会提示一些编译警告，可以添加预定义消除警告。

   在配置属性-C/C++-预处理器-预处理器定义中添加

   ```
   WIN32
   _DEBUG
   HAVE_CONFIG_H
   DLLBUILD
   _CRT_SECURE_NO_DEPRECATE=1
   _CRT_NONSTDC_NO_DEPRECATE=1
   _WINDOWS
   ENABLE_THREADS
   _CONST_CORRECT_OVERLOADS
   NOMINMAX
   FREEGLUT_STATIC
   ```

   ![image-20240924094119246](https://s2.loli.net/2024/11/02/djRF8oK4Xhk3xri.png)

10. 再次运行程序。成功在/src/win32/x64/Release文件夹中生成**modbus.lib** 和**modbus.dll**。至此libmodbus的安装工作结束

    ### 2.3在Qt中使用libmodbus

    1. 新建qt项目

    2. 在pro文件目录中，新建文件夹**libmodbus**，将上面提到的/src文件夹下所有.h和.c文件复制到新建立的libmodbus文件夹下。

       ![image-20240924095203978](https://s2.loli.net/2024/11/02/NIo9OtZQlMPD63d.png)

    3. 将上面提到的modbus.lib和modbus.dll放入项目构建目录（exe所在目录）中

    4. 在qt项目的pro文件中添加

       ```
       LIBS += -lws2_32
       
       INCLUDEPATH += 项目构建目录
       LIBS += 项目构建目录
       LIBS += -lmodbus
       ```

       

    5. 编译后，会提示`无法打开包括文件config.h` ,找到这个`#include <config.h>`改为`#include "libmodbus/config.h"`

    6. 编译后会报一堆**语法错误**，双击去到第一个错误`语法错误: 缺少“)”(在“template”的前面)`  ，这个报错是由于template是**C++关键字不能当变量使用**，将template变量的名称修改了。

    7. 再次编译，发现有3个**语法错误**，也是由于**C++关键字不能当变量使用**，将and变量和or变量重新取一个名称即可。
    
    8. 再次编译，编译通过。
    
       tips: 在使用modbus_new_tcp 函数过后，不能直接读取或写入，需要先modbus_set_slave。
             图片请下载docx版本的本文章观看。
    
       











