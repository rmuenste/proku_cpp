#ifndef PROKU_RENDER_FRAME_HPP
#define PROKU_RENDER_FRAME_HPP

#include <cassert>
#include "jpeg_io.hpp"
#include "camera.hpp"

// Eine Klasse, die den Frame-Buffer repraesentiert
class Frame
{
private:
  // Die Dimensionen des Frames:
  int width, height;
  // Der Farb-Puffer des Frames:
  float* color_buffer;
  // Der Tiefen-Puffer des Frames:
  float* depth_buffer;

public:
  // Konstruktor:
  // Erstellt ein Frame mit den vorgegebenen Ausmassen
  explicit Frame(int _width, int _height) :
    width(_width),
    height(_height),
    color_buffer(nullptr),
    depth_buffer(nullptr)
  {
    assert(width > 0);
    assert(height > 0);

    // Erstelle Puffer
    color_buffer = new float[width*height];
    depth_buffer = new float[width*height];

    // Formatiere Puffer
    clear();
  }

  // Loesche Kopier-Konstruktor
  Frame(const Frame&) = delete;
  // Loesche Zuweisungs-Operator
  Frame& operator=(const Frame&) = delete;

  // Destruktor
  virtual ~Frame()
  {
    if(color_buffer) delete [] color_buffer;
    if(depth_buffer) delete [] depth_buffer;
  }

  // Schreibt den Farb-Puffer des Frames in eine JPEG-Datei.
  bool write_color_jpeg(const char* filename) const
  {
    assert(filename != nullptr);
    return write_jpeg(width, height, color_buffer, filename);
  }

  // Schreibt den Tiefen-Puffer des Frames in eine JPEG-Datei.
  bool write_depth_jpeg(const char* filename) const
  {
    assert(filename != nullptr);
    return write_jpeg(width, height, depth_buffer, filename);
  }

  // Formatiert den Farb- und den Tiefen-Buffer auf 0
  void clear()
  {
    for(int i(0); i < width*height; ++i)
      color_buffer[i] = depth_buffer[i] = 0.0f;
  }

  // Gibt die Breite des Frames zurueck.
  int get_width() const
  {
    return width;
  }

  // Gibt die Hoehe des Frames zurueck.
  int get_height() const
  {
    return height;
  }

  // Gibt den Farb-Wert eines Pixels zurueck.
  //
  // \param[in] x,y
  // Die Indizes des Pixels
  //
  // \returns
  // Der Farb-Wert des Pixels.
  float get_pixel_color(int x, int y) const
  {
    assert((0 <= x) && (x < width));
    assert((0 <= y) && (y < height));
    assert(color_buffer != nullptr);

    return color_buffer[y*width + x];
  }

  // Gibt den Tiefen-Wert eines Pixels zurueck.
  //
  // \param[in] x,y
  // Die Indizes des Pixels
  //
  // \returns
  // Der Tiefen-Wert des Pixels.
  float get_pixel_depth(int x, int y) const
  {
    assert((0 <= x) && (x < width));
    assert((0 <= y) && (y < height));
    assert(depth_buffer != nullptr);

    return depth_buffer[y*width + x];
  }

  // Setzt den Farb- und Tiefen-Wert eines Pixel
  //
  // \param[in] x, y
  // Die Indizes des Pixels
  //
  // \param[in] pixel_depth
  // Die Tiefe des Pixels
  //
  // \param[in] pixel_color
  // Die Farbe des Pixels
  void set_pixel(int x, int y, float pixel_depth, float pixel_color)
  {
    assert((0 <= x) && (x < width));
    assert((0 <= y) && (y < height));
    assert(color_buffer != nullptr);
    assert(depth_buffer != nullptr);

    // Setze Tiefe
    depth_buffer[y*width + x] = pixel_depth;
    // Setze Farbe
    color_buffer[y*width + x] = pixel_color;
  }

  // Aktualisiert einen Pixel, wenn die Tiefe groesser als
  // die bisherige Tiefe des Pixels ist
  //
  // \param[in] x, y
  // Die Indizes des Pixels
  //
  // \param[in] pixel_depth
  // Die Tiefe des Pixels
  //
  // \param[in] pixel_color
  // Die Farbe des Pixels
  void update_pixel(int x, int y, float pixel_depth, float pixel_color)
  {
    assert((0 <= x) && (x < width));
    assert((0 <= y) && (y < height));
    assert(color_buffer != nullptr);
    assert(depth_buffer != nullptr);

    // Pruefe, ob die Tiefe des neuen Pixels groesser ist als die
    // bisherige Tiefe des Pixels im Puffer.
    // Falls ja, dann aktualisiere Tiefe und Farbe, sonst mache nichts.
    if(pixel_depth > depth_buffer[y*width + x])
    {
      // Setze Tiefe
      depth_buffer[y*width + x] = pixel_depth;
      // Setze Farbe
      color_buffer[y*width + x] = pixel_color;
    }
  }
}; // class Frame

#endif // PROKU_RENDER_FRAME_HPP
