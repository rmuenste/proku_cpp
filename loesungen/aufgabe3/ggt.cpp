#include "ggt.hpp"

int ggT(int a, int b)
{
  // negative Vorzeichen eliminieren
  if(a < 0)
    a = -a;
  if(b < 0)
    b = -b;

  // euklidischer Algorithmus
  while(b != 0)
  {
    int h = a % b;
    a = b;
    b = h;
  }
  return a;
}
