CREATE TABLE "CWXSTAT"."HOURSSTAGE" 
   (	"ID" NUMBER(9,0), 
        "date" date,
	"start" TIMESTAMP (6), 
	"stop" TIMESTAMP (6), 
	"lunch" TIMESTAMP (6), 
	"hourMin" TIMESTAMP (6), 
	"payPeriod" integer, 
	"notes" varchar(30), 
	"diff" number, 
	"recorded" number, 
	"converted" number, 
	"rate" number, 
	"gross" number
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT)
  TABLESPACE "CWXSTAT" ;











