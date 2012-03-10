/*
Reference:
http://download.oracle.com/docs/cd/B19306_01/appdev.102/b14407/pc_03dbc.htm#i5880


create or replace procedure get_emp_info (p_rc out sys_refcursor) as
  begin
    open p_rc for
    select   employee_id,
             last_name,
             job_id
    from     employees
    order by last_name;
  end;
/









 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlca.h>
#include <sqlda.h>
#include <sqlcpr.h>
 
/*Watch your name lengh for long connection strings */
#define NAME_LEN 50
 
VARCHAR username[NAME_LEN];
VARCHAR password[NAME_LEN];
VARCHAR connstr[NAME_LEN];
 
/* the cursor variable */
SQL_CURSOR emp_cursor;
 
/* used to strip blanks from the ename and job */
typedef char asciiz[NAME_LEN];
EXEC SQL TYPE asciiz IS STRING(NAME_LEN) REFERENCE;
 
					 int    empno;
					 asciiz ename;
					 asciiz job;
 
					 void sql_error(char *msg)
{
  char err_msg[128];
  size_t buf_len, msg_len;
 
  EXEC SQL WHENEVER SQLERROR CONTINUE;
 
  printf("\n%s\n", msg);
  buf_len = sizeof (err_msg);
  sqlglm(err_msg, &buf_len, &msg_len);
  printf("%.*s\n", msg_len, err_msg);
 
  EXEC SQL ROLLBACK RELEASE;
 
  exit(EXIT_FAILURE);
}
 
int main()
{
  strncpy((char *) username.arr, "chirico", NAME_LEN);
  username.len = (unsigned short) strlen((char *) username.arr);
  
  strncpy((char *) password.arr, "mike", NAME_LEN);
  password.len = (unsigned short) strlen((char *) password.arr);
  
  strncpy((char *) connstr.arr, "cluster0.squeezel.com:1522/orcl", NAME_LEN);
  connstr.len = (unsigned short) strlen((char *) connstr.arr);
 
  EXEC SQL WHENEVER SQLERROR DO sql_error("ORACLE error: \n");
  
  /* My default connstr is not working */
    EXEC SQL CONNECT :username IDENTIFIED BY :password USING :connstr; 
  /*   EXEC SQL CONNECT :username IDENTIFIED BY :password; */
  
  printf("\nConnected to %s as user: %s constr: %s\n\n", connstr.arr, username.arr,connstr.arr);
 
  /* allocate cursor variable */
  EXEC SQL ALLOCATE :emp_cursor;
 
  /* call the stored procedure */
  EXEC SQL EXECUTE
    BEGIN
    get_emp_info(p_rc => :emp_cursor);
  END;
  END-EXEC;
 
  EXEC SQL WHENEVER NOT FOUND DO break;
 
  for (;;)
    {
      EXEC SQL FETCH :emp_cursor INTO :empno, :ename, :job;
 
      printf("EMPNO: %d, ENAME: %s, JOB: %s\n", empno, ename, job);
    }
 
  /* close and free the cursor */
  EXEC SQL CLOSE :emp_cursor;
 
  EXEC SQL FREE :emp_cursor;
 
  EXEC SQL COMMIT RELEASE;
  
  exit(EXIT_SUCCESS);
}
