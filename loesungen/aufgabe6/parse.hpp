#ifndef PROKU_PARSE_HPP
#define PROKU_PARSE_HPP

///
/// Versucht, eine Zeichenkette in eine Zahl zu konvertieren
///
/// \param[in] str
/// Die zu konvertierende Zeichenkette. Darf kein Null-Zeiger sein.
///
/// \param[out] value
/// Eine Referenz auf das Objekt, in welches die Zahl eingelesen werden soll.
///
/// \returns
/// true, falls die Zeichenkette konvertiert werden konnte, oder
/// false, falls bei der Konvertierung ein Fehler aufgetreten ist.
///
bool parse(const char* str, int& value);
bool parse(const char* str, unsigned int& value);
bool parse(const char* str, float& value);
bool parse(const char* str, double& value);

///
/// Versucht, eine Zeichenkette in eine Zahl zu konvertieren,
/// welche in einem vorgegebenen Werte-Bereich liegen muss
///
/// \param[in] str
/// Die zu konvertierende Zeichenkette. Darf kein Null-Zeiger sein.
///
/// \param[out] value
/// Eine Referenz auf das Objekt, in welches die Zahl eingelesen werden soll.
///
/// \param[in] min_val
/// Die untere Schranke fuer gueltige Eingaben
///
/// \param[in] max_val
/// Die obere Schranke fuer gueltige Eingaben
///
/// \returns
/// true, falls die Zeichenkette konvertiert werden konnte, oder
/// false, falls eine der drei folgenden Bedingungen erfuellt ist:
/// 1. bei der Konvertierung ist ein Fehler aufgetreten
/// 2. (value < min_val)
/// 3. (value > max_val)
///
bool parse(const char* str, int& value, int min_val, int max_val);
bool parse(const char* str, unsigned int& value, unsigned int min_val, unsigned int max_val);
bool parse(const char* str, float& value, float min_val, float max_val);
bool parse(const char* str, double& value, double min_val, double max_val);

#endif // PROKU_PARSE_HPP
