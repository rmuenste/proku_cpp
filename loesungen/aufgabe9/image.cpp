#include <cassert>
#include "image.hpp"
#include "jpeg_io.hpp"

// Standard-Konstruktor
Image::Image() :
  my_width(0u),
  my_height(0u),
  my_pixels(nullptr)
{
}

// ben-def Konstruktor #1
Image::Image(uint _width, uint _height) :
  my_width(_width),
  my_height(_height),
  my_pixels(nullptr)
{
  uint size = _width * _height;
  if(size > 0u)
  {
    my_pixels = new float[size];
    for(uint i(0); i < size; ++i)
      my_pixels[i] = 0.0f;
  }
}

// ben-def Konstruktor #2
Image::Image(const char* filename) :
  my_width(0u),
  my_height(0u),
  my_pixels(nullptr)
{
  assert(filename != nullptr);

  // Versuche, das Bild einzulesen
  my_pixels = read_jpeg(my_width, my_height, filename);
  assert(my_pixels != nullptr);
}

// Kopier-Konstruktor
Image::Image(const Image& other) :
  my_width(other.my_width),
  my_height(other.my_height),
  my_pixels(other.my_pixels)
{
  uint size = my_width * my_height;
  if(size > 0u)
  {
    my_pixels = new float[size];
    for(uint i(0); i < size; ++i)
      my_pixels[i] = other.my_pixels[i];
  }
}

// Destruktor
Image::~Image()
{
  if(my_pixels != nullptr)
    delete [] my_pixels;
}

// Zuweisungs-Operator
Image& Image::operator=(const Image& other)
{
  if(this == &other)
    return *this;

  if(my_pixels != nullptr)
    delete [] my_pixels;

  my_width = other.my_width;
  my_height = other.my_height;
  my_pixels = nullptr;

  uint size = my_width * my_height;
  if(size > 0u)
  {
    my_pixels = new float[size];
    for(uint i(0); i < size; ++i)
      my_pixels[i] = other.my_pixels[i];
  }

  return *this;
}

// Gibt die Bild-Breite zurueck
uint Image::width() const
{
  return my_width;
}

// Gibt die Bild-Hoehe zurueck
uint Image::height() const
{
  return my_height;
}

// Gibt eine Referenz auf den Pixel (i,j) zurueck
float& Image::at(uint i, uint j)
{
  assert(i < my_height);
  assert(j < my_width);
  assert(my_pixels != nullptr);
  return my_pixels[i * my_width + j];
}

// Gibt eine const Referenz auf den Pixel (i,j) zurueck
const float& Image::at(uint i, uint j) const
{
  assert(i < my_height);
  assert(j < my_width);
  assert(my_pixels != nullptr);
  return my_pixels[i * my_width + j];
}

// Schreibt das Bild in eine JPEG-Datei
bool Image::write(const char* filename) const
{
  assert(filename != nullptr);
  if(my_pixels == nullptr)
    return false;
  return write_jpeg(my_width, my_height, my_pixels, filename);
}
