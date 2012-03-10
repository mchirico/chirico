/*
  Example of setting the effective UID on a file

  gcc uid_open.c -o uid_open
  su 
  chown root.chirico uid_open
  chmod u+s uid_open
  exit

  Now you can run this as chirico and write to the
  root directory


To set the file immutable simply, execute the following command:
[root@deep /]# chattr +i uid_open

To undo it type the following:
[root@deep /]# chattr -i uid_open





References:

O_CREAT
              If  the file does not exist it will be created.  The owner (user
              ID) of the file is set to the effective user ID of the  process.
              The  group  ownership  (group ID) is set either to the effective
              group ID of the process or to the group ID of the parent  direc-
              tory  (depending  on  filesystem type and mount options, and the
              mode of the parent directory, see, e.g., the mount options  bsd-
              groups  and  sysvgroups  of the ext2 filesystem, as described in
              mount(8)).



Other common problem:

Several people are working on a project in 

   /home/share  

and they need to create and save documents 
so that others in the group can use these 
documents.  How do you do this?

                                                                                                
   /usr/sbin/groupadd share                                                                     
   chown -R root.share /home/share                                                              
   /usr/bin/gpasswd -a <username> share                                                         
   chmod 775 /home/share                                                                        
   chmod 2775 /home/share                                                                       
                                                                                                
   ls -ld /home/share                                                                           
   drwxrwsr-x    2 root     share        4096 Nov  8 16:19 /home/share                          
         ^------- Note the s bit, which was set with the chmod 2775              
                                                                                                






*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main()
{
	int fd;


	if ((fd = open("/root/datajunk", O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "Can't open file \n");
		return 1;
	}


	write(fd, "0123456", strlen("0123456"));
	close(fd);

	return 0;
}
