## 头文件调用

要调用这些代码，你需要在一个新的C++项目中创建文件，并确保项目的构建配置能够找到这些文件。下面是一种可能的方法：

1. **创建新的C++项目**：在你喜欢的集成开发环境（IDE）中，如Visual Studio、CLion或者Code::Blocks中创建一个新的C++项目。
2. **将文件复制到项目中**：将 ThostFtdcMdApi.h，thostmduserapi.dll和 thostmduserapi.lib 文件复制到你的项目文件夹中。
3. **设置项目包含路径**：确保你的项目能够找到 ThostFtdcMdApi.h 文件。在你的IDE中的项目设置或者配置中，添加包含路径，使得编译器能够找到这个文件。
4. **链接库文件**：在项目设置或者配置中，添加 thostmduserapi.lib 文件作为链接库。
5. **编写调用代码**：在你的项目中编写调用 ThostFtdcMdApi.h 中函数的代码。

下面是一个示例代码，假设你要调用 ThostFtdcMdApi.h 中的函数：
```cpp
#include <ThostFtdcMdApi.h>

int main() {
    // 在这里编写你的代码
    return 0;
}
```
6. **编译和运行**：编译你的代码，并确保你的调用能够正确链接并运行 `thostmduserapi.dll`。

这是一个简单的开始。如果你有任何进一步的问题或者需要更详细的解释，请随时提问！


## 运行
要运行 `ThostFtdcMdApi.h` 文件中的函数，你需要完成以下步骤：

1. **包含头文件**：首先，你需要在你的代码中包含 `ThostFtdcMdApi.h` 文件。这样编译器就能识别和使用这个文件中定义的类和函数。
2. **创建派生类**：`CThostFtdcMdSpi` 类是一个接口类，你需要创建一个派生类，并且实现其中的虚拟函数。这样你的派生类就可以处理接收到的事件。
3. **实例化对象**：创建一个 `CThostFtdcMdSpi` 类的对象，并且传递给 `CThostFtdcMdApi` 类的构造函数。
4. **连接交易后台**：使用 ``CThostFtdcMdApi`` 类的方法连接到交易后台。
5. **处理事件**：当与交易后台建立连接或者断开连接时，你实现的派生类中对应的虚拟函数会被调用。你可以在这些函数中处理你需要的逻辑。

以下是一个简单的示例代码，展示了如何使用 `ThostFtdcMdApi.h` 文件中的部分函数：
```cpp
#include <iostream>
#include "ThostFtdcMdApi.h"

// 派生类，实现 CThostFtdcMdSpi 接口
class MyMdSpi : public CThostFtdcMdSpi {
public:
    // 当客户端与交易后台建立起通信连接时，该方法被调用
    virtual void OnFrontConnected() override {
        std::cout << "与交易后台建立连接" << std::endl;
    }

    // 当客户端与交易后台通信连接断开时，该方法被调用
    virtual void OnFrontDisconnected(int nReason) override {
        std::cout << "与交易后台断开连接，原因：" << nReason << std::endl;
    }
};

int main() {
    // 创建派生类对象
    MyMdSpi *pSpi = new MyMdSpi();

    // 创建 CThostFtdcMdApi 对象，并传递派生类对象
    CThostFtdcMdApi *pMdApi = CThostFtdcMdApi::CreateFtdcMdApi(pSpi);

    // 连接交易后台
    pMdApi->Init();
    pMdApi->Join();

    // 释放资源
    pMdApi->Release();
    delete pSpi;

    return 0;
}
```

## 头源文件分离
在项目中分离头文件和源文件是一个很好的实践，可以提高代码的组织性和可维护性。你可以按照以下步骤来存放头文件和源文件，并且在不同文件夹中调用：

1. **创建文件夹结构**：首先，你可以在你的项目文件夹中创建两个文件夹，一个用于存放头文件（例如 include 文件夹），另一个用于存放源文件（例如 `src` 文件夹）。
2. **将头文件和源文件分别放入文件夹**：将 `ThostFtdcMdApi.h` 头文件放入 `include` 文件夹中，将项目代码源文件放入 `src` 文件夹中。
3. **设置编译器包含路径**：在你的项目配置或者构建脚本中，设置编译器的包含路径，以便编译器能够找到头文件。你需要将 `include` 文件夹的路径添加到编译器的包含路径中。
4. **在源文件中包含头文件**：在你的源文件中，使用 `#include` 指令来包含头文件。编译器将会在指定的包含路径中查找头文件。

