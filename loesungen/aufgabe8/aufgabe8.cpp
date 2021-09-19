#include <iostream>
#include <sstream>   // fuer std::istringstream
#include <limits>
#include <cassert>

// Hilfs-Funktion:
// Fehlerbehandlung fuer std::cin
void clear_cin()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Liest ein einzelnes Zeichen von der Konsole:
//
// \param[out] c
// Eine Referenz auf den char, in welchen eingelesen werden soll
//
// \returns
// true, falls ein Zeichen eingelesen wurde, sonst false
bool read_char(char& c)
{
  if((std::cin >> c).good())
    return true;
  std::cout << "FEHLER: Ungueltige Eingabe" << std::endl;
  clear_cin();
  return false;
}

// Liest einen einzelnen int von der Konsole:
//
// \param[out] i
// Eine Referenz auf den int, in welchen eingelesen werden soll
//
// \returns
// true, falls eine Zahl eingelesen wurde, sonst false
bool read_int(int& i)
{
  if((std::cin >> i).good())
    return true;
  std::cout << "FEHLER: Ungueltige Eingabe" << std::endl;
  clear_cin();
  return false;
}

// Konvertiert eine Zeichenkette in einen int (falls moeglich)
//
// \param[in] str
// Die Zeichenkette, die konvertiert werden soll
//
// \param[out] i
// Eine Referenz auf den int, in welchen eingelesen werden soll
//
// \returns
// true, falls die Zeichenkette konvertiert wurde, sonst false
bool parse_int(const char* str, int& i)
{
  assert(str != nullptr);
  std::istringstream iss(str);
  return !(iss >> i).fail();
}


// Die Klasse, welche ein einzelnes Element der Liste repraesentiert:
class IntListElement
{
public:
  // Das zu speichernde Datum
  int value;

  // Der Zeiger auf das naechste Element (oder auf nullptr)
  IntListElement* next;

  // Konstruktor:
  explicit IntListElement(int _value) :
    value(_value), next(nullptr)
  {
  }

  explicit IntListElement(int _value, IntListElement* _next) :
    value(_value), next(_next)
  {
  }
}; // class IntListElement

// Die Klasse, welche eine sortierte Liste von ints repraesentiert:
class IntList
{
public:
  // Ein Zeiger auf das erste Listen-Element
  IntListElement* head;

public:
  // Standard-Konstruktor:
  // Erstellt eine leere Liste
  IntList() :
    head(nullptr)
  {
  }

  // Teilaufgabe g)
  // Destruktor:
  // Leert die Liste
  ~IntList()
  {
    clear();
  }

  // Druckt die Liste auf die Konsole
  void print() const
  {
    // Start der Ausgabe:
    std::cout << "[";

    // Laufe ueber alle Elemente der Liste:
    // Wir starten dazu mit dem Element, auf das "head" zeigt,
    // und iterieren mit dem Zeiger "ptr" ueber alle Elemente
    // der Liste:
    const IntListElement* ptr(head);
    while(ptr != nullptr)
    {
      // Drucke das Datum des Elementes
      std::cout << " " << ptr->value;

      // Und gehe zum naechsten Element ueber:
      ptr = ptr->next;
    }

    // Ende der Ausgabe:
    std::cout << "]" << std::endl;
  }

