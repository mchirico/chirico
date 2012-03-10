set serveroutput on
-- First create table
begin
     EXECUTE IMMEDIATE ('DROP TABLE t2');
     EXECUTE IMMEDIATE ('CREATE TABLE t2(a int, b varchar(20))');
        Dbms_Output.put_line('Table recreated');
        EXCEPTION
         WHEN OTHERS THEN
             EXECUTE IMMEDIATE ('CREATE TABLE t2(a int, b varchar(20))');
        Dbms_Output.put_line('Table initially created');
end;  
/

declare
     B varchar(20);
begin
    for i in 0 .. 10
    loop
        B := i;
       dbms_output.put_line('B=' || B);
        insert into t2 (b) values (B);
   end loop;
 end;
/
