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
  explicit IntListElement(int _value, IntListElement* _next = nullptr) :
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

  // Druckt die Liste auf die Konsole
  void print() const
  {
    // Start der Ausgabe:
    std::cout << "[";

    // Laufe ueber alle Elemente der Liste:
    // Wir starten dazu mit dem Element, auf das "head" zeigt,
    // und iterieren mit dem Zeiger "ptr" ueber alle Elemente
    // der Liste, indem wir "ptr" auf "ptr->next" setzen:
    const IntListElement* ptr(head);
    while(ptr != nullptr)
    {
      // Drucke das Datum des aktuellen Elementes:
      std::cout << " " << ptr->value;

      // Und gehe zum naechsten Element ueber:
      ptr = ptr->next;
    }

    // Ende der Ausgabe:
    std::cout << "]" << std::endl;
  }

  void erase(int val) {

    if(head == nullptr) {
      std::cout << "Die Liste ist leer."  << std::endl;
      return;
    }

    if(head->value == val) {
      std::cout << "Head wird geloescht und new gesetzt." << head->value << std::endl;
      IntListElement* temp = head->next;
      delete head;
      head = temp;
      return;
    }

    IntListElement* iter = head;
    while(iter->next != nullptr) {

      if(iter->next->value == val) {
        IntListElement* temp = iter->next->next;
        std::cout << "Das Element " << iter->next->value << " wurde gefunden." << std::endl;
        delete iter->next;
        iter->next = temp;
        return;
      }
      iter = iter->next;
    }

    std::cout << "Das Element " << val << " ist in der Liste nicht vorhanden." << std::endl;
  }
  //
  void find(int val) {

    IntListElement* iter = head;

    int counter = 0;
    while(iter != nullptr) {
      std::cout << "Wert: " << iter->value << std::endl;
      if (iter->value == val) {
        counter++;
      }
      if ( iter->next != nullptr &&  (val < iter->next->value && val > iter->value)  )
          std::cout << "Einfuege Pos gefunden: " << iter->value << " <= " << val << " < " << iter->next->value << std::endl;
      iter = iter->next;
    }

    if(counter > 0) 
      std::cout << "Wert " << val << " wurde " << counter << " mal gefunden." << std::endl;
  } 

  void insert(int val) {

    if (head == nullptr) {
      std::cout << "Einfuege Pos gefunden: empty new Head" << std::endl;
      IntListElement* newElem = new IntListElement(val, nullptr);
      head = newElem;
      return;
    }

    if (val <= head->value) {
      std::cout << "Einfuege Pos gefunden: new Head" << std::endl;
      IntListElement* newElem = new IntListElement(val, head);
      head = newElem;
      return;
    }

    IntListElement* iter = head;

    while(iter != nullptr) {

      std::cout << "iterating: " << iter->value << std::endl;
      std::cout << "next: " << iter->next << std::endl;

//      if ( iter->next == nullptr) {
//
//          std::cout << "Einfuege Pos gefunden: " << iter->value << " <= " << val << std::endl;
//          IntListElement* newElem = new IntListElement(val, iter->next);
//          iter->next = newElem;
//          break;
//
//      }

      if ( iter->next == nullptr || (val <= iter->next->value && val > iter->value)  ) {

          if (iter->next != nullptr)
            std::cout << "Einfuege Pos gefunden: " << iter->value << " <= " << val << " < " << iter->next->value << std::endl;
          else
            std::cout << "Einfuege Pos gefunden: " << iter->value << " <= " << val << std::endl;
          IntListElement* newElem = new IntListElement(val, iter->next);
          iter->next = newElem;
          break;

      }
      iter = iter->next;

    }

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
}; // class IntList

int main(int argc, char* argv[])
{
  // Erstelle ein Objekt vom Typ IntList:
  IntList list;

  // >>>>>>>>>> TESTWEISE >>>>>>>>>>
  // Wichtig:
  // Loeschen Sie diesen Test-Code, wenn Sie bei Teilaufgabe d) ankommen!
  // Erstelle 5 Elemente auf dem Stack und verkette sie von Hand:
//  IntListElement elem_0(7, nullptr);
//  IntListElement elem_1(5, &elem_0);
//  IntListElement elem_2(5, &elem_1);
//  IntListElement elem_3(3, &elem_2);
//  IntListElement elem_4(2, &elem_3);
//  // Haenge die Elemente in die Liste ein:
//  list.head = &elem_4;
  // <<<<<<<<<< TESTWEISE <<<<<<<<<<
  //
  for (int i(1); i < argc; ++i) {

    int value(0);
    if(!parse_int(argv[i], value)) {

      std::cout << "ungueltige Eingabe" << std::endl;
      return 1;
    }
    list.insert(value);

  }
  list.print();

  // Endlos-Eingabe-Schleife:
  bool quit(false);
  while(!quit)
  {
    // Eine char-Variable fuer das erste Zeichen der Eingabe:
    char command(0);
    int userInput(0);

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

    case 'F':
    case 'f':
      if(read_int(userInput))
        list.find(userInput);
      break;

    case 'I':
    case 'i':
      if(read_int(userInput))
        list.insert(userInput);
      break;

    case 'e':
    case 'E':
      if(read_int(userInput))
        list.erase(userInput);
      break;

    // TODO: weitere Befehle einfuegen

    default:
      std::cout << "FEHLER: unbekannter Befehl '" << command << "'" << std::endl;
      break;
    }
  }

  // Ende
  return 0;
}
