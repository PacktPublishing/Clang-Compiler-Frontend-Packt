#include "Visitor.hpp"
#include "clang/Frontend/ASTConsumers.h"

namespace clangbook {
namespace methodrename {
class Consumer : public clang::ASTConsumer {
public:
  void HandleTranslationUnit(clang::ASTContext &Context) override {
    Visitor V(Context);
    V.TraverseDecl(Context.getTranslationUnitDecl());

    // Apply the replacements.
    clang::Rewriter Rewrite(Context.getSourceManager(), clang::LangOptions());
    auto &Replaces = V.getReplacements();
    for (const auto &Replace : Replaces) {
      if (Replace.isApplicable()) {
        Replace.apply(Rewrite);
      }
    }

    // Apply the Rewriter changes.
    if (Rewrite.overwriteChangedFiles()) {
      llvm::errs() << "Error: Cannot apply changes to the file\n";
    }
  }
};
} // namespace methodrename
} // namespace clangbook
