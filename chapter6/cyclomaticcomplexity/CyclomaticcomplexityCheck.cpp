//===--- CyclomaticcomplexityCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CyclomaticcomplexityCheck.h"

#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang::tidy::misc {
void CyclomaticcomplexityCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(functionDecl().bind("func"), this);
}

void CyclomaticcomplexityCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Func = Result.Nodes.getNodeAs<FunctionDecl>("func");
  if (!Func || !Func->hasBody()) return;

  std::unique_ptr<CFG> cfg =
      CFG::buildCFG(Func, Func->getBody(), Result.Context, CFG::BuildOptions());
  if (!cfg) return;

  unsigned Threshold = Options.get("Threshold", 5);
  unsigned complexity = calculateCyclomaticComplexity(cfg.get());
  if (complexity > Threshold) {
    diag(Func->getLocation(), "function %0 has high cyclomatic complexity (%1)")
        << Func << complexity;
  }
}

unsigned CyclomaticcomplexityCheck::calculateCyclomaticComplexity(
    const CFG *cfg) {
  unsigned edges = 0;
  unsigned nodes = 0;

  for (const auto *block : *cfg) {
    edges += block->succ_size();
    ++nodes;
  }

  return edges - nodes + 2;  // Simplified formula
}

}  // namespace clang::tidy::misc
