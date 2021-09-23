#pragma once
#ifndef PROKU_CANVAS_SVG_WRITER_HPP
#define PROKU_CANVAS_SVG_WRITER_HPP

#include <string>
#include <fstream>

#include "canvas.hpp"

namespace Proku
{
  class SVGWriter : public Canvas
  {
  private:
    std::ofstream outfile;
    const int my_width;
    const int my_height;
    std::string my_color;

  public:
    explicit SVGWriter(const std::string& filename, int width, int height);
    virtual ~SVGWriter();

    /// \see Canvas::get_width()
    virtual int get_width() const override;
    /// \see Canvas::get_height()
    virtual int get_height() const override;
    /// \see Canvas::paint_begin()
    virtual void paint_begin() override;
    /// \see Canvas::paint_finish()
    virtual void paint_finish() override;
    /// \see Canvas::select_color()
    virtual void select_color(double red, double green, double blue) override;
    /// \see Canvas::draw_string()
    virtual void draw_string(int x, int y, const std::string& text) override;
    /// \see Canvas::draw_line()
    virtual void draw_line(int x1, int y1, int x2, int y2) override;
    /// \see Canvas::draw_rect()
    virtual void draw_rect(int x, int y, int width, int height) override;
    /// \see Canvas::fill_rect()
    virtual void fill_rect(int x, int y, int width, int height) override;
    /// \see Canvas::draw_circle()
    virtual void draw_circle(int x, int y, int radius) override;
    /// \see Canvas::fill_circle()
    virtual void fill_circle(int x, int y, int radius) override;
  }; // class SVGWriter
} // namespace Proku

#endif // PROKU_CANVAS_SVG_WRITER_HPP
