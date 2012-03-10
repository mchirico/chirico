#!/usr/bin/perl
# Copyright (c) GPL 2006 Mike Chirico mchirico@gmail.com
# 
# This is a simple scraping program to get the sectors
# for stock.c
#
# It all goes from 1 to 136
#  biz.yahoo.com/p/csv/136conameu.csv






sub file_process
{

    my($filecommand) = @_;

   open (GETS1,$filecommand) or
     die "Cannot open page\n";
    my $count=0;
    my $flag=0;
    my $flag2=0;
    while(<GETS1>) {
    
    if ($_ =~ /^href=[0-9][0-9]*conameu.html/ ) 
    {
          s/\.html/\.csv/g;
          s/href=//g;
          s/\>\<font//g;
          $flag=1;
          print "/p/csv/$_";
    }
    
    
     if ($flag == 1) 
     {
         $count+=1;
     }
    
    
    if ($count == 3 && $flag)
    {
         s/size=-1>//g;
         s/<\/a><\/td><td//g;
         s/<\/font>//g;
         print "$_";
         $flag=0;
         $count=0;
    }
 

  }
}

&file_process("wget -o log -O - http://biz.yahoo.com/p/s_conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/1conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/112conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/2conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/3conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/4conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/5conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/6conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/7conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/8conameu.html|");
&file_process("wget -o log -O - http://biz.yahoo.com/p/9conameu.html|");
