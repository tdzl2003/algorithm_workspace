# CMakeList.txt: cpp 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("cpp")

# 将源代码添加到此项目的可执行文件。
add_executable (cpp "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cpp PROPERTY CXX_STANDARD 20)
endif()

if(MSVC)
  target_compile_options(cpp PUBLIC "/utf-8")
endif()

# TODO: 如有需要，请添加测试并安装目标。
