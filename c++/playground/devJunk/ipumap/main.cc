#include <cstdio>
#include <cstdlib>
#include "ipumap.h"



int main()
{

    IPUmap  ipumap("chirico dev.chirico schirico");
    for (int i =0; i < 20; ++i) {
        if ( ipumap.check("192.168.2.34","chirico") )
            fprintf(stderr,"true ** ALARMS ***\n");
        else
            fprintf(stderr,"false pass\n");

    }

    fprintf(stderr,"\nSuccess login of whitelist\n");
    ipumap.succlogin("192.168.2.34","chirico");

    for (int i =0; i < 20; ++i) {
        if ( ipumap.check("192.168.2.34","chirico") )
            fprintf(stderr,"true ** ALARMS ***\n");
        else
            fprintf(stderr,"false pass\n");

    }



    fprintf(stderr,"Working with bozo\n");
    for (int i =0; i < 20; ++i) {
        if ( ipumap.check("192.168.2.34","bozo") )
            fprintf(stderr,"true ** ALARMS ***\n");
        else
            fprintf(stderr,"false pass\n");
    }


    return 0;
}
