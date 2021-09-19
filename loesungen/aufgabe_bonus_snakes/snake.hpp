#ifndef PROKU_GAME_SNAKE_HPP
#define PROKU_GAME_SNAKE_HPP

#include <deque>
#include "console.hpp"

class Snake
{
private:
  // Die Richtung, in welche die Schlange sich gerade bewegt
  Direction direction;

  // Die Glieder der Schlange
  std::deque<Point> chunks;

public:
  explicit Snake(int _x, int _y, int _length, Direction _dir);
  virtual ~Snake();

  // Zeichnet die Schlange auf den Bildschirm:
  void draw(Console& console);

  // Gibt die aktuelle Richtung der Schlange zurueck:
  Direction get_direction() const;

  // Bewegt die Schlange weiter
  void move(Direction _dir, bool _pop_tail);
  
  // Gibt die aktuelle Kopf-Position zurueck
  const Point& head() const;

  // Testet, ob die Schlange mit dem Kopf den Rahmen beruehrt:
  bool hits_rect(int _x0, int _y0, int _x1, int _y1) const;

  // Testet, ob die Schlange sich mit dem Kopf selbst beruehrt:
  bool hits_self() const;

  // Testet, ob die Schlange eine andere Schlange beruehrt:
  bool hits_other(const Snake& _other) const;

  // Testet, ob die Schlangen sich kuessen:
  bool kiss(const Snake& _other) const;
}; // class Snake

#endif // PROKU_GAME_SNAKE_HPP
