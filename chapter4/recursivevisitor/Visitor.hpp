#include "clang/AST/RecursiveASTVisitor.h"

namespace clangbook {
namespace recursivevisitor {
class Visitor : public clang::RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(clang::ASTContext *C) : Context(C) {}

  bool VisitFunctionDecl(const clang::FunctionDecl *FD) {
    clang::SourceManager &SM = Context->getSourceManager();
    clang::SourceLocation Loc = FD->getLocation();
    clang::SourceLocation ExpLoc = SM.getExpansionLoc(Loc);
    clang::SourceLocation SpellLoc = SM.getSpellingLoc(Loc);
    llvm::StringRef ExpFileName = SM.getFilename(ExpLoc);
    llvm::StringRef SpellFileName = SM.getFilename(SpellLoc);
    unsigned SpellLine = SM.getSpellingLineNumber(SpellLoc);
    unsigned ExpLine = SM.getExpansionLineNumber(ExpLoc);
    llvm::outs() << "Spelling : " << FD->getName() << " at " << SpellFileName
                 << ":" << SpellLine << "\n";
    llvm::outs() << "Expansion : " << FD->getName() << " at " << ExpFileName
                 << ":" << ExpLine << "\n";
    return true;
  }

private:
  clang::ASTContext *Context;
};
} // namespace recursivevisitor
} // namespace clangbook
