#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <math.h>

// Teilaufgabe b)
double norm(const unsigned int n, const double v[])
{
  assert(n > 2);
  assert(v != nullptr);

  double r = 0.0;
  for(unsigned int i(0); i < n; ++i)
  {
    r += v[i]*v[i];
  }

  return std::sqrt(r);
}

// Teilaufgabe c)
void axpy(const unsigned int n, double y[], const double alpha, const double x[])
{
  assert(n > 2);
  assert(x != nullptr);
  assert(y != nullptr);
  for(unsigned int i(0); i < n; ++i)
  {
    y[i] += alpha * x[i];
  }
}

int main()
{
  // Teilaufgabe a)
  // System-Groesse n
  constexpr unsigned int n = 31;

  // pi = 3.14159...
  constexpr double pi = M_PI;
  std::cout << "pi = " << pi << std::endl;

  // lambda = 2 * (1 - cos(pi/(n+1)))
  const double lambda = 2.0 * (1.0 - std::cos(M_PI/double(n+1)));
  std::cout << "lambda = " << lambda << std::endl;

  // Vektoren x, u, b, d
  double x[n], u[n], b[n], d[n];

  // initialisiere Vektoren x,y und b
  for(unsigned int i(0); i < n; ++i)
  {
    x[i] = b[i] = 0.0;
    u[i] = std::sin(pi * double(i+1) / double(n+1));
  }

  // Teilaufgabe b)
  // Setze Formatierung der Ausgaben:
  std::cout << std::scientific;
  std::cout << std::setprecision(12);

  // berechne norm von u
  double norm_u = norm(n, u);
  std::cout << "norm(u) = " << norm_u << std::endl;

  // Teilaufgabe c)
  // aktualisiere b
  axpy(n, b, lambda, u);

  // berechne Norm von b
  double norm_b = norm(n, b);
  std::cout << "norm(b) = " << norm_b << std::endl;

  // Teilaufgabe d)
  // Richardson-Iteration:
  for(unsigned int k(0); k < 10000; ++k)
  {
    // berechne Defekt-Vektor:
    d[0] = b[0] - 2.0*x[0]  + x[1];
    for(unsigned int i(1); i < n-1; ++i)
      d[i] = b[i] - 2.0*x[i] + x[i-1] + x[i+1];
    d[n-1] = b[n-1] - 2.0*x[n-1] + x[n-2];

    // berechne Defekt-Norm:
    double norm_d = norm(n, d);

    // Konvergenz?
    bool converged = (norm_d < norm_b * 1E-5);

    // drucke Defekt-Norm:
    if(converged || ((k % 100) == 0))
    {
      std::cout << std::setw(5) << k << ": ";
      std::cout << norm_d;
      std::cout << " | " << (norm_d / norm_b);
      std::cout << std::endl;
    }

    // Teste Defekt
    if(converged)
    {
      std::cout << "Fertig!" << std::endl;
      break;
    }

    // aktualisiere x
    axpy(n, x, 0.5, d);
  }

  // Teilaufgabe e)
  // Fehler (x-u) berechnen:
  axpy(n, x, -1.0, u);
  double err_norm = norm(n, x);

  // Fehler ausgeben:
  std::cout << "Fehler: " << err_norm << std::endl;

  // Okay
  return 0;
}