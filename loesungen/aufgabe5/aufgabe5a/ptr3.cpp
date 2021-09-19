#include <iostream>

void foo(int* p)
{
  // 2)
  std::cout << "2) foo(p)" << std::endl;
  std::cout << "foo: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;

  // 3)
  *p = 3;
  std::cout << "3) *p = 3" << std::endl;
  std::cout << "foo: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;

  // 4)
  p = nullptr;
  std::cout << "4) p = nullptr" << std::endl;
  std::cout << "foo: p: [" << (&p) << "] = " << p << std::endl;
  std::cout << std::endl;
}

int main()
{
  // 1)
  int x = 7;
  int* p = &x;

  std::cout << "1)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;


  // 2), 3), 4)
  foo(p);


  // 5)
  std::cout << "5)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;

  return 0;
}