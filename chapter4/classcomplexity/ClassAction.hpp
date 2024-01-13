#include "ClassConsumer.hpp"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"

namespace clangbook {
namespace classchecker {
class ClassAction : public clang::PluginASTAction {
protected:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef) {
    return std::make_unique<ClassConsumer>(&CI.getASTContext(),
                                           MethodCountThreshold);
  }

  bool ParseArgs(const clang::CompilerInstance &CI,
                 const std::vector<std::string> &args) {
    for (const auto &arg : args) {
      if (arg.substr(0, 9) == "threshold") {
        auto valueStr = arg.substr(10); // Get the substring after "threshold="
        MethodCountThreshold = std::stoi(valueStr);
        return true;
      }
    }
    return true;
  }
  ActionType getActionType() { return AddAfterMainAction; }

private:
  int MethodCountThreshold = 5; // default value
};
} // namespace classchecker
} // namespace clangbook
