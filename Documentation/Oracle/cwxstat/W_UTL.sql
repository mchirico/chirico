--
-- create view vhours as select beg_time,end_time,extra,recorded,notes from hours;
create or replace PACKAGE W_UTL
AS
TYPE CURSOR_TYPE IS REF CURSOR;
PROCEDURE DROP_SREPORT;
PROCEDURE M_TOT (results_cursor OUT CURSOR_TYPE, mymonth in varchar2);
PROCEDURE R_CLEAR;
PROCEDURE R_CREATE;
PROCEDURE A_DAY(b_time varchar2,e_time  varchar2,actual  number, p_period  int, notes_ varchar2);
PROCEDURE A_DAY2(b_time  varchar2,e_time  varchar2,actual  number, p_period  int,notes_ varchar2,p_cursor OUT SYS_REFCURSOR);
PROCEDURE Reportp;
PROCEDURE Reportc(b_time IN varchar2, p_cursor OUT SYS_REFCURSOR);
end W_UTL;
/



create or replace PACKAGE BODY  W_UTL
AS
-- ************************************************************
-- *  Table report must exist 
-- *  Also Note you cannot truncate table 
-- 
   TYPE W_R      IS RECORD (
      DAT DATE,
      HRS NUMBER(8)
   );

  TYPE W_T      IS TABLE        OF W_R;
  A_W_T            W_T       := W_T();

    l_exists INTEGER;  

PROCEDURE DROP_SREPORT is
BEGIN
     execute immediate 'drop table sreport;create table sreport (a number, b date, c date)'; exception when others then null; 
END;



-- you must put as on this one
PROCEDURE M_TOT (results_cursor OUT CURSOR_TYPE, mymonth in varchar2) as
BEGIN
  OPEN results_cursor FOR

    select 
      CASE
        WHEN  trunc(to_date(mymonth,'MM/DD/YYYY'),'MM') > (trunc(beg_time)-6) then  trunc(to_date(mymonth,'MM/DD/YYYY'),'MM')
         else trunc(beg_time)-6 end as a ,
      CASE
	WHEN (trunc(beg_time)+7) >= last_day(to_date(mymonth,'MM/DD/YYYY')) then last_day(to_date(mymonth,'MM/DD/YYYY'))
	  else trunc(beg_time) end as b
    from hours
	   where rtrim(TO_CHAR (beg_time,'DAY')) = 'FRIDAY'
	   and trunc(beg_time) >=  trunc(to_date(mymonth,'MM/DD/YYYY'),'MM')
	   and trunc(beg_time) <  last_day(to_date(mymonth,'MM/DD/YYYY'));


END M_TOT;





PROCEDURE R_CLEAR is
BEGIN 
   execute immediate 'drop table report'; exception when others then null; 
END R_CLEAR;

PROCEDURE R_CREATE is
BEGIN 
   execute immediate 'create table report (DAT date, hrs number(8))'; exception when others then null; 
END R_CREATE;


PROCEDURE Reportc( b_time IN varchar2
                                , p_cursor OUT SYS_REFCURSOR)
is
begin
  open p_cursor FOR 
  select beg_time,initcap(to_char(beg_time,'DAY')),end_time,notes,recorded,pay_period
  from   hours
  where  trunc(beg_time) >= trunc(to_date(b_time,'MM/DD/YYYY HH24:MI')) order by beg_time desc;

end Reportc;


PROCEDURE Reportp is
 BEGIN
   execute immediate 'truncate table report';
   insert into report (DAT,HRS) select beg_time,(end_time-beg_time)*24-nvl(lunch,0)+nvl(extra,0) from hours;
   commit;
 END ReportP;

PROCEDURE A_DAY(b_time  varchar2,e_time  varchar2,actual  number, p_period  int,notes_ varchar2) is
 BEGIN
--  exec W_UTL.A_DAY('03/21/2010 9:23','18:00',10,13);
  select count(*) INTO l_exists from hours where trunc(beg_time) = trunc(to_date(b_time,'MM/DD/YYYY HH24:MI')) and ROWNUM=1;

  IF l_exists = 1 THEN
    update hours set beg_time=to_date(b_time,'MM/DD/YYYY HH24:MI'), 
                     end_time=to_date(substr(b_time,1,instr(b_time,' ',2,1))||' '||ltrim(e_time) ,'MM/DD/YYYY HH24:MI'), 
                     recorded=actual, 
                     pay_period=p_period, 
                     notes=notes_ 
     where trunc(beg_time)= trunc(to_date(b_time,'MM/DD/YYYY HH24:MI'));
  ELSE
      insert into hours (beg_time,end_time,recorded,pay_period,notes) values (to_date(b_time,'MM/DD/YYYY HH24:MI'),
       to_date(substr(b_time,1,instr(b_time,' ',2,1))||' '||ltrim(e_time) 
          ,'MM/DD/YYYY HH24:MI'),actual,p_period,notes_);

  END IF;
   commit;
 END A_DAY;

PROCEDURE A_DAY2(b_time  varchar2,e_time  varchar2,actual  number, p_period  int,notes_ varchar2,p_cursor OUT SYS_REFCURSOR) is
 BEGIN
--  exec W_UTL.A_DAY('03/21/2010 9:23','18:00',10,13);
  select count(*) INTO l_exists from hours where trunc(beg_time) = trunc(to_date(b_time,'MM/DD/YYYY HH24:MI')) and ROWNUM=1;

  IF l_exists = 1 THEN
    update hours set beg_time=to_date(b_time,'MM/DD/YYYY HH24:MI'), 
                     end_time=to_date(substr(b_time,1,instr(b_time,' ',2,1))||' '||ltrim(e_time) ,'MM/DD/YYYY HH24:MI'), 
                     recorded=actual, 
                     pay_period=p_period, 
                     notes=notes_ 
     where trunc(beg_time)= trunc(to_date(b_time,'MM/DD/YYYY HH24:MI'));
  ELSE
      insert into hours (beg_time,end_time,recorded,pay_period,notes) values (to_date(b_time,'MM/DD/YYYY HH24:MI'),
       to_date(substr(b_time,1,instr(b_time,' ',2,1))||' '||ltrim(e_time) 
          ,'MM/DD/YYYY HH24:MI'),actual,p_period,notes_);

  END IF;
   commit;

open p_cursor FOR
  select *
  from   hours
  where  trunc(beg_time) >= trunc(to_date(b_time,'MM/DD/YYYY HH24:MI'));
 END A_DAY2;

END W_UTL;
/
commit;
