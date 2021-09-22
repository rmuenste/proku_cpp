#ifndef PROKU_IMAGE_HPP
#define PROKU_IMAGE_HPP
#include <cassert>

//  bool write_jpeg(const unsigned int width, const unsigned int height, const float* pixels, const char* filename);
// Ein typedef fuer 'unsigned int'
typedef unsigned int uint;

// Die 'Image' Klasse
class Image
{
private:
  uint my_width;
  uint my_height;
  float *my_pixels;

  void read(const char *fileName);
public:
  Image() : my_width(0), my_height(0), my_pixels(nullptr) {
  }

  explicit Image(const char* fileName);

  explicit Image(uint w, uint h) : my_width(w), my_height(h) {
    my_pixels = new float[w*h];
    for (uint i(0); i < w*h; ++i) 
      my_pixels[i] = 0.0f;
  }


  Image(const Image &copy);

  ~Image(); 

  uint width() const {
    return my_width;
  }

  uint height() const {
    return my_height;
  }

  // TODO
  void write(const char *fileName);

  float& at(uint i, uint j) {
    assert(i < my_height);
    assert(j < my_width);
    assert(my_pixels != nullptr);
    return my_pixels[i * my_width + j];
  }

}; // class Image

#endif // PROKU_IMAGE_HPP
