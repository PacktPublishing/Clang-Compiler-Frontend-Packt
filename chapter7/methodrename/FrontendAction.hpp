#include "Consumer.hpp"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"

namespace clangbook {
namespace methodrename {
class FrontendAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI,
                    llvm::StringRef File) override {
    return std::make_unique<Consumer>();
  }
};
} // namespace methodrename
} // namespace clangbook
