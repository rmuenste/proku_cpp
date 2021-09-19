#include <iostream>

int main()
{
  // Datum einlesen
  int day, month, year;
  std::cout << "Datum eingeben: ";
  std::cin >> day >> month >> year;

  // Ist das ein Schaltjahr?
  bool leap_year = (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));

  // ungueltiges jahr?
  if(year < 1584)
  {
    std::cout << "FEHLER: ungueltiges Jahr: " << year << std::endl;
    return 1;
  }

  // ungueltiger Monat?
  if((month < 1) || (month > 12))
  {
    std::cout << "FEHLER: ungueltiger Monat: " << month << std::endl;
    return 1;
  }

  // ungueltiger Tag?
  if(month == 2)
  {
    // Sonderfall Februar: hoechstens 29 Tage
    if((day < 1) || (day > 29))
    {
      std::cout << "FEHLER: ungueltiger Tag: " << day << std::endl;
      return 1;
    }
    // Ist das ein Schaltjahr?
    if((day == 29) && !leap_year)
    {
      std::cout << "FEHLER: ungueltiger Tag: " << day << std::endl;
      std::cout << "Bemerkung: " << year << " ist kein Schaltjahr!" << std::endl;
      return 1;
    }
  }
  else if((month % 2) == 0)
  {
    // gerader Monat
    if((day < 1) || ((month <= 7) && (day > 30)) || ((month > 7) && (day > 31)))
    {
      std::cout << "FEHLER: ungueltiger Tag: " << day << std::endl;
      return 1;
    }
  }
  else
  {
    // ungerader Monat
    if((day < 1) || ((month <= 7) && (day > 31)) || ((month > 7) && (day > 30)))
    {
      std::cout << "FEHLER: ungueltiger Tag: " << day << std::endl;
      return 1;
    }
  }

  // Berechne Anzahl Tage seit 01.01.1584
  int days = 0;

  // Vergangene Jahre seit 1584
  for(int y(1584); y < year; ++y)
  {
    // Schaltjahr?
    if((y % 400 == 0) || ((y % 100 != 0) && (y % 4 == 0)))
      days += 366;
    else
      days += 365;
  }

  // Vergangene Monate in diesem Jahr
  for(int m(1); m < month; ++m)
  {
    if(m == 2)
      days += (leap_year ? 29 : 28); // Februar: Schaltjahr (?)
    else if((m <= 7) && (m % 2 == 0))
      days += 30; // gerader Monat bis Juli: 30 Tage
    else if((m > 7) && (m % 2 != 0))
      days += 30; // ungerader Monat ab August: 30 Tage
    else
      days += 31; // sonst: 31 Tage
  }

  // Vergangene Tage in diesem Monat
  days += day;

  // Ausgabe:
  std::cout << "Der " << day << "." << month << "." << year << " ist ein ";
  switch(days % 7)
  {
  case 0:
    std::cout << "Samstag" << std::endl;
    break;
  case 1:
    std::cout << "Sonntag" << std::endl;
    break;
  case 2:
    std::cout << "Montag" << std::endl;
    break;
  case 3:
    std::cout << "Dienstag" << std::endl;
    break;
  case 4:
    std::cout << "Mittwoch" << std::endl;
    break;
  case 5:
    std::cout << "Donnerstag" << std::endl;
    break;
  case 6:
    std::cout << "Freitag" << std::endl;
    break;
  }

  // Ende
  return 0;
}