cmake_minimum_required(VERSION 3.16)
project("declvisitor")

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
  set(SOURCE_FILE DeclVisitor.cpp)
  add_executable(declvisitor ${SOURCE_FILE})
  set_target_properties(declvisitor PROPERTIES COMPILE_FLAGS "-fno-rtti")
  target_link_libraries(declvisitor
    LLVMSupport
    clangAST
    clangBasic
    clangFrontend
    clangSerialization
    clangTooling
  )
  add_custom_command(
    OUTPUT ${SOURCE_FILE}.preprocessed
    COMMAND ${CMAKE_CXX_COMPILER} -E -I ${LLVM_HOME}/include ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE} > ${SOURCE_FILE}.preprocessed
    DEPENDS ${SOURCE_FILE}
    COMMENT "Preprocessing ${SOURCE_FILE}"
  )
  add_custom_target(preprocess ALL DEPENDS ${SOURCE_FILE}.preprocessed)
endif()
