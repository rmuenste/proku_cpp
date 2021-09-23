#include "canvas_window.hpp"
#include "shape.hpp"

#include <iostream>
#include <deque>
#include <cmath>
#include <cassert>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Teilaufgabe a)

class Rectangle : public Proku::Shape
{
private:
  // Koordinaten der oberen linken Ecke
  int origin_x, origin_y;
  // Breite und Hoehe des Rechtecks
  int width, height;

public:
  Rectangle(int x, int y, int w, int h) :
    origin_x(x), origin_y(y), width(w), height(h)
  {
  }

  virtual void draw(Proku::Canvas& canvas) const override
  {
    canvas.draw_rect(origin_x, origin_y, width, height);
  }

  virtual bool hit_test(int x, int y) const override
  {
    return (origin_x <= x) &&  (origin_y <= y) && (x < origin_x+width) && (y < origin_y+height);
  }

  virtual void move_by(int dx, int dy) override
  {
    origin_x += dx;
    origin_y += dy;
  }
}; // class Rectangle

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Teilaufgabe b)

class Circle : public Proku::Shape
{
private:
  int center_x, center_y, radius;

public:
  Circle(int cx, int cy, int rad) :
    center_x(cx), center_y(cy), radius(rad)
  {
  }

  virtual void draw(Proku::Canvas& canvas) const override
  {
    canvas.draw_circle(center_x, center_y, radius);
  }

  virtual bool hit_test(int x, int y) const override
  {
    // Teste Distanz zum Mittelpunkt gegen Radius
    // <==> Teste quadrierte Distanz gegen quadrierten Radius
    return (center_x-x)*(center_x-x) + (center_y-y)*(center_y-y) <= radius*radius;
  }

  virtual void move_by(int dx, int dy) override
  {
    center_x += dx;
    center_y += dy;
  }
}; // class Circle

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Teilaufgabe c) bis h)

class ShapeWindow : public Proku::CanvasWindow
{
private:
  // Teilaufgabe d)
  // Die Deque der verwalteten Shape-Objekte
  std::deque<Proku::Shape*> shapes;

  // Teilaufgabe f)
  // Index des aktuell ausgewaehlten Objektes in der Deque
  int selected;

  // Teilaufgabe g)
  // Linke Maustaste gedrueckt?
  bool pressed_l;
  // Aktuelle Position des Mauszeigers
  int mouse_x, mouse_y;

public:
  /// Konstruktor
  ShapeWindow() :
    Proku::CanvasWindow("ShapeWindow", 800, 600),
    selected(-1),
    pressed_l(false),
    mouse_x(0), mouse_y(0)
  {
    // Teilaufgabe d)
    shapes.push_back(new Rectangle(50, 50, 100, 100));
    shapes.push_back(new Rectangle(250, 50, 120, 120));
    shapes.push_back(new Circle(100, 250, 50));
    shapes.push_back(new Circle(300, 250, 60));
  }

  /// virtueller Destruktor
  // Es steht in keiner Teilaufgabe, dass ein Destruktor geschrieben
  // werden soll -- darauf sollen die Studis von allein kommen!
  virtual ~ShapeWindow()
  {
    // Loesche alle Elemente in der Deque
    while(!shapes.empty())
    {
      // Letztes Element vom Heap loeschen
      delete shapes.back();
      // Deque kuerzen
      shapes.pop_back();
    }
  }

protected:
  // Teilaufgabe e)
  virtual void on_paint() override
  {
    // Beginne Zeichnung
    this->paint_begin();

    // Laenge der Deque plotten (keine Teilaufgabe)
    this->draw_string(5, 15, "Anzahl Objekte: " + std::to_string(shapes.size()));

    // Zeichne alle Objekte in der Deque
    for(std::size_t k(0); k < shapes.size(); ++k)
    {
      // Teilaufgabe f)
      // Waehle rote Farbe fuer ausgewaehltes Objekt
      if(int(k) == selected)
        this->select_color(1.0f, 0.0f, 0.0f);
      else
        this->select_color(0.0f, 0.0f, 0.0f);

      // Lasse das Objekt sich selbst zeichnen
      shapes.at(k)->draw(*this);
    }

    // Beende Zeichnung
    this->paint_finish();
  }

