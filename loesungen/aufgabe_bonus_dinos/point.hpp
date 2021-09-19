#ifndef PROKU_RENDER_POINT_HPP
#define PROKU_RENDER_POINT_HPP

#include <iostream>
#include <cmath>

// Eine Klasse, die einen Punkt im R^3 repraesentiert
class Point
{
public:
  // Die X-, Y- und Z-Koordinaten des Punktes
  float x, y, z;

  // Standard-Konstruktor
  Point() {}

  // Konstruktor:
  // Erstellt den Punkt aus den vorgegebenen Koordinaten
  Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
}; // class Point

// Einlese-Operator
std::istream& operator>>(std::istream& is, Point& p)
{
  return is >> p.x >> p.y >> p.z;
}

// Ausgabe-Operator
std::ostream& operator<<(std::ostream& os, const Point& p)
{
  return os << p.x << " " << p.y << " " << p.z;
}

#endif // PROKU_RENDER_POINT_HPP