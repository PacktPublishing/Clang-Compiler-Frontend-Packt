#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/DiagnosticIDs.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "llvm/Support/raw_ostream.h"

int main() {
  llvm::IntrusiveRefCntPtr<clang::DiagnosticOptions> DiagnosticOptions =
      new clang::DiagnosticOptions();
  clang::TextDiagnosticPrinter TextDiagnosticPrinter(
      llvm::errs(), DiagnosticOptions.get(), false);

  llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> DiagIDs =
      new clang::DiagnosticIDs();
  clang::DiagnosticsEngine DiagnosticsEngine(DiagIDs, DiagnosticOptions,
                                             &TextDiagnosticPrinter, false);

  // Emit a warning
  DiagnosticsEngine.Report(DiagnosticsEngine.getCustomDiagID(
      clang::DiagnosticsEngine::Warning, "This is a custom warning."));

  return 0;
}
