#include "kgv.hpp"
#include "ggt.hpp"

int kgV(int a, int b)
{
  int t = a*b;
  if(t == 0)
    return 0;
  else if(t < 0)
    return -t / ggT(a,b);
  else
    return t / ggT(a,b);
}
