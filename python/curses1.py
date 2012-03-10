#!/usr/bin/env python
# Ref: http://www.amk.ca/python/howto/curses/
import curses,time
stdscr = curses.initscr()
curses.start_color()
curses.init_pair(1, curses.COLOR_RED, curses.COLOR_WHITE)
curses.noecho()

stdscr.keypad(1)
x=20;y=7
h=5;w=40
win=curses.newwin(h,w,y,x)
stdscr.addstr(0,0,"Current mode: Typing mode", curses.A_REVERSE)
pad = curses.newpad(100, 100)
#  These loops fill the pad with letters; this is
# explained in the next section
for y in range(0, 100):
    for x in range(0, 100):
        try: pad.addch(y,x, ord('a') + (x*x+y*y) % 26 )
        except curses.error: pass

#  Displays a section of the pad in the middle of the screen

stdscr.addstr(0, 0, "Current mode: Typing mode",
                    curses.A_REVERSE)
stdscr.refresh()
pad.refresh( 0,0, 5,5, 20,75)
time.sleep(3)
stdscr.addstr(0,0, "RED ALERT!", curses.color_pair(1) )
time.sleep(3)

curses.init_pair(1, curses.COLOR_RED, curses.COLOR_WHITE)
stdscr.addstr(0, 0, "                   ****        ",
                    curses.A_REVERSE)
pad.refresh( 0,0, 5,5, 20,75)
stdscr.refresh()
time.sleep(3)
curses.endwin()
