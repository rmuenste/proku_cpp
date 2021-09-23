#include "canvas_window.hpp"

#include <cassert>
#include <stdexcept>

namespace Proku
{
  CanvasWindow::CanvasWindow(const std::string& _title, int _width, int _height) :
    display(nullptr),
    window(0),
    pixmap(0),
    gcontext(nullptr),
    wnd_width(0),
    wnd_height(0),
    wnd_depth(0),
    redraw_flag(false)
  {
    // open display
    display = XOpenDisplay(nullptr);
    if(display == nullptr)
      throw std::runtime_error("Failed to open display!");

    // get delete message:
    wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
    if(wm_delete_window == (Atom)0)
      throw std::runtime_error("Failed to query delete message atom!");

    // try to create a window
    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, _width, _height, 0, 0, 0);
    if(window == Window(0))
      throw std::runtime_error("Failed to create simple X window!");

    // get actual window attributes
    XWindowAttributes attr;
    memset(&attr, 0, sizeof(XWindowAttributes));
    XGetWindowAttributes(display, window, &attr);

    // store initial window dimensions
    wnd_width  = attr.width;
    wnd_height = attr.height;
    wnd_depth  = attr.depth;

    // install delete message handler
    XSetWMProtocols(display, window, &wm_delete_window, 1);

    // set event mask
    XSelectInput(display, window,
      StructureNotifyMask
      | ExposureMask
      | KeyPressMask
      | KeyReleaseMask
      | ButtonPressMask
      | ButtonReleaseMask
      | PointerMotionMask
    );

    // create pixmap for double-buffering
    pixmap = XCreatePixmap(display, window, wnd_width, wnd_height, wnd_depth);
    if(pixmap == Pixmap(0))
      throw std::runtime_error("Failed to create pixmap!");

    // create GC
    gcontext = XCreateGC(display, window, 0, 0);
    if(gcontext == nullptr)
      throw std::runtime_error("Failed to create graphics context!");

    // set colors
    XSetForeground(display, gcontext, BlackPixel(display, DefaultScreen(display)));
    XSetBackground(display, gcontext, WhitePixel(display, DefaultScreen(display)));

    // set window title
    if(!_title.empty())
      XStoreName(display, window, _title.c_str());

    // map window
    XMapWindow(display, window);

    // get screen dimensions
    int disp_width = XDisplayWidth(display, 0);
    int disp_height = XDisplayHeight(display, 0);

    // move window to screen center (ignoring decorations)
    XMoveWindow(display, window, (disp_width-wnd_width)/2, (disp_height-wnd_height)/2);

    // flush display
    XFlush(display);
  }

  CanvasWindow::~CanvasWindow()
  {
    if(gcontext != nullptr)
      XFreeGC(display, gcontext);
    if(pixmap != Pixmap(0))
      XFreePixmap(display, pixmap);
    if(window != Window(0))
      XDestroyWindow(display, window);
    if(display != nullptr)
      XCloseDisplay(display);
  }

  void CanvasWindow::redraw()
  {
    redraw_flag = true;
  }

  int CanvasWindow::get_width() const
  {
    return wnd_width;
  }

  int CanvasWindow::get_height() const
  {
    return wnd_height;
  }

  void CanvasWindow::paint_begin()
  {
    XSetForeground(display, gcontext, WhitePixel(display, DefaultScreen(display)));
    XFillRectangle(display, pixmap, gcontext, 0, 0, wnd_width, wnd_height);
    XSetForeground(display, gcontext, BlackPixel(display, DefaultScreen(display)));
  }

  void CanvasWindow::paint_finish()
  {
    XCopyArea(display, pixmap, window, gcontext, 0, 0, wnd_width, wnd_height, 0, 0);
    XFlush(display);
  }

  void CanvasWindow::select_color(double red, double green, double blue)
  {
    XColor xcolour;
    xcolour.red   = (red   <= 0.0 ? 0 : (red   >= 1.0 ? 65535 : int(red  *65535.0)));
    xcolour.green = (green <= 0.0 ? 0 : (green >= 1.0 ? 65535 : int(green*65535.0)));
    xcolour.blue  = (blue  <= 0.0 ? 0 : (blue  >= 1.0 ? 65535 : int(blue *65535.0)));
    xcolour.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(display, DefaultColormap(display,0), &xcolour);
    XSetForeground(display, gcontext, xcolour.pixel);
  }

  void CanvasWindow::draw_string(int x, int y,const std::string& text)
  {
    XDrawString(display, pixmap, gcontext, x, y, text.data(), text.size());
  }

  void CanvasWindow::draw_line(int x1, int y1, int x2, int y2)
  {
    XDrawLine(display, pixmap, gcontext, x1, y1, x2, y2);
  }

  void CanvasWindow::draw_rect(int x, int y, int w, int h)
  {
    XDrawRectangle(display, pixmap, gcontext, x, y, w, h);
  }

  void CanvasWindow::fill_rect(int x, int y, int w, int h)
  {
    XFillRectangle(display, pixmap, gcontext, x, y, w, h);
  }

  void CanvasWindow::draw_circle(int x, int y, int rad)
  {
    XDrawArc(display, pixmap, gcontext, x-rad, y-rad, 2*rad, 2*rad, 0, 360*64);
  }

  void CanvasWindow::fill_circle(int x, int y, int rad)
  {
    XFillArc(display, pixmap, gcontext, x-rad, y-rad, 2*rad, 2*rad, 0, 360*64);
  }

  void CanvasWindow::main_loop()
  {
    XEvent ev;

    while(true)
    {
      // process all pending events
      while(!redraw_flag || (XPending(display) > 0))
      {
        // wait for next event
        XNextEvent(display, &ev);

        // close window?
        if((ev.type == ClientMessage) && (ev.xclient.data.l[0] == wm_delete_window))
          return;

        // pressed ESC?
        if((ev.type == KeyPress) && (ev.xkey.keycode == 9))
          return;

        // process event
        switch(ev.type)
        {
        case Expose:
          on_paint();
          break;

        case ConfigureNotify:
          if((ev.xconfigure.width != wnd_width) || (ev.xconfigure.height != wnd_height))
          {
            // call resize handler
            on_resize(ev.xconfigure.width, ev.xconfigure.height);

            // recreate Pixmap if necessary
            if(pixmap != Pixmap(0))
            {
              XFreePixmap(display, pixmap);
              pixmap = XCreatePixmap(display, window, ev.xconfigure.width, ev.xconfigure.height, wnd_depth);
            }

            // update window size
            wnd_width = ev.xconfigure.width;
            wnd_height = ev.xconfigure.height;

            // redraw
            redraw_flag = true;
          }
          break;

        case KeyPress:
          on_key_press(ev.xkey.keycode);
          break;

        //case KeyRelease:
          //on_key_release(ev.xkey.keycode);
          //break;

        case ButtonPress:
          on_mouse_button(ev.xbutton.x, ev.xbutton.y, ev.xbutton.button, true);
          break;

        case ButtonRelease:
          on_mouse_button(ev.xbutton.x, ev.xbutton.y, ev.xbutton.button, false);
          break;

        case MotionNotify:
          on_mouse_motion(ev.xmotion.x, ev.xmotion.y);
          break;
        }
      }

      // redraw?
      if(redraw_flag)
      {
        // send Expose event to X window server to enforce redraw
        XEvent evex;
        memset(&evex, 0, sizeof(XEvent));
        evex.type = Expose;
        evex.xexpose.window = window;
        XSendEvent(display, window, False, ExposureMask, &evex);
        XFlush(display);
        redraw_flag = false;
      }
    }
  }
} // namespace Proku
