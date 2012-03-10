load data
 infile '/backup/household/oracle/Hours.csv'
 replace
 into table hoursstage
 fields terminated by "," optionally enclosed by '"' 
 TRAILING NULLCOLS		  
 ( "date" DATE 'mm/dd/yyyy', 
   "start" TIMESTAMP 'HH24:MI',
   "stop"  TIMESTAMP 'HH24:MI',
   "lunch"  TIMESTAMP 'HH24:MI',
   "hourMin"  TIMESTAMP 'HH24:MI',
   "payPeriod" ,
   "notes" CHAR NULLIF ("notes"=BLANKS),
   "diff" float external DEFAULTIF ("diff"=BLANKS),
   "recorded" float external DEFAULTIF ("diff"=BLANKS),
   "converted" CHAR TERMINATED BY ",",
   "rate" CHAR TERMINATED BY ",",
   "gross" )
