## 1. 项目目录结构
首先，建立一个清晰的项目目录结构。这是一个推荐的结构：
```less
ProjectName/
├── include/                     // 放置头文件
│   ├── ThostFtdcMdApi.h
│   ├── ThostFtdcUserApiDataType.h
│   └── ThostFtdcUserApiStruct.h
├── lib/                         // 放置库文件
│   ├── thostmduserapi.lib
│   └── thostmduserapi.dll
├── src/                         // 源代码文件
│   └── main.cpp
└── ProjectName.sln              // Visual Studio 解决方案文件
```

## 2. 创建Visual Studio项目
1. 打开Visual Studio，选择 **File -> New -> Project**。
2. 选择 **Empty Project**，设置项目名称和位置，点击 **Create**。

## 3. 添加头文件和源文件
1. 右键点击解决方案资源管理器中的项目名，选择 **Add -> New Folder**，创建名为 `include` 的文件夹。
2. 将 `ThostFtdcMdApi.h`、`ThostFtdcUserApiDataType.h` 和 `ThostFtdcUserApiStruct.h` 文件复制到 `include` 文件夹中。
3. 再次右键点击项目名，选择 **Add -> New Folder**，创建名为 `lib` 的文件夹。
4. 将 `thostmduserapi.lib` 和 `thostmduserapi.dll` 文件复制到 `lib` 文件夹中。
5. 右键点击项目名，选择 **Add -> New Item**，选择 **C++ File (.cpp)**，命名为 `main.cpp`，并添加到 `src` 文件夹中。

## 4. 配置项目属性
右键点击项目名，选择 Properties，打开项目属性页。
配置包含目录
在左侧菜单中选择 Configuration Properties -> C/C++ -> General。
在右侧的 Additional Include Directories 中添加 `$(ProjectDir)include`。
b. 配置库目录
在左侧菜单中选择 Configuration Properties -> Linker -> General。
在右侧的 Additional Library Directories 中添加 `$(ProjectDir)lib`。
c. 配置依赖库
在左侧菜单中选择 Configuration Properties -> Linker -> Input。
在右侧的 Additional Dependencies 中添加 thostmduserapi.lib。

## 5. 配置DLL文件路径
由于程序在运行时需要找到DLL文件，可以将DLL文件复制到输出目录（例如$(OutDir)），或者在代码中动态加载DLL。

a. 复制DLL文件到输出目录
在项目属性页中选择 Configuration Properties -> Build Events -> Post-Build Event。
在右侧的 Command Line 中添加以下命令：

## 6. 编写main.cpp
在 main.cpp 中包含头文件并使用相关API：

```cpp
6. 编写main.cpp
在 main.cpp 中包含头文件并使用相关API：
```