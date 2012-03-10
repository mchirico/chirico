
BEGIN
   DBMS_AQADM.CREATE_QUEUE_TABLE
      (queue_table => 'msg',
       queue_payload_type => 'message_type',
       multiple_consumers => TRUE,
       message_grouping => DBMS_AQADM.TRANSACTIONAL,
       comment => 'Specialized queue table created on ' || 
          TO_CHAR(SYSDATE,'MON-DD-YYYY HH24:MI:SS'));
END;
/

BEGIN

  DBMS_AQADM.CREATE_QUEUE_TABLE(
      queue_table => 'Q0_T',
      queue_payload_type => 'sys.aq$_jms_message',
      sort_list => 'PRIORITY,ENQ_TIME',
      multiple_consumers => true,
      compatible => '10.0');

  DBMS_AQADM.CREATE_QUEUE(
      queue_name => 'Q0',
      queue_table => 'Q0_T',
      max_retries => 10,
      retry_delay => 360,
      retention_time => 5,
      comment => 'Test Queue Number 0');

  DBMS_AQADM.START_QUEUE (
      queue_name => 'Q0');

END;

             

