#!/usr/bin/env python
"""


"""
import os,time,sys,signal


def signal_handler(signal, frame):
        sys.exit(0)



# Class to be decorated
class Coffee(object):
    def __init__(self):
        self.cost = 4.99
    def get_cost(self):
        return self.cost
 
# Decorator Milk
class Milk(Coffee):
    def __init__(self, coffee):
        self.cost = 1.49
        self.cost += coffee.get_cost()
 
# Decorator Whip
class Whip(Coffee):
    def __init__(self, coffee):
        self.cost = 0.89
        self.cost += coffee.get_cost()
 
# Decorator Sprinkles
class Sprinkles(Coffee):
    def __init__(self, coffee):
        self.cost = 0.79
        self.cost += coffee.get_cost()
 






def main(N):
	coffee = Coffee()
	print "Cost of just Coffee()",coffee.get_cost()
	coffee = Milk(coffee)
	print "Cost of Coffee() with Mil()",coffee.get_cost()
	coffee = Whip(coffee)
	coffee = Sprinkles(coffee)
	print coffee.get_cost()

    


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
