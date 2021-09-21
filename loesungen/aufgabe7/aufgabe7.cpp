#include <iostream>
#include <cassert>  // assert


// Ein typedef fuer 'unsigned int'
typedef unsigned int uint;

///
/// Eine Klasse, welche eine rationale Zahl repraesentiert
///
class Rational
{
private:
  /// der Zaehler als 'int'
  int p;
  /// der Nenner als 'uint'
  uint q;

public:
  /// Standard-Konstruktor
  Rational() :
    p(0), q(1u)
  {
  }

  // Ganzzahl Konstruktor
  explicit Rational(int _p) :
    p(_p), q(1u)
  {
  }

  explicit Rational(int p_in, uint q_in) :
    p(0), q(1u)
  {
    if(p_in == 0)
      return;
    assert(q_in != 0u);

    // berechne ggT(p,q)
    uint a = uint(p_in < 0 ? -p_in : p_in);
    uint b = q_in;
    while(b != 0u)
    {
      uint h = a % b;
      a = b;
      b = h;
    }
    // a ist nun der ggT

    // Kuerzen: durch ggT teilen
    p = p_in / int(a);
    q = q_in /= a;
  }

  /// Gibt den Zaehler des Bruches zurueck
  int numerator() const
  {
    return p;
  }

  /// Gibt den Nenner des Bruches zurueck
  uint denominator() const
  {
    return q;
  }

  /// Prueft, ob dieser Bruch eine ganze Zahl ist
  bool is_integer() const
  {
    return (q == 1u);
  }

  bool equals(int p_ref, uint q_ref) const
  {
    return (p == p_ref) && (q == q_ref);
  }

  Rational operator+(const Rational& r) const
  {
    return Rational(int(r.denominator()) * p + r.numerator() * int(q), q * r.denominator());
    //return Rational(p*int(r.q) + int(q)*r.p, q*r.q);
  }

  Rational operator-(const Rational& r) const
  {
//    return Rational(p*int(r.q) - int(q)*r.p, q*r.q);
    return Rational(p * int(r.denominator()) - r.numerator() * int(q), q * r.denominator());
  }

  Rational operator*(const Rational& r) const
  {
//    return Rational(p*r.p, q*r.q);
    return Rational(p * r.numerator(), q * r.denominator());
  }

  Rational operator/(const Rational& r) const
  {
    // Vermeide Division durch Null
    assert(r.p != 0);

    // Im Falle eines negativen Divisors muessen wir das
    // Vorzeichen in den Zaehler des Resultates ziehen:
    if(r.p < 0)
      return Rational(-p*int(r.q), q*uint(-r.p));
    else
      return Rational(p*int(r.q), q*uint(r.p));
  }


  bool operator==(const Rational& other) const {
    return equals(other.numerator(), other.denominator());
  }
}; // class Rational

std::ostream& operator<<(std::ostream& os, const Rational& r) {
  os << r.numerator();
  if(!r.is_integer())
    os << '/' << r.denominator();
  return os;
}

//std::ostream& operator<<(std::ostream& os, const Rational& rat)
//{
//  os << rat.numerator();
//  if(!rat.is_integer())
//    os << '/' << rat.denominator();
//  return os;
//}

// ############################################################################
// ############################################################################
// ############################################################################

// Konstruktor-Test

bool check_ctor(int p_in, uint q_in, int p_ref, uint q_ref)
{
  // Erstelle r := p/q
  Rational r(p_in, q_in);

  // Vergleiche 'r' mit Referenz-Werten
  if(r.equals(p_ref, q_ref))
  {
    // Okay, 'a' stimmt mit den vorgegebenen Referenz-Werten
    // ueberein, wir geben also 'true' zurueck
    return true; // okay
  }

  // Fehlschlag
  std::cout << "FEHLER" << std::endl;
  std::cout << "!!! Eingabe.: " << p_in << "/" << q_in << std::endl;
  std::cout << "!!! Erwartet: " << p_ref << "/" << q_ref << std::endl;
  std::cout << "!!! Erhalten: " << r.numerator() << "/" << r.denominator() << std::endl;
  return false;
}

