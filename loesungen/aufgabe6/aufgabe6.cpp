#include <iostream>
#include <cassert>
#include <cstdlib>

#include "jpeg_io.hpp"
#include "parse.hpp"

// Transformiert [0, n-1] --> [-r,+r]
float transform(unsigned int i, unsigned int n, float r)
{
  return -r + 2.0f * r * float(i) / float(n-1);
}

// Wendet den Escape-Time Algorithmus an:
float escape_time(
  float x, float y,
  const float c_x, const float c_y,
  const float r_max,
  const unsigned int k_max)
{
  unsigned int k(0);
  for(; (k < k_max) && ((x*x+y*y) < r_max); ++k)
  {
    float x2(x), y2(y);
    x = x2*x2 - y2*y2 + c_x; // = x^2 - y^2 + c_x
    y = 2.0f*x2*y2 + c_y;    // = 2 * x * y + c_y
  }

  // Gebe Grauwert des Pixels zurueck
  return float(k) / float(k_max);
}

int main(int argc, char** argv)
{
  // Stelle sicher, dass wir genug Argumente haben
  if(argc < 10)
  {
    std::cout << "AUFRUF: aufgabe-6 <DateiName> <Breite> <Hoehe> ";
    std::cout << "<r_x> <r_y> <c_x> <c_y> <r_max> <k_max>" << std::endl;
    return 0;
  }

  // Der Datei-Name
  const char* filename = argv[1];

  // Die verschiedenen Parameter
  float r_x, r_y, c_x, c_y, r_max;
  unsigned int width, height, k_max;

  // Versuche, die Parameter zu parsen
  if(!parse(argv[2], width, 8u, 8192u))
  {
    std::cout << "FEHLER: Konnte '" << argv[2] << "' nicht als Breite lesen" << std::endl;
    return 1;
  }
  if(!parse(argv[3], height, 8u, 8192u))
  {
    std::cout << "FEHLER: Konnte '" << argv[3] << "' nicht als Hoehe lesen" << std::endl;
    return 1;
  }
  if(!parse(argv[4], r_x, 0.1f, 2.0f))
  {
    std::cout << "FEHLER: Konnte '" << argv[4] << "' nicht als r_x lesen" << std::endl;
    return 1;
  }
  if(!parse(argv[5], r_y, 0.1f, 2.0f))
  {
    std::cout << "FEHLER: Konnte '" << argv[5] << "' nicht als r_y lesen" << std::endl;
    return 1;
  }
  if(!parse(argv[6], c_x, -2.0f, 2.0f))
  {
    std::cout << "FEHLER: Konnte '" << argv[6] << "' nicht als c_x lesen" << std::endl;
    return 1;
  }
  if(!parse(argv[7], c_y, -2.0f, 2.0f))
  {
    std::cout << "FEHLER: Konnte '" << argv[7] << "' nicht als c_y lesen" << std::endl;
    return 1;
  }
  if(!parse(argv[8], r_max, 10.0f, 500.0f))
  {
    std::cout << "FEHLER: Konnte '" << argv[8] << "' nicht als r_max lesen" << std::endl;
    return 1;
  }
  if(!parse(argv[9], k_max, 10u, 500u))
  {
    std::cout << "FEHLER: Konnte '" << argv[9] << "' nicht als k_max lesen" << std::endl;
    return 1;
  }

  // Ausgabe der eingelesenen Parameter
  std::cout << "Datei-Name.: " << filename << std::endl;
  std::cout << "Bild-Breite: " << width << std::endl;
  std::cout << "Bild-Hoehe.: " << height << std::endl;
  std::cout << "r_x........: " << r_x << std::endl;
  std::cout << "r_y........: " << r_y << std::endl;
  std::cout << "c_x........: " << c_x << std::endl;
  std::cout << "c_y........: " << c_y << std::endl;
  std::cout << "r_max......: " << r_max << std::endl;
  std::cout << "k_max......: " << k_max << std::endl;
  std::cout << std::endl;

  // Pixel allozieren
  float* pixels = new float[width * height];

  // Bild zeichnen
  std::cout << "Berechne Bild..." << std::endl;

  // laufe ueber alle Zeilen des Bildes
  for(unsigned int i(0); i < height; ++i)
  {
    // berechne transformierte Y-Koordinate:
    float y = transform(i, height, r_y);

    // laufe ueber alle Pixel in der Zeile
    for(unsigned int j(0); j < width; ++j)
    {
      // berechne transformierte X-Koordinate:
      float x = transform(j, width , r_x);

      // berechne gemittelten Grauwert
      pixels[i*width + j] = escape_time(x, y, c_x, c_y, r_max, k_max);
    }
  }

  // Bild ausgeben:
  std::cout << "Schreibe '" << filename << "'..." << std::endl;
  write_jpeg(width, height, pixels, filename);

  // Pixel freigeben
  delete [] pixels;

  // Okay
  std::cout << "Fertig!" << std::endl;

  return 0;
}