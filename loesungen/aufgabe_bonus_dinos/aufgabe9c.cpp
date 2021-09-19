#include <iostream>
#include <cassert>

#include "test_helpers.hpp"
#include "point.hpp"
#include "triangle.hpp"
#include "frame.hpp"
#include "rasterizer.hpp"

//
// Testet die "rasterize" Funktion der Frame-Klasse
//
// \param[in] nr
// Die fortlaufende Nummer des Test-Falls
//
// \param[in] tria
// Eine Referenz des zu testenden Frames
//
// \param[in] x, y
// Die Koordinates des zu testenden Pixels
//
// \param[in] color_ref
// Der erwartete Farb-Wert des Pixels
//
// \param[in] depth_ref
// Der erwartete Tiefen-Wert des Pixels
//
// \returns
// true, wenn der Testlauf erfolgreich war, sonst false.
bool test_frame_rasterize(
  const int nr,
  const Frame& frame,
  const int x,
  const int y,
  const float color_ref,
  const float depth_ref)
{
  // Gebe den Test-Fall auf der Konsole aus:
  std::cout << "Teste Fall " << nr << ": ";

  // Lese die Farbe und Tiefe
  float color = frame.get_pixel_color(x, y);
  float depth = frame.get_pixel_depth(x, y);

  // Teste Farb-Wert
  bool okay_color = (std::abs(color-color_ref) < 0.05f);

  // Teste Tiefen-Wert
  bool okay_depth = (std::abs(depth-depth_ref) < 0.05f);

  // Teste Farbe:
  if(!okay_color)
  {
    std::cout << "FEHLER: inkorrekter Farb-Wert an Position (" << x << "," << y << ")" << std::endl;
    std::cout << "! Erwartet: " << color_ref << std::endl;
    std::cout << "! Erhalten: " << color << std::endl;
  }

  // Teste Tiefe:
  if(!okay_depth)
  {
    std::cout << "FEHLER: inkorrekter Tiefen-Wert an Position (" << x << "," << y << ")" << std::endl;
    std::cout << "! Erwartet: " << depth_ref << std::endl;
    std::cout << "! Erhalten: " << depth << std::endl;
  }

  // Beide okay?
  if(!(okay_color && okay_depth))
    return false;

  // Wenn wir hier angekommen sind, ist alles okay
  std::cout << "OK" << std::endl;
  return true;
}

int main()
{
  // Bis jetzt ist kein Test fehlgeschlagen
  bool okay(true);

  // Erstelle Test-Frame
  Frame frame(500, 400);

  // Erstelle Rasterisierer
  Rasterizer raster;

  // Erstelle Test-Dreieck
  Triangle tria;
  tria.vertex[0] = Point(100.0f, 100.0f, 0.5f);
  tria.vertex[1] = Point(400.0f, 200.0f, 0.2f);
  tria.vertex[2] = Point(200.0f, 300.0f, 0.8f);

  // Zeichne Dreieck:
  frame.clear();
  raster.rasterize(frame, tria, 1.0f);

  // Schreibe die Puffer in Dateien:
  frame.write_color_jpeg("./output_9c/color.jpg");
  frame.write_depth_jpeg("./output_9c/depth.jpg");

  // Teste Frame
  okay = okay && test_frame_rasterize( 1, frame,  50, 200, 0.0f, 0.000f);
  okay = okay && test_frame_rasterize( 2, frame, 105, 105, 1.0f, 0.503f);
  okay = okay && test_frame_rasterize( 3, frame, 250, 150, 1.0f, 0.350f);
  okay = okay && test_frame_rasterize( 4, frame, 350, 200, 1.0f, 0.290f);
  okay = okay && test_frame_rasterize( 5, frame, 250, 300, 0.0f, 0.000f);
  okay = okay && test_frame_rasterize( 6, frame, 150, 210, 0.0f, 0.000f);
  okay = okay && test_frame_rasterize( 7, frame, 150, 190, 1.0f, 0.626f);
  okay = okay && test_frame_rasterize( 8, frame, 200, 290, 1.0f, 0.776f);
  okay = okay && test_frame_rasterize( 9, frame, 390, 200, 1.0f, 0.218f);

  // Alle Tests okay?
  return okay ? 0 : 1;
}
