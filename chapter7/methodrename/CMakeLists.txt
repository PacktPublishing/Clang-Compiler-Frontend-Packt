cmake_minimum_required(VERSION 3.16)
project("methodrename")

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ( NOT DEFINED ENV{LLVM_HOME})
  message(FATAL_ERROR "$LLVM_HOME is not defined")
else()
  message(STATUS "$LLVM_HOME found: $ENV{LLVM_HOME}")
  set(LLVM_HOME $ENV{LLVM_HOME} CACHE PATH "Root of LLVM installation")
  set(LLVM_LIB ${LLVM_HOME}/lib)
  set(LLVM_DIR ${LLVM_LIB}/cmake/llvm)
  find_package(LLVM REQUIRED CONFIG)
  include_directories(${LLVM_INCLUDE_DIRS})
  link_directories(${LLVM_LIBRARY_DIRS})
  set(SOURCE_FILE MethodRename.cpp)
  add_executable(methodrename ${SOURCE_FILE})
  set_target_properties(methodrename PROPERTIES COMPILE_FLAGS "-fno-rtti")
  target_link_libraries(methodrename
    LLVMSupport
    clangAST
    clangBasic
    clangFrontend
    clangSerialization
    clangToolingCore
    clangRewrite
    clangTooling
  )
endif()
