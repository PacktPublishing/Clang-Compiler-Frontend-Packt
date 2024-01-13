//===--- ClasscheckerCheck.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ClasscheckerCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misc {

void ClasscheckerCheck::registerMatchers(MatchFinder *Finder) {
    // Match every C++ class.
    Finder->addMatcher(cxxRecordDecl().bind("class"), this);
}

void ClasscheckerCheck::check(const MatchFinder::MatchResult &Result) {
    const auto *ClassDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("class");

    if (!ClassDecl || !ClassDecl->isThisDeclarationADefinition())
        return;

    unsigned MethodCount = 0;
    for (const auto *D : ClassDecl->decls()) {
        if (isa<CXXMethodDecl>(D))
            MethodCount++;
    }

    unsigned Threshold = Options.get("Threshold", 5);
    if (MethodCount > Threshold) {
        diag(ClassDecl->getLocation(),
             "class %0 is too complex: method count = %1",
             DiagnosticIDs::Warning)
            << ClassDecl->getName() << MethodCount;
    }
}
  
} // namespace clang::tidy::misc
