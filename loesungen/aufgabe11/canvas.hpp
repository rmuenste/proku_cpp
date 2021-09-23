#pragma once
#ifndef PROKU_CANVAS_HPP
#define PROKU_CANVAS_HPP

#include <string>

namespace Proku
{
  /**
   * \brief Schnittstelle einer Leinwand
   *
   * Diese abstrakte Klasse definiert eine Schnittstelle fuer eine Leinwand,
   * auf welcher mit Hilfe der zur Verfuegung gestellten Member-Funktionen
   * gezeichnet werden kann.
   */
  class Canvas
  {
  public:
    /// virtueller leerer Destruktor
    virtual ~Canvas()
    {}

    /// Gibt die aktuelle Breite der Leinwand zurueck.
    virtual int get_width() const = 0;

    /// Gibt die aktuelle Hoehe der Leinwand zurueck.
    virtual int get_height() const = 0;

    /**
     * \brief Beginnt das Zeichnen auf der Leinwand.
     *
     * Diese Funktion muss aufgerufen werden, bevor die
     * erste Zeichen-Funktion aufgerufen werden kann.
     */
    virtual void paint_begin() = 0;

    /**
     * \brief Beendet das Zeichnen auf der Leinwand.
     * 
     * Diese Funktion muss aufgerufen werden, nachdem
     * die letzte Zeichen-Funktion aufgerufen wurde.
     */
    virtual void paint_finish() = 0;

    /**
     * \brief Waehlt die aktuelle Zeichenfarbe.
     *
     * \param[in] red
     * Der Rot-Anteil der auszuwaehlenden RGB-Farbe im Bereich [0,1].
     *
     * \param[in] green
     * Der Gruen-Anteil der auszuwaehlenden RGB-Farbe im Bereich [0,1].
     *
     * \param[in] blue
     * Der Blau-Anteil der auszuwaehlenden RGB-Farbe im Bereich [0,1].
     */
    virtual void select_color(double red, double green, double blue) = 0;

    /**
     * \brief Zeichnet einen String.
     *
     * \param[in] x, y
     * Die Koordinaten des Punktes, an dem der String gezeichnet werden soll.
     *
     * \param[in] text
     * Die Zeichenkette, die gezeichnet werden soll.
     */
    virtual void draw_string(int x, int y, const std::string& text) = 0;

    /**
     * \brief Zeichnet eine Linie.
     *
     * \param[in] x1, y1
     * Die Koordinaten des Anfangspunktes.
     *
     * \param[in] x2, y2
     * Die Koordinaten des Endpunktes.
     */
    virtual void draw_line(int x1, int y1, int x2, int y2) = 0;

    /**
     * \brief Zeichnet ein Rechteck.
     *
     * \param[in] x, y
     * Die Koordinaten der oberen linken Ecke.
     *
     * \param[in] width, height
     * Die Breite und Hoehe des Recheckts. Muessen beide > 0 sein.
     */
    virtual void draw_rect(int x, int y, int width, int height) = 0;

    /**
     * \brief Zeichnet eine ausgefuellte Rechteckflaeche.
     *
     * \param[in] x, y
     * Die Koordinaten der oberen linken Ecke.
     *
     * \param[in] width, height
     * Die Breite und Hoehe des Recheckts. Muessen beide > 0 sein.
     */
    virtual void fill_rect(int x, int y, int width, int height) = 0;

    /**
     * \brief Zeichnet einen Kreis.
     *
     * \param[in] x, y
     * Die Koordinaten des Kreismittelpunktes.
     *
     * \paran[in] radius
     * Der Radius des Kreises. Muss > 0 sein.
     */
    virtual void draw_circle(int x, int y, int radius) = 0;

    /**
     * \brief Zeichnet eine ausgefuellte Kreisflaeche.
     *
     * \param[in] x, y
     * Die Koordinaten des Kreismittelpunktes.
     *
     * \paran[in] radius
     * Der Radius des Kreises. Muss > 0 sein.
     */
    virtual void fill_circle(int x, int y, int radius) = 0;
  }; // class Canvas
} // namespace Proku

#endif // PROKU_CANVAS_HPP
