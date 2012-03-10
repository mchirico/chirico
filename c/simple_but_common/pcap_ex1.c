/*   This example must be run as user root

     You'll need the pcap libraries:

           $ yum install libpcap-devel
*/



#include <pcap.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(void)
{
  pcap_t *handle;                        /* Session handle */
  char *dev;                                /* The device to sniff on */
  char errbuf[PCAP_ERRBUF_SIZE]; /* Error string */
  struct bpf_program filter;            /* The compiled filter */
  char filter_app[] = "port 10000";       /* The filter expression */
  bpf_u_int32 mask;                     /* Our netmask */
  bpf_u_int32 net;                        /* Our IP */
  struct pcap_pkthdr header;          /* The header that pcap gives us */
  const u_char *packet;                 /* The actual packet */


  if(getuid( )){
    fprintf(stderr,"\n Also, you must be root to run this program:  \n");
    return 1;
  }




  /* Define the device */
  dev = pcap_lookupdev(errbuf);
  /* Find the properties for the device */
  pcap_lookupnet(dev, &net, &mask, errbuf);
  /* Open the session in promiscuous mode */
  handle = pcap_open_live(dev, BUFSIZ, 1, 0, errbuf);
  /* Compile and apply the filter */
  pcap_compile(handle, &filter, filter_app, 0, net);
  pcap_setfilter(handle, &filter);
  /* Grab a packet */
  packet = pcap_next(handle, &header);
  /* Print its length */
  printf("Jacked a packet with length of [%d]\n", header.len);
  /* And close the session */
  pcap_close(handle);
  return(0);
}
