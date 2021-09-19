#ifndef PROKU_RENDER_RASTERIZER_HPP
#define PROKU_RENDER_RASTERIZER_HPP

#include "camera.hpp"
#include "frame.hpp"
#include "point.hpp"
#include "triangle.hpp"

class Rasterizer
{
public:
  // Aufgabe 9a)
  //
  // Setzt diesen Punkt auf den Schnittpunkt der Strecke zwischen
  // P1 und P2 mit einer vorgegeben Y-Koordinate, falls ein eindeutiger
  // Schnittpunkt existiert.
  //
  // \param[in] y
  // Die Y-Koordinate, deren Schnitt mit der Eingabe-Gerade gesucht wird
  //
  // \param[in] p1, p2
  // Die beiden Punkte der Gerade, deren Schnitt mit der Y-Koordinate
  // gesucht wird
  //
  // \returns
  // true, wenn ein eindeutiger Schnittpunkt gefunden wurde, oder
  // false, falls kein eindeutiger Schnittpunkt existiert
  bool scan_edge(Point& q, float y, const Point& p1, const Point& p2) const
  {
    // Stelle sicher, dass P1P2 nicht senkrecht zur Y-Achse steht,
    // da wir sonst gleich durch 0 dividieren wuerden
    if(std::abs(p2.y - p1.y) < 1E-3f)
      return false;

    // Berechne t so, dass:
    //       y = p1.y + t*(p2.y - p1.y)
    // <==>  t = (y - p1.y) / (p2.y - p1.y)
    const float t = (y - p1.y) / (p2.y - p1.y);

    // Stelle sicher, dass t in [0,1], d.h. dass der Schnittpunkt
    // zwischen P1 und P2 liegt
    if((t < 0.0f) || (1.0f < t))
      return false;

    // Interpoliere: q = p1 + t*(p2 - p1)
    q.y = y;
    q.x = p1.x + t*(p2.x - p1.x);
    q.z = p1.z + t*(p2.z - p1.z);

    // Okay
    return true;
  }

  // Aufgabe 9b)
  //
  // Berechnet die Schnittpunkte Q1 und Q2 dieses Dreiecks mit
  // einer vorgegebenen Y-Koordinate.
  //
  // \param[out] q1, q2
  // Die beiden Punkte Q1 und Q2 auf dem Rand des Dreiecks,
  // welche die Y-Koordinate schneiden.
  //
  // \param[in] y
  // Die Y-Koordinate, deren Schnitt mit dem Dreieck gesucht wird
  //
  // \returns
  // true, wenn die Schnittpunkte gefunden wurden, oder
  // false, falls kein Schnittpunkt existiert
  bool scan_tria(Point& q1, Point& q2, float y, const Triangle& t) const
  {
    // Berechne alle 3 Linien-Schnitte:
    Point p1, p2, p3;
    bool on_edge1 = scan_edge(p1, y, t.vertex[0], t.vertex[1]);
    bool on_edge2 = scan_edge(p2, y, t.vertex[1], t.vertex[2]);
    bool on_edge3 = scan_edge(p3, y, t.vertex[2], t.vertex[0]);

    // Es gibt viele Moeglichkeiten, um die beiden Punkte Q1 und Q2
    // zu identifizieren.

    // Das hier ist die wohl einfachste:
    // Pruefe alle 4 moeglichen Kombinationen der drei Kanten:
    if(on_edge1 && on_edge2 && on_edge3)
    {
      // Sonderfall: Alle 3 Kanten schneiden die y-Koordinate,
      // d.h. der Schnitt verlaeuft durch einen Knoten des Dreiecks.

      // Finde den linken Knoten Q1:
      if((p1.x <= p2.x) && (p1.x <= p3.x))
        q1 = p1;
      else if((p2.x <= p1.x) && (p2.x <= p3.x))
        q1 = p2;
      else
        q1 = p3;

      // Finde den rechten Knoten Q2:
      if((p1.x >= p2.x) && (p1.x >= p3.x))
        q2 = p1;
      else if((p2.x >= p1.x) && (p2.x >= p3.x))
        q2 = p2;
      else
        q2 = p3;

      // Okay
      return true;
    }
    else if(on_edge1 && on_edge2)
    {
      // Kandidaten: P1 und P2
      if(p1.x <= p2.x)
      {
        q1 = p1;
        q2 = p2;
      }
      else
      {
        q1 = p2;
        q2 = p1;
      }
      return true;
    }
    else if(on_edge1 && on_edge3)
    {
      // Kandidaten: P1 und P3
      if(p1.x <= p3.x)
      {
        q1 = p1;
        q2 = p3;
      }
      else
      {
        q1 = p3;
        q2 = p1;
      }
      return true;
    }
    else if(on_edge2 && on_edge3)
    {
      // Kandidaten: P2 und P3
      if(p2.x <= p3.x)
      {
        q1 = p2;
        q2 = p3;
      }
      else
      {
        q1 = p3;
        q2 = p2;
      }
      return true;
    }

    // Fail: keine zwei Schnittpunkte gefunden
    return false;

    // Hier ist eine alternative kuerzere Moeglichkeit:

    // Finde den ersten Schnittpunkt mit einer der
    // Kanten dieses Dreiecks und setze Q1=Q2 auf diesen.
    if(on_edge1)
      q1 = q2 = p1;
    else if(on_edge2)
      q1 = q2 = p2;
    else if(on_edge3)
      q1 = q2 = p3;
    else
      return false;

    // Versuche nun, einen zweiten Schnittpunkt zu finden
    if(on_edge2)
    {
      // Links oder rechts vom bisherigen Schnittpunkt?
      if(p2.x < q1.x)
        q1 = p2;
      if(p2.x > q2.x)
        q2 = p2;
    }
    if(on_edge3)
    {
      if(p3.x < q1.x)
        q1 = p3;
      if(p3.x > q2.x)
        q2 = p3;
    }
    return true;
  }

