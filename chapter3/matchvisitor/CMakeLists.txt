cmake_minimum_required(VERSION 3.16)
project("matchvisitor")

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
  set(SOURCE_FILE MatchVisitor.cpp)
  add_executable(matchvisitor ${SOURCE_FILE})
  set_target_properties(matchvisitor PROPERTIES COMPILE_FLAGS "-fno-rtti")
  target_link_libraries(matchvisitor
    LLVMFrontendOpenMP
    LLVMSupport
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangSerialization
    clangTooling
  )
endif()