bool test_ctor()
{
  std::cout << "Teste Konstruktor: ";

  // Durchlaufe Tests
  bool okay = true;
  okay = okay && check_ctor( 2, 1u,  2, 1u); // 2/1
  okay = okay && check_ctor( 1, 3u,  1, 3u); // 1/3
  okay = okay && check_ctor( 0, 7u,  0, 1u); // 0/7 -> 0/1
  okay = okay && check_ctor(-6, 9u, -2, 3u); // -6/9 -> -2/3
  okay = okay && check_ctor( 6, 2u,  3, 1u); // 6/2 -> 3/1

  // Waren alle Tests erfolgreich?
  if(okay)
    std::cout << "OK" << std::endl;
  return okay;
}

// ############################################################################
// ############################################################################
// ############################################################################

// Operator Tests

bool check_plus(const Rational& a, const Rational& b, int p_ref, uint q_ref)
{
//  // Berechne r := (a + b)
//  Rational r = a + b;
//
//  // Vergleiche 'r' mit gegebenen Referenz-Werten
//  if(r.equals(p_ref, q_ref))
//  {
//    // Okay, 'r' stimmt mit den vorgegebenen Referenz-Werten
//    // ueberein, wir geben also 'true' zurueck
    return true; // okay
//  }
//
//  // Fehlschlag
//  std::cout << "FEHLER" << std::endl;
//  std::cout << "!!! Eingabe.:     a = " << a << std::endl;
//  std::cout << "!!! Eingabe.:     b = " << b << std::endl;
//  std::cout << "!!! Erwartet: a + b = " << p_ref << "/" << q_ref << std::endl;
//  std::cout << "!!! Erhalten: a + b = " << r.numerator() << "/" << r.denominator() << std::endl;
//  return false;
}

bool test_plus_op()
{
  // Erstelle ein paar Zahlen zum Testen
  Rational a( 3, 2);
  Rational b(10, 4); // = 5/2
  Rational c( 1, 3);
  Rational d(-5, 2);
  Rational e( 0);

  // Ausgabe:
  std::cout << "Teste operator+(): ";

  // Durchlaufe Tests
  bool okay = true;
  okay = okay && check_plus(a, b,  4, 1u); //  3/2 +  5/2 =  4
  okay = okay && check_plus(a, c, 11, 6u); //  3/2 +  1/3 = 11/6
  okay = okay && check_plus(b, c, 17, 6u); // 10/4 +  1/3 = 17/6
  okay = okay && check_plus(a, d, -1, 1u); //  3/2 + -5/2 = -1
  okay = okay && check_plus(b, d,  0, 1u); // 10/4 + -5/2 = 0
  okay = okay && check_plus(c, d,-13, 6u); //  1/3 + -5/2 = -13/6
  okay = okay && check_plus(e, b,  5, 2u); //    0 + 10/4 = 5/2

  // Waren alle Tests erfolgreich?
  if(okay)
    std::cout << "OK" << std::endl;
  return okay;
}

bool check_minus(const Rational& a, const Rational& b, int p_ref, uint q_ref)
{
  // Berechne r := (a - b)
  Rational r = a - b;

  // Vergleiche 'r' mit Referenz-Werten
  if(r.equals(p_ref, q_ref))
  {
    // Okay, 'r' stimmt mit den vorgegebenen Referenz-Werten
    // ueberein, wir geben also 'true' zurueck
    return true; // okay
  }

  // Fehlschlag
  std::cout << "FEHLER" << std::endl;
  std::cout << "!!! Eingabe.:     a = " << a << std::endl;
  std::cout << "!!! Eingabe.:     b = " << b << std::endl;
  std::cout << "!!! Erwartet: a - b = " << p_ref << "/" << q_ref << std::endl;
  std::cout << "!!! Erhalten: a - b = " << r.numerator() << "/" << r.denominator() << std::endl;
  return false;
}

