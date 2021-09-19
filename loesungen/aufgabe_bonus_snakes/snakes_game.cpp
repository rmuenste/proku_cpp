#include <iostream>
#include "console.hpp"
#include "timer.hpp"
#include "snake.hpp"

bool run_game(Console& console, const std::string& player_1, const std::string& player_2)
{
  // Lese die Dimensionen des Bildschirms aus:
  const int max_x = console.get_max_x();
  const int max_y = console.get_max_y();

  // Erstelle Timer
  Timer timer;

  // Setze Eingabe-Modus auf 'nicht Warten'
  console.set_wait_mode(true);

  // TODO: Beide Schlangen erstellen

  // Laufe in einer Endlos-Schleife, bis der Benutzer Backspace drueckt
  for(int step(1); true; ++step)
  {
    // Loesche Spielfeld
    console.clear();

    // TODO: Spielfeld und Schlangen zeichnen

    // TODO: Spielzustand ueberpruefen: Ist eine Schlange tot?

    // TODO: Pruefen, ob jemand verloren hat und ggf. Dialogbox anzeigen

    // Eingabe-Schleife
    while(true)
    {
      // Versuche, eine Eingabe zu lesen
      int key = console.get_key();

      // Keine Eingabe vorhanden?
      if(key == 0)
        break;

      // Okay, welche Taste war das?
      switch(key)
      {
      case ' ':
        // Pause-Dialog anzeigen:
        console.show_dialog("Spiel Pausiert\n\nLeertaste zum Fortfahren");
        // Console wieder auf Nicht-Warten setzen:
        console.set_wait_mode(false);
        break;

      case KEY_BACKSPACE:
        // Programm beenden
        return false;

        // TODO: Weitere Eingaben behandeln
      }
    }

    // TODO: Schlangen weiterbewegen

    // auf Timer warten
    timer.sync(50);

  } // Endlos-Schleife

  // Programm-Ende
  return false;
}


int main(int argc, char* argv[])
{
  std::string player_1("Spieler 1");
  std::string player_2("Spieler 2");

  if(argc > 1) player_1 = argv[1];
  if(argc > 2) player_2 = argv[2];

  // Erstelle Console
  Console console;

  // Lese die Dimensionen des Bildschirms aus:
  const int max_x = console.get_max_x();
  const int max_y = console.get_max_y();

  // Pruefe dimensionen des Bildschirms
  if((max_x < 50) || (max_y < 30))
  {
    std::cout << "FEHLER: Bildschirm ist zu klein" << std::endl;
    return 1;
  }

  // Spiele in Endlos-Scjleife
  while(run_game(console, player_1, player_2))
  {
  }

  // Fertig
  return 0;
}