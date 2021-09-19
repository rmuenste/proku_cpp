#include <iostream>
#include "kgv.hpp"

int main()
{
  // Verifiziere die Korrekheit der kgV Funktion:
  std::cout << "kgV( 3,  4) = " << kgV( 3,  4) << std::endl;
  std::cout << "kgV( 6,-13) = " << kgV( 6,-13) << std::endl;
  std::cout << "kgV(-8, 24) = " << kgV(-8, 24) << std::endl;
  std::cout << "kgV(-7,-17) = " << kgV(-7,-17) << std::endl;
  std::cout << "kgV( 0,  1) = " << kgV( 0,  1) << std::endl;
  std::cout << "kgV( 0,  0) = " << kgV( 0,  0) << std::endl;

  return 0;
}