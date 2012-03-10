#!/usr/bin/env python
"""


"""
import os,time,sys,signal,getopt,popen2,re,curses


stdscr=curses.initscr()
curses.start_color()
def mycurses_cleanup():
	curses.nocbreak()
	stdscr.keypad(0)
	curses.echo()
	curses.endwin()

def mycurses_init():
#	stdscr = curses.initscr()
	curses.cbreak()
	stdscr.keypad(1) 
	return stdscr


def signal_handler(signal, frame):
	mycurses_cleanup()
        sys.exit(0)


# Runs ssh command
def runcmd(N,len=0):
    scmd=N
    r,w,e = popen2.popen3(scmd)
    m=r.readlines()
    e.readlines()
    r.close()
    e.close()
    w.close()
    return [os.getpid(),m]
            


def menu(N):
	j=0
	for i in range(0,len(N)):
		stdscr.addstr(0,j,str(N[i]),curses.color_pair(3))
		j=j+10
	stdscr.refresh()



def main(N):
	curses.init_pair(1,curses.COLOR_RED, curses.COLOR_WHITE)
	curses.init_pair(2,curses.COLOR_RED, curses.COLOR_BLUE)
	curses.init_pair(3,curses.COLOR_BLACK, curses.COLOR_WHITE)
	try:
		curses.use_default_colors()
	except:
		print "This version of python does not use curses.use_default_colors()"
	stdscr.addstr(0,0,"RED",curses.color_pair(1))
	stdscr.addstr(10,5,'Quit with q or ctl-c')
	stdscr.addch(9,5,'X')
	stdscr.addstr(11,5,'Input character:',curses.color_pair(2))
	stdscr.refresh()
	menu(['One','Two','Three'])
	key = 'X'
	while key != ord('q'):
		curses.noecho()
		key = stdscr.getch()
		stdscr.addch(9,5,key)
		mwrite(key)
		if key == 258:
			stdscr.addstr(5,10,"Down Arrow: 258")
		if curses.KEY_LEFT == key:
			stdscr.addstr(3,10,"Key left")
		stdscr.addstr(11,5,'Input character:',curses.color_pair(3))
#		s=stdscr.getstr(15,15,5)
#		stdscr.addstr(20,5,s)
		stdscr.refresh()

"""	
	print "program "+sys.argv[0]+" called with "+str(len(sys.argv)) +" parameters"
	if len(sys.argv) > 1:
		print sys.argv
"""


def mwrite(n):
	f=open('file','a')
	f.write(str(n))
	f.write('\n')
	f.close()


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
	mycurses_init()
        main(sys.argv)
	mycurses_cleanup()
