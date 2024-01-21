#pragma once

#include <iostream>
//#include "header1.h"

void foo2() {
#ifdef H1
  std::cout << "foo2 (header2) with H1" << std::endl;
  std::cout << "Macro from H2: " << H1FUN(10) << std::endl;
#else
  std::cout << "foo2 (header2) without H1" << std::endl;
#endif
}