  // Teilaufgabe f)
  virtual void on_mouse_button(int x, int y, int button, bool pressed) override
  {
    // Ist es die linke Taste?
    if(button == 1)
    {
      // Merke aktuellen Zustant
      pressed_l = pressed;

      // linke Taste gedrueckt?
      if(pressed)
      {
        // Durchlaufe alle Elemente der Deque und test
        int new_sel = -1;
        for(std::size_t k(0); k < shapes.size(); ++k)
        {
          // Nutze die hit_test Funktion, um zu pruefen,
          // ob der Mauszeiger dieses Objekt trifft
          if(shapes.at(k)->hit_test(x,y))
          {
            new_sel = int(k);
          }
        }

        // Hat sich die Auswahl geaendert?
        // Falls ja, dann neue Auswahl speichern und Fenster neu zeichnen
        if(new_sel != selected)
        {
          selected = new_sel;
          redraw();
        }
      }
    }
  }

  // Teilaufgabe g)
  virtual void on_mouse_motion(int x, int y) override
  {
    // Ist die linke Maustaste gedrueckt und ein Element ausgewaehlt?
    if(pressed_l && (selected >= 0))
    {
      // Verschiebe das Objekt um die Distanz, die der Mauszeiger
      // seit dem letzten Aufruf gewandert ist.
      shapes.at(selected)->move_by(x-mouse_x, y-mouse_y);
      redraw();
    }

    // Neue Position des Mauszeigers speichern
    mouse_x = x;
    mouse_y = y;
  }

  // Teilaufgabe h)
  virtual void on_key_press(int keycode) override
  {
    // Hinweis: Die keycodes koennen mit dem Programm example-3 herausgefunden werden
    switch(keycode)
    {
    case 10: // 1
      // Neues Reckteck #1
      shapes.push_back(new Rectangle(mouse_x-50, mouse_y-50, 100, 100));
      selected = int(shapes.size())-1;
      redraw();
      break;

    case 11: // 2
      // Neues Reckteck #2
      shapes.push_back(new Rectangle(mouse_x-30, mouse_y-60, 60, 120));
      selected = int(shapes.size())-1;
      redraw();
      break;

    case 12: // 3
      // Neues Reckteck #3
      shapes.push_back(new Rectangle(mouse_x-60, mouse_y-30, 120, 60));
      selected = int(shapes.size())-1;
      redraw();
      break;

    case 13: // 4
      // Neuer Kreis #1
      shapes.push_back(new Circle(mouse_x, mouse_y, 25));
      selected = int(shapes.size())-1;
      redraw();
      break;

    case 14: // 5
      // Neuer Kreis #2
      shapes.push_back(new Circle(mouse_x, mouse_y, 50));
      selected = int(shapes.size())-1;
      redraw();
      break;

    case 15: // 6
      // Neuer Kreis #3
      shapes.push_back(new Circle(mouse_x, mouse_y, 75));
      selected = int(shapes.size())-1;
      redraw();
      break;

    case 111: // Pfeiltaste Hoch
      if(selected >= 0)
      {
        shapes.at(selected)->move_by(0, -10);
        redraw();
      }
      break;

    case 113: // Pfeiltaste Links
      if(selected >= 0)
      {
        shapes.at(selected)->move_by(-10, 0);
        redraw();
      }
      break;

    case 114: // Pfeiltaste Rechts
      if(selected >= 0)
      {
        shapes.at(selected)->move_by(10, 0);
        redraw();
      }
      break;

    case 116: // Pfeiltaste Links
      if(selected >= 0)
      {
        shapes.at(selected)->move_by(0, 10);
        redraw();
      }
      break;

    case 119: // Entfernen
      if(selected >= 0)
      {
        // Loesche das ausgewaehlte Element
        delete shapes.at(selected);
        // Verschiebe alle darauf folgenden Objekte in der
        // Deque um eine Position nach vorne
        for(int k(selected); k+1 < shapes.size(); ++k)
          shapes.at(k) = shapes.at(k+1);
        // Entferne das letzte Element
        shapes.pop_back();
        // Auswahl aufheben und neu zeichnen
        selected = -1;
        redraw();
      }
      break;
    }
  }
}; // class ShapeWindow

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Teilaufgabe c)

int main()
{
  ShapeWindow window;
  window.main_loop();
  return 0;
}
