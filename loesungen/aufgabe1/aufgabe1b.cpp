#include <iostream>
#include <iomanip>

int main()
{
  // Die Bailey-Borwein-Plouffe Formel zur Berechnung von pi:
  //
  //       infty   1     (   4      2      1      1  )
  // pi :=  sum  ----  * ( ---- - ---- - ---- - ---- )
  //        k=0  16^k    ( 8k+1   8k+4   8k+5   8k+6 )
  //

  // Der Startwert:
  double pi(0.0);

  // Der Vorfaktor 1/16^k
  // Diesen werden wir sukzessiv berechnen
  double scale = 1.0;

  // Die Endlos-Schleife fuer die Reihe
  for(int k(0); true; ++k)
  {
    // merke vorherige Approximation:
    double pi_old(pi);

    // aktualisiere Approximation:
    pi += scale * (
      4.0 / double(8*k+1) -
      2.0 / double(8*k+4) -
      1.0 / double(8*k+5) -
      1.0 / double(8*k+6));

    // Haben wir nichts mehr dazugewonnen?
    if(pi == pi_old)
      break;

    // aktualisiere Skalierung fuer naechste Iteration:
    scale /= 16.0;
  }

  // Ausgabe:
  std::cout << "pi = ";
  std::cout << std::fixed << std::setprecision(15) << pi << std::endl;

  return 0;
}