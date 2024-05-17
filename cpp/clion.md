在CLion中配置C++项目，并将库文件（lib）、头文件（include）、动态链接库文件（dll）分开，通常涉及到CMakeLists.txt文件的配置。下面是一个基本的指南：

## 1. 项目目录结构

假设你的项目目录结构如下：
```css
MyProject
│   CMakeLists.txt
│   main.cpp
├───include
│       my_header.h
├───lib
│       my_library.lib
├───dll
│       my_library.dll
└───src
        my_source.cpp
```

## 2. 配置CMakeLists.txt
在CMakeLists.txt文件中，你需要指定头文件路径、库文件路径和库名称。以下是一个示例：
```cmake
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(MyProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加源文件
set(SOURCES
    src/my_source.cpp
    main.cpp
)

# 添加可执行文件
add_executable(MyProject ${SOURCES})

# 指定库文件目录
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 链接库文件
target_link_libraries(MyProject my_library)

# 复制dll文件到目标文件夹（例如，构建目录）
add_custom_command(TARGET MyProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/dll/my_library.dll
    $<TARGET_FILE_DIR:MyProject>)
```
## 3. 项目代码示例
**main.cpp**
```cpp
#include <iostream>
#include "my_header.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    myFunction();
    return 0;
}
```
**include/my_header.h**
```cpp
#ifndef MY_HEADER_H
#define MY_HEADER_H

void myFunction();

#endif //MY_HEADER_H
```
**src/my_source.cpp**
```cpp
#include "my_header.h"
#include <iostream>

void myFunction() {
    std::cout << "This is a function from the library." << std::endl;
}
```

## 4. 构建项目
1. 打开CLion并加载你的项目。
2. CLion会自动检测CMakeLists.txt文件，并尝试配置项目。
3. 点击工具栏上的“Reload CMake Project”按钮（如果需要的话）。
4. 点击“Build”按钮来构建项目。
## 5. 运行项目
在构建成功后，你可以运行项目。CLion会将你的dll文件复制到构建目录中，这样可执行文件就能找到并加载动态库。

## 注意事项
+ 确保库文件和头文件在正确的目录中。
+ 如果你使用的是Windows系统，lib文件是静态库文件，dll文件是动态库文件。如果是其他操作系统，相应的文件扩展名可能会不同（例如，.so文件用于Linux的动态库）。
+这个配置假定你的lib和dll文件已经编译好了。如果需要编译库文件，请确保在CMakeLists.txt中包含相应的构建步骤。
通过这种方式，你可以清晰地将库文件、头文件和动态库文件分开管理，并在CLion中正确配置你的C++项目。