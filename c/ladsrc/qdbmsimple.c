/* qdbmsimple.c - Opens and closes a qdbm database */

#include <depot.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    DEPOT * dp;

    dp = dpopen("test.db", DP_OWRITER | DP_OCREAT, 0);
    if (!dp) {
        printf("error: %s\n", dperrmsg(dpecode));
        return 1;
    }

    dpclose(dp);

    return 0;
}
