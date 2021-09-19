#include <iostream>

int main()
{
  // Erste Summe fuer x berechnen:
  double x = 0.0;
  for(int k(1); k <= 8; ++k)
    x += 1.0 / 8.0; /* oder: 0.125 */

  // Zweite Summe fuer y berechnen:
  double y = 0.0;
  for(int k(1); k <= 10; ++k)
    y += 1.0 / 10.0; /* oder 0.1 */

  // Werte von x und y ausgeben:
  std::cout << "x = " <<        x  << std::endl;
  std::cout << "y = " <<        y  << std::endl;

  // Werte von 1-x und 1-y ausgeben:
  std::cout << "1-x = " << (1.0 - x) << std::endl;
  std::cout << "1-y = " << (1.0 - y) << std::endl;

  // Vergleich von x und y ausgeben:
  if(x == y)
    std::cout << "x und y sind gleich" << std::endl;
  else
    std::cout << "x und y sind verschieden" << std::endl;

  return 0;
}
