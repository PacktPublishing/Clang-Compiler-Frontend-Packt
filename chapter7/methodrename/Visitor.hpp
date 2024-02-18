#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/Refactoring.h"

namespace clangbook {
namespace methodrename {
class Visitor : public clang::RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(clang::ASTContext &Ctx) : Context(Ctx) {}
  bool VisitCXXRecordDecl(clang::CXXRecordDecl *Class) {
    if (!Class->isClass())
      return true;
    if (!Class->isThisDeclarationADefinition())
      return true;
    if (!Class->getName().starts_with("Test"))
      return true;
    for (const clang::CXXMethodDecl *Method : Class->methods()) {
      clang::SourceLocation StartLoc = Method->getLocation();
      if (!processMethod(Method, StartLoc, "Renamed method"))
        return false;
    }
    return true;
  }

  bool VisitCXXMemberCallExpr(clang::CXXMemberCallExpr *Call) {
    if (clang::CXXMethodDecl *Method = Call->getMethodDecl()) {
      clang::CXXRecordDecl *Class = Method->getParent();
      if (!Class->getName().starts_with("Test"))
        return true;
      clang::SourceLocation StartLoc = Call->getExprLoc();
      return processMethod(Method, StartLoc, "Renamed method call");
    }
    return true;
  }

  const std::vector<clang::tooling::Replacement> &getReplacements() {
    return Replaces;
  }

private:
  clang::ASTContext &Context;
  std::vector<clang::tooling::Replacement> Replaces;

  bool processMethod(const clang::CXXMethodDecl *Method,
                     clang::SourceLocation StartLoc, const char *LogMessage) {
    if (Method->getAccess() != clang::AS_public)
      return true;
    if (llvm::isa<clang::CXXConstructorDecl>(Method))
      return true;
    if (!Method->getIdentifier() || Method->getName().starts_with("test_"))
      return true;

    std::string OldMethodName = Method->getNameAsString();
    std::string NewMethodName = "test_" + OldMethodName;
    clang::SourceManager &SM = Context.getSourceManager();
    clang::tooling::Replacement Replace(SM, StartLoc, OldMethodName.length(),
                                        NewMethodName);
    Replaces.push_back(Replace);
    llvm::outs() << LogMessage << ": " << OldMethodName << " to "
                 << NewMethodName << "\n";
    return true;
  }
};
} // namespace methodrename
} // namespace clangbook
