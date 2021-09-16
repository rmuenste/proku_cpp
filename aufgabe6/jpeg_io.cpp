#include <iostream>
#include <limits>
#include <cstdio>
#include <cstdlib>

#include <jpeglib.h>



float* read_jpeg(unsigned int& width, unsigned int& height, const char* filename)
{
  if(filename == nullptr)
  {
    std::cerr << "FEHLER: kein Dateiname angegeben" << std::endl;
    return nullptr;
  }

  // Versuche die Datei zu oeffnen
  FILE* file = fopen(filename, "rb");
  if(file == nullptr)
  {
    std::cerr << "FEHLER: konnte Datei '" << filename << "' nicht oeffnen!" << std::endl;
    return nullptr;
  }

  // Erstelle JPEG decompress struct
  jpeg_error_mgr jerr;
  jpeg_std_error(&jerr);
  jpeg_decompress_struct cinfo;
  jpeg_create_decompress(&cinfo);
  cinfo.err = &jerr;

  // Lese Datei-Header ein
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  // Setze gewuenschtes Ausgabe-Format: 8-bit Graustufen
  cinfo.out_color_space = JCS_GRAYSCALE;
  cinfo.output_components = 1;
  cinfo.data_precision = 8;
  jpeg_start_decompress(&cinfo);

  // Lese Bild-Dimensionen aus
  width = static_cast<unsigned int>(cinfo.output_width);
  height = static_cast<unsigned int>(cinfo.output_height);

  // Erstelle Buffer
  JSAMPLE* buffer = new JSAMPLE[4*width * height];

  // Erstelle Zeilen-Zeiger
  JSAMPROW* rows = new JSAMPROW[height];
  for(unsigned int i(0); i < height; ++i)
    rows[i] = &buffer[i*width];

  // Dekompimiere das Bild
  while (cinfo.output_scanline < cinfo.output_height)
  {
    jpeg_read_scanlines(&cinfo, &rows[cinfo.output_scanline],  cinfo.output_height-cinfo.output_scanline);
  }

  // Dekompression beenden
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  // Datei schliessen
  fclose(file);

  // Bild von 8-bit nach float konvertieren
  float* pixels = new float[width * height];
  for(unsigned int i(0); i < width*height; ++i)
    pixels[i] = float(buffer[i]) / 255.0f;

  // Buffer freigeben
  delete [] rows;
  delete [] buffer;

  // okay
  return pixels;
}

bool write_jpeg(const unsigned int width, const unsigned int height, const float* pixels, const char* filename)
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

  // Versuche die Datei zu oeffnen
  FILE* file = fopen(filename, "wb");
  if(file == nullptr)
  {
    std::cerr << "FEHLER: konnte Datei '" << filename << "' nicht erstellen!" << std::endl;
    return false;
  }

  // Erstelle JPEG compress struct
  jpeg_error_mgr jerr;
  jpeg_compress_struct cinfo;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  // Setze die Bild-Informationen
  cinfo.in_color_space = JCS_GRAYSCALE;
  cinfo.input_components = 1;
  cinfo.data_precision = 8;
  cinfo.image_width = (JDIMENSION)width;
  cinfo.image_height = (JDIMENSION)height;
  cinfo.optimize_coding = TRUE;

  // Konfiguriere Kompressor
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 95, FALSE);
  jpeg_stdio_dest(&cinfo, file);
  jpeg_start_compress(&cinfo, TRUE);

  // Erstelle Buffer und konvertiere Bild-Daten
  JSAMPLE* buffer = new JSAMPLE[width * height];
  for(unsigned int i(0); i < width*height; ++i)
  {
    if(pixels[i] <= 0.0f)
      buffer[i] = 0;
    else if(pixels[0] >= 1.0f)
      buffer[i] = 255;
    else
      buffer[i] = JSAMPLE(pixels[i] * 255.0f);
  }

  // Erstelle Zeilen-Zeiger
  JSAMPROW* rows = new JSAMPROW[height];
  for(unsigned int i(0); i < height; ++i)
    rows[i] = &buffer[i*width];

  // Komprimiere das Bild
  while (cinfo.next_scanline < cinfo.image_height)
  {
    jpeg_write_scanlines(&cinfo, &rows[cinfo.next_scanline],  cinfo.image_height-cinfo.next_scanline);
  }

  // Kompression beenden
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  // Datei schliessen
  fclose(file);

  // Buffer freigeben
  delete [] rows;
  delete [] buffer;

  // okay
  return true;
}

float* read_jpeg(unsigned int& width, unsigned int& height)
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
    return nullptr;

  // Behandle evtl. aufgetretene Fehler
  if(!std::cin.good()) std::cin.clear();

  // Loesche ggf. den Rest der Eingabe
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Datei lesen
  return read_jpeg(width, height, name);
}

bool write_jpeg(const unsigned int width, const unsigned int height, const float* pixels)
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