  //
  // Aufgabe 9c)
  //
  // Rastert ein Dreieck mit einer Farbe.
  //
  // \param[inout] frame
  // Das Frame, in welches gezeichnet werden soll
  //
  // \param[in] tria
  // Das Dreieck, welches gerastert werden soll
  //
  // \param[in] color
  // Der Farbwert des Dreiecks.
  //
  void rasterize(Frame& frame, const Triangle& tria, const float color)
  {
    const int width = frame.get_width();
    const int height = frame.get_height();

    // Berechne die minimalen und maximalen Y-Indizes
    // der zu zeichnenden Pixel.
    // Wichtig:  Stelle sicher, dass wir nicht ueber
    // die Grenzen des Frames hinaus laufen.
    int y_min = std::max(int(tria.get_min_y()), 0);
    int y_max = std::min(int(tria.get_max_y()), height-1);

    // Pruefe, ob das Dreieck ueberhaupt im Frame liegt
    // Falls nicht, dann gibt es auch nichts zu rastern.
    if((y_max < 0) || (y_min >= height))
      return;

    // Laufe ueber alle Zeilen, welche das Dreieck
    // scheiden koennten:
    for(int y(y_min); y <= y_max; ++y)
    {
      // Berechne die beiden Punkte Q1 und Q2, welche die
      // minimale und maximale X-Koordinate besitzen
      Point q1, q2;
      if(!scan_tria(q1, q2, float(y),tria))
        continue;

      // Berechne die minimalen und maximalen X-Indizes
      // der zu zeichnenden Pixel in dieser Zeile.
      // Wichtig:  Stelle sicher, dass wir nicht ueber
      // die Grenzen des Frames hinaus laufen.
      int x_min = std::max(int(q1.x), 0);
      int x_max = std::min(int(q2.x), width-1);

      // Laufe ueber alle Pixel der aktuellen Zeile:
      for(int x(x_min); x <= x_max; ++x)
      {
        // Berechne den Transformations-Koeffizienten
        // fuer den aktuellen Pixel:
        // S = q1 + t*(q2 - q1)
        float t = (float(x) - q1.x) / (q2.x - q1.x);

        // Berechne anhand der Transformation
        // jetzt noch die Z-Koordinate des Pixels
        float z = q1.z + t*(q2.z - q1.z);

        // Teste, ob die Z-Koordinate im Bereich [0,1] liegt
        if((z <= 0.0f) || (z >= 1.0f))
          continue;

        // Aktualisiere den Pixel:
        frame.update_pixel(x, y, z, color);
      }
    }
  }

  // Zeichnet ein Dreieck aus Sicht einer Kamera
  //
  // \param[inout] frame
  // Das Frame, in welches gerendert werden soll
  //
  // \param[in] tria
  // Das Dreieck, welches gerendert werden soll
  //
  // \param[in] camera
  // Die Kamera, aus deren Sicht gerendert wird
  void render(Frame& frame, const Triangle& tria, const Camera& camera)
  {
    // Transformiere das Dreieck in das Koordinaten-System
    // der Kamera.
    Triangle tria_view = camera.transform(tria);

    // Berechene Z-Normale des Dreiecks im Kamera-System:
    const float normal_z = tria_view.normal_z();

    // Projiziere das Dreieck auf den Bild-Bereich der Kamera:
    Triangle tria_proj = camera.project(tria_view);

    // Zeiche das projizierte Dreieck
    // Der Farbwert entspricht dabei der absoluten Z-Normale
    rasterize(frame, tria_proj, std::abs(normal_z));
  }
}; // class Rasterizer

#endif // PROKU_RENDER_RASTERIZER_HPP
