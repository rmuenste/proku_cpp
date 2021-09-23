#include "canvas_window.hpp"

#include <deque>

/**
 * \brief Beispiel-Klasse fuer ein Fenster, welches Ereignisse protokolliert
 *
 * Diese Klasse implementiert ein Fenster, welches alle Event-Handler-Methoden
 * der CanvasWindow-Klasse ueberschreibt und jeden einzelnen Aufruf mitsamt
 * der uebergebenen Parameter in einer std::deque aus std::strings abspeichert
 * und anschliessend in der on_paint() Methode im Fenster anzeigt.
 *
 * Um einen (zumindest theoretisch moeglichen) Ueberlauf der deque zu verhindern,
 * werden immer nur die maximal letzten 50 Events in der deque abgespeichert.
 */
class EventLoggerWindow : public Proku::CanvasWindow
{
private:
  // maximal erlaubte Anzahl an gespeicherten Events (50)
  const std::size_t max_events;
  // Anzahl insgesamt gezaehlter Events
  std::size_t num_events;
  // Deque der letzten gespeicherten Events
  std::deque<std::string> last_events;

public:
  /// Konstruktor
  EventLoggerWindow() :
    Proku::CanvasWindow("EventLoggerWindow", 640, 480),
    max_events(50u),
    num_events(0u)
  {
  }

private:
  /**
   * \brief Fuegt ein neues Event in die deque ein
   *
   * \param[in] method
   * Der Name der aufgerufenen Event-Handler-Methode als String
   *
   * \param[in] arguments
   * Die Liste der Argumente der Event-Handler-Methode als String
   */
  void push_event(const std::string& method, const std::string& arguments)
  {
    // Stelle sicher, dass wir die erlaubte Anzahl nicht ueberschreiten
    while(last_events.size() >= max_events)
      last_events.pop_back();

    // Event am Anfang der deque einfuegen
    last_events.push_front(std::to_string(++num_events) + ": " + method + " ( " + arguments + " )");

    // Teile der Basis-Klasse mit, dass das Fenster neu gezeichnet werden soll
    redraw();
  }

protected:
  // Es folgen die Ueberschreibungen aller Event-Handler-Methoden.
  // Die ueberschriebene on_paint() Methode zeichet (wie immer) das Fenster
  // neu, waehrend alle anderen ueberschriebenen Methoden nur die oben
  // definierte push_event() Funktion aufrufen.

  virtual void on_paint() override
  {
    // Der Aufruf dieser on_paint() Methode selbst wird nicht in die deque
    // eingetragen, da wir aufgrund des Aufrufs der 'redraw' Funktion
    // innerhalb der 'push_new_event' Funktion eine Art Endlos-Schleife
    // erzeugen wuerden. Ausserdem sieht der Benutzer ja, dass diese
    // on_paint() Methode aufgerufen wurde, da sich der Fensterinhalt
    // aendert :)

    // Beginne Zeichnung
    this->paint_begin();

    // Zeichne alle Events in chronologisch umgekehrter Reihenfolge:
    for(std::size_t k(0); k < last_events.size(); ++k)
    {
      this->draw_string(5, 15 + k*20, last_events.at(k));
    }

    // Beende Zeichnung
    this->paint_finish();
  }

  virtual void on_resize(int width, int height) override
  {
    push_event("on_resize", std::to_string(width) + ", " + std::to_string(height));
  }

  virtual void on_key_press(int keycode) override
  {
    push_event("on_key_press", std::to_string(keycode));
  }

  virtual void on_mouse_button(int x, int y, int button, bool pressed) override
  {
    push_event("on_mouse_button", std::to_string(x) + ", " + std::to_string(y)
      + ", " + std::to_string(button) + ", " + (pressed ? "true" : "false"));
  }

  virtual void on_mouse_motion(int x, int y) override
  {
    push_event("on_mouse_motion", std::to_string(x) + ", " + std::to_string(y));
  }
}; // class EventLoggerWindow

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Die eigentliche main() Funktion des Programms:
int main()
{
  EventLoggerWindow window;
  window.main_loop();
  return 0;
}
