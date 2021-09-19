#ifndef PROKU_GAME_TIMER_HPP
#define PROKU_GAME_TIMER_HPP

// Eine Klasse, die einen einfachen Timer repraesentiert
class Timer
{
private:
  long long last_time;

public:
  explicit Timer();

  // Sychronisiert den Timer
  //
  // Diese Funktion stellt sicher, dass seit ihrem letzten
  // Aufruf mindestens '_millis' Millisekunden vergangen sind.
  //
  // \param[in] _millis
  // Die Zeit, welche seit dem letzten Aufruf vergangen sein muss,
  void sync(long long _millis);

private:
  static long long tick();
  static void wait(long long _micros);
}; // class Timer

#endif // PROKU_GAME_TIMER_HPP
