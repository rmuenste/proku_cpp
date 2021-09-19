#include <iostream>
#include <cassert>

#include "test_helpers.hpp"
#include "point.hpp"
#include "rasterizer.hpp"

//
// Testet die "scan_y" Funktion der Point-Klasse
//
// \param[in] nr
// Die fortlaufende Nummer des Test-Falls
//
// \param[in] p1, p2
// Die beiden Punkte P1 und P2
//
// \param[in] y
// Die zu testende Y-Koordinate
//
// \param[in] found_ref
// Gibt an, ob ein Schnittpunkt existiert
//
// \param[in] x_ref, z_ref
// Die X- und Z-Koordinaten des Schnittpunktes
// Werden ignoriert, wenn (found_ref == false)
//
// \returns
// true, wenn der Testlauf erfolgreich war, sonst false.
bool test_point_scan_y(
  const int nr,
  const Point& p1,
  const Point& p2,
  const float y,
  const bool found_ref,
  const float x_ref = 0.0f,
  const float z_ref = 0.0f)
{
  // Erstelle rasterisierer:
  Rasterizer raster;

  // Gebe den Test-Fall auf der Konsole aus:
  std::cout << "Teste Fall " << nr << ": ";

  // Versuche, den Schnittpunkt zu berechnen:
  Point q;
  bool found = raster.scan_edge(q, y, p1, p2);

  // Stelle sicher, dass wir den Punkt korrekt erkannt haben
  if(found_ref != found)
  {
    std::cout << "FEHLER bei Erkennung des Schnittpunktes" << std::endl;
    std::cout << "! Erwartet: ";
    std::cout << (found_ref ? "gefunden" : "nicht gefunden");
    std::cout << std::endl;
    std::cout << "! Erhalten: ";
    std::cout << (found ? "gefunden" : "nicht gefunden");
    std::cout << std::endl;

    // Test fehlgeschlagen
    return false;
  }

  // Falls es einen Schnittpunkt gibt, pruefen wir, ob die Koordinaten korrekt sind
  if(found_ref)
  {
    // Pruefe die Koordinaten des Punktes "Q" mit einer Toleranz von 10^{-3}
    if(!test_point(q, x_ref, y, z_ref, 1E-3f, "Q"))
      return false;
  }

  // Wenn wir hier angekommen sind, ist alles okay
  std::cout << "OK" << std::endl;
  return true;
}

int main()
{
  // Bis jetzt ist kein Test fehlgeschlagen
  bool okay(true);

  // Test-Linie 1: P1=(5,3,7) P2=(2,1,4)
  Point p1(5.0f, 3.0f, 7.0f);
  Point p2(2.0f, 1.0f, 4.0f);
  okay = okay && test_point_scan_y( 1, p1, p2, 1.0f, true, 2.00f, 4.00f);
  okay = okay && test_point_scan_y( 2, p1, p2, 1.5f, true, 2.75f, 4.75f);
  okay = okay && test_point_scan_y( 3, p1, p2, 2.0f, true, 3.50f, 5.50f);
  okay = okay && test_point_scan_y( 4, p1, p2, 2.5f, true, 4.25f, 6.25f);
  okay = okay && test_point_scan_y( 5, p1, p2, 3.0f, true, 5.00f, 7.00f);
  okay = okay && test_point_scan_y( 6, p1, p2, 0.999f, false); // unterhalb
  okay = okay && test_point_scan_y( 7, p1, p2, 3.001f, false); // oberhalb

  // Test-Linie 2: P1=(0.5,1.0,1.5) P2=(3.5,1.0,0.5)
  Point p3(0.5f, 1.0f,1.5f);
  Point p4(3.5f, 1.0f, 0.5f);
  okay = okay && test_point_scan_y( 8, p3, p4, 0.5f, false); // unterhalb
  okay = okay && test_point_scan_y( 9, p3, p4, 1.0f, false); // nicht eindeutig
  okay = okay && test_point_scan_y(10, p3, p4, 1.5f, false); // oberhalb

  // Alle Tests okay?
  return okay ? 0 : 1;
}
