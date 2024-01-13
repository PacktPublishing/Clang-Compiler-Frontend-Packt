#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

namespace clangbook {
namespace matchvisitor {
using namespace clang::ast_matchers;
static const char *MatchID = "match-id";
clang::ast_matchers::DeclarationMatcher M =
    functionDecl(decl().bind(MatchID), matchesName("max"));

class MatchCallback : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
  virtual void
  run(const clang::ast_matchers::MatchFinder::MatchResult &Result) final {
    if (const auto *FD = Result.Nodes.getNodeAs<clang::FunctionDecl>(MatchID)) {
      const auto &SM = *Result.SourceManager;
      const auto &Loc = FD->getLocation();
      llvm::outs() << "Found 'max' function at " << SM.getFilename(Loc) << ":"
                   << SM.getSpellingLineNumber(Loc) << ":"
                   << SM.getSpellingColumnNumber(Loc) << "\n";
    }
  }
};

} // namespace matchvisitor
} // namespace clangbook
