/* ptypair.h - Defines function interface for ptypair.c */

#ifndef _PTYPAIR_H
#define _PTYPAIR_H
int get_master_pty(char **name);
int get_slave_pty(char *name);
#endif /* _PTYPAIR_H */
