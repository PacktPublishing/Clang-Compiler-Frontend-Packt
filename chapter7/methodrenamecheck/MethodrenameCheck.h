//===--- MethodrenameCheck.h - clang-tidy -----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_METHODRENAMECHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_METHODRENAMECHECK_H

#include "../ClangTidyCheck.h"

namespace clang::tidy::misc {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misc/methodrename.html
class MethodrenameCheck : public ClangTidyCheck {
public:
  MethodrenameCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
  void processMethod(const clang::CXXMethodDecl *Method,
                     clang::SourceLocation StartLoc, const char *LogMessage);
};

}  // namespace clang::tidy::misc

#endif  // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_METHODRENAMECHECK_H
