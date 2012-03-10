#!/usr/bin/env python
def t():
    try:
        r=os.popen("w").readlines()

    except NameError:
        import os;
        r=os.popen("w").readlines()

    except:
        print "Really bad"
        exit

    finally:
        print r



t()
print "sample data"

