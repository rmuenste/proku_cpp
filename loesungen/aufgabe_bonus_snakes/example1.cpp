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

  // Loesche den Inhalt des Bildschirms
  console.clear();

  // Zeichne "Hello World" in "Rot auf Weiss"
  console.set_color(Color::red_on_white);
  std::string msg(" Hello World from ncurses! ");
  console.draw_string((max_x - int(msg.size()))/2, max_y/2-2, msg);

  // Zeichne Dimensionen in "Gelb auf Schwarz"
  console.set_color(Color::yellow_on_black);
  console.draw_string(max_x/2 - 10, max_y/2, "Max-X:");
  console.draw_int   (max_x/2 -  3, max_y/2, max_x);
  console.draw_string(max_x/2 +  2, max_y/2, "Max-Y:");
  console.draw_int   (max_x/2 +  9, max_y/2, max_y);

  // Zeichne Info in "Cyan auf Schwarz"
  console.set_color(Color::cyan_on_black);
  console.draw_string(max_x/2 - 17, max_y/2+2, "Druecken Sie Backspace zum Beenden");

  // Zeichne einen Rahmen um das Obige
  // Berechne Rahmen-Grenzen:
  int rx0 = max_x/2 - 22;
  int rx1 = max_x/2 + 22;
  int ry0 = max_y/2 -  4;
  int ry1 = max_y/2 +  4;

  // Zeichne Rahmen-Eckpunkte
  console.set_color(Color::white_on_black);
  console.draw_rect(rx0, ry0, rx1, ry1);

  // Setze Eingabe-Modus auf 'Warten'
  console.set_wait_mode(true);

  // Laufe solange in einer Endlos-Schleife,
  // bis der Benutzer Backspace drueckt
  while(console.get_key() != KEY_BACKSPACE)
  {
    // tue nichts...
  }

  // Fertig
  return 0;
}