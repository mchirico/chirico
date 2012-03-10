#include <pcap.h>
#include <string.h>
#include <stdlib.h>

#define MAXBYTES2CAPTURE 2048



int main(void) {
  char *device=NULL;
  pcap_if_t *alldevsp;

  char errbuf[PCAP_ERRBUF_SIZE];


  device = pcap_lookupdev(errbuf);
  printf("device %s\n",device);




  if (pcap_findalldevs (&alldevsp, errbuf) < 0)   
    {
      fprintf (stderr, "Error %s", errbuf);
      exit (1);
    }

  while (alldevsp != NULL)
    {
      printf ("%s\n", alldevsp->name);
      alldevsp = alldevsp->next;
    }

  return 1;

}
