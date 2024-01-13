#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h" // llvm::cl::extrahelp

#include "FrontendAction.hpp"

namespace {
llvm::cl::OptionCategory TestCategory("Test project");
llvm::cl::extrahelp
    CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);
} // namespace

int main(int argc, const char **argv) {
  llvm::Expected<clang::tooling::CommonOptionsParser> OptionsParser =
      clang::tooling::CommonOptionsParser::create(argc, argv, TestCategory);
  if (!OptionsParser) {
    llvm::errs() << OptionsParser.takeError();
    return 1;
  }
  clang::tooling::ClangTool Tool(OptionsParser->getCompilations(),
                                 OptionsParser->getSourcePathList());
  return Tool.run(clang::tooling::newFrontendActionFactory<
                      clangbook::declvisitor::FrontendAction>()
                      .get());
}
