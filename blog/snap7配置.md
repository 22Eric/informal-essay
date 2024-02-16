1.在qt配置snap7注意要在pro文件添加下列代码（MSVC也要添加）

```c++
win32:LIBS += D:/Soft/Qt/Tools/mingw730_64/x86_64-w64-mingw32/lib/libws2_32.a
win32:LIBS += D:/Soft/Qt/Tools/mingw730_64/x86_64-w64-mingw32/lib/libwinmm.a
```

2.注意添加dll文件