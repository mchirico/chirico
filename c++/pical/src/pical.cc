/* 
    pical - Personal Income Calculator.
    Copyright (C) 2007  Mike Chirico <mchirico@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



    Updated:
    Thu Nov 29 14:10:16 EST 2007

    Simple program to calculate weekly,yearly gross margin.

    For tax % reference:
           http://turbotax.intuit.com/tax_help/tax_calculators/tax_estimator.jhtml

    svn:
           http://chirico.googlecode.com/svn/trunk/c++/pical/

    download:

           http://code.google.com/p/chirico/downloads/list

*/


#include <iostream>
#include <stdlib.h>
#include <getopt.h>


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "version.h"



class Work {

public:
  Work(double n): _rate(n),_taxrate(.28), _taxratetaken(0),_weeksyr(50) { }

  void set_hrs(double n) {
    if(n > 0) {
          _hours=n; 
          }
  }
  void set_taxrate(double n) {
    if(n > 0) { 
        _taxrate=n; 
         }
  }
  void set_taxratetaken(double n) {
    if(n > 0) { 
        _taxratetaken=n; 
         }
  }
  void set_weeksyr(double n) {
    if(n > 0) { _weeksyr=n; }
  }
 
  void prn() {
    if(error_check())
       calc();

    printf("week_margin \t%12.2f\n"
	   "year_margin \t%12.2f\n\n"
	   "week_gross  \t%12.2f\n"
	   "year_gross  \t%12.2f\n\n"
           "Avg hrs day \t%12.2f\n"
           "Fed tx      \t%12.2f\n"
           "State tx    \t%12.2f\n"
           ,_week_margin,_year_margin,_week_gross,
           _year_gross,_hours/5.0,
           _fed_tax,
	   _state_tax);
  }

private:

   void calc() {
      if(_hours > 40) {
	_week_gross= _rate*40+_rate*1.5*(_hours - 40);
      } else {
	_week_gross= _rate*_hours;
      }
      _week_margin=_week_gross*(1 -_taxrate) - _week_gross*0.028;
      _year_margin=_week_margin*_weeksyr;
      _year_gross=_week_gross*_weeksyr;
      _fed_tax=_year_gross*_taxrate;
      _state_tax = _year_gross* 0.028;
    }

  int error_check() {
    if(_hours < 0 || _hours > 168)
      return 0;
    if(_rate < 0 || _rate > 600)
      return 0;
    if(_weeksyr < 0 || _weeksyr > 52)
      return 0;



    return 1;
  }

    
  double _hours;
  double _rate;
  double _taxrate;
  double _taxratetaken;
  double _weeksyr;
  double _week_margin;
  double _year_margin;
  double _week_gross;
  double _year_gross;
  double _fed_tax;
  double _state_tax;

};





void input(int argc, char **argv,double &rate,double &hours,
	  double &taxrate,double &weeksyr)
{
	int c;
	int flags =0;

	while (1) {

		int option_index = 0;
		static struct option long_options[] = {
			{"rate", 1, 0, 'r'},
			{"hours", 1, 0, 'h'},
			{"taxrate", 1, 0, 't'},
			{"weeksyr", 1, 0, 'w'},
			{"version", 0, 0, 'v'},
			{"help", 0, 0, 'z'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "r:h:t:w:v",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			printf("option %s",
			       long_options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
			break;

		case 'h':
		        flags |= 0x1;
			hours=atof(optarg);
			break;

		case 'r':
		        flags |= 0x2;
			rate=atof(optarg);
			break;
		case 't':
			taxrate=atof(optarg);
			break;
		case 'w':
			weeksyr=atof(optarg);
			break;
		case 'v':
		  printf("Copyright (C) GPL 2007 by Mike Chirico <mchirico@users.sourceforge.net>\n"
			 "version %s \n"
                         "  try --help\n"
			 "Download:\n"
			 "  http://sourceforge.net/project/showfiles.php?group_id=79320&package_id=233333\n"
			 "Source:\n"
			 "  http://chirico.googlecode.com/svn/trunk/c++/pical/src/pical.cc\n\n",
			 VERSION
                         );
			break;
		case 'z':
		  printf("Please reference the manual.\nman pical\n");
		  exit(0);
		  break;
		case '?':
			break;

		default:
			printf
			    ("?? getopt returned character code 0%o ??\n",
			     c);
		}
	}

	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
	}

        if ((flags & 0x1) && (flags & 0x2)) {

	} else {
	  printf("pical: Personal Income CALculator\n");
	  printf("%s -r <Pay Rate> -h <Hours per Week> [-t <taxrate> -w <weeks in year>]\n",argv[0]);
	  printf("Example: %s -r 60 -h 40 -t .28\n",argv[0]);
	  printf("\nFor help try man pical\n");
	  exit(0);
	}
}




int main(int argc, char **argv)
{
  double rate=0;
  double hours=0;
  double taxrate=0;
  double weeksyr=0;

  input(argc,argv,rate,hours,taxrate,weeksyr);


  Work *w = new Work(rate);
  w->set_hrs(hours);
  w->set_taxrate(taxrate);
  w->set_weeksyr(weeksyr);

  w->prn();

  delete w;

}
