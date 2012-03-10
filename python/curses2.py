#!/usr/bin/env python
import curses, traceback

# startcurses: initialize curses environment
def startcurses():
    stdscr = curses.initscr()
    curses.start_color()
    stdscr.keypad(1)
    return stdscr

# killcurses: return the terminal emulator to it's usual mode
def killcurses(stdscr):
    stdscr.keypad(0)
    curses.endwin()
    return 0

# can_evaluate: returns: True if a string can be evaluated safeley, else False.
def can_evaluate(s):
    try:
        eval(s)
    except:
        return False

    return True        

# mainloop: the main loop for the interactive curses interface
def mainloop(stdscr):
    str_max = 4096

    curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_RED,   curses.COLOR_BLACK)
    curses.init_pair(3, curses.COLOR_GREEN, curses.COLOR_BLACK)

    while True:
        stdscr.addstr("Expression: ", curses.color_pair(1))
        stdscr.refresh()

        s = stdscr.getstr(str_max)

        if s == "":
            continue # Blank string; user probably just wants more space

        if can_evaluate(s) == False: # Make sure it's eval'able
            stdscr.addstr("Error: string can't be evaluated.\n")
            continue # No, get a new string

        stdscr.addstr(s + " evaluates to: ", curses.color_pair(2))
        
        stdscr.addstr(str(eval(s)) + "\n", curses.color_pair(3))

        stdscr.refresh()

# intmain: initialize curses, call mainloop()
def intmain():
    try:
        stdscr = startcurses()
        
        mainloop(stdscr)
    except: # Make sure to restore the terminal so it doesn't get messed up
        killcurses(stdscr)
        return 1

    killcurses(stdscr) # Restore the terminal anyway; we're done.
    return 0


intmain()
