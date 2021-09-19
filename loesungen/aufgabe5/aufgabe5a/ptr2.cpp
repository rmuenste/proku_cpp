#include <iostream>

int main()
{
  // 1)
  int x = 7;
  int y = 3;
  int z = 5;
  int* p = &x;
  int* q = &z;

  std::cout << "1)" << std::endl;
  std::cout << "x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "z: [" << (&z) << "] = " << z << std::endl;
  std::cout << "p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "q: [" << (&q) << "] = " << q << " -> " << (*q) << std::endl;
  std::cout << std::endl;


  // 2)
  *p = *q;

  std::cout << "2) *p = *q" << std::endl;
  std::cout << "x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "z: [" << (&z) << "] = " << z << std::endl;
  std::cout << "p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "q: [" << (&q) << "] = " << q << " -> " << (*q) << std::endl;
  std::cout << std::endl;


  // 3)
  *q = 6;

  std::cout << "3) *q = 6" << std::endl;
  std::cout << "x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "z: [" << (&z) << "] = " << z << std::endl;
  std::cout << "p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "q: [" << (&q) << "] = " << q << " -> " << (*q) << std::endl;
  std::cout << std::endl;


  // 4)
  p = q;

  std::cout << "4) p = q" << std::endl;
  std::cout << "x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "z: [" << (&z) << "] = " << z << std::endl;
  std::cout << "p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "q: [" << (&q) << "] = " << q << " -> " << (*q) << std::endl;
  std::cout << std::endl;


  // 5)
  q = &y;

  std::cout << "5) q = &y" << std::endl;
  std::cout << "x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "z: [" << (&z) << "] = " << z << std::endl;
  std::cout << "p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "q: [" << (&q) << "] = " << q << " -> " << (*q) << std::endl;
  std::cout << std::endl;

  return 0;
}