bool test_minus_op()
{
  // Erstelle ein paar Zahlen zum Testen
  Rational a( 3, 2);
  Rational b(10, 4); // = 5/2
  Rational c( 1, 3);
  Rational d(-5, 2);
  Rational e( 0);

  // Ausgabe:
  std::cout << "Teste operator-(): ";

  // Durchlaufe Tests
  bool okay = true;
  okay = okay && check_minus(a, b, -1, 1u); //  3/2 -  5/2 = -1
  okay = okay && check_minus(a, c,  7, 6u); //  3/2 -  1/3 = 7/6
  okay = okay && check_minus(b, c, 13, 6u); // 10/4 -  1/3 = 13/6
  okay = okay && check_minus(a, d,  4, 1u); //  3/2 - -5/2 = 4
  okay = okay && check_minus(b, d,  5, 1u); // 10/4 - -5/2 = 5
  okay = okay && check_minus(c, d, 17, 6u); //  1/3 - -5/2 = 17/6
  okay = okay && check_minus(e, b, -5, 2u); //    0 - 10/4 = -5/2

  // Waren alle Tests erfolgreich?
  if(okay)
    std::cout << "OK" << std::endl;
  return okay;
}

bool check_multiply(const Rational& a, const Rational& b, int p_ref, uint q_ref)
{
  // Berechne r := (a * b)
  Rational r = a * b;

  // Vergleiche 'r' mit Referenz-Werten
  if(r.equals(p_ref, q_ref))
  {
    // Okay, 'r' stimmt mit den vorgegebenen Referenz-Werten
    // ueberein, wir geben also 'true' zurueck
    return true; // okay
  }

  // Fehlschlag
  std::cout << "FEHLER" << std::endl;
  std::cout << "!!! Eingabe.:     a = " << a << std::endl;
  std::cout << "!!! Eingabe.:     b = " << b << std::endl;
  std::cout << "!!! Erwartet: a * b = " << p_ref << "/" << q_ref << std::endl;
  std::cout << "!!! Erhalten: a * b = " << r.numerator() << "/" << r.denominator() << std::endl;
  return false;
}

bool test_multiply_op()
{
  // Erstelle ein paar Zahlen zum Testen
  Rational a( 3, 2);
  Rational b(10, 4); // = 5/2
  Rational c( 1, 3);
  Rational d(-5, 2);
  Rational e( 0);

  // Ausgabe:
  std::cout << "Teste operator*(): ";

  // Durchlaufe Tests
  bool okay = true;
  okay = okay && check_multiply(a, b, 15, 4u); //  3/2 *  5/2 = 15/4
  okay = okay && check_multiply(a, c,  1, 2u); //  3/2 *  1/3 = 1/2
  okay = okay && check_multiply(b, c,  5, 6u); // 10/4 *  1/3 = 5/6
  okay = okay && check_multiply(a, d,-15, 4u); //  3/2 * -5/2 = -15/4
  okay = okay && check_multiply(b, d,-25, 4u); // 10/4 * -5/2 = -25/4
  okay = okay && check_multiply(c, d, -5, 6u); //  1/3 * -5/2 = -5/6
  okay = okay && check_multiply(e, b,  0, 1u); //    0 * 10/4 = 0

  // Waren alle Tests erfolgreich?
  if(okay)
    std::cout << "OK" << std::endl;
  return okay;
}

bool check_divide(const Rational& a, const Rational& b, int p_ref, uint q_ref)
{
  // Berechne r := (a / b)
  Rational r = a / b;

  // Vergleiche 'r' mit Referenz-Werten
  if(r.equals(p_ref, q_ref))
  {
    // Okay, 'r' stimmt mit den vorgegebenen Referenz-Werten
    // ueberein, wir geben also 'true' zurueck
    return true; // okay
  }

  // Fehlschlag
  std::cout << "FEHLER" << std::endl;
  std::cout << "!!! Eingabe.:     a = " << a << std::endl;
  std::cout << "!!! Eingabe.:     b = " << b << std::endl;
  std::cout << "!!! Erwartet: a / b = " << p_ref << "/" << q_ref << std::endl;
  std::cout << "!!! Erhalten: a / b = " << r.numerator() << "/" << r.denominator() << std::endl;
  return false;
}

