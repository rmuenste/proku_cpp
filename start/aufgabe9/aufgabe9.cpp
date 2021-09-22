#include <iostream>
#include <cmath>      // std::round
#include "image.hpp"

void threshold(Image& img)
{
  // TODO
}

void floyd_steinberg(Image& img)
{
  // TODO
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
  Image image(argv[1]);
  std::cout << "Schreibe Datei '" << argv[2] << "'..." << std::endl;
  image.write(argv[2]);

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
