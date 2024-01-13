//===--- MethodrenameCheck.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MethodrenameCheck.h"

#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misc {

AST_MATCHER(CXXMethodDecl, isNotTestMethod) {
  if (Node.getAccess() != clang::AS_public) return false;
  if (llvm::isa<clang::CXXConstructorDecl>(&Node)) return false;
  if (!Node.getIdentifier() || Node.getName().startswith("test_")) return false;

  return true;
}

void MethodrenameCheck::registerMatchers(MatchFinder *Finder) {
  auto ClassMatcher = hasAncestor(cxxRecordDecl(matchesName("::Test.*$")));
  auto MethodMatcher = cxxMethodDecl(isNotTestMethod(), ClassMatcher);
  auto CallMatcher = cxxMemberCallExpr(callee(MethodMatcher));
  Finder->addMatcher(MethodMatcher.bind("method"), this);
  Finder->addMatcher(CallMatcher.bind("call"), this);
}

void MethodrenameCheck::check(const MatchFinder::MatchResult &Result) {
  if (const auto *Method = Result.Nodes.getNodeAs<CXXMethodDecl>("method")) {
    processMethod(Method, Method->getLocation(), "Method");
  }

  if (const auto *Call = Result.Nodes.getNodeAs<CXXMemberCallExpr>("call")) {
    if (CXXMethodDecl *Method = Call->getMethodDecl()) {
      processMethod(Method, Call->getExprLoc(), "Method call");
    }
  }
}

void MethodrenameCheck::processMethod(const clang::CXXMethodDecl *Method,
                                      clang::SourceLocation StartLoc,
                                      const char *LogMessage) {
  diag(StartLoc, "%0 %1 does not have 'test_' prefix") << LogMessage << Method;
  diag(StartLoc, "insert 'test_'", DiagnosticIDs::Note)
      << FixItHint::CreateInsertion(StartLoc, "test_");
}

}  // namespace clang::tidy::misc
