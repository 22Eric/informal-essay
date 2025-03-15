1. pro文件格式

   ```
   DESTDIR = $$PWD/../../Bin
   LIBS += -lws2_32
   DLL_PATH = D:/GitProject/DLL      #这个文件夹的位置可以修改
   include($$PWD/ExternalDeps/ExternalDeps.pri)
   ```

   

2. pri文件格式（两层）

   ```
   #第一层 ExternalDeps.pri
   include($$PWD/findFreeWorld.pri)
   include($$PWD/findlibmodbus.pri)
   include($$PWD/findSzmodel.pri)
   include($$PWD/findQxOrm.pri)
   ```

   ```
   #第二层 findlibmodbus.pri等
   
   # 这是标准引用格式。
   # 1. 修改MODULE_NAME = 文件夹名称
   # 2. 修改-l后面的名称以匹配lib名称
   # 3. 文件夹结构如下
   #   - bin
   #   - include
   #   - lib
   
   # 以下是一个例子，根据实际情况修改
   MODULE_NAME = libmodbus
   INCLUDEPATH += $$DLL_PATH/$$MODULE_NAME/include
   LIBS += -L$$DLL_PATH/$$MODULE_NAME/lib -lmodbus
   
   # 配置复制操作在编译前执行
   win32 {
       # 定义源目录和目标目录
       DLL_SOURCE = $$DLL_PATH/$$MODULE_NAME/bin  # 修改为你的dll目录路径
       DEST_DIR = $$DESTDIR
   
       # 创建递归复制命令
       copy_command = if not exist $$DEST_DIR mkdir $$DEST_DIR $$escape_expand(\n\t)
       copy_command += xcopy /E /Y /I $$shell_path($$DLL_SOURCE) $$shell_path($$DEST_DIR)\\
   
       # 动态设置预编译目标名称
       PRE_COPY_TARGET = pre_copy_$$MODULE_NAME
   
       # 设置为预编译步骤
       QMAKE_EXTRA_TARGETS += $$PRE_COPY_TARGET
       $${PRE_COPY_TARGET}.commands = $$copy_command
       PRE_TARGETDEPS += $$PRE_COPY_TARGET
   
       # 可选：调试输出
       # message("DLL复制配置已启用，源目录：$$DLL_SOURCE，目标名称：$$PRE_COPY_TARGET")
   }
   ```

3. 举例

   ```
   #文件夹
   D:/GitProject/DLL/libmodbus
   
   #libmodbus的格式如下
   #   - bin
   #   - include
   #   - lib
   ```

   