#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ex_assert.hpp>
#include <string>
#include <limits>


namespace ex {

    inline bool leapYear(int y) {
        return ((y % 400 == 0) || ((y % 100 != 0) && (y % 4 == 0)));
    }

    int ex2p(int day, int month, int year) {
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

      std::cout << "1> Tage vergangen: " << days << std::endl;
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
      std::cout << "2> Tage vergangen: " << days << std::endl;

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

    }

    int ex2b() {

        int d, m, y;
        std::cout << "Geben Sie ein Datum der Form: 7 9 2021<return> ein." << std::endl;

        std::cin >> d >> m >> y;

        if (std::cin.fail()) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Error: invalid input." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        bool ly = leapYear(y);

        // ungueltiges jahr?
        if(y < 1584)
        {
          std::cout << "FEHLER: ungueltiges Jahr: " << y << std::endl;
          return 1;
        }
  
        // ungueltiger Monat?
        if((m < 1) || (m > 12))
        {
          std::cout << "FEHLER: ungueltiger Monat: " << m << std::endl;
          return 1;
        }
  
        // ungueltiger Tag?
        if(m == 2)
        {
          // Sonderfall Februar: hoechstens 29 Tage
          if((d < 1) || (d > 29))
          {
            std::cout << "FEHLER: ungueltiger Tag: " << d << std::endl;
            return 1;
          }
          // Ist das ein Schaltjahr?
          if((d == 29) && !ly)
          {
            std::cout << "FEHLER: ungueltiger Tag: " << d << std::endl;
            std::cout << "Bemerkung: " << y << " ist kein Schaltjahr!" << std::endl;
            return 1;
          }
        }
        else if((m % 2) == 0)
        {
          // gerader Monat
          if((d < 1) || ((m <= 7) && (d > 30)) || ((m > 7) && (d > 31)))
          {
            std::cout << "FEHLER: ungueltiger Tag: " << d << std::endl;
            return 1;
          }
        }
        else
        {
          // ungerader Monat
          if((d < 1) || ((m <= 7) && (d > 31)) || ((m > 7) && (d > 30)))
          {
            std::cout << "FEHLER: ungueltiger Tag: " << d << std::endl;
            return 1;
          }
        }

        std::cout << "Der " << d << "." << m << "." << y << " ist ein ";

        //std::cout << "Jahre vergangen: " << y_passed << std::endl;

        int daysPassed = 0;
        for (int i(1584); i < y; ++i) {

            if (leapYear(i))
                daysPassed += 366;
            else
                daysPassed += 365;

        }

        for (int month = 1; month < m; ++month) {

            if (month == 2)
                daysPassed += (ly ? 29 : 28);
            else if ((month <= 7) && (month % 2 == 0))
                daysPassed += 30;
            else if ((month > 7) && (month % 2 != 0))
                daysPassed += 30;
            else
                daysPassed += 31;

        }

        daysPassed += d;

        switch (daysPassed % 7) {
        case 0:
            std::cout << "Samstag." << std::endl;
            break;
        case 1:
            std::cout << "Sonntag." << std::endl;
            break;
        case 2:
            std::cout << "Montag." << std::endl;
            break;
        case 3:
            std::cout << "Dienstag." << std::endl;
            break;
        case 4:
            std::cout << "Mittwoch." << std::endl;
            break;
        case 5:
            std::cout << "Donnerstag." << std::endl;
            break;
        case 6:
            std::cout << "Freitag." << std::endl;
            break;
        }


    }

};

using namespace ex;

int main(int argc, char *argv[]) {

    ex_HEADLINE("EX1B");
    ex_EMPTY_LINE(2);
    ex2b();

    return EXIT_SUCCESS;
}
