#include <cassert>  // assert
#include <cstdlib>  // strto***
#include <cerrno>   // errno, ERANGE
#include <cmath>    // HUGE_VAL
#include <climits>  // ***_MIN, ***_MAX

#include "parse.hpp"

bool parse(const char* str, long long int& value)
{
  assert(str != nullptr);
  // Siehe:
  // http://www.cplusplus.com/reference/cstdlib/strtoll/
  // http://stackoverflow.com/questions/14176123/correct-usage-of-strtol
  char* endptr(nullptr);
  errno = 0;
  value = std::strtoll(str, &endptr, 0);
  if((endptr == str) || (*endptr != '\0'))
    return false;
  if(((value == LLONG_MIN) || (value == LLONG_MAX)) && (errno == ERANGE))
    return false;
  return true;
}

bool parse(const char* str, long long int& value, long long int min_val, long long int max_val)
{
  if(!parse(str, value))
    return false;
  return (min_val <= value) && (value <= max_val);
}

bool parse(const char* str, unsigned long long int& value)
{
  assert(str != nullptr);
  char* endptr(nullptr);
  errno = 0;
  value = std::strtoull(str, &endptr, 0);
  if((endptr == str) || (*endptr != '\0'))
    return false;
  if((value == ULLONG_MAX) && (errno == ERANGE))
    return false;
  return true;
}

bool parse(const char* str, unsigned long long int& value, unsigned long long int min_val, unsigned long long int max_val)
{
  if(!parse(str, value))
    return false;
  return (min_val <= value) && (value <= max_val);
}

bool parse(const char* str, int& value)
{
  // Nutze die "long long int"-Variante und
  // pruefe gegen die Grenzen von "int"
  long long int llval = 0ll;
  if(!parse(str, llval, INT_MIN, INT_MAX))
    return false;
  // Okay. konvertiere von long long nach int
  value = static_cast<int>(llval);
  return true;
}

bool parse(const char* str, int& value, int min_val, int max_val)
{
  if(!parse(str, value))
    return false;
  return (min_val <= value) && (value <= max_val);
}

bool parse(const char* str, unsigned int& value)
{
  unsigned long long int llval = 0ull;
  if(!parse(str, llval, 0ull, UINT_MAX))
    return false;
  value = static_cast<unsigned int>(llval);
  return true;
}

bool parse(const char* str, unsigned int& value, unsigned int min_val, unsigned int max_val)
{
  if(!parse(str, value))
    return false;
  return (min_val <= value) && (value <= max_val);
}

bool parse(const char* str, float& value)
{
  assert(str != nullptr);
  // Siehe:
  // http://www.cplusplus.com/reference/cstdlib/strtof/
  char* endptr(nullptr);
  errno = 0;
  value = std::strtof(str, &endptr);
  if((endptr == str) || (*endptr != '\0'))
    return false;
  if(((value == -HUGE_VALF) || (value == +HUGE_VALF)) && (errno == ERANGE))
    return false;
  return true;
}

bool parse(const char* str, float& value, float min_val, float max_val)
{
  if(!parse(str, value))
    return false;
  return (min_val <= value) && (value <= max_val);
}

bool parse(const char* str, double& value)
{
  assert(str != nullptr);
  // Siehe:
  // http://www.cplusplus.com/reference/cstdlib/strtod/
  char* endptr(nullptr);
  errno = 0;
  value = std::strtod(str, &endptr);
  if((endptr == str) || (*endptr != '\0'))
    return false;
  if(((value == -HUGE_VAL) || (value == +HUGE_VAL)) && (errno == ERANGE))
    return false;
  return true;
}

bool parse(const char* str, double& value, double min_val, double max_val)
{
  if(!parse(str, value))
    return false;
  return (min_val <= value) && (value <= max_val);
}
