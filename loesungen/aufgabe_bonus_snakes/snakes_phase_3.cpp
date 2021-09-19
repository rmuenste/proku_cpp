#include <iostream>
#include "console.hpp"
#include "timer.hpp"
#include "snake.hpp"

bool run_game(Console& console, const std::string& player_1, const std::string& player_2)
{
  // Lese die Dimensionen des Bildschirms aus:
  const int max_x = console.get_max_x();
  const int max_y = console.get_max_y();

  // Setze Eingabe-Modus auf 'nicht Warten'
  console.set_wait_mode(true);

  // Erstelle Timer
  Timer timer;

  // Erstelle Schlangen:
  Snake snake_1(     +10, max_y/2, 17, Direction::right);
  Snake snake_2(max_x-10, max_y/2, 17, Direction::left);

  // Laufe in einer Endlos-Schleife, bis der Benutzer Backspace drueckt
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
      console.draw_string(max_x/2-21, max_y/2+5, " D E M O - V E R S I O N  :  P H A S E  3 ");
    }
    else
    {
      console.draw_string(max_x/2-25, max_y/2-3, " F A K U L T A E T   F U E R   M A T H E M A T I K ");
      console.draw_string(max_x/2-32, max_y/2+3, " T E C H N I S C H E   U N I V E R S I T A E T   D O R T M U N D ");
    }

    //#####################################################################
    //#####################################################################

    // Zeichne Schlange 1
    console.set_color(Color::yellow_on_black);
    snake_1.draw(console);

    // Zeichne Schlange 2
    console.set_color(Color::cyan_on_black);
    snake_2.draw(console);

    // Setze Farbe zurueck:
    console.set_color(Color::white_on_black);

    // Pruefe, was alles passiert ist:
    bool snake1_hits_rect  = snake_1.hits_rect(0, 0, max_x-1, max_y-1);
    bool snake1_hits_self  = snake_1.hits_self();
    bool snake1_hits_other = snake_1.hits_other(snake_2);
    bool snake2_hits_rect  = snake_2.hits_rect(0, 0, max_x-1, max_y-1);
    bool snake2_hits_self  = snake_2.hits_self();
    bool snake2_hits_other = snake_2.hits_other(snake_1);

    // Schlangen tot?
    bool snake1_is_dead = snake1_hits_rect || snake1_hits_self || snake1_hits_other;
    bool snake2_is_dead = snake2_hits_rect || snake2_hits_self || snake2_hits_other;

    // Beide Schlangen tot?
    if(snake1_is_dead && snake2_is_dead)
    {
      std::string msg = "Beide Schlagen sind gestorben!\n\nWollen Sie nochmal spielen?";
      return console.show_yes_no_dialog(msg);
    }
    // Schlange 1 tot?
    if(snake1_is_dead)
    {
      std::string msg = player_1 + " hat einen Unfall gebaut!\n\n";
      msg += player_2 + " hat gewonnen!\n\n";
      msg += "Wollen Sie nochmal spielen?";
      return console.show_yes_no_dialog(msg);
    }
    // Schlange 2 tot?
    if(snake2_is_dead)
    {
      std::string msg = player_2 + " hat einen Unfall gebaut!\n\n";
      msg += player_1 + " hat gewonnen!\n\n";
      msg += "Wollen Sie nochmal spielen?";
      return console.show_yes_no_dialog(msg);
    }

    // Erste Iteration?
    if(step == 1)
    {
      //std::string msg = player_2 + " (Blau)  *vs*  " + player_1 + "  (Gelb)\n\n";
      std::string msg = player_1 + " (Gelb)  *vs*  " + player_2 + "  (Blau)\n\n";
      msg += "Druecken Sie die Leertaste,\num das Spiel zu beginnen";
      console.show_dialog(msg);
      console.set_wait_mode(false);
    }

    // Die aktuelle Richtung der Schlangen
    Direction snake_dir_1 = snake_1.get_direction();
    Direction snake_dir_2 = snake_2.get_direction();

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

      case KEY_UP:
        if(snake_1.get_direction() != Direction::down)
          snake_dir_1 = Direction::up;
        break;

      case KEY_DOWN:
        if(snake_1.get_direction() != Direction::up)
          snake_dir_1 = Direction::down;
        break;

      case KEY_LEFT:
        if(snake_1.get_direction() != Direction::right)
          snake_dir_1 = Direction::left;
        break;

      case KEY_RIGHT:
        if(snake_1.get_direction() != Direction::left)
          snake_dir_1 = Direction::right;
        break;

      case 'w':
        if(snake_2.get_direction() != Direction::down)
          snake_dir_2 = Direction::up;
        break;

      case 's':
        if(snake_2.get_direction() != Direction::up)
          snake_dir_2 = Direction::down;
        break;

      case 'a':
        if(snake_2.get_direction() != Direction::right)
          snake_dir_2 = Direction::left;
        break;

      case 'd':
        if(snake_2.get_direction() != Direction::left)
          snake_dir_2 = Direction::right;
        break;
      }
    }

    // Schlange weiter bewegen
    snake_1.move(snake_dir_1, (step % 5) == 0);
    snake_2.move(snake_dir_2, (step % 5) == 0);

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