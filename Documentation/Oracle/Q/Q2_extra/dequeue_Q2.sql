SET SERVEROUTPUT ON

DECLARE

    dequeue_options      dbms_aq.dequeue_options_t;
    message_properties   dbms_aq.message_properties_t;
    message_handle       RAW(16);
    message              message_type;

BEGIN

    -- -------------------------------------------------------

    dequeue_options.CONSUMER_NAME           := NULL;
    dequeue_options.DEQUEUE_MODE            := DBMS_AQ.REMOVE;
    dequeue_options.NAVIGATION              := DBMS_AQ.NEXT_MESSAGE;
    dequeue_options.VISIBILITY              := DBMS_AQ.IMMEDIATE;
    dequeue_options.WAIT                    := DBMS_AQ.FOREVER;
    dequeue_options.MSGID                   := null;
    dequeue_options.CORRELATION             := 'TEST MESSAGE';

    -- -------------------------------------------------------

    DBMS_AQ.DEQUEUE (
        queue_name         => 'Q2'
      , dequeue_options    => dequeue_options
      , message_properties => message_properties
      , payload            => message
      , msgid              => message_handle
    );

    -- -------------------------------------------------------

    dbms_output.put_line('+-----------------+');
    dbms_output.put_line('| MESSAGE PAYLOAD |');
    dbms_output.put_line('+-----------------+');
    dbms_output.put_line('- Message ID   := ' || message.message_id);
    dbms_output.put_line('- Subject      := ' || message.subject);
    dbms_output.put_line('- Message      := ' || message.text);
    dbms_output.put_line('- Dollar Value := ' || message.dollar_value);

    -- -------------------------------------------------------

    COMMIT;

    -- -------------------------------------------------------

END;
/
