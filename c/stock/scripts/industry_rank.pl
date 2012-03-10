#!/usr/bin/perl
#  Copyright (C) GPL mchirico@users.sourceforge.net
#
#  This script give industry rank

use Text::ParseWords;
use strict;


my @data;
my %industry;
my $count=0;

open (SI,"stock -i|") or die "Could not run the stock -i command\n";
while(<SI>)
{
    if ($count >= 1) {
        @data = quotewords(",", 0, $_);
        $industry{$data[1]}=$data[0];
    }
    $count++;
}
print "\"Industry\"",",","\"1-Day Price Chg \%\"\n";
# You may want reverse sort here
foreach my $i ( sort keys %industry) {
   print "$i\t\"$industry{$i}\"\n";
}
