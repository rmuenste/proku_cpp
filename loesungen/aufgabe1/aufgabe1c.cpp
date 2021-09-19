#include <iostream>

int main()
{
  // Laenge des Arrays
  constexpr int n = 100;

  // Array zum Streichen
  int x[n];

  // Initiale Formatierung:
  for(int i(0); i < n; ++i)
    x[i] = 0;

  // Deklariere Zaehler:
  int count = 0;

  // Laufe ueber alle 1 < i < n
  for(int i(2); i < n; ++i)
  {
    // Wurde i bereits gestrichen?
    if(x[i] != 0)
      continue;

    // Wir haben eine neue Primzahl!
    ++count;

    // Gebe die Zahl aus:
    std::cout << i << " ";

    // Streiche alle Vielfachen von i
    for(int j(2*i); j < n; j += i)
      x[j] = 1;
  }

  // Gebe Anzahl aus:
  std::cout << std::endl;
  std::cout << "Es gibt " << count;
  std::cout << " Primzahlen im Intervall";
  std::cout << "(1," << n << ")" << std::endl;

  return 0;
}