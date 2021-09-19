#include <iostream>
#include "console.hpp"

int main()
{
  // Erstelle Console-Objekt
  Console console;

  // Lese die Dimensionen des Bildschirms aus:
  const int max_x = console.get_max_x();
  const int max_y = console.get_max_y();

  // Stelle sicher, dass die Console gross genug ist:
  if((max_x < 50) || (max_y < 30))
  {
    std::cout << "FEHLER: Konsole ist zu klein" << std::endl;
    return 1;
  }

  // Setze Eingabe-Modus auf 'Warten'
  console.set_wait_mode(true);

  // Position des Punktes
  int pos_x = max_x / 2;
  int pos_y = max_y / 2;

  // Laufe solange in einer Endlos-Schleife,
  // bis der Benutzer die Leertaste drueckt
  bool quit(false);
  while(!quit)
  {
    // Loesche Bildschirm
    console.clear();

    // Zeichne Info-Text
    console.draw_string(max_x/2-10, max_y/2-2, "Backspace zum Beenden");
    console.draw_string(max_x/2-11, max_y/2+2, "Pfeiltasten zum Steuern");

    // Zeichne den Marker an seiner aktuellen Position
    console.set_char(pos_x, pos_y, '*');

    // Eingabe-Schleife
    bool have_input(false);
    while(!quit && !have_input)
    {
      // Warte auf naechsten Tastendruck:
      switch(console.get_key())
      {
      case KEY_RIGHT:
        // Laufe nach Rechts
        pos_x = std::min(pos_x+1, max_x-1);
        have_input = true;
        break;

      case KEY_LEFT:
        // Laufe nach Links
        pos_x = std::max(pos_x-1, 0);
        have_input = true;
        break;

      case KEY_DOWN:
        // Laufe nach Unten
        pos_y = std::min(pos_y+1, max_y-1);
        have_input = true;
        break;

      case KEY_UP:
        // Laufe nach Oben
        pos_y = std::max(pos_y-1, 0);
        have_input = true;
        break;

      case KEY_BACKSPACE:
        // Programm Beenden
        quit = true;
        break;
      }
    } // Eingabe-Schleife
  } // Endlos-Schleife

  // Fertig
  return 0;
}