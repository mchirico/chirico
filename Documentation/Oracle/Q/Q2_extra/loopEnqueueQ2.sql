SET SERVEROUTPUT ON
DECLARE

  enqueue_options      dbms_aq.enqueue_options_t;
  message_properties   dbms_aq.message_properties_t;
  message_handle       RAW(16);
  message              message_type;
  message_id           NUMBER;


begin

    enqueue_options.VISIBILITY           := DBMS_AQ.ON_COMMIT;
    enqueue_options.SEQUENCE_DEVIATION   := null;

    message_properties.PRIORITY            := -5;
    message_properties.DELAY               := DBMS_AQ.NO_DELAY;
    message_properties.EXPIRATION          := DBMS_AQ.NEVER;
    message_properties.CORRELATION         := 'TEST MESSAGE';


  for i in 1..200 loop
     dbms_output.put_line('Test '||i);



    SELECT  message_seq.nextval
    INTO    message_id
    FROM    dual;


    message := MESSAGE_TYPE (
                     message_id
                   , 'Subject: EXAMPLE MESSAGE'
                   , 'Message: THIS IS A SAMPLE MESSAGE. '||i
                   , 10.2
               );


    DBMS_AQ.ENQUEUE (
          queue_name         => 'Q2'
        , enqueue_options    => enqueue_options
        , message_properties => message_properties
        , payload            => message
        , msgid              => message_handle
    );



  end loop;

  commit;

end;
/