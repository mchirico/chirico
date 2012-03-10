AUTOMAKE_OPTIONS = gnu

bin_PROGRAMS = pipedup pipedrv

pipedup_SOURCES = src/pipedup.c 
pipedrv_SOURCES = src/pipedrv.c src/wrapper.c

pipedup_LDADD = @MLIBS@ 


man_MANS = man/pipedup.1

EXTRA_DIST = $(man_MANS) VERSION cmds src/wrapper.h
