load data
 infile '/backup/household/oracle/HouseHoldTrends.csv'
 into table trends
 fields terminated by "," optionally enclosed by '"' 
 TRAILING NULLCOLS		  
 ( "DATE" DATE 'mm/dd/yyyy', ACCOUNT_NAME, "CHECK", TRANSACTION, CATEGORY, NOTE, EXPENSE, DEPOSIT )
