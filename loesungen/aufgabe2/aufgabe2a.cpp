#include <iostream>
#include <limits>

int main()
{
  // Operanden einlesen:
  int a,b;
  char op;
  std::cin >> a >> op >> b;

  // Fehlerhafte Eingabe?
  if(!std::cin.good())
  {
    // Fehlerbehandlung
    std::cin.clear();
    std::cin.ignore(
      std::numeric_limits<std::streamsize>::max(), '\n');

    // Fehlermeldung ausgeben
    std::cout << "FEHLER: Ungueltige Eingabe" << std::endl;
    return 1;
  }

  // Welchen Operator haben wir?
  switch(op)
  {
  // Addition
  case '+':
    std::cout << a << " + " << b << " = " << (a + b) << std::endl;
    break;

  // Subtraktion
  case '-':
    std::cout << a << " - " << b << " = " << (a - b) << std::endl;
    break;

  // Multiplikation
  case '*':
    std::cout << a << " * " << b << " = " << (a * b) << std::endl;
    break;

  // Division
  case '/':
    if(b == 0)
      std::cout << "FEHLER: Division durch 0 ist nicht definiert" << std::endl;
    else
      std::cout << a << " / " << b << " = " << (a / b) << std::endl;
    break;

  // Modulo
  case '%':
    if(b == 0)
      std::cout << "FEHLER: Division durch 0 ist nicht definiert" << std::endl;
    else
      std::cout << a << " % " << b << " = " << (a % b) << std::endl;
    break;

  // Irgendein Zeichen, dass nicht zu unseren Operatoren gehoert
  default:
    std::cout << "FEHLER: unbekannter Operator '" << op << "'" << std::endl;
    break;
  }

  return 0;
}