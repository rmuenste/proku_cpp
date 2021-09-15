#include <iostream>

void foo(int** p, int x)
{
  *p = &x;
  std::cout << "foo: *p = &x" << std::endl;
  std::cout << "foo: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "foo: p: [" << (&p) << "] = " << p << " -> " << (*p) << " -> " << (**p) << std::endl;
  std::cout << std::endl;
}

void bar(int** q, int y)
{
  int a = y;
  int b = a;
  *q = &b;
  std::cout << "bar: a = y; b = a; *q = &b" << std::endl;
  std::cout << "bar: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "bar: a: [" << (&a) << "] = " << a << std::endl;
  std::cout << "bar: b: [" << (&b) << "] = " << b << std::endl;
  std::cout << "bar: q: [" << (&q) << "] = " << q << " -> " << (*q) << " -> " << (**q) << std::endl;
  std::cout << std::endl;
}

int main()
{
  int x = 7;
  int y = 3;
  int* p = nullptr;
  int* q = nullptr;

  // 1)
  std::cout << "1)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "main: p: [" << (&p) << "] = " << p << std::endl;
  std::cout << "main: q: [" << (&q) << "] = " << q << std::endl;
  std::cout << std::endl;


  // 2)
  std::cout << "2) foo(&p, x)" << std::endl;
  foo(&p, x);


  // 3)
  std::cout << "3)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "main: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "main: q: [" << (&q) << "] = " << q << std::endl;
  std::cout << std::endl;


  // 4)
  std::cout << "4) bar(&q, y)" << std::endl;
  bar(&q, y);


  // 5)
  std::cout << "5)" << std::endl;
  std::cout << "main: x: [" << (&x) << "] = " << x << std::endl;
  std::cout << "main: y: [" << (&y) << "] = " << y << std::endl;
  std::cout << "main: p: [" << (&p) << "] = " << p << " -> " << (*p) << std::endl;
  std::cout << "main: q: [" << (&q) << "] = " << q << " -> " << (*q) << std::endl;
  std::cout << std::endl;

  return 0;
}