#include "clang/Frontend/FrontendPluginRegistry.h"

#include "ClassAction.hpp"

static clang::FrontendPluginRegistry::Add<clangbook::classchecker::ClassAction>
    X("classchecker", "Checks the complexity of C++ classes");
