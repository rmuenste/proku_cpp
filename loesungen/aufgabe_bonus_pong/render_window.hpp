#pragma once
#ifndef PROKU_RENDER_WINDOW_HPP
#define PROKU_RENDER_WINDOW_HPP

#include <cassert>
#include <string>
#include <stdexcept>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

namespace Proku
{
  /**
   * \brief Hilfs-Klasse zur Abfrage des aktuellen Tastatur-Status
   *
   * \author Peter Zajac
   */
  class Keymap
  {
  public:
    /// internes Daten-Array; nicht weiter beachten
    char keymap[32];

    /**
     * \brief Prueft, ob aktuell eine bestimme Taste gedrueckt ist
     *
     * \param[in] keycode
     * Der Code der Taste, deren Zustand abgefragt werden soll.
     * Muss zwischen 0 und 255 liegen.
     *
     * \returns
     * \c true, falls die Taste aktuell gedrueckt ist, sonst \c false.
     */
    bool check(int keycode) const
    {
      assert(keycode >= 0);
      assert(keycode <= 255);
      return ((keymap[keycode >> 3] >> (keycode & 7)) & 1) != 0;
    }
  }; // class Keymap

  /**
   * \brief Klasse zur Verwaltung eines Zeichen-Fensters
   *
   * Diese Klasse bietet einen einfachen Wrapper fuer das X-Fenstersystem
   * mit eingebauten Double-Buffering fuer die flackerfreie Darstellung von
   * schnell wechselnden Frames.
   *
   * \author Peter Zajac
   */
  class RenderWindow
  {
  private:
    // Ein ganzer Batzen an selstam klingenden internen Member-Variablen, die
    // uns Objekt-Orientierung sei Dank nicht die Bohne interessieren... :)
    Display* display;
    int x11_fd;
    fd_set x11_fds;
    Atom wm_delete_window;
    Window window;
    Pixmap pixmap;
    GC gcontext;
    int wnd_width, wnd_height, wnd_depth;
    long long last_time;

  public:
    /**
     * \brief Erstellt ein Fenster mit gegebenen Titel
     *
     * \param[in] _title
     * Der Titel des Fensters.
     *
     * \param[in] _width
     * Die gewuenschte Breite des Fensters (Standard: 640)
     *
     * \param[in] _height
     * Die gewuenschte Hoehe des Fensters (Standard: 480)
     */
    explicit RenderWindow(const std::string& _title, int _width = 640, int _height = 480);
    /// Kopierschutz
    RenderWindow(const RenderWindow&) = delete;
    /// Kopierschutz
    RenderWindow& operator=(const RenderWindow&) = delete;
    /// virtueller Destruktor
    virtual ~RenderWindow();

    /// Gibt die aktuelle Breite des Zeichenbereiches zurueck.
    int width() const
    {
      return wnd_width;
    }

    /// Gibt die aktuelle Hoehe des Zeichenbereiches zurueck.
    int height() const
    {
      return wnd_height;
    }

    /**
     * \brief Gibt die aktuelle Keymap zurueck
     *
     * \returns
     * Ein Keymap-Objekt, welches den aktuellen Tastatur-Zustand repraesentiert.
     */
    Keymap query_keymap();

    /**
     * \brief Arbeitet die Interaktion mit dem Betriebssystem ab.
     *
     * Diese Funktion muss in regelmaessigen Abstaenden aufgerufen werden,
     * damit die Interaktion des Fensters mit dem Betriebssystem abgearbeitet
     * werden kann.
     *
     * \param[in] _timeout
     * Der timeout in Millisekunden.
     *
     * \returns
     * \c true, falls der timeout erreicht wurde, oder
     * \c false, falls der Benutzer das Fenster geschlossen hat.
     */
    bool process_events(int timeout);

    /**
     * \brief Leert die Zeichenflaeche des Fenters.
     */
    void clear();

    /**
     * \brief Aktualisiert die Zeichenflaeche.
     *
     * Diese Funktion muss aufgerufen werden, sobald alle Zeichenbefehle
     * ausgefuehrt wurden, damit die Aenderungen auf das Fenster
     * uebertragen werden koennen.
     */
    void update();

    /**
     * \brief Zeichnet einen String in das Fenster
     *
     * \param[in] x, y
     * Die Position des Strings im Fenster.
     *
     * \param[in] text
     * Der zu zeichnende String.
     */
    void draw_string(int x, int y, const std::string& text);

    /**
     * \brief Zeichnen einen String horizontal zentriert ins Fenster
     *
     * \param[in] y
     * Die vertikale Position des Strings im Fenster.
     *
     * \param[in] text
     * Der zu zeichnende String.
     */
    void draw_string_center_x(int y, const std::string& text);

    /**
     * \brief Zeichnet einen einzelnen Punkt ins Fenster
     *
     * \param[in] x, y
     * Die Position des Punktes im Fenster.
     */
    void draw_point(int x, int y);

    /**
     * \brief Zeichnet eine Linie ins Fenster
     *
     * \param[in] x1, y1
     * Die Position des Linien-Start-Punktes im Fenster.
     *
     * \param[in] x2, y2
     * Die Position des Linien-End-Punktes im Fenster.
     */
    void draw_line(int x1, int y1, int x2, int y2);

    /**
     * \brief Zeichnet einen Rechteck-Rahmen ins Fenster
     *
     * \param[in] x, y
     * Die Position der oberen linken Ecke des Rechtecks im Fenster.
     *
     * \param[in] w, h
     * Die Breite und Hoehe des Rechtecks.
     */
    void draw_rect(int x, int y, int w, int h);

    /**
     * \brief Zeichnet eine Rechteck-Flaeche ins Fenster
     *
     * \param[in] x, y
     * Die Position der oberen linken Ecke des Rechtecks im Fenster.
     *
     * \param[in] w, h
     * Die Breite und Hoehe des Rechtecks.
     */
    void fill_rect(int x, int y, int w, int h);

    /**
     * \brief Zeichnet einen Kreis ins Fenster
     *
     * \param[in] x, y
     * Die Position des Kreis-Mittelpunktes im Fenster.
     *
     * \param[in] radius
     * Der Radius des Kreises.
     */
    void draw_circle(int x, int y, int radius);

    /**
     * \brief Zeichnet eine Kreis-Flaeche ins Fenster
     *
     * \param[in] x, y
     * Die Position des Kreis-Mittelpunktes im Fenster.
     *
     * \param[in] radius
     * Der Radius des Kreises.
     */
    void fill_circle(int x, int y, int radius);

  protected:
    /// interne Hilfs-Funktion: Event-Handler fuer configure-Event
    virtual void on_configure(XConfigureEvent& ev);
  }; // class RenderWindow

} // namespace Proku

#endif // PROKU_RENDER_WINDOW_HPP
