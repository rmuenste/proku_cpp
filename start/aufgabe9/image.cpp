#include <cassert>
#include "image.hpp"
#include "jpeg_io.hpp"
#include <iostream>

// TODO
void Image::write(const char *fileName) {

    write_jpeg(my_width, my_height, my_pixels, fileName);

}


Image::Image(const char* fileName)  {

  std::cout << "Lese Datei '" << fileName << "'..." << std::endl;
  my_pixels = read_jpeg(my_width, my_height, fileName);
  std::cout <<  "fertig" << std::endl;

}


Image::~Image() {
  if(my_pixels != nullptr) {
    delete[] my_pixels;
    my_pixels = nullptr;
  }
}

Image::Image(const Image &copy) {

    my_width = copy.width();
    my_height = copy.height();
    my_pixels = new float[my_width * my_height];
    for (uint i(0); i < my_width * my_height; ++i) 
      my_pixels[i] = copy.my_pixels[i];
}