#include <iostream>
#include <string>     // std::string
#include <deque>      // std::deque

#define SPLIT_MANUAL

// Zerlegt einen Satz in eine deque aus Woertern
//
// Beispiel:
// Eingabe: "Hello World"
// Ausgabe: ["Hello", "World"]
//
// \param[in] str
// Der string, der in seine Worte zerlegt werden soll
//
// \returns
// Eine deque aus strings, welche die einzelnen Worte
// von 'str' enthaelt
#ifdef SPLIT_MANUAL

// "manuelle" Version von "split"
std::deque<std::string> split(const std::string& str)
{
  // Eine deque fuer die Ausgabe
  std::deque<std::string> r;

  // das aktuelle Wort
  std::string word;

  // Laufe ueber alle Zeichen der Eingabe
  for(std::size_t i(0); i < str.size(); ++i)
  {
    // Ist das kein Leerzeichen?
    if(str.at(i) != ' ')
    {
      // an Wort anfuegen
      word.push_back(str.at(i));
      continue;
    }

    // Es ist ein Leerzeichen:
    // Haben wir schon ein Wort?
    if(!word.empty())
    {
      // Wort in die Liste aufnehmen
      r.push_back(word);

      // Und wort leeren
      word.clear();
    }
  }

  // Ist noch ein Wort uebrig?
  if(!word.empty())
    r.push_back(word);

  // deque zurueckgeben
  return r;
}

#else // not SPLIT_MANUAL

// Version mit Member-Funktionen von std::string
std::deque<std::string> split(const std::string& str)
{
  // Eine deque fuer die Ausgabe
  std::deque<std::string> r;

  // Finde das erste Nicht-Leerzeichen
  std::size_t off = str.find_first_not_of(' ');
  while(off != str.npos)
  {
    // Finde das naechste Leerzeichen
    std::size_t upto = str.find_first_of(' ', off);

    // Ist das das Ende des Strings?
    if(upto == str.npos)
    {
      // Neues Wort: von 'off' bis zum Ende der Eingabe
      r.push_back(str.substr(off));
      break;
    }
    else
    {
      // Neues Wort: von 'off' bis 'upto'
      r.push_back(str.substr(off, upto - off));
    }

    // Finde das naechste Nicht-Leerzeichen
    off = str.find_first_not_of(' ', upto);
  }

  // deque zurueckgeben
  return r;
}

#endif // SPLIT_MANUAL

// Kehrt die Buchstaben in einem string um
//
// Beispiel:
// Eingabe: "foobar"
// Ausgabe: "raboof"
//
// \param[in] str
// Der string, dessen Buchstaben umgekehrt werden soll
//
// \returns
// Der umgekehrte string
std::string reverse(const std::string& str)
{
  std::string r;
  for(std::size_t i(0); i < str.size(); ++i)
    r.push_back(str.at(str.size()-i-1));
  return r;
}

// Kehrt die Buchstaben in jedem string einer deque um
//
// \param[in,out] words
// Eine deque aus strings, welche umgekehrt werden sollen.
void reverse_words(std::deque<std::string>& words)
{
  for(std::deque<std::string>::iterator it = words.begin(); it != words.end(); ++it)
  {
    *it = reverse(*it);
  }
}

// Fuegt eine deque aus strings zu einem mit Leerzeichen getrennten string zusammen
//
// Beispiel:
// Eingabe: ["foo", "bar"]
// Ausgabe: "foo bar"
//
// \param[in] words
// Die deque aus strings, welche zusammengefuegt werden sollen
//
// \returns
// Der zusammengesetzte string
std::string join(const std::deque<std::string>& words)
{
  std::string r;

  // erstes Wort ohne fuehrendes Leerzeichen
  if(!words.empty())
    r = words.front();

  // alle uebrigen Worte mit Leerzeichen anfuegen
  for(std::size_t i(1); i < words.size(); ++i)
  {
    r += ' ';
    r += words.at(i);
  }

  return r;
}

// Die main Funktion
int main()
{
  // Eingabe-Text
  const std::string text = "eht kciuq nworb xof spmuj revo a yzal god";

  // Zerlege in Worte
  std::deque<std::string> words = split(text);

  // Worte umkehren
  reverse_words(words);

  // Worte zusammenfuegen
  std::string rev_text = join(words);

  // Ausgabe
  std::cout << rev_text << std::endl;

  // okay
  return 0;
}