#!/usr/bin/env python

import curses

def main(stdscr):
    stdscr.clear()
    curses.start_color()
    curses.use_default_colors()
    curses.init_pair(2,curses.COLOR_WHITE,-1) #set white to term default

    curses.init_pair(1,curses.COLOR_BLACK, curses.COLOR_CYAN)
    curses.init_pair(2,curses.COLOR_BLACK, curses.COLOR_WHITE)
   
    #paint 20 rows, 60 columns cyan
    i = 0
    while i < 20:
        j = 0
        while j < 60:
            stdscr.addstr(i,j," ",curses.color_pair(1))
            j += 1
        i += 1
    stdscr.refresh()
   
    #make 2nd window
    height = 5
    width = 40
    secondWindow = curses.newwin(height, width,5,5)

    #display color content
    x,y,z = curses.color_content(curses.COLOR_WHITE)
    secondWindow.addstr(0,3,"Color content of COLOR_WHITE:")
    secondWindow.addstr(1,3,str(x))
    secondWindow.addstr(2,3,str(y))
    secondWindow.addstr(3,3,str(z))
    secondWindow.addstr(4,3,"Not same as default white")
    secondWindow.refresh()
   
    stdscr.getch()

   
if __name__ == '__main__':
    print "init..."
    curses.wrapper(main)