  // Testet die Elemente der Liste
  bool test() const
  {
    // Lese den Rest der Zeile von der Konsole ein
    std::string values;
    std::getline(std::cin, values);

    // Laufe ueber die Liste:
    std::size_t so = 0u, sn = 0u;
    const IntListElement* ptr(head);
    for(int pos = 1; true; ++pos)
    {
      // Finde naechtes Datum in Eingabe
      so = values.find_first_not_of(' ', sn);

      // Kein naechstes Datum erwartet?
      if(so == values.npos)
      {
        // Weitere Elemente in der Liste vorhanden?
        if(ptr != nullptr)
        {
          std::cout << "TEST FEHLGESCHLAGEN!" << std::endl;
          std::cout << "Position: " << pos << std::endl;
          std::cout << "Erwartet: Ende der Liste" << std::endl;
          std::cout << "Gefunden: " << ptr->value << std::endl;
          return false;
        }

        // Okay, erwartetes Listen-Ende gefunden
        break;
      }

      // Finde naechstes Leerzeichen nach Datum
      sn = values.find_first_of(' ', so);
      if(sn == values.npos)
        sn = values.size();

      // Extrahiere naechstes Datum in einen int
      std::string sval = values.substr(so, sn-so);
      int value(0);
      if(!parse_int(sval.c_str(), value))
      {
        std::cout << "FEHLER: Konnte '" << sval << "' nicht als Ganzzahl einlesen!" << std::endl;
        return false;
      }

      // Keine weiteren Elemente vorhanden?
      if(ptr == nullptr)
      {
        std::cout << "TEST FEHLGESCHLAGEN!" << std::endl;
        std::cout << "Position: " << pos << std::endl;
        std::cout << "Erwartet: " << value << std::endl;
        std::cout << "Gefunden: Ende der Liste"  << std::endl;
        return false;
      }

      // Vergleiche Daten
      if(value != ptr->value)
      {
        std::cout << "TEST FEHLGESCHLAGEN!" << std::endl;
        std::cout << "Position: " << pos << std::endl;
        std::cout << "Erwartet: " << value << std::endl;
        std::cout << "Gefunden: " << ptr->value << std::endl;
        return false;
      }

      // Gehe zum naechsten Element ueber
      ptr = ptr->next;
    }

    // Okay, Test erfolgreich
    std::cout << "TEST OK" << std::endl;
    return true;
  }

  // ##########################################################################
  // ##########################################################################
  // ##########################################################################
  // Teilaufgabe a)

  // Gibt die Laenge der Liste auf der Konsole aus
  void size() const
  {
    int count(0);
    const IntListElement* ptr(head);
    while(ptr != nullptr)
    {
      ++count;
      ptr = ptr->next;
    }

    // Ausgabe:
    if(count > 0)
      std::cout << "Es gibt " << count << " Elemente in der Liste" << std::endl;
    else
      std::cout << "Die Liste ist leer" << std::endl;
  }

  // ##########################################################################
  // ##########################################################################
  // ##########################################################################
  // Teilaufgabe b)

  // Sucht nach einem Element in der Liste
  void find(const int value) const
  {
    // Anzahl der gefundenen Elemente
    int count(0);

    // Starte mit einer Kopie des Head-Zeigers
    const IntListElement* ptr(head);

    // Ueberspringe alle kleineren Elemente:
    while((ptr != nullptr) && (ptr->value < value))
      ptr = ptr->next;

    // Zaehle gesuchte Elemente
    while((ptr != nullptr) && (ptr->value == value))
    {
      ++count;
      ptr = ptr->next;
    }

    // Wie viele haben wir?
    std::cout << "Das Element " << value << " ist ";
    if(count > 0)
       std::cout << count << " mal in der Liste vorhanden" << std::endl;
    else
       std::cout << "in der Liste nicht vorhanden" << std::endl;
  }

  // ##########################################################################
  // ##########################################################################
  // ##########################################################################
  // Teilaufgabe c)

  // Es gibt 2 Moeglichkeiten, wie man diese Aufgabe loesen kann:
  // 1. Man merkt sich zusaetzlich den Zeiger auf das Vorgaenger-Element
  // 2. Man merkt sich den Zeiger auf den Zeiger auf das aktuelle Element
  //
  // Hier sind beide Varianten implementiert, die Umschaltung erfolgt der
  // #define INSERT_VARIANT_2

//#define INSERT_VARIANT_2

#ifndef INSERT_VARIANT_2
  // Fuegt ein neues Element in die Liste ein
  void insert(const int value)
  {
    // Der Zeiger auf das akutelle Element:
    IntListElement* ptr(head);

    // Der Zeiger auf das Vorgaenger-Element:
    IntListElement* prev(nullptr);

    // Solange der Vorgaenger einen Nachfolger hat:
    while(ptr != nullptr)
    {
      // Pruefe, ob dieses Element schon groesser ist.
      // Falls ja, dann duerfen wir nicht weiter laufen:
      if(ptr->value >= value)
        break;

      // Merke dieses Element als Vorgaenger:
      prev = ptr;

      // Mache mit dem naechsten Element weiter:
      ptr = ptr->next;
    }

    // Muessen wir am Listen-Anfang einfuegen?
    if(prev == nullptr)
    {
      // Das ist also das neue erste Listen-Element
      head = new IntListElement(value, head);
    }
    else
    {
      // Nicht am Anfang der Liste
      prev->next = new IntListElement(value, ptr);
    }
  }

#else // INSERT_VARIANT_2

