set serveroutput on
declare
  mc integer;
begin
   select count(a) into mc from junk;
   if (mc >= 4)
    then
       dbms_output.put_line('mc = ' || mc);
    else
       dbms_output.put_line('mc (less) = ' || mc);
    end if;
end;
/
