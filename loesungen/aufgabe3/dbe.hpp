#ifndef PROKU_DBE_HPP
#define PROKU_DBE_HPP 1

///
/// \brief Fuehrt die Dezimalbruchentwicklung durch
///
/// \param[in] d
/// Die nicht-periodischen Dezimalstellen als Ganzzahl
///
/// \param[in] m
/// Die Anzahl der nicht-periodischen Nachkomma-Dezimalstellen
///
/// \param[in] p
/// Die periodischen Dezimalstellen als Ganzzahl
///
/// \param[in] n
/// Die Anzahl der periodischen Dezimalstellen (einschl. fuehrender Nullen)
///
void dbe(int d, int m, int p, int n);

#endif // PROKU_DBE_HPP
