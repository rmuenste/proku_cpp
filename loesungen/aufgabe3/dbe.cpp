#include <iostream>
#include <iomanip>
#include "ggt.hpp"

void dbe(int d, int m, int p, int n)
{
  // 10^m
  int pm = 1;
  for(int i(0); i < m; ++i)
    pm *= 10;

  // (10^n-1) bzw. 1 falls n == 0
  int pn = 1;
  if(n > 0)
  {
    for(int i(0); i < n; ++i)
      pn *= 10;
    pn -= 1;
  }

  // Zaehler: d * (10^n -1) + p
  int nom = d * pn + p;

  // Nenner: 10^m * (10^n-1)
  int den = pm * pn;

  // ggf. Bruch kuerzen
  int k = ggT(nom, den);
  if(k > 1)
  {
    nom /= k;
    den /= k;
  }

  // Ausgabe des Bruchs
  std::cout << nom;
  if(den > 1)
    std::cout << " / " << den;

  // Ausgabe des Vergleichs
  std::cout << " = " << std::setprecision(15) << (double(nom) / double(den)) << std::endl;
}
