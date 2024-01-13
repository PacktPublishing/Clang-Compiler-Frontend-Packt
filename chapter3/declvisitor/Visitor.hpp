#include "clang/AST/DeclVisitor.h"

namespace clangbook {
namespace declvisitor {
class Visitor : public clang::DeclVisitor<Visitor> {
public:
  void VisitFunctionDecl(const clang::FunctionDecl *FD) {
    llvm::outs() << "Function: '" << FD->getName() << "'\n";
    for (auto Param : FD->parameters()) {
      Visit(Param);
    }
  }
  void VisitParmVarDecl(const clang::ParmVarDecl *PVD) {
    llvm::outs() << "\tParameter: '" << PVD->getName() << "'\n";
  }
  void VisitTranslationUnitDecl(const clang::TranslationUnitDecl *TU) {
    for (auto Decl : TU->decls()) {
      Visit(Decl);
    }
  }
};
} // namespace declvisitor
} // namespace clangbook
