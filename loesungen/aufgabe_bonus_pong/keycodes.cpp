#include <X11/Xlib.h>

#include <iostream>
#include <cassert>
#include <string>

int main()
{
  // open display
  Display* display = XOpenDisplay(nullptr);
  assert(display != nullptr);

  // try to create a window
  Window window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 320, 240, 0, 0, 0);
  assert(window != Window(0));

  // set delete message protocol
  Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
  assert(wm_delete_window != Atom(0));
  XSetWMProtocols(display, window, &wm_delete_window, 1);

  // create GC
  GC gcontext = XCreateGC(display, window, 0, 0);
  assert(gcontext != nullptr);

  // set colors
  XSetBackground(display, gcontext, BlackPixel(display, DefaultScreen(display)));
  XSetForeground(display, gcontext, WhitePixel(display, DefaultScreen(display)));

  // select event mask
  XSelectInput(display, window, KeyPressMask);

  // set window title
  XStoreName(display, window, "Bitte Taste Druecken");

  // map window
  XMapWindow(display, window);

  // main loop
  XEvent ev;
  while(true)
  {
    XNextEvent(display, &ev);

    // window closed?
    if((ev.type == ClientMessage) && (ev.xclient.data.l[0] == wm_delete_window))
      break;

    // key pressed?
    if(ev.type == KeyPress)
    {
      std::string s = std::string("Keycode = ") + std::to_string(ev.xkey.keycode);

      // write to console
      std::cout << s << std::endl;

      // write to window
      XClearWindow(display, window);
      XDrawString(display, window, gcontext, 10, 20, s.data(), s.size());
      XFlush(display);
    }
  } // main loop

  // cleanup
  XFreeGC(display, gcontext);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}