#include "svg_writer.hpp"

namespace Proku
{
  SVGWriter::SVGWriter(const std::string& filename, int width, int height) :
    outfile(filename, std::ios_base::out),
    my_width(width), my_height(height),
    my_color("black")
  {
  }

  SVGWriter::~SVGWriter()
  {
  }

  int SVGWriter::get_width() const
  {
    return my_width;
  }

  int SVGWriter::get_height() const
  {
    return my_height;
  }

  void SVGWriter::paint_begin()
  {
    outfile << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;
  }

  void SVGWriter::paint_finish()
  {
    outfile << "</svg>" << std::endl;
    outfile.close();
  }

  void SVGWriter::select_color(double red, double green, double blue)
  {
    my_color = "rgb(" +
      std::to_string(red   <= 0.0 ? 0 : (red   >= 1.0 ? 255 : int(red  *255.0))) + "," +
      std::to_string(green <= 0.0 ? 0 : (green >= 1.0 ? 255 : int(green*255.0))) + "," +
      std::to_string(blue  <= 0.0 ? 0 : (blue  >= 1.0 ? 255 : int(blue *255.0))) + ")";
  }

  void SVGWriter::draw_string(int x, int y, const std::string& text)
  {
    outfile << "<text";
    outfile << " fill=\"" << my_color << "\"";
    outfile << " x=\"" << x << "\"";
    outfile << " y=\"" << y << "\"";
    outfile << ">";
    outfile << text << "</text>" << std::endl;;
  }

  void SVGWriter::draw_line(int x1, int y1, int x2, int y2)
  {
    outfile << "<line";
    outfile << " stroke=\"" << my_color << "\"";
    outfile << " stroke-width=\"" << (1) << "\"";
    outfile << " x1=\"" << x1 << "\"";
    outfile << " x2=\"" << x2 << "\"";
    outfile << " y1=\"" << y1 << "\"";
    outfile << " y2=\"" << y2 << "\"";
    outfile << " />" << std::endl;
  }

  void SVGWriter::draw_rect(int x, int y, int width, int height)
  {
    outfile << "<rect";
    outfile << " x=\"" << x << "\"";
    outfile << " y=\"" << y << "\"";
    outfile << " width=\"" << width << "\"";
    outfile << " height=\"" << height << "\"";
    outfile << " style=\"fill:none;stroke:" << my_color << "\"";
    outfile << " />" << std::endl;
  }

  void SVGWriter::fill_rect(int x, int y, int width, int height)
  {
    outfile << "<rect";
    outfile << " x=\"" << x << "\"";
    outfile << " y=\"" << y << "\"";
    outfile << " width=\"" << width << "\"";
    outfile << " height=\"" << height << "\"";
    outfile << " style=\"fill:" << my_color << ";stroke:none\"";
    outfile << " />" << std::endl;
  }

  void SVGWriter::draw_circle(int x, int y, int radius)
  {
    outfile << "<circle";
    outfile << " cx=\"" << x << "\"";
    outfile << " cy=\"" << y << "\"";
    outfile << " r=\"" << radius << "\"";
    outfile << " style=\"fill:none;stroke:" << my_color << "\"";
    outfile << " />" << std::endl;
  }

  void SVGWriter::fill_circle(int x, int y, int radius)
  {
    outfile << "<circle";
    outfile << " cx=\"" << x << "\"";
    outfile << " cy=\"" << y << "\"";
    outfile << " r=\"" << radius << "\"";
    outfile << " style=\"fill:" << my_color << ";stroke:none\"";
    outfile << " />" << std::endl;
  }
} // namespace Proku
