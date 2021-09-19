#ifndef PROKU_RENDER_TRIANGLE_HPP
#define PROKU_RENDER_TRIANGLE_HPP

#include <iostream>
#include <algorithm> // std:min, std::max
#include <cmath>

#include "point.hpp"

// Eine Klasse, die ein Dreieck im R^3 repraesentiert
class Triangle
{
public:
  // Die drei Eckpunkte des Dreiecks
  Point vertex[3];

  // Standard-Konstuktor:
  Triangle()
  {
  }

  // Konstruktor:
  // Erstellt das Dreieck aus den vorgegebenen Punkten
  explicit Triangle(Point p1, Point p2, Point p3)
  {
    vertex[0] = p1;
    vertex[1] = p2;
    vertex[2] = p3;
  }

  // Gibt die minimale Y-Koordinate des Dreiecks zurueck:
  float get_min_y() const
  {
    return std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y));
  }

  // Gibt die maximale Y-Koordinate des Dreiecks zurueck:
  float get_max_y() const
  {
    return std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y));
  }

  // Gibt die Z-Koordinate des Normalen-Vektors
  // auf dem Dreieck zurueck:
  float normal_z() const
  {
    // Berechne die Kanten P0P1 und P0P2
    float x1 = vertex[1].x - vertex[0].x;
    float x2 = vertex[2].x - vertex[0].x;
    float y1 = vertex[1].y - vertex[0].y;
    float y2 = vertex[2].y - vertex[0].y;
    float z1 = vertex[1].z - vertex[0].z;
    float z2 = vertex[2].z - vertex[0].z;

    // Berechne das Kreuzprodukt der Kanten
    float cx = y1*z2 - y2*z1;
    float cy = z1*x2 - z2*x1;
    float cz = x1*y2 - x2*y1;

    // Gebe die normierte Z-Koordinate aus
    return cz / std::sqrt(cx*cx+cy*cy+cz*cz);
  }
}; // class Triangle

// Einlese-Operator
std::istream& operator>>(std::istream& is, Triangle& t)
{
  return is >> t.vertex[0] >> t.vertex[1] >> t.vertex[2];
}

// Ausgabe-Operator
std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
  return os << t.vertex[0] << "   " << t.vertex[1] << "   " << t.vertex[2];
}

#endif // PROKU_RENDER_TRIANGLE_HPP
