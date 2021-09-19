#include <iostream>
#include <limits>
#include <cassert>

int main()
{
  // Teilaufgabe a)
  // Spielfeld erstellen und mit 0 initialisieren
  constexpr int m = 6;
  constexpr int n = 7;
  int field[m][n];
  for(int i(0); i < m; ++i)
    for(int j(0); j < n; ++j)
      field[i][j] = 0;

  // Teilaufgabe b)
  // leeres Spielfeld zeichnen
  for(int i(0); i < m; ++i)
  {
    for(int j(0); j < n; ++j)
      std::cout << " |  ";
    std::cout << " |" << std::endl;
  }
  std::cout << " +";
  for(int i(0); i < n; ++i)
    std::cout << "---+";
  std::cout << std::endl;
  for(int j(0); j < n; ++j)
    std::cout << " | " << (j+1);
  std::cout << " |" << std::endl;

  // Teilaufgabe c)
  // Spiel-Schleife
  for(int turn(0); turn < n*m; ++turn)
  {
    // Spieler-Nummer
    const int player = (turn % 2) + 1;

    // Spieler-Eingabe
    int x(0);
    while(true)
    {
      std::cout << std::endl;
      std::cout << "Spieler " << player << ": ";

      // Spalte waehlen:
      std::cin >> x;
      if(!std::cin.good())
      {
        std::cin.clear();
        std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "FEHLER : Ungueltige Eingabe" << std::endl;
        continue;
      }

      // Gueltige Spalte?
      if((x < 0) || (x > n))
      {
        std::cout << "FEHLER: Ungueltige Spalte" << std::endl;
        continue;
      }

      // Aufgabe?
      if(x == 0)
      {
        std::cout << "Spieler " << player << " hat aufgegeben!" << std::endl;
        std::cout << "Spieler " << ((player%2)+1) << " gewinnt!" << std::endl;
        return 0;
      }

      // Ist die Spalte noch frei?
      if(field[0][x-1] != 0)
      {
        std::cout << "FEHLER: Spalte " << x << " ist bereits voll" << std::endl;
        continue;
      }

      // okay
      std::cout << std::endl;
      break;
    }

    // Teilaufgabe d)

    // Null-Indizierung
    --x;

    // Muenze fallen lassen
    int y(m-1);
    for(; y > 0; --y)
    {
      if(field[y][x] == 0)
      {
        field[y][x] = player;
        break;
      }
    }

    // Spielfeld zeichnen
    for(int i(0); i < m; ++i)
    {
      for(int j(0); j < n; ++j)
      {
        std::cout << " | ";
        if(field[i][j] == 0)
          std::cout << ' ';
        else
          std::cout << field[i][j];
      }
      std::cout << " |" << std::endl;
    }
    std::cout << " +";
    for(int i(0); i < n; ++i)
      std::cout << "---+";
    std::cout << std::endl;
    for(int j(0); j < n; ++j)
      std::cout << " | " << (j+1);
    std::cout << " |" << std::endl;
    std::cout << std::endl;

    // Teilaufgabe e)

    // Teste vertikale Linien in aktueller Spalte
    for(int i(0); i+3 < m; ++i)
    {
      if(
        (field[i  ][x] == player) &&
        (field[i+1][x] == player) &&
        (field[i+2][x] == player) &&
        (field[i+3][x] == player))
      {
        std::cout << "Spieler " << player << " gewinnt!" << std::endl;
        return 0;
      }
    }

    // Teste horizontale Linien in aktueller Zeile
    for(int j(0); j+3 < n; ++j)
    {
      if(
        (field[y][j  ] == player) &&
        (field[y][j+1] == player) &&
        (field[y][j+2] == player) &&
        (field[y][j+3] == player))
      {
        std::cout << "Spieler " << player << " gewinnt!" << std::endl;
        return 0;
      }
    }

    // Teste alle diagonale Linien
    for(int i(0); i+3 < m; ++i)
    {
      for(int j(0); j+3 < n; ++j)
      {
        if((
          // diagonale 1
          (field[i  ][j  ] == player) &&
          (field[i+1][j+1] == player) &&
          (field[i+2][j+2] == player) &&
          (field[i+3][j+3] == player)
          ) || (
          // diagonale 2
          (field[i+3][j  ] == player) &&
          (field[i+2][j+1] == player) &&
          (field[i+1][j+2] == player) &&
          (field[i  ][j+3] == player)
          ))
        {
          std::cout << "Spieler " << player << " gewinnt!" << std::endl;
          return 0;
        }
      }
    }

    // Naechster Spielzug
  }

  // Unentschieden
  std::cout << "Das Spielfeld ist voll -- unentschieden!" << std::endl;
  return 0;
}