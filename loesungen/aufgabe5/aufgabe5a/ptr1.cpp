#include <iostream>

int main()
{
  // 1)
  int x = 7;
  int* p = &x;

  std::cout << "1)" << std::endl;
  std::cout << "x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;


  // 2)
  *p = 3;

  std::cout << "2) *p = 3" << std::endl;
  std::cout << "x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;

  return 0;
}