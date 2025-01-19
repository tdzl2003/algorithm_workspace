# 个人的模板库+bundle工具包

## 安装

工具包部分需要安装NodeJS和yarn，然后安装依赖

```bash
# 安装npm依赖并构建
yarn
```

## C++开发环境

目前我个人主要使用 Visual Studio 2022 ，可以直接打开cpp文件夹进行 CMake 方式的构建。

CMake理论上也可以用于其它环境，如 clang/g++ 等，不过本工程可能缺少对应的具体配置和测试，有可能有些问题需要解决。

实际上也可以自己搭建其他形式的开发环境，只要能编译 `main.cpp` 就可以。

## bundle工具包

现在只提供watch bundle，赛中一直开着即可

```bash
yarn bundle:cpp
```

## 模板库

因为维护迭代较随意，不提供文档，使用方法参考注释。
