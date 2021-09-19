#ifndef PROKU_GAME_CONSOLE_HPP
#define PROKU_GAME_CONSOLE_HPP

#include <string>
#include "base.hpp"

// Eine Enumeration fuer verschiedene Farb-Kombinationen
enum class Color
{
  // Auf Schwarz:
   white_on_black = 01,
     red_on_black = 02,
   green_on_black = 03,
    blue_on_black = 04,
    pink_on_black = 05,
  yellow_on_black = 06,
    cyan_on_black = 07,
  // Auf Weiss:
   black_on_white = 11,
     red_on_white = 12,
   green_on_white = 13,
    blue_on_white = 14,
    pink_on_white = 15,
  yellow_on_white = 16,
    cyan_on_white = 17,
}; // enum class Color

/// Eine Klasse, welche die Console unter 'curses' repräsentiert
class Console
{
public:
  /// Konstruktor:
  /// Schaltet auf den Modus von curses um.
  Console();

  /// Destruktor:
  /// Schaltet zurueck zum Standard-Konsolen-Modus.
  virtual ~Console();

  /// Loesche Kopier-Konstruktor
  Console(const Console&) = delete;
  /// Loesche Zuweisungs-Operator
  Console& operator=(const Console&) = delete;

  /// Setzt den Warte-Modus von 'get_key()'
  ///
  /// Diese Funktion bestimmt, wie die 'get_key()' Funktion reagiert, wenn
  /// seit dem letzten Aufruf dieser Funktion keine Taste eingegeben wurde.
  ///
  /// Fuer _block = true:
  /// Die 'get_key()' Funktion wartet so lange, bis der naechste Tastendruck
  /// erfolgt ist.
  ///
  /// Fuer _block = false:
  /// Die 'get_key()' Funktion gibt 0 zurueck, wenn seit dem letzten Aufruf
  /// kein neuer Tastendruck erfolgt ist.
  ///
  void set_wait_mode(bool _block);

  /// Gibt den naechten Tastendruck zurueck
  ///
  /// \returns
  /// Den Code der jeweiligen Taste, oder 0, falls der wartende Block-Modus
  /// per set_wait_mode(false) ausgeschaltet wurde und seit dem letzten
  /// Aufruf kein neuer Tastendruck erfolgt ist.
  int get_key();

  /// Gibt die Breite der Console zurueck.
  int get_max_x() const;

  /// Gibt die Hoese der Console zurueck
  int get_max_y() const;

  /// Aendert das verwendete Farb-Paar fuer alle folgenden
  /// Zeichen-Operationen
  void set_color(Color _color);

  /// Loescht den Inhalt der Console.
  void clear();

  /// Aktualisiert die Console.
  void refresh();

  /// Setzt ein einzelnes Zeichen in der Console
  ///
  /// \param[in] _p
  /// Der Punkt mit den Koordinaten
  ///
  /// \param[in] _char
  /// Das Zeichen, welches gesetzt werden soll.
  void set_char(const Point& _p, int _char);

  /// Setzt ein einzelnes Zeichen in der Console
  ///
  /// \param[in] _x, _y
  /// Die Koordinaten des "Pixels"
  ///
  /// \param[in] _char
  /// Das Zeichen, welches gesetzt werden soll.
  void set_char(int _x, int _y, int _char);

  /// Zeichnet einen rechteckigen Rahmen:
  ///
  /// \param[in] _x0, _y0
  /// Die Koordinaten der Ecke "Oben-Links"
  ///
  /// \param[in] _x1, _y1
  /// Die Koordinaten der Ecke "Unten-Rechts"
  void draw_rect(int _x0, int _y0, int _x1, int _y1);

  /// Zeichnet einen String:
  ///
  /// \param[in] _p
  /// Der Punkt mit den Koordinaten
  ///
  /// \param[in] _str
  /// Der zu zeichnende String.
  void draw_string(const Point& _p, const std::string& _str);

  /// Zeichnet einen String:
  ///
  /// \param[in] _x, _y
  /// Die Koordinaten des "Pixels"
  ///
  /// \param[in] _str
  /// Der zu zeichnende String.
  void draw_string(int _x, int _y, const std::string& _str);

  /// Zeichnet einen int-Wert:
  ///
  /// \param[in] _p
  /// Der Punkt mit den Koordinaten
  ///
  /// \param[in] _value
  /// Der zu zeichnende int-Wert.
  void draw_int(const Point& _p, int _value);

  /// Zeichnet einen int-Wert:
  ///
  /// \param[in] _x, _y
  /// Die Koordinaten des "Pixels"
  ///
  /// \param[in] _value
  /// Der zu zeichnende int-Wert.
  void draw_int(int _x, int _y, int _value);

  ///
  /// Zeigt eine zentrierte Dialog-Box mit Text an
  ///
  /// \param[in] msg
  /// Die Nachricht, welche gezeichnet werden soll
  ///
  /// \param[in] _center_text
  /// Gibt an, ob die Nachricht in der Box zentriert werden soll
  ///
  /// \param[in] _wait_key
  /// Die Taste, welche gedrueckt werden muss, um fortzufahren
  void show_dialog(const std::string& _msg, bool _center_text = true, int _wait_key = ' ');

  ///
  /// Zeigt eine zentrierte Dialog-Box mit Text an und
  /// wartet, bis 'j' oder 'n' eingegeben wurde.
  ///
  /// \param[in] msg
  /// Die Nachricht, welche gezeichnet werden soll
  ///
  /// \param[in] _center_text
  /// Gibt an, ob die Nachricht in der Box zentriert werden soll
  ///
  /// \returns
  ///  true, falls 'j' eingeben wurde
  /// false, falls 'n' eingegeben wurde
  bool show_yes_no_dialog(const std::string& _msg, bool _center_text = false);
}; // class Console

#endif // PROKU_GAME_CONSOLE_HPP
