#include <iostream>
#include "console.hpp"
#include "timer.hpp"
#include "snake.hpp"

bool run_game(Console& console)
{
  // Lese die Dimensionen des Bildschirms aus:
  const int max_x = console.get_max_x();
  const int max_y = console.get_max_y();

  // Setze Eingabe-Modus auf 'nicht Warten'
  console.set_wait_mode(true);

  // Erstelle Schlange:
  Snake snake(+10, max_y/2, 17, Direction::right);

  // Erstelle Timer
  Timer timer;

  // Laufe in einer Endlos-Schleife, bis der Benutzer die Leertaste drueckt
  for(int step(1); true; ++step)
  {
    // Loesche Spielfeld
    console.clear();

    // Zeichne Spielfeldrand
    console.set_color(Color::white_on_black);
    console.draw_rect(0, 0, max_x-1, max_y-1);

    //#####################################################################
    //#####################################################################
    // Zeichne "Demo" Branding
    console.set_color(Color::red_on_white);
    if((step / 20) % 2 == 0)
    {
      console.draw_string(max_x/2-27, max_y/2-5, " C / C + +    P R O G R A M M I E R K U R S    2 0 2 1 ");
      console.draw_string(max_x/2-21, max_y/2+5, " D E M O - V E R S I O N  :  P H A S E  2 ");
    }
    else
    {
      console.draw_string(max_x/2-25, max_y/2-3, " F A K U L T A E T   F U E R   M A T H E M A T I K ");
      console.draw_string(max_x/2-32, max_y/2+3, " T E C H N I S C H E   U N I V E R S I T A E T   D O R T M U N D ");
    }

    //#####################################################################
    //#####################################################################

    // Zeichne Schlange
    console.set_color(Color::yellow_on_black);
    snake.draw(console);

    // Setze Farbe zurueck:
    console.set_color(Color::white_on_black);

    // Pruefe, was alles passiert ist:
    bool snake_hits_rect = snake.hits_rect(0, 0, max_x-1, max_y-1);
    bool snake_hits_self = snake.hits_self();

    // Pruefe, ob die Schlange mit der Wand kollidiert ist
    if(snake_hits_rect)
    {
      std::string msg = "Die Schlange ist mit der Wand kollidiert!";
      msg += "\n\nWollen Sie nochmal spielen?";
      return console.show_yes_no_dialog(msg);
    }

    // Pruefe, ob die Schlange mit sich selbst kollidiert ist
    if(snake_hits_self)
    {
      std::string msg = "Die Schlange hat sich selbst gebissen!";
      msg += "\n\nWollen Sie nochmal spielen?";
      return console.show_yes_no_dialog(msg);
    }

    // Erste Iteration?
    if(step == 1)
    {
      console.show_dialog("Leertaste zum Spielstart");
      console.set_wait_mode(false);
    }

    // Die aktuelle Richtung der Schlange
    Direction snake_dir = snake.get_direction();

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
        return false;

      case KEY_UP:
        if(snake_dir != Direction::down)
          snake_dir = Direction::up;
        break;

      case KEY_DOWN:
        if(snake_dir != Direction::up)
          snake_dir = Direction::down;
        break;

      case KEY_LEFT:
        if(snake_dir != Direction::right)
          snake_dir = Direction::left;
        break;

      case KEY_RIGHT:
        if(snake_dir != Direction::left)
          snake_dir = Direction::right;
        break;
      }
    }

    // Schlange weiter bewegen
    snake.move(snake_dir, (step % 5) == 0);

    // auf Timer warten
    timer.sync(50);

  } // Endlos-Schleife

  // Programm-Ende
  return false;
}

int main()
{
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

  // Spiel in Endlos-Schleife:
  while(run_game(console))
  {
  }

  // Fertig
  return 0;
}