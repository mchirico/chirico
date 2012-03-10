SET SERVEROUTPUT ON

BEGIN

    -- -------------------------------------------------------

    DBMS_AQADM.CREATE_QUEUE_TABLE (
        queue_table         => 'chirico.Q2_T'
      , queue_payload_type  => 'chirico.message_type'
    );

    -- -------------------------------------------------------

    DBMS_AQADM.CREATE_QUEUE (
        queue_name          => 'Q2'
      , queue_table         => 'chirico.Q2_T'
      , queue_type          => DBMS_AQADM.NORMAL_QUEUE
      , max_retries         => 0
      , retry_delay         => 0
      , retention_time      => 1209600
      , dependency_tracking => FALSE
      , comment             => 'Test Object Type Queue'
      , auto_commit         => FALSE
    );

    -- -------------------------------------------------------

    DBMS_AQADM.START_QUEUE('chirico.Q2');

    -- -------------------------------------------------------

    DBMS_AQADM.GRANT_QUEUE_PRIVILEGE (
        privilege     =>     'ALL'
      , queue_name    =>     'chirico.Q2'
      , grantee       =>     'chirico'
      , grant_option  =>      FALSE
    );

    -- -------------------------------------------------------

END;
/
