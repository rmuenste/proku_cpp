#ifndef PROKU_JPEG_IO_HPP
#define PROKU_JPEG_IO_HPP

///
/// Liest ein Bild aus einer JPEG-Datei.
///
/// \param[out] width
/// Die Breite des eingelesenen Bildes.
///
/// \param[out] height
/// Die Hoehe des eingelesenen Bildes.
///
/// \param[in] filename
/// Der Dateipfad der einzulesenden JPEG-Datei.
///
/// \returns
/// Ein Zeiger auf ein Heap-Array der Laenge (width*height),
/// welches die Pixel des Bildes zeilen-weise enthaelt.
/// Im Falle eines Fehlers gibt diese Funktion einen Null-Zeiger zurueck.
///
/// \attention
/// Das Heap-Array, welches von dieser Funktion zurueckgegeben wird,
/// muss vom Benutzer dealloziiert werden, sobald es nicht mehr
/// benoetigt wird.
float* read_jpeg(unsigned int& width, unsigned int& height, const char* filename);

///
/// Schreibt ein Bild in eine JPEG-Datei.
///
/// \param[in] width
/// Die Breite des Bildes. Muss zwischen 8 und 8192 liegen.
///
/// \param[in] height
/// Die Hoehe des Bildes. Muss zwischen 8 und 8192 liegen.
///
/// \param[in] pixels
/// Das zweilen-weise gespeicherte Pixel-Array des Bildes.
///
/// \param[in] filename
/// Der Dateipfad der zu schreibenden JPEG-Datei.
///
/// \returns
/// true, falls die Datei erfolgreich gespeichert wurde, oder
/// false, falls ein Fehler aufgetreten ist.
bool write_jpeg(const unsigned int width, const unsigned int height, const float* pixels, const char* filename);

///
/// Liest ein Bild aus einer JPEG-Datei.
///
/// Der benoetigte Datei-Name wird von der Konsole eingelesen.
/// Diese Funktion druckt keine Eingabe-Aufforderung.
///
/// \param[out] width
/// Die Breite des eingelesenen Bildes.
///
/// \param[out] height
/// Die Hoehe des eingelesenen Bildes.
///
/// \returns
/// Ein Zeiger auf ein Heap-Array der Laenge (width*height),
/// welches die Pixel des Bildes zeilen-weise enthaelt.
/// Im Falle eines Fehlers gibt diese Funktion einen Null-Zeiger zurueck.
///
/// \attention
/// Das Heap-Array, welches von dieser Funktion zurueckgegeben wird,
/// muss vom Benutzer dealloziiert werden, sobald es nicht mehr
/// benoetigt wird.
float* read_jpeg(unsigned int& width, unsigned int& height);

///
/// Schreibt ein Bild in eine JPEG-Datei.
///
/// Der benoetigte Datei-Name wird von der Konsole eingelesen.
/// Diese Funktion druckt keine Eingabe-Aufforderung.
//
/// \param[in] width
/// Die Breite des Bildes. Muss zwischen 8 und 8192 liegen.
///
/// \param[in] height
/// Die Hoehe des Bildes. Muss zwischen 8 und 8192 liegen.
///
/// \param[in] pixels
/// Das zweilen-weise gespeicherte Pixel-Array des Bildes.
///
/// \returns
/// true, falls die Datei erfolgreich gespeichert wurde, oder
/// false, falls ein Fehler aufgetreten ist.
bool write_jpeg(const unsigned int width, const unsigned int height, const float* pixels);

#endif // PROKU_JPEG_IO_HPP