  // Fuegt ein neues Element in die Liste ein
  void insert(const int value)
  {
    // Wir merken und den next-Zeiger des Vorgaenger-Elementes.
    // Das erste Listen-Element hat keinen Vorgaenger, aber dafuer
    // zeigt der head der Liste auf genau dieses Element:
    IntListElement** p_previous_next = &head;

    // Solange der Vorgaenger einen Nachfolger hat:
    while(*p_previous_next != nullptr)
    {
      // Zeiger auf das aktuelle Element:
      IntListElement* ptr = *p_previous_next;

      // Pruefe, ob dieses Element schon groesser ist.
      // Falls ja, dann duerfen wir nicht weiter laufen:
      if(ptr->value >= value)
        break;

      // Mache mit dem next-Zeiger des aktuellen Elementes weiter:
      p_previous_next = &(ptr->next);
    }

    // Erstelle ein neues Element
    IntListElement* elem = new IntListElement(value, *p_previous_next);

    // Haenge das Element ein:
    // Wir muessen dazu den next-Zeiger des Vorgaengers umsetzen:
    *p_previous_next = elem;
  }
#endif // INSERT_VARIANT_1/2

  // ##########################################################################
  // ##########################################################################
  // ##########################################################################
  // Teilaufgabe e)

  // Auch hier gibt es wieder zwei Varianten analog zu insert().

//#define ERASE_VARIANT_2

#ifndef ERASE_VARIANT_2
  // Loescht ein oder mehrere Elemente aus der Liste
  void erase(const int value)
  {
    // Ein Zaehler fuer die Elemente:
    int count(0);

    // Loesche alle betroffenen Elemente, wenn sie am Anfang der Liste stehen
    while((head != nullptr) && (head->value == value))
    {
      // Das zu loeschende Element
      IntListElement* p_elem = head;

      // Neuen head setzen:
      head = head->next;

      // Element loeschen
      delete p_elem;
      ++count;
    }

    // Der Zeiger auf das aktuelle Element:
    IntListElement* ptr(head);

    // Der Zeiger auf das Vorgaenger-Element:
    IntListElement* prev(nullptr);

    // Ueberspringe alle Elemente mit kleinerem Wert
    while((ptr != nullptr) && (ptr->value < value))
    {
      // Vorgaenger merken
      prev = ptr;
      // Naechstes Element
      ptr = ptr->next;
    }

    // Loesche alle Elemente mit dem gesuchten Datum
    while((ptr != nullptr) && (ptr->value == value))
    {
      // Setze den next-Zeiger unseres Vorgaengers auf unseren Nachfolger:
      prev->next = ptr->next;

      // Loesche das aktuelle Element
      delete ptr;
      ++count;

      // Naechstes element
      ptr = prev->next;
    }

    // Ausgabe:
    if(count > 0)
      std::cout << "Das Element " << value << " wurde " << count << " mal geloescht" << std::endl;
    else
      std::cout << "Das Element " << value << " ist in der Liste nicht vorhanden" << std::endl;
  }

#else // ERASE_VARIANT_2

