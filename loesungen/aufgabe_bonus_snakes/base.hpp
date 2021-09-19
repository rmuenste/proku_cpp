#ifndef PROKU_GAME_BASE_HPP
#define PROKU_GAME_BASE_HPP

#include <algorithm>
#include <curses.h>

// Repraesentiert eine Richtung
enum class Direction
{
  up,    // oben
  down,  // unten
  left,  // links
  right  // rechts
};

// Eine Klasse, die einen Punkt repraesentiert
class Point
{
public:
  // Die beiden Koordinaten
  int x, y;

  // Standard-Konstruktor
  Point() :
    x(0), y(0)
  {
  }

  // "Koordinaten-Konstruktor"
  explicit Point(int _x, int _y) :
    x(_x), y(_y)
  {
  }

  // Vergleichs-Operator (gleich)
  bool operator==(const Point& _other) const
  {
    return (this->x == _other.x) && (this->y == _other.y);
  }

  // Vergleichs-Operator (ungleich)
  bool operator!=(const Point& _other) const
  {
    return (this->x != _other.x) || (this->y != _other.y);
  }
}; // class Point

#endif // PROKU_GAME_BASE_HPP
