#include "render_window.hpp"

// Hilfs-Funktion fuer FPS-Messung: gibt aktuelle Zeit zurueck
long long now()
{
  timeval tv;
  gettimeofday(&tv, nullptr);
  return 1000000ll * (long long)tv.tv_sec + (long long)tv.tv_usec;
}

// Hilfs-Funktion: v <- min(max(a,v),b))
void clamp(int& v, int a, int b)
{
  if(v < a) v = a;
  if(v > b) v = b;
}

int main(int argc, char* argv[])
{
  // Spieler-Namen setzen
  const std::string player_l = (argc > 1 ? argv[1] : "Spieler Links");
  const std::string player_r = (argc > 2 ? argv[2] : "Spieler Rechts");

  // Fenter-Titel setzen
  std::string title = "Classic Pong";
  if(argc > 2)
    title += ": " + player_l + " *VS* " + player_r;

  // Fenter erstellen
  Proku::RenderWindow window(title.c_str(), 1280, 640);

  // Zunaechst ein Satz an Konstanten

  // Timeout fuer Hauptschleife: 33ms (~30FPS)
  static constexpr int frame_timeout = 33;

  // Breite und Hoehe der Balken (10x100)
  static constexpr int bar_w = 10;
  static constexpr int bar_h = 100;

  // Ball-Radius
  static constexpr int ball_r = 10;

  // Bewegungs-Geschwindigkeit der Balken
  static constexpr int speed_bars = frame_timeout / 2;
  static constexpr int speed_ball = frame_timeout / 4;


  // Fenster-Dimensionen abfragen
  int wnd_w = window.width();
  int wnd_h = window.height();

  // Spiel-Zustand: laeuft bei dir?
  bool is_running = false;

  // An welchen Spieler geht der Punkt?
  // -1 -> linker Spieler
  // +1 -> rechter Spieler
  // 0  -> kein Punkt
  int point_for = 0;

  // Punkte der beiden Spieler
  int points_l = 0, points_r = 0;

  // Position des linken Spieler-Balkens
  const int bar_l_x = 30;
  int bar_l_y = (wnd_h - bar_h)/2;

  // Position des rechen Spieler-Balkens
  const int bar_r_x = wnd_w - bar_w - 30;
  int bar_r_y = (wnd_h - bar_h)/2;

  // Position des Spiel-Balls
  int ball_x = wnd_w/2, ball_y = wnd_h/2;

  // Bewegungs-Richtung des Spiel-Balls
  int move_x = 0, move_y = 0;

  // ein paar Zaehler fuer die FPS-Berechnung
  int frame_count(0), last_count(0);
  double fps = 0.0;
  long long last_time = now();
  long long first_time = last_time;


  // Haupt-Schleife
  while(window.process_events(frame_timeout))
  {
    // Zeit bestimmen und ggf FPS berechnen
    long long cur_time = now();
    ++frame_count;
    if(cur_time > last_time + 1000000ll)
    {
      fps = 1E6 * double(frame_count - last_count) / double(cur_time - last_time);
      last_time = cur_time;
      last_count = frame_count;
    }

    // Aktuelle Fenster-Groesse abfragen
    wnd_w = window.width();
    wnd_h = window.height();

    // aktuelle Keymap abfragen
    Proku::Keymap keymap = window.query_keymap();

    // Wurde ESC gedrueckt?
    if(keymap.check(9))
      break;

    // Falls das Spiel gerade pausiert ist und der Benutzer
    // die Leertaste drueckt, dann starten wir eine neue Runde:
    if(!is_running && keymap.check(65))
    {
      // Ball zurueck in die Fenster-Mitte
      ball_x = wnd_w / 2;
      ball_y = wnd_h / 2;
      // Ball-Richtung zuruecksetzen: Ball in Richtung des
      // Spielers, der die letzte Runde verloren hat:
      move_x = 3*(point_for <= 0 ? +speed_ball : -speed_ball);
      move_y = 0;
      // Wall-Punkte-Zaehler zuruecksetzen
      point_for = 0;
      // Neue Runde beginnt
      is_running = true;
    }

    // Bevor wir die Benutzer-Eingaben abfragen und die neuen
    // Balken-Positionen berechnen, legen wir zunaechst Kopien
    // der alten Balken-Posititionen an:
    const int old_bar_r_y = bar_r_y;
    const int old_bar_l_y = bar_l_y;

    // Eingaben des linken Spielers abfragen:
    if(keymap.check( 25))  bar_l_y -= speed_bars; // W
    if(keymap.check( 39))  bar_l_y += speed_bars; // S

    // Eingaben des rechten Spielers abfragen:
    if(keymap.check(111)) bar_r_y -= speed_bars; // UP
    if(keymap.check(116)) bar_r_y += speed_bars; // DOWN

    // Stelle sicher, dass beide Balken innerhalb ihrer
    // Bewegungszone liegen; nutze dazu die 'clamp' Funktion
    clamp(bar_l_y, 0, wnd_h - bar_h);
    clamp(bar_r_y, 0, wnd_h - bar_h);

    // Die Balken sind jetzt an ihrer neuen Position

    // Luaeft bei dir?
    if(is_running)
    {
      // Okay, Spiel laueft (d.h. es ist nicht pausiert),
      // also aktualisiere die Ball-Position:
      ball_x += move_x;
      ball_y += move_y;

      // Wir muessen jetzt pruefen, ob der Ball mit einem
      // Balken oder einer (oder mehreren) Wa(e)nd(en) kollidiert ist.

      // Wir muessen nun pruefen, ob der Ball und der linke Balken zwischen
      // diesem und dem letzten Frame eine identische X-Koordinate hatten.
      // In Formeln ausgedrueckt
      // * R  = der Radius des Balls
      // * B' = aktuelle X-Koordinate des Balls ("ball_x")
      // * B  = vorherige X-Koordinate des Balls ("ball_x - move_x")
      // * Q  = aktuelle X-Koordinate des Balkens ("bar_l_x")
      // * W  = die Breite des Balkens
      //
      // Dann: Suche t in [0,1], so dass:
      //    Q + W = B' - R - t*(B' - B)
      //
      // Aufloesen nach 't' ergibt:
      //    t = (B' - R - Q - W) / (B' - B)
      //
      // Hinweis: Hier ist move_x = (B' - B).
      double t_l = double(ball_x - ball_r - bar_l_x - bar_w) / double(move_x);

      // Ball und Balken hatten eine gemeinsame X-Koordinate, falls 0<t<=1:
      if((0.0 <= t_l) && (t_l < 1.0))
      {
        // Berechne Ball-Position zum Zeitpunkt -t:
        double ball_xt  = double(ball_x) - t_l * double(move_x);
        double ball_yt  = double(ball_y) - t_l * double(move_y);

        // Berechne Y-Koordinate des Balkens zum Zeitpunkt -t
        double bar_l_yt = double(bar_l_y) - t_l * double(bar_l_y - old_bar_l_y);

        // Pruefe, ob die Y-Koordinate des Balls im Y-Intervall des
        // Balkens liegt (falls nicht, dann ist der Ball ueber oder unter
        // dem Balken vorbeigegangen):
        if((bar_l_yt <= ball_yt) && (ball_yt <= bar_l_yt + double(bar_h)))
        {
          // Kollision: Ball trifft Balken

          // X-Koordinate des Balls korrigieren und
          // Bewegungsrichtung umkehren:
          ball_x = int(2.0*ball_xt) - ball_x;
          move_x = -move_x;

          // Jetzt pruefen wir noch, ob der Balken sich bewegt hat und
          // lenken ggf. den Ball nach oben oder unten ab:
          if(bar_l_y > old_bar_l_y) // nach unten
            move_y += speed_ball;
          if(bar_l_y < old_bar_l_y) // nach oben
            move_y -= speed_ball;
        }
      }

      // Jetzt testen wir den rechten Balken:
      // Hier gilt es eine aehnliche Gleichung zu loesen im Falle des
      // linken Balkens, allerdings:
      // 1. die Balken-Breite faellt weg
      // 2. wir haben "B + R" statt "B - R" auf der rechten Seite
      //
      // Also: Suche t in [0,1], so dass:
      //    Q = B + R - t*(B - B')
      //
      // Aufloesen nach 't' ergibt:
      //    t = (B + R - Q) / (B - B')

      double t_r = double(ball_x + ball_r - bar_r_x) / double(move_x);

      // Gemeinsame X-Koordinate?
      if((0.0 < t_r) && (t_r <= 1.0))
      {
        // Berechne Ball-Position zum Zeitpunkt -t:
        double ball_xt  = double(ball_x) - t_r * double(move_x);
        double ball_yt  = double(ball_y) - t_r * double(move_y);

        // Berechne Y-Koordinate des Balkens zum Zeitpunkt -t
        double bar_r_yt = double(bar_r_y) - t_r * double(bar_r_y - old_bar_r_y);

        // Teste Ball-Balken-Kollision:
        if((bar_r_yt <= ball_yt) && (ball_yt <= bar_r_yt + double(bar_h)))
        {
          // Ball-Position korrigieren und Richtung umkehren
          ball_x = int(2.0*ball_xt) - ball_x;
          move_x = -move_x;

          // Ball ablenken, falls der Balken sich bewegt:
          if(bar_r_y > old_bar_r_y) // nach unten
            move_y += speed_ball;
          if(bar_r_y < old_bar_r_y) // nach oben
            move_y -= speed_ball;
        }
      }

      // Teste, ob der Ball mit der oberen Wand kollidiert ist:
      if(ball_y < ball_r)
      {
        // Ball-Position korrigieren und Y-Richtung umkehren
        ball_y = 2*ball_r - ball_y;
        move_y = -move_y;
      }

      // Teste, ob der Ball mit der unteren Wand kollidiert ist:
      if(ball_y + ball_r > wnd_h)
      {
        // Ball-Position korrigieren und Y-Richtung umkehren
        ball_y = 2*(wnd_h-ball_r) - ball_y;
        move_y = -move_y;
      }

      // Teste, ob der Ball mit der linken Wand kollidiert ist:
      if(ball_x < ball_r)
      {
        // Ein Punkt fuer den rechten Spieler
        point_for = +1;
        ++points_r;
        is_running = false;

        // Zur Optik: Halte Ball am Rand fest:
        ball_y += (ball_x*move_y) / (move_x);
        ball_x = 0;
      }

      // Teste, ob der Ball mit der rechten Wand kollidiert ist:
      if(ball_x + ball_r > wnd_w)
      {
        // Ein Punkt fuer den linken Spieler:
        point_for = -1;
        ++points_l;
        is_running = false;

        // Zur Optik: Halte Ball am Rand fest:
        ball_y -= ((wnd_w-ball_x)*move_y) / (move_x);
        ball_x = wnd_w;
      }

    } // if(is_running)

    // Okay, Spiel-Stand ist aktualisiert, d.h. wir koennen jetzt
    // das neue Spiel-Feld zeichnen

    // Fenster loeschen:
    window.clear();

    // Debug-Informationen drucken
    {
      // QUICK & DIRTY: DON'T TRY THIS AT HOME !!!
      char buffer[1024];
      char* b = buffer-32;
      sprintf(b+=32, "WINDOW  : %i x %i", wnd_w, wnd_h);
      sprintf(b+=32, "FRAME   : %10i", frame_count);
      sprintf(b+=32, "TIME    : %10.3f", 1E-6*double(cur_time-first_time));
      sprintf(b+=32, "FPS     : %10.3f", fps);
      sprintf(b+=32, "BALL POS: %4i, %4i", ball_x, ball_y);
      sprintf(b+=32, "MOVE DIR: %4i, %4i", move_x, move_y);
      sprintf(b+=32, "LEFT BAR: %4i, %4i", bar_l_x, bar_l_y);
      sprintf(b+=32, "RGHT BAR: %4i, %4i", bar_r_x, bar_r_y);
      sprintf(b+=32, "POINTS  : %4i, %4i", points_l, points_r);
      for(int i(0); &buffer[32*i] <= b; ++i)
        window.draw_string(10, 13*(i+1), &buffer[32*i]);
    }

    // Falls das Spiel pausiert ist, schreiben wir eine Aufforderung,
    // dass die Leertaste gedrueckt werden soll, in das Fenster
    if(!is_running)
    {
      if(point_for != 0)
      {
        // Jemand hat einen Punkt gemacht; Anstoss ankuendigen
        std::string msg1 = "Punkt fuer ";
        std::string msg2 = "Anstoss fuer ";
        msg1 += (point_for < 0 ? player_l : player_r);
        msg2 += (point_for < 0 ? player_r : player_l);
        window.draw_string_center_x(wnd_h/2-50, msg1);
        window.draw_string_center_x(wnd_h/2-35, msg2);
      }

      window.draw_string_center_x(wnd_h/2-20, "Leertaste zum Starten");
    }

    // Punkte-Stand am oberen Bildschirmrand anzeigen:
    window.draw_string_center_x(15,
      std::to_string(points_l) + " : " + std::to_string(points_r));

    // nerviges Proku-Branding:
    if((frame_count / frame_timeout) % 2)
    {
      window.draw_string_center_x(wnd_h/2-200, "C/C++ Programmierkurs 2021");
      //window.draw_string_center_x(wnd_h/2-180, "Dipl.-Math. Peter Zajac");
      window.draw_string_center_x(wnd_h/2-160, "Lehrstuhl fuer angewandte Mathematik und Numerik");
      window.draw_string_center_x(wnd_h/2-140, "Fakultaet fuer Mathematik");
      window.draw_string_center_x(wnd_h/2-120, "Technische Universitaet Dortmund");
    }

    // zeiche die Mittellinie
    //window.draw_line(w/2, 0, w/2, h);

    // Zeichne linken Spiel-Balken
    window.fill_rect(bar_l_x, bar_l_y, bar_w, bar_h);

    // Zeichne rechten Spiel-Balken
    window.fill_rect(bar_r_x, bar_r_y, bar_w, bar_h);

    // Zeichne Spiel-Ball
    window.fill_circle(ball_x, ball_y, ball_r);

    // Fenster aktualisieren:
    window.update();

    // Frame fertig
  }

  return 0;
}
