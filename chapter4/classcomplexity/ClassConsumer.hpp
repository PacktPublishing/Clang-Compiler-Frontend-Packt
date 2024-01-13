#include "clang/AST/ASTConsumer.h"

#include "ClassVisitor.hpp"

namespace clangbook {
namespace classchecker {
class ClassConsumer : public clang::ASTConsumer {
public:
  explicit ClassConsumer(clang::ASTContext *Context, int Threshold)
      : Visitor(Context, Threshold) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  ClassVisitor Visitor;
};
} // namespace classchecker
} // namespace clangbook
