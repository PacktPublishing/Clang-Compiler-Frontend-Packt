#include "Consumer.hpp"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"

namespace clangbook {
namespace recursivevisitor {
class FrontendAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef File) {
    return std::make_unique<Consumer>(&CI.getASTContext());
  }
};
} // namespace recursivevisitor
} // namespace clangbook