  // Loescht ein oder mehrere Elemente aus der Liste
  void erase(const int value)
  {
    // Ein Zaehler fuer die Elemente:
    int count(0);

    // Next-Zeiger des vorgaengers
    IntListElement** p_last_next = &head;

    // Solange der Vorgaenger einen Nachfolger hat, der nicht
    // groesser ist als unser gesuchtes Datum:
    while((*p_last_next != nullptr) && ((*p_last_next)->value < value))
    {
      // Laufe ein Element weiter
      p_last_next = &((*p_last_next)->next);
    }

    // Loesche alle Elemente mit dem gesuchten Datum
    while((*p_last_next != nullptr) && ((*p_last_next)->value == value))
    {
      // Das zu loeschende Element
      IntListElement* p_elem = *p_last_next;

      // Setze den next-Zeiger unseres Vorgaengers auf unseren Nachfolger:
      *p_last_next = ((*p_last_next)->next);

      // Loesche das aktuelle Element
      delete p_elem;

      // Wir haben ein Element geloescht
      ++count;
    }

    // Ausgabe:
    if(count > 0)
      std::cout << "Das Element " << value << " wurde " << count << " mal geloescht" << std::endl;
    else
      std::cout << "Das Element " << value << " ist in der Liste nicht vorhanden" << std::endl;
  }

#endif // ERASE_VARIANT_2

  // ##########################################################################
  // ##########################################################################
  // ##########################################################################
  // Teilaufgabe f)

  // Leert die gesamte Liste
  void clear()
  {
    // Starte mit einer Kopie des Head-Zeigers
    IntListElement* ptr(head);

    // Setze head auf nullptr
    head = nullptr;

    // Laufe ueber die Liste
    while(ptr != nullptr)
    {
      // Merke dir den Zeiger auf das naechste Element
      IntListElement* p_next(ptr->next);

      // Loesche aktuelles Element
      delete ptr;

      // Mache mit naechstem Element weiter
      ptr = p_next;
    }
  }
}; // class IntList

// ############################################################################
// ############################################################################
// ############################################################################

int main(int argc, char* argv[])
{
  // Erstelle ein Objekt vom Typ IntList:
  IntList list;

  // Fuege alle Elemente von der Kommando-Zeile ein:
  for(int i(1); i < argc; ++i)
  {
    // Versuche, den Parameter zu konvertieren:
    int value(0);
    if(!parse_int(argv[i], value))
    {
      std::cout << "FEHLER: ungueltiges Argument '" << (argv[i]) << "'" << std::endl;
      return 1;
    }
    // Okay, einfuegen:
    list.insert(value);
  }

  // Liste ausgeben:
  list.print();

  // Endlos-Eingabe-Schleife:
  bool quit(false);
  while(!quit)
  {
    // Eine char-Variable fuer das erste Zeichen der Eingabe:
    char command(0);

    // Eine int-Hilfsvariable fuer die Befehle, die einen
    // int als Parameter erwarten.
    int value(0);
    std::string values;

    // Eingabe-Aufforderung:
    std::cout << "> ";

    // Lese den Befehl ein:
    if(!read_char(command))
      continue;

    // Welcher Befehl ist das?
    switch(command)
    {
    case 'Q':
    case 'q':
      // Beende Schleife
      quit = true;
      break;

    case 'P':
    case 'p':
      // Liste ausgeben
      list.print();
      break;

    case 'T':
    case 't':
      // Liste testen
      list.test();
      break;

    case 'S':
    case 's':
      // Teilaufgabe a)
      // Listen-Groesse ausgeben
      list.size();
      break;

    case 'F':
    case 'f':
      // Teilaufgabe b)
      // Element in der Liste finden
      if(!read_int(value))
        break;
      list.find(value);
      break;

    case 'I':
    case 'i':
      // Teilaufgabe c)
      // Element in die Liste einfuegen
      if(!read_int(value))
        break;
      list.insert(value);
      list.print();
      break;

    case 'E':
    case 'e':
      // Teilaufgabe e)
      // Element aus der Liste loeschen
      if(!read_int(value))
        break;
      list.erase(value);
      list.print();
      break;

    case 'C':
    case 'c':
      // Teilaufgabe f)
      // Liste leeren
      list.clear();
      list.print();
      break;

    default:
      std::cout << "FEHLER: unbekannter Befehl '" << command << "'" << std::endl;
      break;
    }
  }

  // Ende
  return 0;
}
