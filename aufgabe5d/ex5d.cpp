#include <iostream>

// Diese Funktion soll die beiden Zeiger 'p_min' und
// 'p_max' aus der main-Funktion aktualisieren, falls
// 'ak' ein kleineres bzw. groesseres Element darstellt.
void minimax(int* ak, int** p_min, int** p_max)
{
  if(*ak < **p_min)
    *p_min = ak;
  if(*ak > **p_max)
    *p_max = ak;
}

int main()
{
  // Erstelle ein int-Array der Laenge 10 und
  // fuelle es mit ein paar zufaelligen Werten:
  constexpr int n = 10;
  int a[n] = {17, 13, 22, 51, 42, 30, 67, 23, 71, 18};

  // Erstelle je einen Zeiger, welcher am Ende der
  // nachfolgenden for-Schleife auf das kleinste
  // bzw. groesste Element von 'a' zeigen soll.
  // Wir initialisieren beide Zeiger zunaechst
  // auf das erste Element von 'a':
  int* p_min = &a[0];
  int* p_max = &a[0];

  // Laufe ueber alle uebrigen Elemente von 'a'
  for(int k(1); k < n; ++k)
  {
    // Rufe 'minimax' auf, um  'p_min' bzw. 'p_max' zu
    // aktualisieren, falls a[k] kleiner bzw. groesser ist:
    minimax(&a[k], &p_min, &p_max);
  }

  // Laufe ueber alle Elemente von 'a' und gebe sie
  // auf der Konsole aus
  for(int k(0); k < n; ++k)
  {
    std::cout << "a[" << k << "] = " << a[k];

    // Falls dieses Element das kleinste ist,
    // dann markieren wir das auf der Konsole:
    if(&a[k] == p_min)
    {
      std::cout << " <-- Minimum!";
    }
    // Falls dieses Element das groesste ist,
    // dann markieren wir das auf der Konsole:
    if(&a[k] == p_max)
    {
      std::cout << " <-- Maximum!";
    }

    std::cout << std::endl;
  }

  // okay
  return 0;
}