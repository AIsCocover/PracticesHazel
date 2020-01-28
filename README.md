# PracticesHazel

> **A practice of https://github.com/TheCherno/Hazel**
> 
> 学习项目

### Hazel

* **src\Hazel**
    - **Application.h/cpp** : Application的基类，定义App运行的生命周期。
    - **Core.h** : 目前放置的是预处理常量的定义。根据Project在 Properties > C/C-- > Preprocessor Definitions 处定义的常量来决定HAZEL_API常量是表示导出到DLL还是导入DLL。
    - **EntryPoint.h** : 引擎程序入口。通过使用extern关键字，让App来实现Application的创建。
    - **Log.h/cpp** : 日志系统。 使用第三方库：https://github.com/gabime/spdlog Hazel/vendor/spdlog
* **Hazel.h** : 包含Application应用将会使用到的所有.h文件。

### Sandbox

* **src\\**
    - **SandboxApp.cpp** : 继承Hazel/Application，实现具体的Application类。