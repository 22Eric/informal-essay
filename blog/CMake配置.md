# Cmake配置

## 概要
本文件基于 `CMakeLists.txt` 模板，说明如何用 CMake 在 Windows（MSVC 2019）上配置、生成和构建项目，并特别标注 **Qt** 相关设置和常见问题。

---

## 前提（Prerequisites）
- Visual Studio 2019 (MSVC 2019) 已安装（含 C++ 工作负载）。
- CMake >= 3.16。
- Qt6（与项目中 `find_package(Qt6 ...)` 匹配的安装）。
- 其它依赖（VTK、Boost、PCL、OpenCASCADE 等）已安装并可被 CMake 找到，或在 `CMAKE_PREFIX_PATH` 中指定。

---

## CMake下载

网址：`https://cmake.org/download/`

![image-20260106162657495](https://s2.loli.net/2026/01/06/pjEwgKCsukLId4e.png)

## Qt Creator使用cmake

在管理构建套件里面选择正确的Cmake Tool

![1767688079934_d](https://s2.loli.net/2026/01/06/sHGZciM4EeQ5XCk.png)

## 常用步骤（命令行方式）

1. 在源码目录外新建构建目录（推荐：out-of-source build）

```powershell
cd D:/Git/sz-measure-pack/FreeWorld2/src
cmake -S . -B build -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="D:/GitProject/DLL;C:/Qt/6.5/msvc2019_64/lib/cmake"
```

解释：
- `-S . -B build`：源目录与构建目录（推荐分开）。
- `-DCMAKE_PREFIX_PATH`：告诉 CMake 去哪里找 Qt、VTK 等。可以用分号分隔多个路径。

2. 构建项目

```powershell
cmake --build build --config Release -- /m
```

或打开 `build\FreeWorld2.sln` 用 Visual Studio 编译。

---

## 使用 CMake-GUI 或 Qt Creator
- 在 CMake-GUI 中：Source 路径选择 `FreeWorld2/src`，Build 路径选择 `FreeWorld2/src/build`，然后 Configure（选择 Visual Studio 2019 x64），填入 `CMAKE_PREFIX_PATH` 等缓存变量，点击 Generate。
- 在 Qt Creator：文件 -> 打开 CMake 项目，选择源码目录，设置构建目录与 kit（使用 MSVC2019），然后 Configure/Run CMake。

---

## 示例：完整 `CMakeLists.txt` 模板 ✅
下面是一个最小且实用的 CMakeLists 模板，展示了如何查找 Qt、使用 `CMAKE_AUTOMOC`，并与自定义 Find 模块（如 `FindVTK930.cmake`）配合：

```cmake
cmake_minimum_required(VERSION 3.16)	#指定 CMake 最低版本
project(FreeWorld2 LANGUAGES CXX)		#定义项目名称和语言
set(CMAKE_CXX_STANDARD 17)				#设置 C++ 标准（默认可能不同，但推荐）。

# 搜索自定义 Find 模块的路径（可按需修改）
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakes" "D:/GitProject/DLL/cmakes")

# Qt（必须）
find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL OpenGLWidgets Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)   # 如果使用 .qrc
set(CMAKE_AUTOUIC ON)   # 如果使用 .ui

# 自定义 Find 模块（例：FindVTK930.cmake）
find_package(VTK930 REQUIRED)

# 源文件与头文件（示例）
set(SOURCES ...)
set(HEADERS ...)

#创建共享库
add_library(FreeWorld2 SHARED ${SOURCES} ${HEADERS})

#添加编译宏（项目特定，可选，其他项目可能不需要）
target_compile_definitions(FreeWorld2 PRIVATE FREEWORLD_LIBRARY)

#设置包含目录（至少需要当前目录）
target_include_directories(FreeWorld2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 将 Find 模块导出的 include dir 与 lib 加入 target
if(VTK930_FOUND)
    target_include_directories(FreeWorld2 PUBLIC ${VTK930_INCLUDE_DIRS})
    target_link_libraries(FreeWorld2 PUBLIC ${VTK930_LIBS})
endif()

# 链接 Qt（使用导出 target）
target_link_libraries(FreeWorld2 PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)

# 指定输出目录
set_target_properties(FreeWorld2 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
)
```

> 提示：修改完 `CMakeLists.txt`（如启用 `AUTOMOC`）后，必须重新运行 CMake（Configure/Generate），再编译。

---

## 示例：`FindVTK930.cmake` 模板（放在 `cmakes/` 下） 🔧
下面是一个更健壮的 `FindXXX.cmake` 示例。放置位置应在 `CMAKE_MODULE_PATH` 指定的目录中，文件名为 `FindVTK930.cmake`：

```cmake
set(VTK930_INCLUDE_DIRS "D:/GitProject/DLL/vtk-9.3.0/vtk-9.3.0-release/include/vtk-9.3")
set(VTK930_LIB_DIR "D:/GitProject/DLL/vtk-9.3.0/vtk-9.3.0-release/lib")
file(GLOB VTK930_LIBS "${VTK930_LIB_DIR}/*.lib")
set(VTK930_DLL_DIR "D:/GitProject/DLL/vtk-9.3.0/vtk-9.3.0-release/bin")
set(VTK930_FOUND TRUE)
```

- 使用方式：在 `CMakeLists.txt` 中使用 `find_package(VTK930 REQUIRED)`，如果找到，则 `VTK930_FOUND` 为真，且可使用 `VTK930_INCLUDE_DIRS` / `VTK930_LIBS`。
- 注意：若目标库采用 CMake **Config** 包（比如现代的 VTK），优先使用 `find_package(VTK CONFIG REQUIRED)`；自定义 `Find` 模块适用于没有提供 Config 包的旧式或手工安装库。

---

## 小结（补充） 🎯
- `CMakeLists.txt` 负责描述如何构建，你应把 Qt 设置（find_package + AUTOMOC/AUTORCC/AUTOUIC）放在顶部并确保 `CMAKE_MODULE_PATH` 能找到自定义的 `FindXXX.cmake`。
- `FindXXX.cmake` 要设置一致且清晰的输出变量（例如 `XXX_FOUND`、`XXX_INCLUDE_DIRS`、`XXX_LIBS`），以便上层 `CMakeLists.txt` 使用。