bool test_divide_op()
{
  // Erstelle ein paar Zahlen zum Testen
  Rational a( 3, 2);
  Rational b(10, 4); // = 5/2
  Rational c( 1, 3);
  Rational d(-5, 2);
  Rational e( 0);

  // Ausgabe:
  std::cout << "Teste operator/(): ";

  // Durchlaufe Tests
  bool okay = true;
  okay = okay && check_divide(a, b,  3, 5u); //  3/2 /  5/2 = 3/5
  okay = okay && check_divide(a, c,  9, 2u); //  3/2 /  1/3 = 9/2
  okay = okay && check_divide(b, c, 15, 2u); // 10/4 /  1/3 = 15/2
  okay = okay && check_divide(a, d, -3, 5u); //  3/2 / -5/2 = -3/5
  okay = okay && check_divide(b, d, -1, 1u); // 10/4 / -5/2 = -1
  okay = okay && check_divide(c, d, -2,15u); //  1/3 / -5/2 = -2/15
  okay = okay && check_divide(e, b,  0, 1u); //    0 / 10/4 = 0

  // Waren alle Tests erfolgreich?
  if(okay)
    std::cout << "OK" << std::endl;
  return okay;
}

bool run_tests()
{
  std::cout << "Starte Tests..." << std::endl;
  std::cout << std::endl;

  // Durchlaufe alle Tests
  bool okay = true;
  okay = okay && test_ctor();
//  //okay = okay && test_less_op();
  okay = okay && test_plus_op();
  okay = okay && test_minus_op();
  okay = okay && test_multiply_op();
  okay = okay && test_divide_op();

  if(okay)
  {
    std::cout << std::endl;
    std::cout << "Alle Tests waren erfolgreich!" << std::endl;
    return true;
  }
  else
    return false;
}

void lyness(Rational a, Rational x_0, Rational x_1)
{
  Rational x_k_2(x_0); // x_{k-2}
  Rational x_k_1(x_1); // x_{k-1}

  // Ausgabe von x_0 und x_1
  std::cout << "a = " << a << ": " << x_k_2 << ", " << x_k_1;

  // Berechne x_2, ..., x_20
  for(int k(2); k < 20; ++k)
  {
    // Berechne x_k und gebe es aus
    Rational x_k = (a + x_k_1) / x_k_2;
    std::cout << ", " << x_k;

    // Pruefe, ob wir die Periode erreicht haben
    if((x_k == x_1) && (x_k_1 == x_0))
    {
      std::cout << std::endl;
      std::cout << "Periode bei k = " << k << std::endl;
      return;
    }

    // Setze x_{k-2} und x_{k-1} fuer die naechste Iteration
    x_k_2 = x_k_1;
    x_k_1 = x_k;
  }
}

void lyness2(const Rational &a, const Rational &x0, const Rational &x1) {

  Rational x_k_1 = x1;
  Rational x_k_2 = x0;

  std::cout << "a = " << a << ": , x_0: " << x_k_2 << ", x_1: " << x_k_1 << ", ";

  for(int k(2); k < 20; ++k) {

    Rational x_k = (a + x_k_1)/x_k_2;

    std::cout << "x_" << k << ": " << x_k;

    if(x_k == x1 && x_k_1 == x0)
      break;

    std::cout << ", ";

    x_k_2 = x_k_1;
    x_k_1 = x_k;

  }

  std::cout << std::endl;

}

int main()
{
  run_tests();

  std::cout << std::endl;
  std::cout << "Lyness-Folgen:" << std::endl;
  lyness(Rational(11), Rational(29,82u), Rational(19,22));
  lyness2(Rational(11), Rational(29,82u), Rational(19,22));
//  lyness(Rational(20), Rational(-11,3u), Rational(-35,32u));
//  //lyness(Rational(20), Rational(5,166u), Rational(-95,12u));
//  //lyness(Rational(21, 37u), Rational(221,14u), Rational(-645, 658u));
//  lyness(Rational(21, 37u), Rational(-51,35), Rational(-32,7));

  return 0;
}
