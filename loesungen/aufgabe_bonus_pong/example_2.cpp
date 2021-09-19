#include "render_window.hpp"

int main()
{
  // Erstelle ein Fenster mit Titel "Beispiel 2" der Breite 640 und Hoehe 480:
  Proku::RenderWindow window("Beispiel 2", 640, 480);

  // In diesem Beispiel wird ein Kreis auf dem Fenster gezeichnet, wobei
  // die Position des Kreises ueber die Pfeiltasten gesteuert werden kann.
  // Ausserdem werden in der oberen linken Ecke des Fenters die X- und
  // Y-Koordinates des Kreis-Mittelpunktes als String ausgegeben.

  // Zwei Variablen fuer die aktuelle Position des Kreises;
  // wir starten am Mittelpunkt des erstellten Fensters:
  int ball_x = window.width()  / 2; // halbe Breite
  int ball_y = window.height() / 2; // halbe Hoehe

  // In diesem Beispiel waehlen wir 50ms als Timeout, was knapp 20
  // Haupt-Schleifen-Iterationen pro Sekunde entspricht:
  while(window.process_events(50))
  {
    // Zunaechst wollen wir pruefen, welche Tasten aktuell gedrueckt sind.
    // Dazu rufen wir die 'query_keymap' Funktion auf, welche uns ein
    // Keymap Objekt zurueckgibt, welches den aktuellen Zustand der
    // Tastatur zum Zeitpunkt des Funktionsaufrufes repraesentiert:
    Proku::Keymap keymap = window.query_keymap();

    // Wichtig: Es ist zu beachten, dass das 'keymap' Objekt den Zustand
    // der Tastatur in dem Moment speichert, in welchem das Objekt erstellt
    // wurde. Aus diesem Grunde muessen wir in jeder Iteration der Haupt-
    // Schleife das 'keymap' Objekt neu erstellen, um den jeweils akutellen
    // Zustand der Tastatur zu pruefen.

    // Mit Hilfe der 'check' Funktion koennen wir jetzt pruefen, ob eine
    // bestimmte Taste gedrueckt wurde. Dazu muessen wir der Funktion den
    // Code der jeweiligen Taste uebergeben. Bedauerlicherweise sind die
    // Codes system-abhaengig, so dass dieser Quell-Code nicht portabel
    // ist, aber die hier angegebenen Codes sollten zumindest im CIP-Pool
    // einheitlich sein. Weitere Tasten-Codes koennen mit Hilfe der
    // "keycodes" App erforscht werden; dazu einfach in der Konsole
    // "make keycodes && ./keycodes" ausfuehren.

    // Die Escape-Taste hat den Code 9. Falls diese gedruckt wurde, beenden
    // wir die Haupt-Schleife, so dass das Programm beendet werden kann.
    if(keymap.check(9)) // ESC
      break;

    // Falls die Leertaste gedrueckt wurde, bringen wir den Kreis wieder
    // zurueck an den Fenster-Mittelpunkt:
    if(keymap.check(65)) // Leertaste
    {
      ball_x = window.width()  / 2;
      ball_y = window.height() / 2;
    }

    // Nun pruefen wir, ob eine (oder mehrere) Pfeiltaste(n) gedrueckt
    // wurde(n). Falls ja, dann veraendern wir entsprechend die Kreis-
    // Position um 10 Pixel in die jeweilige Richtung:
    if(keymap.check(111)) // Pfeiltaste hoch
      ball_y -= 10;
    if(keymap.check(116)) // Pfeiltaste runter
      ball_y += 10;
    if(keymap.check(113)) // Pfeiltaste links
      ball_x -= 10;
    if(keymap.check(114)) // Pfeiltaste rechts
      ball_x += 10;

    // Jetzt koennen wir den Fenster-Inhalt zeichnen.
    window.clear();

    // Zeichne die X- und Y-Koordinaten als Strings in die obere linke
    // Ecke des Fensters:
    window.draw_string(10, 20, "X: " + std::to_string(ball_x));
    window.draw_string(10, 40, "Y: " + std::to_string(ball_y));

    // Zeichne den Kreis mit Radius 10 an der aktuellen Position:
    window.draw_circle(ball_x, ball_y, 10);

    // Zu guter Letzt muessen wir noch die 'update' Funktion aufrufen:
    window.update();

  } // Haupt-Schleife

  // Wenn wir hier ankommen, dann hat der Benutzer das Fenter geschlossen
  // oder die ESC Taste gedrueckt und wir koennen das Programm jetzt beenden.

  return 0;
}