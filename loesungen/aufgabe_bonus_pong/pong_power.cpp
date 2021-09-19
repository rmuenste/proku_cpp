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

// Hilfs-Funktion:
// Gebe den Index 0 <= k < n der groessten Zahl 0 <= x[k] < 1 zurueck.
int imax_0_1(double* x, int n)
{
  int k = -1;
  double t = -1.0;
  for(int i(0); i < n; ++i)
  {
    if((x[i] >= 0.0) && (x[i] < 1.0) && (x[i] > t))
    {
      k = i;
      t = x[i];
    }
  }
  return k;
}

int main(int argc, char* argv[])
{
  // Spieler-Namen setzen
  const std::string player_l = (argc > 1 ? argv[1] : "Spieler Links");
  const std::string player_r = (argc > 2 ? argv[2] : "Spieler Rechts");

  // Fenter-Titel setzen
  std::string title = "Power Pong";
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

  // Benoetigte Wand-Treffer pro Punkt
  int hits_per_point = 3;

  // Punkte der beiden Spieler
  int points_l = 0, points_r = 0;

  // Position des linken Spieler-Balkens
  int bar_l_x = 10;
  int bar_l_y = (wnd_h - bar_h)/2;

  // Position des rechen Spieler-Balkens
  int bar_r_x = wnd_w - bar_w - 10;
  int bar_r_y = (wnd_h - bar_h)/2;

  // Position des Spiel-Balls
  int ball_x = wnd_w/2, ball_y = wnd_h/2;

  // Bewegungs-Richtung des Spiel-Balls
  int move_x = 0, move_y = 0;

  // Treffer-Anzahl der linken/rechten Wand
  int hits_wall_l = 0, hits_wall_r = 0;

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

    // Pruefe, ob die Fenstergroesse geaendert wurde:
    {
      const int old_w = wnd_w;
      const int old_h = wnd_h;
      wnd_w = window.width();
      wnd_h = window.height();
      if((wnd_w != old_w) || (wnd_h != old_h))
      {
        // neue Fenstergroesse
        // interpoliere neue Balkenpositionen
        bar_r_x = (bar_r_x * wnd_w) / old_w;
        bar_r_y = (bar_r_y * wnd_h) / old_h;
        bar_l_x = (bar_l_x * wnd_w) / old_w;
        bar_l_y = (bar_l_y * wnd_h) / old_h;

        // interpoliere neue Ballposition
        (ball_x *= wnd_w) /= old_w;
        (ball_y *= wnd_h) /= old_h;

        // Geschwindigkeit anpassen
        //(move_x *= wnd_w) /= old_w;
        //(move_y *= wnd_h) /= old_h;
      }
    }

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
      move_x = (point_for <= 0 ? +speed_bars : -speed_bars);
      move_y = 0;
      // Wall-Punkte-Zaehler zuruecksetzen
      point_for = 0;
      hits_wall_l = hits_wall_r = 0;
      // Neue Runde beginnt
      is_running = true;
    }

    // Falls das Spiel pausiert ist, kann die Anzahl der benoetigten
    // Wand-Treffer pro Punk eingestellt werden:
    if(!is_running)
    {
      // Teste alle Tasten von 1 bis 9
      for(int i(1); i < 10; ++i)
      {
        if(keymap.check(9+i))
        {
          hits_per_point = i;
        }
      }
    }

    // Bevor wir die Benutzer-Eingaben abfragen und die neuen
    // Balken-Positionen berechnen, legen wir zunaechst Kopien
    // der alten Balken-Posititionen an:
    const int old_bar_r_x = bar_r_x;
    const int old_bar_r_y = bar_r_y;
    const int old_bar_l_x = bar_l_x;
    const int old_bar_l_y = bar_l_y;

    // Eingaben des linken Spielers abfragen:
    if(keymap.check( 25))  bar_l_y -= speed_bars; // W
    if(keymap.check( 39))  bar_l_y += speed_bars; // S
    if(keymap.check( 38))  bar_l_x -= speed_bars; // A
    if(keymap.check( 40))  bar_l_x += speed_bars; // D

    // Eingaben des rechten Spielers abfragen:
    if(keymap.check(111)) bar_r_y -= speed_bars; // UP
    if(keymap.check(116)) bar_r_y += speed_bars; // DOWN
    if(keymap.check(113)) bar_r_x -= speed_bars; // LEFT
    if(keymap.check(114)) bar_r_x += speed_bars; // RIGHT

    // Stelle sicher, dass beide Balken innerhalb ihrer
    // Bewegungszone liegen; nutze dazu die 'clamp' Funktion
    clamp(bar_l_y, 0, wnd_h - bar_h);
    clamp(bar_r_y, 0, wnd_h - bar_h);
    clamp(bar_l_x, 10, wnd_w/2 - bar_w - 100);
    clamp(bar_r_x, wnd_w/2 + 100, wnd_w - bar_w - 10);

    // Die Balken sind jetzt an ihrer neuen Position

    // Luaeft bei dir?
    if(is_running)
    {
      // Okay, Spiel laueft (d.h. es ist nicht pausiert),
      // also aktualisiere die Ball-Position:
      ball_x += move_x;
      ball_y += move_y;
    }

    // Kollisions-Schleife:
    bool coll_testing = is_running;
    while(coll_testing)
    {
      // Array fuer die Kollisions-Zeiten
      double coll_times[6] =
      {
        -1.0, -1.0, // Balken links/rects
        -1.0, -1.0, // Wand links/rechts
        -1.0, -1.0  // Wand oben/unten
      };

      // Zunaechst testen wir den linken Balken:
      // Dazu muessen wir zuerst sicherstellen, dass
      // 1.) sich der Ball nach links bewegt
      // 2.) sich Ball und Balken nicht gleich schnell bewegen,
      //     da wir sonst gleich durch Null dividieren wuerden
      if((move_x < 0) && (move_x != bar_l_x - old_bar_l_x))
      {
        // Wir muessen nun pruefen, ob der Ball und der linke Balken zwischen
        // diesem und dem letzten Frame eine identische X-Koordinate hatten.
        // In Formeln ausgedrueckt
        // * R  = der Radius des Balls
        // * B' = aktuelle X-Koordinate des Balls ("ball_x")
        // * B  = vorherige X-Koordinate des Balls ("ball_x - move_x")
        // * Q' = aktuelle X-Koordinate des Balkens ("bar_l_x")
        // * Q  = vorherige X-Koordinate des Balkens ("old_bar_l_x")
        // * W  = die Breite des Balkens
        //
        // Dann: Suche t in [0,1], so dass:
        //    Q' + W - t*(Q' - Q) = B' - R - t*(B' - B)
        //   \___________________/ \__________________/
        //        Balken zum             Ball zum
        //       Zeitpunkt -t          Zeitpunkt -t
        //
        // Aufloesen nach 't' ergibt:
        //    t = (Q' + W - B' + R) / (Q' - Q - (B' - B))
        //
        // Die obige if-Abfrage stellt sicher, dass der Nenner nicht Null ist
        //
        // Hinweis: Hier ist move_x = (B' - B).
        double t_l = double(bar_l_x + bar_w - ball_x + ball_r)
                    / double(bar_l_x - old_bar_l_x - move_x);

        // Berechne Ball-Position zum Zeitpunkt -t:
        double ball_yt  = double(ball_y) - t_l * double(move_y);

        // Berechne Y-Koordinate des Balkens zum Zeitpunkt -t
        double bar_l_yt = double(bar_l_y) - t_l * double(bar_l_y - old_bar_l_y);

        // Pruefe, ob die Y-Koordinate des Balls im Y-Intervall des
        // Balkens liegt (falls nicht, dann ist der Ball ueber oder unter
        // dem Balken vorbeigegangen):
        if((bar_l_yt <= ball_yt) && (ball_yt <= bar_l_yt + double(bar_h)))
        {
          // Jawohl, Kollision
          coll_times[0] = t_l;
        }
      }

      // Jetzt testen wir den rechten Balken:
      // Analog zum linken Balken
      if((move_x > 0) && (move_x != bar_r_x - old_bar_r_x))
      {
        // Hier gilt es eine aehnliche Gleichung zu loesen im Falle des
        // linken Balkens, allerdings:
        // 1. die Balken-Breite faellt weg
        // 2. wir haben "B' + R" statt "B' - R" auf der rechten Seite
        //
        // Also: Suche t in [0,1], so dass:
        //    Q' - t*(Q' - Q) = B' + R - t*(B' - B)
        //   \_______________/ \_________________/
        //      Balken zum          Ball zum
        //     Zeitpunkt -t       Zeitpunkt -t
        //
        // Aufloesen nach 't' ergibt:
        //    t = (Q' - B' - R) / (Q' - Q - (B' - B))

        double t_r = double(bar_r_x - ball_x - ball_r)
                   / double(bar_r_x - old_bar_r_x - move_x);

        // Berechne Ball-Position zum Zeitpunkt -t:
        double ball_yt  = double(ball_y) - t_r * double(move_y);

        // Berechne Y-Koordinate des Balkens zum Zeitpunkt -t
        double bar_r_yt = double(bar_r_y) - t_r * double(bar_r_y - old_bar_r_y);

        // Teste Ball-Balken-Kollision:
        if((bar_r_yt <= ball_yt) && (ball_yt <= bar_r_yt + double(bar_h)))
        {
          // Jawohl, Kollision
          coll_times[1] = t_r;
        }
      }

      // Kollisions-Zeit linke Wand:
      // Formel analog zu linkem Balken mit Q = Q' = W = 0
      if(move_x < 0)
        coll_times[2] = double(ball_x - ball_r) / double(move_x);

      // Kollisions-Zeit rechte Wand
      // Formel analog zu rechtem Balken mit Q = Q' = 0
      if(move_x > 0)
        coll_times[3] = double(ball_x + ball_r - wnd_w) / double(move_x);

      // Kollisions-Zeit obere Wand (analog zu linke Wand)
      if(move_y < 0)
        coll_times[4] = double(ball_y - ball_r) / double(move_y);

      // Kollisions-Zeit untere Wand (analog zu rechte Wand)
      if(move_y > 0)
        coll_times[5] = double(ball_y + ball_r - wnd_h) / double(move_y);

      // Bestimme die frueheste Kollision (falls ueberhaupt):
      switch(imax_0_1(coll_times, 6))
      {
      case 0: // Kollision mit linkem Balken
        // Ball-Position korrigieren und Richtung umkehren
        ball_x = ball_x - int(2.0 * coll_times[0] * double(move_x));
        move_x = -move_x;

        // Jetzt noch die Richtungsaenderung durch die Balken-Bewegung:
        if(bar_l_x > old_bar_l_x) // nach rechts -> beschleunigen
          move_x += speed_ball;
        if(bar_l_x < old_bar_l_x) // nach links -> abbremsen
          move_x -= speed_ball;
        if(bar_l_y > old_bar_l_y) // nach unten
          move_y += speed_ball;
        if(bar_l_y < old_bar_l_y) // nach oben
          move_y -= speed_ball;
        break;

      case 1: // Kollision mit rechtem Balken
        // Ball-Position korrigieren und Richtung umkehren
        ball_x = ball_x - int(2.0 * coll_times[1] * double(move_x));
        move_x = -move_x;

        if(bar_r_x < old_bar_r_x) // nach links -> beschleunigen
          move_x -= speed_ball;
        if(bar_r_x > old_bar_r_x) // nach rechts -> abbremsen
          move_x += speed_ball;
        if(bar_r_y > old_bar_r_y) // nach unten
          move_y += speed_ball;
        if(bar_r_y < old_bar_r_y) // nach oben
          move_y -= speed_ball;
        break;

      case 2: // Kollision mit linker Wand
        // Hat der rechte Spieler einen Punkt errungen?
        if(++hits_wall_l >= hits_per_point)
        {
          // Ein Punkt fuer den rechten Spieler
          point_for = +1;
          ++points_r;
          is_running = false;
          coll_testing = false;
          // Zur Optik: Halte Ball am Rand fest:
          ball_y += (ball_x*move_y) / (move_x);
          ball_x = 0;
        }
        else
        {
          // Ball-Position korrigieren und X-Richtung umkehren
          ball_x = 2*ball_r - ball_x;
          move_x = -move_x;
        }
        break;

      case 3: // Kollision mit rechter Wand
        // Hat der linke Spieler einen Punkt errungen?
        if(++hits_wall_r >= hits_per_point)
        {
          // Ein Punkt fuer den linken Spieler:
          point_for = -1;
          ++points_l;
          is_running = false;
          coll_testing = false;
          // Zur Optik: Halte Ball am Rand fest:
          ball_y -= ((wnd_w-ball_x)*move_y) / (move_x);
          ball_x = wnd_w;
          break;
        }
        else
        {
          // Ball-Position korrigieren und X-Richtung umkehren
          ball_x = 2*(wnd_w-ball_r) - ball_x;
          move_x = -move_x;
          continue;
        }

      case 4: // Kollision mit oberer Wand
        // Ball-Position korrigieren und Y-Richtung umkehren
        ball_y = 2*ball_r - ball_y;
        move_y = -move_y;
        break;

      case 5: // Kollision mit unterer Wand
        // Ball-Position korrigieren und Y-Richtung umkehren
        ball_y = 2*(wnd_h-ball_r) - ball_y;
        move_y = -move_y;
        break;

      default: // keine weiteren Kollisionen
        coll_testing = false;
        break;
      }
    } // if(coll_testing)

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
      sprintf(b+=32, "WALL HIT: %4i, %4i", hits_wall_l, hits_wall_r);
      sprintf(b+=32, "HITS PPT: %4i", hits_per_point);
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