以下是一个示例项目结构：
```
project/
│
├── include/
│   └── ThostFtdcMdApi.h
│
└── src/
    └── main.cpp
```
在 `main.cpp` 源文件中，你可以这样包含头文件：
```cpp
#include <iostream>
#include "ThostFtdcMdApi.h"

int main() {
    // 在这里编写你的代码
    return 0;
}
```
这样设置之后，编译器会在 `include` 文件夹中找到 `ThostFtdcMdApi.h` 头文件，并且能够正常编译你的代码。

如果你的项目有多个源文件，并且它们分布在不同的文件夹中，你可以在编译器设置中添加多个包含路径，以确保编译器能够找到所有的头文件。

希望这能帮助到你！如果有任何问题，请随时问我。


## vs
在 Visual Studio 中，你可以使用属性页或者项目文件（`.vcxproj`）来设置头文件的目录。以下是通过修改项目文件来设置头文件目录的方法：

1. **打开项目文件**：在 Visual Studio 中，右键点击项目，选择 "Unload Project" 以卸载项目。然后再次右键点击项目，选择 "Edit [YourProjectName].vcxproj" 以编辑项目文件。
2. **设置头文件目录**：在 `.vcxproj` 文件中，你会找到类似下面这样的 XML 代码：
```xml
<ItemGroup>
    <ClInclude Include="path\to\ThostFtdcMdApi.h" />
</ItemGroup>
```
你可以将 `<ClInclude>` 标签中的 `Include` 属性修改为你希望的头文件目录，例如：
```xml
<ItemGroup>
    <ClInclude Include="include\ThostFtdcMdApi.h" />
</ItemGroup>
```
这样就把头文件放进了名为 `include` 的目录中。

3. **保存并重新加载项目**：保存 `.vcxproj` 文件，并且在 Visual Studio 中右键点击项目，选择 "Reload Project" 以重新加载项目。
4. **验证设置**：确保在项目中正确引用了头文件，编译项目以验证设置是否生效。
   
通过修改项目文件来设置头文件目录可以确保这些设置被固化在项目文件中，方便团队合作和版本控制。希望这个步骤能够帮到你！如果有任何问题，请随时提问。

## vs 项目文件
当然，以下是一个简单的 Visual Studio 项目文件示例，其中包含了设置头文件目录的部分：
```xml
<Project DefaultTargets="Build" ToolsVersion="16.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup>
    <ClCompile Include="src\main.cpp" />
    <!-- 添加其他源文件 -->
  </ItemGroup>
  <ItemGroup>
    <ClInclude Include="include\ThostFtdcMdApi.h" />
    <!-- 添加其他头文件 -->
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <ProjectGuid>{YOUR-PROJECT-GUID}</ProjectGuid>
    <RootNamespace>YourProjectName</RootNamespace>
    <Keyword>Win32Proj</Keyword>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <PlatformToolset>v142</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <PlatformToolset>v142</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="Shared">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup />
  <ItemDefinitionGroup>
    <ClCompile>
      <PreprocessorDefinitions>WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <WarningLevel>Level3</WarningLevel>
      <Optimization>Disabled</Optimization>
      <SDLCheck>true</SDLCheck>
    </ClCompile>
  </ItemDefinitionGroup>
  <ItemGroup />
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>
```
在这个示例中：

+ `src\main.cpp` 是你的源文件，你可以在 `<ClCompile>` 标签中添加其他源文件。
+ `include\ThostFtdcMdApi.h` 是你的头文件，你可以在 `<ClInclude>` 标签中添加其他头文件。
+ `$(VCTargetsPath)` 是一个 Visual Studio 定义的路径，用于引入相关的项目设置。
+ `Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'"` 和`Condition="'$(Configuration)|$(Platform)'=='Release|Win32'"` 分别指定了 Debug 和 Release 配置下的设置。
  
你需要将上面的示例代码保存为你的项目文件`（.vcxproj）`，并替换其中的占位符（如 `{YOUR-PROJECT-GUID}`）为你项目的实际信息。

希望这可以帮助到你！如果有任何问题，请随时提问。

## 项目结构
```
MyProject/
│
├── include/
│   └── ThostFtdcMdApi.h
│
├── src/
│   └── main.cpp
│
└── MyProject.vcxproj
```

在这个示例中：

+ `include/` 文件夹包含了头文件 `ThostFtdcMdApi.h`。
+ `src/` 文件夹包含了源文件 `main.cpp`。
+ `MyProject.vcxproj` 是 Visual Studio 项目文件，其中包含了项目的配置信息，包括了源文件和头文件的引用路径。

你可以根据这个结构在你的项目中进行组织，将头文件放入 `include/` 文件夹，源文件放入 `src/` 文件夹，并在 `MyProject.vcxproj` 中引用这些文件。

希望这个示例对你有所帮助！如果有任何问题，请随时提问。