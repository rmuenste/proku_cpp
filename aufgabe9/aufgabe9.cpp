#include <iostream>
#include <cmath>      // std::round
#include "image.hpp"

void threshold(Image& img)
{
  for(uint i(0); i < img.height(); ++i)
  {
    for(uint j(0); j < img.width(); ++j)
    {
      img.at(i,j) = (img.at(i,j) < 0.5f ? 0.0f : 1.0f);
    }
  }
}

void floyd_steinberg(Image& img)
{
  // apply Floyd-Steinberg
  for(uint i(0); i < img.height(); ++i)
  {
    for(uint j(0); j < img.width(); ++j)
    {
      // alten Pixel-Wert merken
      float old = img.at(i,j);

      // neuer Pixel-Wert berechnen
      img.at(i,j) = (old < 0.5f ? 0.0f : 1.0f);

      // Rundungs-Fehler berechnen
      float err = old - img.at(i,j);

      // Fehler-Diffusion
      if(j+1u < img.width())
        img.at(i,j+1u) += err * 0.4375f;
      if(i+1u < img.height())
      {
        img.at(i+1u,j) += err * 0.3125f;
        if(j > 0u)
          img.at(i+1u,j-1u) += err * 0.1875f;
        if(j+1 < img.width())
          img.at(i+1u,j+1u) += err * 0.0625f;
      }
    }
  }
}

int main(int argc, char* argv[])
{
  // Haben wir genuegend Argumente?
  if(argc < 4)
  {
    std::cout << "BENUTZE: aufgabe-9 <EingabeDatei> <AusgabeDatei1> <AusgabeDatei2>" << std::endl;
    return 0;
  }

  // versuche, das Bild einzulesen
  std::cout << "Lese Datei '" << argv[1] << "'..." << std::endl;
  const Image image(argv[1]);

  // Erstelle eine Kopie von 'image',
  // wende 'threshold' Algorithmus darauf an
  // und exportiere das Bild in eine Datei:
  Image image_1(image);

  std::cout << "Wende 'threshold' an..." << std::endl;
  threshold(image_1);

  std::cout << "Schreibe Datei '" << argv[2] << "'..." << std::endl;
  image_1.write(argv[2]);

  // Erstelle eine Kopie von 'image',
  // wende Floyd-Steinberg darauf an
  // und exportiere das Bild in eine Datei:
  Image image_2(image);

  std::cout << "Wende 'floyd_steinberg' an..." << std::endl;
  floyd_steinberg(image_2);

  std::cout << "Schreibe Datei '" << argv[3] << "'..." << std::endl;
  image_2.write(argv[3]);


  // okay
  std::cout << "Fertig!" << std::endl;
  return 0;
}
