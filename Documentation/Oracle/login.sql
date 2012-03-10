set time on
define _editor=vi
column tablespace_name format a40 truncate
column file_name format a45 truncate
column username format a20 truncate
set lines 132
set pages 55
set termout on
set time on
SET SQLPROMPT '&_USER@&_CONNECT_IDENTIFIER> '
