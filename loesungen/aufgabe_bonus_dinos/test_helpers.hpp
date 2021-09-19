#ifndef PROKU_RENDER_TEST_HELPERS_HPP
#define PROKU_RENDER_TEST_HELPERS_HPP

#include <iostream>
#include <cmath>

#include "point.hpp"

//
// Testet eine Koordinate
//
// \param[in] v
// Die zu testende Koordinate
//
// \param[in] v_ref
// Der Referenz-Wert der Koordinate
//
// \param[in] tol
// Die Toleranz des Tests
//
// \param[in] which
// Eine Zeichenkette mit dem Namen der Koordinate,
// z.B. "X-Koordinate"
//
// \param[in] name
// Optional: Der Name des Punktes, zu dem die Koordinate gehoert,
// z.B. "P1"
//
// \returns
// true, falls |v-v_ref| < tol, sonst false
//
bool test_coord(
  const float v,
  const float v_ref,
  const float tol,
  const char* which,
  const char* name = nullptr)
{
  assert(tol > 0.0f);

  // Wir testen nicht auf (v == v_ref), da es hier
  // aufgrund von Rechenungenauigkeiten zu
  // "false negatives" kommen wuerde.
  // Stattdessen testen wir, ob |v-v_ref| < tol
  if(std::abs(v - v_ref) < tol)
    return true;

  // Fehlschlag !

  // Schreibe "FEHLER in <which>" bzw. "FEHLER in <which> von <name>"
  std::cout << "FEHLER in " << which;
  if(name != nullptr)
    std::cout << " von "<< name;
  std::cout << std::endl;

  // Schreibe Soll und Haben:
  std::cout << "! Erwartet: " << v_ref << std::endl;
  std::cout << "! Erhalten: " << v << std::endl;
  return false;
}

//
// Testet einen Punkt
//
// \param[in] p
// Der zu testende Punkt
//
// \param[in] x, y, z
// Der Referenz-Koordinaten des Punktes
//
// \param[in] tol
// Die Toleranz des Tests
//
// \param[in] name
// Optional: Der Name des Punktes, z.B. "P1"
//
// \returns
// true, falls alle Koordinaten richtig sind, sonst false
//
bool test_point(
  const Point& p,
  const float x,
  const float y,
  const float z,
  const float tol,
  const char* name = nullptr)
{
  assert(tol > 0.0f);

  // Teste alle Koordinaten des Punktes:
  bool okay_x = test_coord(p.x, x, tol, "X-Koordinate", name);
  bool okay_y = test_coord(p.y, y, tol, "Y-Koordinate", name);
  bool okay_z = test_coord(p.z, z, tol, "Z-Koordinate", name);

  // Alle drei Koordinaten okay?
  return okay_x && okay_y && okay_z;
}

#endif // PROKU_RENDER_TEST_HELPERS_HPP
