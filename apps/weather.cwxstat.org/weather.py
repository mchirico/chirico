#!/usr/bin/env python
import sqlite3

def weather(n='2008-08-26 13:15:25'):
    con = sqlite3.connect("/var/log/cwxstat/weathersqliter")
    c = con.cursor()
    s="""
select temp*9/5+32,hum,sensor,timeEnter from outside2 where timeEnter > '%s' order by timeEnter asc limit 200
"""%n.strip()
    c.execute(s)
    a=c.fetchall()
    c.close()
    con.close()
    return a


def wind(n='2008-08-26 13:15:25'):
    con = sqlite3.connect("/var/log/cwxstat/weathersqliter")
    c = con.cursor()
    s="""
select direction,gust,avg,timeEnter from wind where timeEnter > '%s' order by timeEnter asc limit 800
"""%n.strip()
    c.execute(s)
    a=c.fetchall()
    c.close()
    con.close()
    return a

def hpa(n='2008-08-26 13:15:25'):
    con = sqlite3.connect("/var/log/cwxstat/weathersqliter")
    c = con.cursor()
    s="""
select hpa,timeEnter from inside where timeEnter > '%s' order by timeEnter asc limit 800
"""%n.strip()
    c.execute(s)
    a=c.fetchall()
    c.close()
    con.close()
    return a


def rain(n='2008-08-26 13:15:25'):
    con = sqlite3.connect("/var/log/cwxstat/weathersqliter")
    c = con.cursor()
    s="""
select rate,tips,total,reset,timeEnter from rain where timeEnter > '%s' order by timeEnter asc limit 200
"""%n.strip()
    c.execute(s)
    a=c.fetchall()
    c.close()
    con.close()
    return a


