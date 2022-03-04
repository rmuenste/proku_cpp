#ifndef PROKU_IMAGE_HPP
#define PROKU_IMAGE_HPP

// Ein typedef fuer 'unsigned int'
typedef unsigned int uint;

// Die 'Image' Klasse
class Image
{
private:
  // Bild-Dimensionen
  uint my_width, my_height;
  // Pixel-Array auf dem Heap
  float* my_pixels;

public:
  // standard konstruktor
  Image();

  // ben-def Konstruktor
  explicit Image(uint _width, uint _height);

  // ben-def Konstruktor
  explicit Image(const char* filename);

  // Kopier-Konstruktor
  Image(const Image& other);

  // Destruktor
  ~Image();

  // Zuweisungs-Operator
  Image& operator=(const Image& other);

  // Gibt die Bild-Breite zurueck
  uint width() const;

  // Gibt die Bild-Hoehe zurueck
  uint height() const;

  // Gibt eine Referenz auf den Pixel (i,j) zurueck
  float& at(uint i, uint j);

  // Gibt eine const Referenz auf den Pixel (i,j) zurueck
  const float& at(uint i, uint j) const;

  // Schreibt das Bild in eine JPEG-Datei
  bool write(const char* filename) const;
}; // class Image

#endif // PROKU_IMAGE_HPP
