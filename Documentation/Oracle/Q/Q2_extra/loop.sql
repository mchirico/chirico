SET SERVEROUTPUT ON
begin
  for i in 1..200 loop
     dbms_output.put_line('Test '||i);
  end loop;
end;
/