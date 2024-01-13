cmake_minimum_required(VERSION 3.16)

project(classchecker)

if ( NOT DEFINED ENV{LLVM_HOME})
  message(FATAL_ERROR "$LLVM_HOME is not defined")
else()
  message(STATUS "$LLVM_HOME found: $ENV{LLVM_HOME}")
  set(LLVM_HOME $ENV{LLVM_HOME} CACHE PATH "Root of LLVM installation")
  set(LLVM_LIB ${LLVM_HOME}/lib)
  set(LLVM_DIR ${LLVM_LIB}/cmake/llvm)
  set(LLVM_BUILD $ENV{LLVM_BUILD} CACHE PATH "Root of LLVM build")
  find_package(LLVM REQUIRED CONFIG)
  include_directories(${LLVM_INCLUDE_DIRS})
  link_directories(${LLVM_LIBRARY_DIRS})
  
  # Add the plugin's shared library target
  add_library(classchecker MODULE
    ClassChecker.cpp
  )
  set_target_properties(classchecker PROPERTIES COMPILE_FLAGS "-fno-rtti")
  target_link_libraries(classchecker
    LLVMSupport
    clangAST
    clangBasic
    clangFrontend
    clangTooling
  )

  # Locate the 'lit' tool and FileCheck utility, both of which are required
  find_program(LIT_COMMAND llvm-lit PATH ${LLVM_BUILD}/bin)
  find_program(FILECHECK_COMMAND FileCheck ${LLVM_BUILD}/bin)
  if(LIT_COMMAND AND FILECHECK_COMMAND)
    message(STATUS "$LIT_COMMAND found: ${LIT_COMMAND}")
    message(STATUS "$FILECHECK_COMMAND found: ${FILECHECK_COMMAND}")
    
    # Point to our custom lit.cfg.py
    set(LIT_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/test/lit.cfg.py")

    # Configure lit.site.cfg.py using current settings
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/test/lit.site.cfg.py.in"
                   "${CMAKE_CURRENT_BINARY_DIR}/test/lit.site.cfg.py"
                   @ONLY)
                 
    # Add a custom target to run tests with lit
    add_custom_target(check-classchecker
                      COMMAND ${LIT_COMMAND} -v ${CMAKE_CURRENT_BINARY_DIR}/test
                      COMMENT "Running lit tests for classchecker clang plugin"
                      USES_TERMINAL)
  else()
    message(FATAL_ERROR "It was not possible to find the LIT executables at ${LLVM_BUILD}/bin")
  endif()
  
endif()
