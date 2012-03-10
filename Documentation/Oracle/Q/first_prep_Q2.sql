



CREATE TYPE message_type AS OBJECT (
    message_id     NUMBER(15)
  , subject        VARCHAR2(100)
  , text           VARCHAR2(100)
  , dollar_value   NUMBER(4,2)
)
/


CREATE SEQUENCE message_seq
       INCREMENT BY 1
       START WITH 1000
       NOMAXVALUE
       NOCYCLE;
