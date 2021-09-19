#include <iostream>
#include <algorithm>
#include "console.hpp"
#include "timer.hpp"

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

  // Setze Eingabe-Modus auf 'nicht Warten'
  console.set_wait_mode(false);

  // Start-Position des Punktes
  Point pos(max_x / 2, max_y / 2);

  // Bewegungs-Richtung des Punktes
  Direction dir(Direction::right);

  // Erstelle Timer
  Timer timer;

  // Laufe in einer Endlos-Schleife, bis der Benutzer Backspace drueckt
  bool quit(false);
  while(!quit)
  {
    // Zeichne Feld
    console.clear();
    console.set_char(pos, '*');

    // Zeichne Info-Text
    console.draw_string(max_x/2-11, max_y/2-2, "Leertaste zum Pausieren");
    console.draw_string(max_x/2-10, max_y/2+2, "Backspace zum Beenden");

    // warte auf den Timer
    timer.sync(30);

    // Eingabe-Schleife
    while(!quit)
    {
      // Versuche, eine Eingabe zu lesen
      int key = console.get_key();

      // Keine Eingabe vorhanden?
      if(key == 0)
        break;

      // War das die Leertaste?
      switch(key)
      {
      // Leertaste: Spiel pausieren
      case ' ':
        // Pause-Dialog anzeigen:
        console.show_dialog("Spiel Pausiert\n\nLeertaste zum Fortfahren");
        // Console wieder auf Nicht-Warten setzen:
        console.set_wait_mode(false);
        break;

      // Backspace: "Spiel" beenden
      case KEY_BACKSPACE:
        quit = true;
        break;

      // Jede andere Taste wird ignoriert
      default:
        break;
      }
    }

    // Position aktualisieren
    switch(dir)
    {
    case Direction::right:
      // Laufe einen Schritt nach rechts und pruefe,
      // ob wir am Rand angekommen sind
      if(++pos.x >= max_x)
      {
        // Wir sind am rechten Rand, aendere Richtung
        dir = Direction::left;
        pos.x = max_x - 1;
      }
      break;

    case Direction::left:
      // Laufe einen Schritt nach links und pruefe,
      // ob wir am Rand angekommen sind
      if(--pos.x < 0)
      {
        // Wir sind am linken Rand, aendere Richtung
        dir = Direction::right;
        pos.x = 0;
      }
      break;

    // Nur damit der g++ nicht meckert:
    case Direction::up:
    case Direction::down:
      break;
    }
  } // Endlos-Schleife

  // Fertig
  return 0;
}