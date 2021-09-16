#include <iostream>

// Die Funktion 'func_1' soll den Inhalt der
// beiden Variablen vertauschen, falls der
// Wert der ersten Variable durch 2 teilbar ist:
void func_1(int* p, int* q)
{
  if((*p % 2) == 0)
  {
    int t(*p);
    *p = *q;
    *q = t;
  }
}

// Die Funktion 'func_2' soll einen Zeiger
// auf die Variable zurueckgeben, welche den
// kleineren Wert enthaelt:
int* func_2(int* p, int* q)
{
  return (*p < *q ? p : q);
}

// Die Funktion 'func_3' soll die Summe der
// beiden Variablen-Werte zurueckgeben, falls es
// sich um zwei verschiedene Variablen handelt,
// oder 0, falls beide Parameter ein und dieselbe
// Variable repraesentieren:
int func_3(int* p, int* q)
{
  return (p != q ? *p + *q : 0);
}

int main()
{
  int x = 7;
  int y = 2;
  int z = 5;

  func_1(&x, &z); // func_1 auf 'x' und 'z' anwenden
  func_1(&y, &z); // func_1 auf 'y' und 'z' anwenden
  // z = 2, y = 5

  int* p1 = func_2(&x, &y); // func_2 auf 'x' und 'y' anwenden
  // p1 = &y
  int* p2 = func_2(&y, &z); // func_2 auf 'y' und 'z' anwenden
  // p2 = &z

  int a = func_3(p1, &y); // func_3 auf 'p1' und 'y' anwenden
  int b = func_3(p2, &x); // func_3 auf 'p2' und 'x' anwenden
  int c = func_3(p1, p2); // func_3 auf 'p1' und 'p2' anwenden

  // Ausgabe:
  std::cout << "a = " << a << "  (Soll: a = 0)" << std::endl;
  std::cout << "b = " << b << "  (Soll: b = 9)" << std::endl;
  std::cout << "c = " << c << "  (Soll: c = 7)" << std::endl;

  return 0;
}