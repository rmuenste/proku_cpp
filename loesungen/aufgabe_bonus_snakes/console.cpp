#include <algorithm>
#include <deque>
#include <iostream>
#include <cstdlib> // fuer abort

#include "console.hpp"

void curses_clear() {clear();}
void curses_refresh() {refresh();}

void swap(int& x, int& y)
{
  int t(x);
  x = y;
  y = t;
}

int split_lines(std::deque<std::string>& _ds, const std::string& _msg)
{
  std::string s;
  int maxl(0);
  for(const char* p = _msg.c_str(); *p != 0; ++p)
  {
    if(*p == '\n')
    {
      maxl = std::max(maxl, int(s.length()));
      _ds.push_back(s);
      s.clear();
    }
    else
    {
      s.push_back(*p);
    }
  }
  // Letzte Zeile nicht vergessen:
  if(!s.empty())
  {
    maxl = std::max(maxl, int(s.length()));
    _ds.push_back(s);
  }
  return maxl;
}

// Haben wir schon eine Console?
static bool have_console = false;

Console::Console()
{
  // No Nonsense...
  if(have_console)
  {
    std::cerr << "FEHLER: Sie koennen nicht mehr als eine Console erstellen!" << std::endl;
    abort();
  }

  // initialise curses mode
  initscr();

  // enable colors
  start_color();

  // disable echoing of characters
  noecho();

  // fetch characters
  cbreak();

  // enable keypad
  keypad(stdscr, TRUE);

  // disable cursor visibility
  curs_set(0);

  // initialise colors
  init_pair( 1, COLOR_WHITE,   COLOR_BLACK);
  init_pair( 2, COLOR_RED,     COLOR_BLACK);
  init_pair( 3, COLOR_GREEN,   COLOR_BLACK);
  init_pair( 4, COLOR_BLUE,    COLOR_BLACK);
  init_pair( 5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair( 6, COLOR_YELLOW,  COLOR_BLACK);
  init_pair( 7, COLOR_CYAN,    COLOR_BLACK);
  init_pair(11, COLOR_BLACK,   COLOR_WHITE);
  init_pair(12, COLOR_RED,     COLOR_WHITE);
  init_pair(13, COLOR_GREEN,   COLOR_WHITE);
  init_pair(14, COLOR_BLUE,    COLOR_WHITE);
  init_pair(15, COLOR_MAGENTA, COLOR_WHITE);
  init_pair(16, COLOR_YELLOW,  COLOR_WHITE);
  init_pair(17, COLOR_CYAN,    COLOR_WHITE);

  // okay
  have_console = true;
}

Console::~Console()
{
  endwin();
  have_console = false;
}

void Console::set_wait_mode(bool _block)
{
  if(_block)
    timeout(-1);
  else
    timeout(0);
}

int Console::get_key()
{
  int key = getch();
  return (key != ERR ? key : 0);
}

int Console::get_max_x() const
{
  return getmaxx(stdscr);
}

int Console::get_max_y() const
{
  return getmaxy(stdscr);
}

void Console::set_color(Color _color)
{
  color_set((short)_color, 0);
}

void Console::clear()
{
  curses_clear();
}

void Console::refresh()
{
  curses_refresh();
}

void Console::set_char(const Point& _p, int _char)
{
  set_char(_p.x, _p.y, _char);
}

void Console::set_char(int _x, int _y, int _char)
{
  mvaddch(_y, _x, _char);
}

void Console::draw_rect(int _x0, int _y0, int _x1, int _y1)
{
  if(_x1 < _x0) swap(_x0, _x1);
  if(_y1 < _y0) swap(_y0, _y1);

  // Zeichne Rahmen-Ecken
  set_char(_x0, _y0, ACS_ULCORNER); // oben-links
  set_char(_x1, _y0, ACS_URCORNER); // oben-rechts
  set_char(_x0, _y1, ACS_LLCORNER); // unten-links
  set_char(_x1, _y1, ACS_LRCORNER); // unten-rechts

  // Zeichne Horizontale Rahmen-Linien
  for(int x(_x0+1); x < _x1; ++x)
  {
    set_char(x, _y0, ACS_HLINE); // oben
    set_char(x, _y1, ACS_HLINE); // unten
  }

  // Zeichne Vertikale Rahmen-Linien
  for(int y(_y0+1); y < _y1; ++y)
  {
    set_char(_x0, y, ACS_VLINE); // links
    set_char(_x1, y, ACS_VLINE); // rechts
  }
}

void Console::draw_string(const Point& _p, const std::string& _str)
{
  draw_string(_p.x, _p.y, _str.c_str());
}

void Console::draw_string(int _x, int _y, const std::string& _str)
{
  if(!_str.empty())
     mvprintw(_y, _x, "%s", _str.c_str());
}

void Console::draw_int(const Point& _p, int _v)
{
  draw_int(_p.x, _p.y, _v);
}

void Console::draw_int(int _x, int _y, int _v)
{
  mvprintw(_y, _x, "%i", _v);
}

void Console::show_dialog(const std::string& _msg, bool _center_text, int _wait_key)
{
  // Zerlege Nachricht in einzelne Zeilen:
  std::deque<std::string> str;
  int maxl = std::max(split_lines(str, _msg), 15);

  // Anzahl Zeilen:
  int nrow = int(str.size());

  // Dimensionen der Box:
  int nc = maxl+3;
  int nr = nrow+1;

  // Zentrierte Box-Offsets:
  int x0 = (get_max_x() - nc) / 2;
  int y0 = (get_max_y() - nr) / 2;

  // Zeichne Rahmen
  draw_rect(x0, y0, x0+nc, y0+nr);

  // Zeichne Text-Zeilen
  for(int i(0); i < nrow; ++i)
  {
    // Berechne x-offset
    int xo = (_center_text ? (maxl - int(str[i].length())) / 2 : 0);

    // Zeichne Text
    draw_string(x0+xo+2, y0+i+1, str[i].c_str());
  }

  // Warte auf Eingabe
  set_wait_mode(true);
  while(get_key() != _wait_key) { }
}

bool Console::show_yes_no_dialog(const std::string& _msg, bool _center_text)
{
  // Zerlege Nachricht in einzelne Zeilen:
  std::deque<std::string> str;
  int maxl = std::max(split_lines(str, _msg), 15);

  // Anzahl Zeilen:
  int nrow = int(str.size());

  // Dimensionen der Box:
  int nc = maxl+3;
  int nr = nrow+3;

  // Zentrierte Box-Offsets:
  int x0 = (get_max_x() - nc) / 2;
  int y0 = (get_max_y() - nr) / 2;

  // Zeichne Rahmen
  draw_rect(x0, y0, x0+nc, y0+nr);

  // Zeichne Text-Zeilen
  for(int i(0); i < nrow; ++i)
  {
    // Berechne x-offset
    int xo = (_center_text ? (maxl - int(str[i].length())) / 2 : 0);

    // Zeichne Text
    draw_string(x0+xo+2, y0+i+1, str[i].c_str());
  }

  // Zeichne "[J]a" und "[N]ein":
  draw_string(x0+4, y0+nrow+2, "[J]a");
  draw_string(x0+nc-9, y0+nrow+2, "[N]ein");

  // Warte auf Eingabe
  set_wait_mode(true);
  while(true)
  {
    switch(get_key())
    {
    case 'J':
    case 'j':
      return true;

    case 'N':
    case 'n':
      return false;
    }
  }
}
