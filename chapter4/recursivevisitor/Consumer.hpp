#include "Visitor.hpp"
#include "clang/Frontend/ASTConsumers.h"

namespace clangbook {
namespace recursivevisitor {
class Consumer : public clang::ASTConsumer {
public:
  Consumer(clang::ASTContext *Context)
      : V(std::make_unique<Visitor>(Context)) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) override {
    V->TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  std::unique_ptr<Visitor> V;
};
} // namespace recursivevisitor
} // namespace clangbook
