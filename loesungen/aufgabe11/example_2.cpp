#include "canvas_window.hpp"

#include <cmath>

/**
 * \brief Beispiel-Klasse fuer ein Fenster, dass den Mauszeiger verfolgt :)
 *
 * Diese Klasse implementiert eine klassische 1990er "Scherz-App", welche zwei
 * Augen zeichnet, die den Mauszeiger verfolgen. Die Position und Groesse
 * der Augen kann mit Hilfe des Mausrades und der Pfeiltasten angepasst werden.
 */
class EyeTrackerWindow : public Proku::CanvasWindow
{
private:
  // aktuelle Position des Mauszeigers
  int mouse_x, mouse_y;
  // Distanz der beiden Augen voneinander
  int eye_dist;
  // Radius eines Auges
  int radius_eye;
  // Radius einer Iris
  int radius_iris;

public:
  /// Konstruktor
  EyeTrackerWindow() :
    Proku::CanvasWindow("EyeTrackerWindow", 640, 480),
    mouse_x(0), mouse_y(0),
    eye_dist(130),
    radius_eye(50),
    radius_iris(15)
  {
    // Mausposition auf Fenstermitte initialisieren
    mouse_x = this->get_width() / 2;
    mouse_y = this->get_height() / 2;
  }

private:
  /**
   * \brief Zeichnet ein einzelnes Auge in das Fenster
   *
   * \param[in] eye_x, eye_y
   * Die Koordinaten des Augenmittelpunktes
   */
  void draw_eye(int eye_x, int eye_y)
  {
    // Distanzvektor vom Augenmittelpunkt zum Mauszeiger
    int rx = mouse_x - eye_x;
    int ry = mouse_y - eye_y;

    // Berechne Distanz und pruefe, ob der Mauszeiger im Auge liegt
    double dist = std::sqrt(double(rx*rx + ry*ry));
    if(double(radius_eye-radius_iris) < dist)
    {
      // Mauszeiger ausserhalb des Auges ==>
      // Distanzvektor auf maximale Laenge kuerzen
      double dd = double(radius_eye-radius_iris) / dist;
      rx = int(double(rx) * dd);
      ry = int(double(ry) * dd);
    }

    // Zeichne Auge
    this->select_color(0.0, 0.0, 0.0);
    this->draw_circle(eye_x, eye_y, radius_eye);

    // Zeichne Iris
    this->select_color(0.0, 0.0, 1.0);
    this->fill_circle(eye_x+rx, eye_y+ry, radius_iris);
  }

protected:
  // Es folgen die Ueberschreibungen der Event-Handler-Methoden
  virtual void on_paint() override
  {
    // Beginne Zeichnung
    this->paint_begin();

    // Mittelpunkt des Fensters berechnen
    const int cx = this->get_width()  / 2;
    const int cy = this->get_height() / 2;

    // Zwei Augen zeichnen
    this->draw_eye(cx - eye_dist/2, cy); // Linkes Auge
    this->draw_eye(cx + eye_dist/2, cy); // Rechtes Auge

    // Beende Zeichnung
    this->paint_finish();
  }

  virtual void on_mouse_motion(int x, int y) override
  {
    // Position des Mauszeigers abspeichern und Fenster neu zeichnen
    mouse_x = x;
    mouse_y = y;
    redraw();
  }

  virtual void on_mouse_button(int x, int y, int button, bool pressed) override
  {
    // Mausrad hoch: Augen auseinander
    if(pressed && (button == 4))
    {
      eye_dist += 10;
      redraw();
    }

    // Mausrad runter: Augen zusammen
    if(pressed && (button == 5))
    {
      // stelle sicher, dass sich die Augen nicht ueberschneiden
      if(eye_dist > 2*radius_eye + 10)
      {
        eye_dist -= 10;
        redraw();
      }
    }
  }

  virtual void on_key_press(int keycode) override
  {
    switch(keycode)
    {
    case 111: // Pfeiltaste Hoch
      // Augenradius um 5 erhoehen, dabei:
      // stelle sicher, dass sich die Augen nicht ueberschneiden
      if(2*radius_eye + 10 < eye_dist)
      {
        radius_eye += 5;
        redraw();
      }
      break;

    case 116: // Pfeiltaste Runter
      // Augenradius um 5 verringern, dabei:
      // stelle sicher, dass ein Auge groesser ist als die Iris
      if(radius_eye > radius_iris+10)
      {
        radius_eye -= 5;
        redraw();
      }
      break;

    case 113: // Pfeiltaste Links
      // Irisradius um 2 verringern, dabei:
      // stelle sicher, dass die Iris nicht zu klein wird
      if(radius_iris > 5)
      {
        radius_iris -= 2;
        redraw();
      }
      break;

    case 114: // Pfeiltaste Rechts
      // Irisradius um 2 erhoehen, dabei:
      // stelle sicher, dass die Iris kleiner ist als ein Auge
      if(radius_iris+10 < radius_eye)
      {
        radius_iris += 2;
        redraw();
      }
      break;
    }
  }
}; // class EyeTrackerWindow

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Die eigentliche main() Funktion des Programms:
int main()
{
  EyeTrackerWindow window;
  window.main_loop();
  return 0;
}
