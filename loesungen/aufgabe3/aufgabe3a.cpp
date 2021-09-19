#include <iostream>
#include "ggt.hpp"

int main()
{
  // Verifiziere die Korrekheit der ggT Funktion:
  std::cout << "ggT(  3, 17) = " << ggT(  3, 17) << std::endl;
  std::cout << "ggT( 12,-18) = " << ggT( 12,-18) << std::endl;
  std::cout << "ggT(-70, 42) = " << ggT(-70, 42) << std::endl;
  std::cout << "ggT(-24,-96) = " << ggT(-24,-96) << std::endl;
  std::cout << "ggT(  0,  1) = " << ggT(  0,  1) << std::endl;
  std::cout << "ggT(  0,  0) = " << ggT(  0,  0) << std::endl;

  return 0;
}