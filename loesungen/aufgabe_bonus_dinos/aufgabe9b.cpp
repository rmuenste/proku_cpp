#include <iostream>
#include <cassert>

#include "test_helpers.hpp"
#include "point.hpp"
#include "triangle.hpp"
#include "rasterizer.hpp"

//
// Testet die "scan_y" Funktion der Triangle-Klasse
//
// \param[in] nr
// Die fortlaufende Nummer des Test-Falls
//
// \param[in] tria
// Eine Referenz des zu testenden Dreiecks
//
// \param[in] y
// Die zu testende Y-Koordinate
//
// \param[in] found_ref
// Gibt an, ob die Schnittpunkte existieren
//
// \param[in] q1x_ref, q1z_ref
// Die X- und Z-Koordinaten des Schnittpunktes Q1 (falls dieser existiert)
// Die Y-Koordinate von Q1 entspricht immer dem Parameter y.
//
// \param[in] q2x_ref, q2z_ref
// Die X- und Z-Koordinaten des Schnittpunktes Q2 (falls dieser existiert)
// Die Y-Koordinate von Q2 entspricht immer dem Parameter y.
//
// \returns
// true, wenn der Testlauf erfolgreich war, sonst false.
bool test_triangle_scan_y(
  const int nr,
  const Triangle& tria,
  const float y,
  const bool found_ref,
  const float q1x_ref = 0.0f,
  const float q1z_ref = 0.0f,
  const float q2x_ref = 0.0f,
  const float q2z_ref = 0.0f)
{
  // Erstelle rasterisierer:
  Rasterizer raster;

  // Gebe den Test-Fall auf der Konsole aus:
  std::cout << "Teste Fall " << nr << ": ";

  // Versuche, die Schnittpunkte zu berechnen:
  Point q1, q2;
  bool found = raster.scan_tria(q1, q2, y, tria);

  // Stelle sicher, dass wir den Punkt korrekt erkannt haben
  if(found_ref != found)
  {
    std::cout << "FEHLER bei Erkennung der Schnittpunkte" << std::endl;
    std::cout << "! Erwartet: ";
    std::cout << (found_ref ? "gefunden" : "nicht gefunden");
    std::cout << std::endl;
    std::cout << "! Erhalten: ";
    std::cout << (found ? "gefunden" : "nicht gefunden");
    std::cout << std::endl;

    // Test fehlgeschlagen
    return false;
  }

  // Falls es Schnittpunkte gibt, pruefen wir, ob die Koordinaten korrekt sind
  if(found_ref)
  {
    // Teste die Koordinaten der Punkte mit einer Toleranz von 10^{-2}
    bool okay_q1 = test_point(q1, q1x_ref, y, q1z_ref, 1E-2f, "Q1");
    bool okay_q2 = test_point(q2, q2x_ref, y, q2z_ref, 1E-2f, "Q2");

    // Beide okay?
    if(!(okay_q1 && okay_q2))
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

  // Erstelle Test-Dreieck #1
  Triangle tria_1;
  tria_1.vertex[0] = Point(1.0f, 1.0f, 1.0f);
  tria_1.vertex[1] = Point(4.0f, 2.0f, 3.0f);
  tria_1.vertex[2] = Point(2.0f, 3.0f, 2.0f);

  // Teste Dreieck #1
  okay = okay && test_triangle_scan_y( 1, tria_1, 0.5f, false); // unterhalb
  okay = okay && test_triangle_scan_y( 2, tria_1, 1.5f, true, 1.25f, 1.25f, 2.5f, 2.0f);
  okay = okay && test_triangle_scan_y( 3, tria_1, 2.0f, true, 1.50f, 1.50f, 4.0f, 3.0f);
  okay = okay && test_triangle_scan_y( 4, tria_1, 2.5f, true, 1.75f, 1.75f, 3.0f, 2.5f);
  okay = okay && test_triangle_scan_y( 5, tria_1, 3.5f, false); // oberhalb

  // Erstelle Test-Dreieck #1
  Triangle tria_2;
  tria_2.vertex[0] = Point(1.0f, 1.0f, 1.0f);
  tria_2.vertex[1] = Point(3.0f, 1.0f, 3.0f);
  tria_2.vertex[2] = Point(1.0f, 3.0f, 2.0f);

  // Teste Dreieck #2
  okay = okay && test_triangle_scan_y( 5, tria_2, 0.00f, false); // unterhalb
  okay = okay && test_triangle_scan_y( 6, tria_2, 1.01f, true, 1.00f, 1.00f, 3.00f, 3.00f);
  okay = okay && test_triangle_scan_y( 7, tria_2, 1.50f, true, 1.00f, 1.25f, 2.50f, 2.75f);
  okay = okay && test_triangle_scan_y( 8, tria_2, 3.50f, false); // oberhalb

  // Alle Tests okay?
  return okay ? 0 : 1;
}
