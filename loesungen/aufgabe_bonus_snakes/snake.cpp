#include "snake.hpp"

Snake::Snake(int _x, int _y, int _length, Direction _dir) :
  direction(_dir),
  chunks()
{
  int ix(0), iy(0);
  switch(_dir)
  {
  case Direction::up:    iy = -1; break;
  case Direction::down:  iy = +1; break;
  case Direction::left:  ix = -1; break;
  case Direction::right: ix = +1; break;
  }

  // erzeuge Glieder
  for(int i(0); i < _length; ++i)
  {
    chunks.push_back(Point(_x, _y));
     _x += ix;
     _y += iy;
  }
}

Snake::~Snake()
{
}

void Snake::draw(Console& console)
{
  // Zeichne den Schwanz:
  {
    int x0 = chunks.at(0).x;
    int y0 = chunks.at(0).y;
    int x1 = chunks.at(1).x;
    //int y1 = chunks.at(1).y;
    if(x0 == x1)
      console.set_char(x0, y0, ACS_VLINE);
    else
      console.set_char(x0, y0, ACS_HLINE);
  }

  // Zeichne die inneren Glieder:
  for(int i(1); (i+1) < int(chunks.size()); ++i)
  {
    // letztes Glied
    int xp = chunks.at(i-1).x;
    int yp = chunks.at(i-1).y;
    // aktuelles Glied
    int xc = chunks.at(i).x;
    int yc = chunks.at(i).y;
    // naechstes Glied
    int xn = chunks.at(i+1).x;
    int yn = chunks.at(i+1).y;

    // Vertikal
    if((xp == xc) && (xc == xn))
      console.set_char(xc, yc, ACS_VLINE);
    // Horizontal:
    else if((yp == yc) && (yc == yn))
      console.set_char(xc, yc, ACS_HLINE);
    // Oben-Links:
    else if(((yc < yp) && (xc < xn)) || ((yc < yn) && (xc < xp)))
      console.set_char(xc, yc, ACS_ULCORNER);
    // Oben-Rechts:
    else if(((yc < yp) && (xc > xn)) || ((yc < yn) && (xc > xp)))
      console.set_char(xc, yc, ACS_URCORNER);
    // Unten-Links:
    else if(((yc > yp) && (xc < xn)) || ((yc > yn) && (xc < xp)))
      console.set_char(xc, yc, ACS_LLCORNER);
    // Unten-Rechts:
    else if(((yc > yp) && (xc > xn)) || ((yc > yn) && (xc > xp)))
      console.set_char(xc, yc, ACS_LRCORNER);
    // Fall-Back:
    else
      console.set_char(xc, yc, 'X');
  }

  // Zeichne den Kopf:
  {
    int x = chunks.back().x;
    int y = chunks.back().y;
    switch(direction)
    {
    case Direction::up:
      console.set_char(x, y, '^');
      break;
    case Direction::down:
      console.set_char(x, y, 'v');
      break;
    case Direction::right:
      console.set_char(x, y, '>');
      break;
    case Direction::left:
      console.set_char(x, y, '<');
      break;
    }
  }
}

Direction Snake::get_direction() const
{
  return direction;
}

void Snake::move(Direction _dir, bool _pop_tail)
{
  // aktuelle Kopf-Position
  int x = chunks.back().x;
  int y = chunks.back().y;

  // Naechste Kopf-Position
  switch(_dir)
  {
  case Direction::up:    --y; break;
  case Direction::down:  ++y; break;
  case Direction::left:  --x; break;
  case Direction::right: ++x; break;
  }

  // Laufe weiter
  chunks.push_back(Point(x, y));
  direction = _dir;

  // Ziehe ggf. Schwanz ein
  if(_pop_tail)
    chunks.pop_front();
}

const Point& Snake::head() const
{
  return chunks.back();
}

bool Snake::hits_rect(int _x0, int _y0, int _x1, int _y1) const
{
  int x = chunks.back().x;
  int y = chunks.back().y;
  return (x == _x0) || (y == _y0) || (x == _x1) || (y == _y1);
}

bool Snake::hits_self() const
{
  for(int i(0); (i+1) < int(chunks.size()); ++i)
  {
    if(chunks.at(i) == chunks.back())
      return true;
  }
  return false;
}

bool Snake::hits_other(const Snake& _other) const
{
  for(int i(0); (i) < int(_other.chunks.size()); ++i)
  {
    if(_other.chunks.at(i) == chunks.back())
      return true;
  }
  return false;
}

bool Snake::kiss(const Snake& _other) const
{
  return chunks.back() == _other.chunks.back();
}

