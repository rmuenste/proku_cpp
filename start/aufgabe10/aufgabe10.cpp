#include <iostream>
#include <string>     // std::string
#include <deque>      // std::deque


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
std::deque<std::string> split(const std::string& str)
{

  // TODO: implementier mich!

}

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
  // TODO: durch Implementierung ersetzen
  return str;
}

// Kehrt die Buchstaben in jedem string einer deque um
//
// \param[in,out] words
// Eine deque aus strings, welche umgekehrt werden sollen.
void reverse_words(std::deque<std::string>& words)
{
  // TODO: implementier mich!
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
  // TODO: durch Implementierung ersetzen
  return words.front();
}

// Die main Funktion
int main()
{
  // Eingabe-Text
  const std::string text = "eht kciuq nworb xof spmuj revo a yzal god";

  // Zerlege in Worte
  //std::deque<std::string> words = split(text);

  // Worte umkehren
  //reverse_words(words);

  // Worte zusammenfuegen
  //std::string rev_text = join(words);

  // Ausgabe
  //std::cout << rev_text << std::endl;

  // okay
  return 0;
}