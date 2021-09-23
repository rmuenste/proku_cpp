#include "canvas_window.hpp"

/**
 * \brief Beispiel-Klasse fuer ein Fenster mit Smiley
 *
 * Diese Klasse implementiert ein Fenster, welches mit Hilfe der zur Verfuegung
 * gestellten Member-Funktionen einen Smiley im Fenster zeichnet.
 */
class SmileyWindow : public Proku::CanvasWindow
{
public:
  /// Konstruktor
  SmileyWindow() :
    Proku::CanvasWindow("SmileyWindow", 640, 480)
  {
  }

protected:
  // Ueberschreibe die on_paint() Methode von Window
  virtual void on_paint() override
  {
    // Wir nutzen hier die Methoden der Basisklasse zum Zeichnen

    // Beginne Zeichnung
    this->paint_begin();

    // Berechne Mittelpunkt des Fensters
    const int cx = this->get_width()  / 2;
    const int cy = this->get_height() / 2;

    // Zeichne Kopf in Schwarz
    this->select_color(0.0, 0.0, 0.0); // R=0, G=0, B=0
    this->draw_rect(cx-175, cy-200, 350, 400);

    // Zeichne Augen in Blau
    this->select_color(0.0, 0.0, 1.0); // R=0, G=0, B=1
    this->draw_circle(cx-90, cy-80, 30);
    this->draw_circle(cx+90, cy-80, 30);

    // Zeichne Mund in Rot
    this->select_color(1.0, 0.0, 0.0); // R=1, G=0, B=0
    this->draw_line(cx-140, cy+ 50, cx+140, cy+ 50);
    this->draw_line(cx-140, cy+ 50, cx- 70, cy+120);
    this->draw_line(cx- 70, cy+120, cx+ 70, cy+120);
    this->draw_line(cx+ 70, cy+120, cx+140, cy+ 50);

    // Beende Zeichnung
    this->paint_finish();
  }
}; // class SmileyWindow

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Die eigentliche main() Funktion des Programms:
int main()
{
  // Erstelle eine neues SmileyWindow
  SmileyWindow window;

  // Rufe die main_loop-Funktion der Basisklasse CanvasWindow auf,
  // welche die Hauptnachrichtenschleife implementiert:
  window.main_loop();

  // Beende das Programm
  return 0;
}
