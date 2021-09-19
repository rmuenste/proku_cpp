#include <iostream>

#include "point.hpp"
#include "triangle.hpp"
#include "frame.hpp"
#include "rasterizer.hpp"

int main()
{
  // Erstelle Test-Frame
  Frame frame(500, 500);

  // Erstelle Rasterisierer
  Rasterizer raster;

  // Erstelle vier Test-Dreiecke
  Triangle tria_1(Point( 50.0f, 100.0f, 0.5f), Point(570.0f, 100.0f, 0.2f), Point( 50.0f, 250.0f, 0.8f));
  Triangle tria_2(Point(400.0f,  50.0f, 0.5f), Point(400.0f, 570.0f, 0.2f), Point(250.0f,  50.0f, 0.8f));
  Triangle tria_3(Point(450.0f, 400.0f, 0.5f), Point(-70.0f, 400.0f, 0.2f), Point(450.0f, 250.0f, 0.8f));
  Triangle tria_4(Point(100.0f, 450.0f, 0.5f), Point(100.0f, -70.0f, 0.2f), Point(250.0f, 450.0f, 0.8f));

  // Zeiche die Dreiecke
  frame.clear();
  raster.rasterize(frame, tria_1, 0.2f);
  raster.rasterize(frame, tria_2, 0.4f);
  raster.rasterize(frame, tria_3, 0.6f);
  raster.rasterize(frame, tria_4, 0.8f);

  // Schreibe JPEG-Dateien raus:
  frame.write_color_jpeg("./output_9d/color.jpg");
  frame.write_depth_jpeg("./output_9d/depth.jpg");

  // Okay
  return 0;
}

