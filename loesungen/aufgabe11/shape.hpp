#pragma once
#ifndef PROKU_SHAPE_HPP
#define PROKU_SHAPE_HPP

#include "canvas.hpp"

namespace Proku
{
  /**
   * \brief Schnittstelle fuer ein geometrisches Objekt
   */
  class Shape
  {
  public:
    /// virtueller Destruktor
    virtual ~Shape()
    {
    }

    /**
     * \brief Zeichnet das geometrische Objekt auf eine Leinwand
     *
     * \param[in,out] canvas
     * Eine Referenz auf ein Leinwand-Objekt, auf welches gezeichnet werden soll
     */
    virtual void draw(Proku::Canvas& canvas) const = 0;

    /**
     * \brief Testet, ob ein Punkt innerhalb des geometrischen Objektes liegt
     *
     * \param[in] x,y
     * Die Koordinaten des Punktes, welcher getestet werden soll
     *
     * \returns
     * \c true, falls der getestete Punkt im Inneren des Objektes liegt, sonst \c false.
     */
    virtual bool hit_test(int x, int y) const = 0;

    /**
     * \brief Verschiebt das geometrische Objekt um eine vorgegebene Distanz.
     *
     * \param[in] dx,dy
     * Die Distanz in X- und Y-Richtung, in welche das geometrische Objekt verschoben werden soll
     */
    virtual void move_by(int dx, int dy) = 0;
  }; // class Shape
} // namespace Proku

#endif // PROKU_SHAPE_HPP
