#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"

namespace clangbook {
namespace classchecker {
class ClassVisitor : public clang::RecursiveASTVisitor<ClassVisitor> {
public:
  explicit ClassVisitor(clang::ASTContext *C, int T)
      : Context(C), Threshold(T) {}

  bool VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration) {
    if (Declaration->isThisDeclarationADefinition()) {
      int MethodCount = 0;
      for (const auto *M : Declaration->methods()) {
        MethodCount++;
      }

      if (MethodCount > Threshold) {
        clang::DiagnosticsEngine &D = Context->getDiagnostics();
        unsigned DiagID =
            D.getCustomDiagID(clang::DiagnosticsEngine::Warning,
                              "class %0 is too complex: method count = %1");
        clang::DiagnosticBuilder DiagBuilder =
            D.Report(Declaration->getLocation(), DiagID);
        DiagBuilder << Declaration->getName() << MethodCount;
      }
    }
    return true;
  }

private:
  clang::ASTContext *Context;
  int Threshold;
};
} // namespace classchecker
} // namespace clangbook
