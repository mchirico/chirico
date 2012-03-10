SELECT
    NVL(b.tablespace_name,nvl(a.tablespace_name,'UNKOWN')) name
  , kbytes_alloc                                           kbytes
  , kbytes_alloc-NVL(kbytes_free,0)                        used
  , NVL(kbytes_free,0)                                     free
  , ((kbytes_alloc-NVL(kbytes_free,0))/kbytes_alloc)*100   pct_used
  , NVL(largest,0)                                         largest
FROM   ( SELECT   SUM(bytes)/1024 Kbytes_free
                , MAX(bytes)/1024 largest
                , tablespace_name
         FROM sys.dba_free_space
         GROUP BY tablespace_name
       ) a
     , ( SELECT   SUM(bytes)/1024 Kbytes_alloc
                , tablespace_name
         FROM sys.dba_data_files
         GROUP BY tablespace_name
       ) b
WHERE a.tablespace_name (+) = b.tablespace_name
/
