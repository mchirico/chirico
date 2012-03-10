#!/usr/bin/env python

import curses

scr=curses.initscr()
scr.border(0)
scr.addstr(12,25,"Enter q for quit")
scr.addstr(13,25,"")
#scr.hline(13, 25, curses.ACS_HLINE, 10)
scr.refresh()
k='x'
while k != ord('q'):
    curses.noecho()
    k=scr.getch()
    scr.refresh()


curses.endwin()

