#!/usr/bin/env python
import sys
if len(sys.argv) <= 1:
    print sys.argv[0] + " <item> <item2>"
else:
    for item in sys.argv:
        print item
