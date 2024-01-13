#include "CommonHeaders.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/ADT/SmallString.h"

void testStringRef() {
  llvm::StringRef StrRef("Hello, LLVM!");
  // Efficient substring, no allocations
  llvm::StringRef SubStr = StrRef.substr(0, 5);  
  
  llvm::outs() << "Original StringRef: " << StrRef.str() << "\n";
  llvm::outs() << "Substring: " << SubStr.str() << "\n";
}

void testTwine() {
    llvm::StringRef Part1("Hello, ");
    llvm::StringRef Part2("Twine!");
    llvm::Twine Twine = Part1 + Part2;  // Efficient concatenation

    // Convert twine to a string (actual allocation happens here)
    std::string TwineStr = Twine.str();
    llvm::outs() << "Twine result: " << TwineStr << "\n";
}

void testSmallString() {
  // Stack allocate space for up to 20 characters.
  llvm::SmallString<20> SmallStr;

  // No heap allocation happens here.
  SmallStr = "Hello, ";
  SmallStr += "LLVM!";

  llvm::outs() << "SmallString result: " << SmallStr << "\n";
}

void testString() {
  testStringRef();
  testTwine();
  testSmallString();
}
