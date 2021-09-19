#ifndef PROKU_JPEG_IO_HPP
#define PROKU_JPEG_IO_HPP

//
// Schreibt ein Bild in eine JPEG-Datei.
//
// Parameter:
// * width, height (Eingabe)
//   Die Dimension des Bildes. Müssen zwischen 8 und 8192 liegen.
//
// * pixels (Eingabe)
//   Das zweilen-weise gespeicherte Pixel-Array des Bildes.
//
// * filename (Eingabe)
//   Der Dateipfad der zu schreibenden JPEG-Datei.
//
// Rueckgabe:
// true, falls die Datei erfolgreich gespeichert wurde, oder
// false, falls ein Fehler aufgetreten ist.
bool write_jpeg(const int width, const int height, const float* pixels, const char* filename);

//
// Schreibt ein Bild in eine JPEG-Datei.
// Der benoetigte Datei-Name wird von der Konsole eingelesen.
// Diese Funktion druck keine Eingabe-Aufforderung.
//
// Parameter:
// * width, height (Eingabe)
//   Die Dimension des Bildes. Müssen zwischen 8 und 8192 liegen.
//
// * pixels (Eingabe)
//   Das zweilen-weise gespeicherte Pixel-Array des Bildes.
//
// Rueckgabe:
// true, falls die Datei erfolgreich gespeichert wurde, oder
// false, falls ein Fehler aufgetreten ist.
bool write_jpeg(const int width, const int height, const float* pixels);

#endif // PROKU_JPEG_IO_HPP
