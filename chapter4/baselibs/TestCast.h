#pragma once

#include "CommonHeaders.h"
#include "llvm/Support/Casting.h"

#include <memory>

namespace clangbook {
class Animal {
public:
  enum AnimalKind { AK_Horse, AK_Sheep };

public:
  Animal(AnimalKind K) : Kind(K){};
  AnimalKind getKind() const { return Kind; }

private:
  const AnimalKind Kind;
};

class Horse : public Animal {
public:
  Horse(int S) : Animal(AK_Horse), Speed(S){};

  static bool classof(const Animal *A) { return A->getKind() == AK_Horse; }

  int getSpeed() { return Speed; }

private:
  int Speed;
};

class Sheep : public Animal {
public:
  Sheep(int WM) : Animal(AK_Sheep), WoolMass(WM){};

  static bool classof(const Animal *A) { return A->getKind() == AK_Sheep; }

  int getWoolMass() { return WoolMass; }

private:
  int WoolMass;
};
} // namespace clangbook

void testAnimal() {
  auto AnimalPtr = std::make_unique<clangbook::Horse>(10);
  if (llvm::isa<clangbook::Horse>(AnimalPtr)) {
    llvm::outs()
        << "Animal is a Horse and the horse speed is: "
        << llvm::dyn_cast<clangbook::Horse>(AnimalPtr.get())->getSpeed()
        << "mph \n";
  } else {
    llvm::outs() << "Animal is not a Horse\n";
  }
}

void testCast() { testAnimal(); }
