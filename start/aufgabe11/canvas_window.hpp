#pragma once
#ifndef PROKU_CANVAS_WINDOW_HPP
#define PROKU_CANVAS_WINDOW_HPP

#include "canvas.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

namespace Proku
{
  /**
   * \brief Klasse zur Verwaltung eines Zeichen-Fensters
   *
   * Diese Klasse implementiert die Canvas-Schnittstelle und bietet einen
   * Wrapper fuer das X-Fenstersystem, welches die Zeichenbefehle aus der
   * Basisklasse in einem graphischen Fenster umsetzt.
   *
   * Zusaetzlich bietet diese Klasse eine ausgewaehlte Menge an sogenannten
   * Event-Handler-Methoden, welche aufgerufen werden, wenn der Benutzer
   * ein bestimmtes Ereignis im Fenster ausloest, wie z.B. einen Tastendruck.
   */
  class CanvasWindow : public Canvas
  {
  private:
    // Ein ganzer Batzen an seltsam klingenden internen Member-Variablen, die
    // uns Objekt-Orientierung sei Dank nicht die Bohne interessieren... :)
    Display* display;
    Atom wm_delete_window;
    Window window;
    Pixmap pixmap;
    GC gcontext;
    int wnd_width, wnd_height, wnd_depth;
    bool redraw_flag;

  public:
    /**
     * \brief Erstellt ein Fenster mit gegebenen Titel
     *
     * \param[in] title
     * Der Titel des Fensters.
     *
     * \param[in] width
     * Die gewuenschte Breite des Fensters (Standard: 640)
     *
     * \param[in] height
     * Die gewuenschte Hoehe des Fensters (Standard: 480)
     */
    explicit CanvasWindow(const std::string& title, int width = 640, int height = 480);
    /// Kopierschutz
    CanvasWindow(const CanvasWindow&) = delete;
    /// Kopierschutz
    CanvasWindow& operator=(const CanvasWindow&) = delete;
    /// virtueller Destruktor
    virtual ~CanvasWindow();

    /**
     * \brief Hauptnachrichtenschleife
     *
     * Diese Funktion implementiert die sogenannte Hauptnachrichtenschleife,
     * welche die Interaktion des Programms mit dem X-Fenstersystem bzw. dem
     * Betriebssystem abarbeitet und bei Bedarf die Event-Handler-Methoden
     * aufruft.
     *
     * Diese Funktion wird in der eigentlichen main() Funktion aufgerufen,
     * nachdem das Fenster-Objekt erstellt wurde, und kehrt erst dann
     * zurueck, wenn das Fenster geschlossen wurde und das Programm dann
     * beendet werden kann.
     */
    void main_loop();

    /**
     * \brief Fordert eine Neuzeichnung des Fensters an
     *
     * Diese Funktion kann genutzt werden, um dem Betriebssystem mitzuteilen,
     * dass das Fenster (so bald wie moeglich) neu gezeichnet werden soll.
     * Dies sorgt dafuer, dass die on_paint() Methode aufgerufen wird, sobald
     * alle noch ausstehenden Events abgearbeitet wurden.
     *
     * \attention
     * Ein Aufruf dieser Funktion fuehrt *nicht* dazu, dass das Fenster sofort
     * neugezeichnet wird. Stattdessen werden zunaechst alle noch ausstehenden
     * Events abgearbeitet und das Fenster anschliessend von der on_paint()
     * Methode neu gezeichnet.
     */
    void redraw();

  protected:
    ///////////////////////////////////////////////////////////////////////////
    // Event-Handler Methoden
    ///////////////////////////////////////////////////////////////////////////

    /**
     * \brief Wird aufgerufen, wenn das Fenster neu gezeichnet werden muss.
     *
     * Diese Methode muss (bzw. sollte) von jeder abgeleiteten Klasse
     * ueberschrieben werden, um den Fensterinhalt zu zeichnen.
     *
     * \important
     * Diese Funktion wird von der Hauptnachrichtenschleife aufgerufen und
     * sollte nicht manuell aufgerufen werden. Um ein Neuzeichnen des
     * Fensters zu bewirken, sollte stattdessen die "redraw()" Funktion
     * genutzt werden.
     */
    virtual void on_paint()
    {
    }

    /**
     * \brief Wird aufgerufen, wenn die Fenstergroesse geaendert wurde
     *
     * \param[in] width, height
     * Die neue Breite und Hoehe des Fensters
     */
    virtual void on_resize(int width, int height)
    {
    }

    /**
     * \brief Wird aufgerufen, wenn eine Taste auf der Tastatur gedrueckt wurde.
     *
     * \param[in] keycode
     * Der Code der gedrueckten Taste.
     */
    virtual void on_key_press(int keycode)
    {
    }

    /**
     * \brief Wird aufgerufen, wenn eine Maustaste gedrueckt oder losgelassen wurde.
     *
     * \param[in] x,y
     * Die aktuellen Koordinaten des Mauszeigers,
     * relativ zur oberen linken Fensterecke.
     *
     * \param[in] button
     * Der Code der betroffenen Maustaste
     *
     * \param[in] pressed
     * Gibt an, ob die Maustaste gedrueckt (\c true) oder losgelassen (\c false) wurde.
     */
    virtual void on_mouse_button(int x, int y, int button, bool pressed)
    {
    }

    /**
     * \brief Wird aufgerufen, wenn der Mauszeiger im Fenster bewegt wurde.
     *
     * \param[in] x,y
     * Die aktuellen Koordinaten des Mauszeigers,
     * relativ zur oberen linken Fensterecke.
     */
    virtual void on_mouse_motion(int x, int y)
    {
    }


  public:
    ///////////////////////////////////////////////////////////////////////////
    // Implementierung der Schnittstelle "Canvas"
    ///////////////////////////////////////////////////////////////////////////

    /// \see Canvas::get_width()
    virtual int get_width() const override;
    /// \see Canvas::get_height()
    virtual int get_height() const override;
    /// \see Canvas::paint_begin()
    virtual void paint_begin() override;
    /// \see Canvas::paint_finish()
    virtual void paint_finish() override;
    /// \see Canvas::select_color()
    virtual void select_color(double red, double green, double blue) override;
    /// \see Canvas::draw_string()
    virtual void draw_string(int x, int y, const std::string& text) override;
    /// \see Canvas::draw_line()
    virtual void draw_line(int x1, int y1, int x2, int y2) override;
    /// \see Canvas::draw_rect()
    virtual void draw_rect(int x, int y, int width, int height) override;
    /// \see Canvas::fill_rect()
    virtual void fill_rect(int x, int y, int width, int height) override;
    /// \see Canvas::draw_circle()
    virtual void draw_circle(int x, int y, int radius) override;
    /// \see Canvas::fill_circle()
    virtual void fill_circle(int x, int y, int radius) override;
  }; // class CanvasWindow
} // namespace Proku

#endif // PROKU_CANVAS_WINDOW_HPP
