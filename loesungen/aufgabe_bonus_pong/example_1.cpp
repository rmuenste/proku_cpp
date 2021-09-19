#include "render_window.hpp"

int main()
{
  // Erstelle ein Fenster mit Titel "Beispiel 1" der Breite 320 und Hoehe 240:
  Proku::RenderWindow window("Beispiel 1", 320, 240);

  // In diesem Beispiel wird ein Kreis auf dem Fenster gezeichnet, welcher
  // sich horizontal auf dem Fenster hin und her bewegt und dabei an den
  // Fensterraendern "abprallt".

  // Zwei Variablen fuer die aktuelle Position des Kreises;
  // wir starten am Mittelpunkt des erstellten Fensters:
  int ball_x = window.width()  / 2; // halbe Breite
  int ball_y = window.height() / 2; // halbe Hoehe

  // Eine weitere Variable fuer die aktuelle Richtung, in welche sich der
  // Ball bewegt. Ein positiver Wert ist eine Bewegung nach rechts, ein
  // negativer Wert entsprechend eine Bewegung nach links.
  int move_x = 15;

  // Und eine Konstante, welche den Ball-Radius repraesentiert:
  const int ball_radius = 10;

  // Das eigentliche Programm wird in einer sogenannten Haupt-Schleife
  // ausgefuehrt, welche hier in einer einfachen while-Schleife realisiert
  // wird. In jeder Iteration muss zunaechst die 'process_events' Funktion
  // aufgerufen werden, in welcher das Fenter-Objekt diverse Interaktionen
  // mit dem Betriebssystem vollzieht (welche uns hier nicht naeher inter-
  // essieren). Das einzige Argument, welches an die Funktion uebergeben
  // wird, ist ein sogenannter "timeout" in Millisekunden, welcher angibt,
  // wie viel Zeit zwischen den Rueckgaben zweier aufeinander folgender
  // Funtionsaufrufe maximal vergehen darf -- oder anders ausgedrueckt:
  // Wenn wir wollen, dass die Hauptschleife maximal N Iterationen pro
  // Sekunde ausgefuehrt wird, dann koennen wir dies erreichen, indem wir
  // einem timeout von (1000/N) waehlen. Die Funktion gibt einen Bool'schen
  // Wert zurueck, welcher angibt, ob das Programm beendet werden soll
  // (false) oder ob die naechste Iteration der Haupt-Schleife ausgefuehrt
  // werden soll (true). Ein typischer Fall, in welchem die Funktion 'false'
  // zurueckgibt, ist, dass der Benutzer das Fenster mit einem Mausklick auf
  // das 'X' im Fensterrahmen geschlossen hat.

  // In diesem Beispiel waehlen wir 40ms als Timeout, was knapp 25
  // Haupt-Schleifen-Iterationen pro Sekunde entspricht:
  while(window.process_events(40))
  {
    // Als erstes aktualisieren wir die Position des Balls:
    ball_x += move_x;

    // Es kann sein, dass der Ball jetzt den Rand des Fensters "durchschlagen"
    // hat. Wir muessen jetzt pruefen, ob dies passiert ist und, falls ja,
    // entsprechend die Bewegungsrichtung des Balls aendern und zusaetzlich
    // die gerade berechnete Ball-Position korrigieren.
    // Bemerkung: Bei der Kollisions-Abfrage und der Positions-Korrektur ist
    // natuerlich auch der Radius des Balls zu beachten!

    // Hat der Ball die linke Wand durchschlagen?
    if(ball_x - ball_radius < 0)
    {
      // Bewegungs-Richung umkehren:
      move_x = -move_x;
      // Ball-Position korrigieren:
      ball_x = 2*ball_radius - ball_x;
    }

    // Fuer die Kollisions-Abfrage mit der rechten Wand benoetigen wir die
    // aktuelle Fenster-Breite:
    const int wnd_w = window.width();

    // Hat der Ball die rechte Wand durchschlagen?
    if(ball_x + ball_radius >= wnd_w)
    {
      // Bewegungs-Richung umkehren:
      move_x = -move_x;
      // Ball-Position korrigieren:
      ball_x = 2*(wnd_w - ball_radius) - ball_x;
    }

    // Jetzt wollen wir den Fenster-Inhalt zeichnen.
    // Dazu muessen wir zunaechst das Fenster "leeren":
    window.clear();

    // Nun koennen wir den Ball zeichnen:
    window.fill_circle(ball_x, ball_y, ball_radius);

    // Zu guter Letzt muessen wir noch die 'update' Funktion aufrufen,
    // damit unsere oben aufgefuehrten Zeichen-Befehle auf das Fenter
    // angewandt werden. Falls dieser Aufruf vergessen wird, bleibt
    // das Fenster schlicht schwarz.
    window.update();
  }

  // Wenn wir hier ankommen, dann hat der Benutzer das Fenter geschlossen
  // und wir koennen das Programm jetzt beenden. Objekt-Orientierung sei
  // Dank brauchen wir jetzt auch nichts mehr aufzuraeumen, da sich die
  // Destruktoren der Stack-Objekte darum kuemmern :)

  return 0;
}