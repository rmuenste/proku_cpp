#include <iostream>

int main()
{
  int x = 7;
  int y = 3;
  int z = 1;

  // Erstelle: ptr1 -> x
  int* ptr1 = &x;

  // Erstelle: ptr2 -> *ptr1
  int* ptr2 = ptr1;

  // Setze: ptr1 -> y
  ptr1 = &y;

  // Erstelle: ptr3 -> ptr2
  int** ptr3 = &ptr2;

  // Setze: ptr1 = nullptr
  // Dabei: Nutze ptr3, um indirekt auf ptr1 zuzugreifen
  ptr3 = &ptr1;
  *ptr3 = nullptr;

  // Setze: *ptr2 = z
  // Dabei: Nutze ptr3, um indirekt auf ptr2 zuzugreifen
  ptr3 = &ptr2;
  **ptr3 = z;

  // Frage: Welche der drei Variablen 'x', 'y', 'z' wurde
  //        bei der letzten Anweisung ueberschrieben?

  // Antwort: 'x', da 'ptr2' seit Zeile 13 nicht mehr
  //          geaendert wurde.

  return 0;
}