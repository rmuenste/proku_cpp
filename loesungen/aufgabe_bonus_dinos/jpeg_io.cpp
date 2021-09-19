#include <iostream>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <jpeglib.h>

bool write_jpeg(const int width, const int height, const float* pixels, const char* filename)
{
  if(filename == nullptr)
  {
    std::cerr << "FEHLER: kein Dateiname angegeben" << std::endl;
    return false;
  }
  if((width < 8) || (width > 8192))
  {
    std::cerr << "FEHLER: ungueltige Bild-Breite; unterstuetzt: 8 - 8192" << std::endl;
    return false;
  }
  if((height < 8) || (height > 8192))
  {
    std::cerr << "FEHLER: ungueltige Bild-Hoehe; unterstuetzt: 8 - 8192" << std::endl;
    return false;
  }
  if(pixels == nullptr)
  {
    std::cerr << "FEHLER: keine Pixel angegeben" << std::endl;
    return false;
  }

  // Try to open file
  FILE* file = fopen(filename, "wb");
  if(file == nullptr)
  {
    std::cerr << "FEHLER: konnte Datei '" << filename << "' nicht erstellen!" << std::endl;
    return false;
  }

  // create a jpeg compressor
  jpeg_error_mgr jerr;
  jpeg_compress_struct cinfo;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  // set image information
  cinfo.in_color_space = JCS_GRAYSCALE;
  cinfo.input_components = 1;
  cinfo.data_precision = 8;
  cinfo.image_width = (JDIMENSION)width;
  cinfo.image_height = (JDIMENSION)height;
  cinfo.optimize_coding = TRUE;

  // configure compressor
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 95, FALSE);
  jpeg_stdio_dest(&cinfo, file);
  jpeg_start_compress(&cinfo, TRUE);

  // create buffer and convert image
  JSAMPLE* buffer = new JSAMPLE[width * height];
  for(int i(0); i < width*height; ++i)
  {
    if(pixels[i] <= 0.0f)
      buffer[i] = 0;
    else if(pixels[0] >= 1.0f)
      buffer[i] = 255;
    else
      buffer[i] = JSAMPLE(pixels[i] * 255.0f);
  }

  // sample row pointers
  JSAMPROW* rows = new JSAMPROW[height];
  for(int i(0); i < height; ++i)
    rows[i] = &buffer[i*width];

  // write scanlines
  while (cinfo.next_scanline < cinfo.image_height)
  {
    jpeg_write_scanlines(&cinfo, &rows[cinfo.next_scanline],  cinfo.image_height-cinfo.next_scanline);
  }

  // delete buffers
  delete [] rows;
  delete [] buffer;

  // finish compressor
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  // close file
  fclose(file);

  // okay
  return true;
}

bool write_jpeg(const int width, const int height, const float* pixels)
{
  // Schlucke alle newlines
  char c = 0;
  while((c = getc(stdin)) == '\n') {}
  ungetc(c, stdin);

  // Array fuer den Datei-Namen
  char name[1024];

  // Versuche, den Namen einzulesen:
  const int n = int(std::cin.get(name, 1024).gcount());
  if(n <= 0)
    return false;

  // Behandle evtl. aufgetretene Fehler
  if(!std::cin.good()) std::cin.clear();

  // Loesche ggf. den Rest der Eingabe
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Datei schreiben
  return write_jpeg(width, height, pixels, name);
}