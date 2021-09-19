#include "render_window.hpp"

namespace Proku
{
  // helper function
  long long get_time()
  {
    timeval tv;
    gettimeofday(&tv, nullptr);
    return 1000000ll * (long long)tv.tv_sec + (long long)tv.tv_usec;
  }

  // helper function
  bool calc_timeout(timeval& tv_to, long long next)
  {
    long long to = next - get_time();
    if(to <= 0ll)
    {
      tv_to.tv_sec = tv_to.tv_usec = 0;
      return false;
    }
    else
    {
      tv_to.tv_sec  = to / 1000000;
      tv_to.tv_usec = to % 1000000;
      return true;
    }
  }

  RenderWindow::RenderWindow(const std::string& _title, int _width, int _height) :
    display(nullptr),
    window(0),
    pixmap(0),
    gcontext(nullptr),
    wnd_width(0),
    wnd_height(0),
    wnd_depth(0),
    last_time(0ll)
  {
    FD_ZERO(&x11_fds);

    // open display
    display = XOpenDisplay(nullptr);
    if(display == nullptr)
      throw std::runtime_error("Failed to open display!");

    // get connection number
    x11_fd = ConnectionNumber(display);
    if(x11_fd == 0)
      throw std::runtime_error("Failed to query display connection number!");

    // set file-descriptor
    FD_SET(x11_fd, &x11_fds);

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
    //XSelectInput(display, window, KeyPressMask);
    XSelectInput(display, window, StructureNotifyMask);

    // create pixmap for double-buffering
    pixmap = XCreatePixmap(display, window, wnd_width, wnd_height, wnd_depth);
    if(pixmap == Pixmap(0))
      throw std::runtime_error("Failed to create pixmap!");

    // create GC
    gcontext = XCreateGC(display, window, 0, 0);
    if(gcontext == nullptr)
      throw std::runtime_error("Failed to create graphics context!");

    // set colors
    XSetBackground(display, gcontext, BlackPixel(display, DefaultScreen(display)));
    XSetForeground(display, gcontext, WhitePixel(display, DefaultScreen(display)));

    // set window title
    if(!_title.empty())
      XStoreName(display, window, _title.c_str());

    // map window and flush
    XMapWindow(display, window);
    XFlush(display);
  }

  RenderWindow::~RenderWindow()
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

  Keymap RenderWindow::query_keymap()
  {
    Keymap keymap;
    XQueryKeymap(display, keymap.keymap);
    return keymap;
  }

  bool RenderWindow::process_events(int _timeout)
  {
    // compute time value of next timeout
    long long next_time = last_time + 1000ll * (long long)_timeout;
    timeval tv_next;
    XEvent ev;

    while(true)
    {
      // process all pending events
      while((XPending(display) > 0) && ((_timeout <= 0) || (get_time() < next_time)))
      {
        // wait for next event
        XNextEvent(display, &ev);

        // close window?
        if((ev.type == ClientMessage) && (ev.xclient.data.l[0] == wm_delete_window))
          return false;

        // pressed ESC?
        //if((ev.type == KeyPress) && (ev.xkey.keycode == 9))
          //return false;

        // configure?
        if(ev.type == ConfigureNotify)
          on_configure(ev.xconfigure);
      }

      if(_timeout > 0)
      {
        if(!calc_timeout(tv_next, next_time) || select(x11_fd+1, &x11_fds, nullptr, nullptr, &tv_next) <= 0)
        {
          // timeout occured
          last_time = get_time();
          return true;
        }
      }

      // next iteration
    }

    // we should not arrive here
    return false;
  }

  void RenderWindow::clear()
  {
    XWindowAttributes attr;
    XGetWindowAttributes(display, window, &attr);
    XSetForeground(display, gcontext, BlackPixel(display, DefaultScreen(display)));
    XFillRectangle(display, pixmap, gcontext, 0, 0, attr.width, attr.height);
    XSetForeground(display, gcontext, WhitePixel(display, DefaultScreen(display)));
  }

  void RenderWindow::update()
  {
    XWindowAttributes attr;
    XGetWindowAttributes(display, window, &attr);
    XCopyArea(display, pixmap, window, gcontext, 0, 0, attr.width, attr.height, 0, 0);
    XFlush(display);
    //XSync(display, False); // not necessary???
  }

  void RenderWindow::draw_string(int x, int y, const std::string& text)
  {
    XDrawString(display, pixmap, gcontext, x, y, text.data(), text.size());
  }

  void RenderWindow::draw_string_center_x(int y, const std::string& text)
  {
    // card-coded for default X11 font size
    draw_string(width()/2-3*text.length()+1, y, text);
  }

  void RenderWindow::draw_point(int x, int y)
  {
    XDrawPoint(display, pixmap, gcontext, x, y);
  }

  void RenderWindow::draw_line(int x1, int y1, int x2, int y2)
  {
    XDrawLine(display, pixmap, gcontext, x1, y1, x2, y2);
  }

  void RenderWindow::draw_rect(int x, int y, int w, int h)
  {
    XDrawRectangle(display, pixmap, gcontext, x, y, w, h);
  }

  void RenderWindow::fill_rect(int x, int y, int w, int h)
  {
    XFillRectangle(display, pixmap, gcontext, x, y, w, h);
  }

  void RenderWindow::draw_circle(int x, int y, int rad)
  {
    XDrawArc(display, pixmap, gcontext, x-rad, y-rad, 2*rad, 2*rad, 0, 360*64);
  }

  void RenderWindow::fill_circle(int x, int y, int rad)
  {
    XFillArc(display, pixmap, gcontext, x-rad, y-rad, 2*rad, 2*rad, 0, 360*64);
  }

  void RenderWindow::on_configure(XConfigureEvent& ev)
  {
    // window size changed?
    if((ev.width != wnd_width) || (ev.height != wnd_height))
    {
      wnd_width = ev.width;
      wnd_height = ev.height;

      // We have to create a new pixmap for the new window dimensions
      if(pixmap != Pixmap(0))
        XFreePixmap(display, pixmap);
      pixmap = XCreatePixmap(display, window, wnd_width, wnd_height, wnd_depth);
      if(pixmap == Pixmap(0))
        throw std::runtime_error("Failed to create pixmap!");
    }
  }
}
