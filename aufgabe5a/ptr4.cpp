#include <iostream>

void swap1(int a, int b)
{
  std::cout << "swap1: a: [" << (&a) << "] = " << a << std::endl;
  std::cout << "swap1: b: [" << (&b) << "] = " << b << std::endl;
  int t(a);
  a = b;
  b = t;
}

void swap2(int* p, int* q)
{
  std::cout << "swap2: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "swap2: q: [" << (&q) << "] = " << q << " -> " << (*q) << std::endl;
  int t(*p);
  *p = *q;
  *q = t;
}

int main()
{
  int x = 7;
  int y = 3;

  // 1)
  std::cout << "1)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << std::endl;


  // 2)
  std::cout << "2) swap1(x,y)" << std::endl;
  swap1(x, y);
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << std::endl;


  // 3)
  std::cout << "3) swap2(&x,&y)" << std::endl;
  swap2(&x, &y);
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << std::endl;

  return 0;
}