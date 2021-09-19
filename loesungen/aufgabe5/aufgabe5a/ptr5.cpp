#include <iostream>

void foo(int** pp, int* pa, int *pb)
{
  std::cout << "foo: pp: [" << (&pp) << "] = " << pp << " -> " << (*pp) << " -> " << (**pp) << std::endl;
  std::cout << "foo: pa: [" << (&pa) << "] = " << pa << " -> " << (*pa) << std::endl;
  std::cout << "foo: pb: [" << (&pb) << "] = " << pb << " -> " << (*pb) << std::endl;
  std::cout << std::endl;


  // 3)
  *pp = (*pa < *pb ? pa : pb);

  std::cout << "3) *pp = (*pa < *pb ? pa : pb)" << std::endl;
  std::cout << "foo: pp: [" << (&pp) << "] = " << pp << " -> " << (*pp) << " -> " << (**pp) << std::endl;
  std::cout << "foo: pa: [" << (&pa) << "] = " << pa << " -> " << (*pa) << std::endl;
  std::cout << "foo: pb: [" << (&pb) << "] = " << pb << " -> " << (*pb) << std::endl;
  std::cout << std::endl;
}

int main()
{
  int x = 7;
  int y = 3;
  int* p = &x;

  // 1)
  std::cout << "1)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "main: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;


  // 2)
  std::cout << "2) foo(&p, &x, &y)" << std::endl;
  foo(&p, &x, &y);

  // 4)
  std::cout << "4)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "main: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << std::endl;

  return 0;
}