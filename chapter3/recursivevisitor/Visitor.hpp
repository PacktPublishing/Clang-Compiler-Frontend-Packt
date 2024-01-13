#include "clang/AST/RecursiveASTVisitor.h"

namespace clangbook {
namespace recursivevisitor {
class Visitor : public clang::RecursiveASTVisitor<Visitor> {
public:
  bool VisitFunctionDecl(const clang::FunctionDecl *FD) {
    llvm::outs() << "Function: '" << FD->getName() << "'\n";
    return true;
  }
  bool VisitParmVarDecl(const clang::ParmVarDecl *PVD) {
    llvm::outs() << "\tParameter: '" << PVD->getName() << "'\n";
    return true;
  }
};
} // namespace recursivevisitor
} // namespace clangbook
