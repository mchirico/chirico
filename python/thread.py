#!/usr/bin/env python
import thread
import time
def print_time(delay):
    while 1:
        time.sleep(delay)
        print time.ctime(time.time())


# Start the new thread
thread.start_new_thread(print_time,(1,))
# Now go do something else while the thread runs
while 1:
      pass
