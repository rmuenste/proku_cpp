#include <iostream>
#include <cassert>
#include "dbe.hpp"

// Hinweis 1:
// Diese Datei ist bereits fertig implementiert und braucht von Ihnen nicht
// mehr angepasst zu werden.
//
// Hinweis 2:
// Am Ende der ersten Kurs-Woche sollten Sie prinzipiell in der Lage sein,
// den Code in dieser Datei nachvollziehen zu koennen.

///
/// \brief Konvertiert eine Dezimalzahl in einen Bruch und gibt diesen auf der Konsole aus
///
/// \param[in] str
/// Eine Zeichenkette, welche die zu konvertierende Dezimalzahl enthaelt
///
/// \returns
/// 0, falls die Eingabe erfolgreich abgearbeitet wurde,
/// k > 0, falls das k-te Zeichen in 'str' ungueltig war
///
int process(const char* str)
{
  assert(str != nullptr);

  // Vorzeichen
  bool negative = false;

  // die zu parsenden Variablen
  int d = 0, m = 0, p = 0, n = 0;

  // Index des aktuell betrachteten Zeichens von str
  int i = 0;

  // dekodiere Vorzeichen
  for(; str[i] != 0; ++i)
  {
    // positives Vorzeichen?
    if(str[i] == '+')
    {
      ++i;
      break;
    }
    // negatives Vorzeichen?
    if(str[i] == '-')
    {
      negative = true;
      ++i;
      break;
    }
    // Beginn der Dezimal-Ziffern?
    if((str[i] == '.') || ((str[i] >= '0') && (str[i] <= '9')))
      break;
    // Jedes andere Zeichen ist ungueltig
    return i+1;
  }

  // dekodiere Dezimalstellen vor dem Punkt
  for(; str[i] != 0; ++i)
  {
    // Ziffer?
    if((str[i] >= '0') && (str[i] <= '9'))
    {
      // aktualisiere 'd': d_neu := 10*d_alt + ziffer
      (d *= 10) += int(str[i] - '0');
      continue;
    }
    // Dezimal-Punkt?
    if(str[i] == '.')
    {
      // weiter zum naechsten Zeichen
      ++i;
      break;
    }
    // Jedes andere Zeichen ist ungueltig
    return i+1;
  }

  // dekodiere Dezimalstellen vor der Periode
  for(; str[i] != 0; ++i)
  {
    // Ziffer?
    if((str[i] >= '0') && (str[i] <= '9'))
    {
      // aktualisiere 'd'
      (d *= 10) += int(str[i] - '0');
      // erhoehe Nachkomma-Stellen-Zaehler
      ++m;
      continue;
    }
    // Perioden-Trennzeichen?
    if((str[i] == 'p') || (str[i] == 'P'))
    {
      // weiter zum naechsten Zeichen
      ++i;
      break;
    }
    // Jedes andere Zeichen ist ungueltig
    return i+1;
  }

  // dekodiere Periode
  for(; str[i] != 0; ++i)
  {
    // Ziffer?
    if((str[i] >= '0') && (str[i] <= '9'))
    {
      // aktualisiere 'p' und erhoehe Perioden-Stellen-Zaehler
      (p *= 10) += int(str[i] - '0');
      ++n;
      continue;
    }
    // Jedes andere Zeichen ist ungueltig
    return i+1;
  }

  // negatives Vorzeichen?
  if(negative)
  {
    d = -d;
    p = -p;
  }

  /*
  // >>>>> DEBUG >>>>>
  std::cout << " s = " << str << std::endl;
  std::cout << " d = " << d << std::endl;
  std::cout << " m = " << m << std::endl;
  std::cout << " p = " << p << std::endl;
  std::cout << " n = " << n << std::endl;
  // <<<<< DEBUG <<<<<
  */

  // Eingabe-Zeichenkette ausgeben
  std::cout << str << " = ";

  // Dezimal-Bruch-Entwicklung durchfuehren:
  dbe(d, m, p, n);

  // okay
  return 0;
}

// Die main-Funktion:
int main(int argc, char* argv[])
{
  // laufe ueber alle Eingabe-Argumente
  for(int i(1); i < argc; ++i)
  {
    // versuche, das i-te Argument abzuarbeiten
    int r = process(argv[i]);

    // Fehlerhafte Eingabe?
    if(r > 0)
    {
      // Fehlerhaftes Zeichen in der Eingabe
      std::cout << "Ungueltige Eingabe: unerwartetes Zeichen' " << argv[i][r-1] << "' bei:" << std::endl;
      std::cout << ' ' << argv[i] << std::endl;
      for(int j(0); j < r; ++j)
        std::cout << ' ';
      std::cout << '^' << std::endl;
      return 1;
    }
  }
  // okay
  return 0;
}
