#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include "Remotery.h"

double delay() {
    int i, end;
    double j = 0;

    rmt_BeginCPUSample(delay, 0);
    for( i = 0, end = rand()/100; i < end; ++i ) {
        j += sin(i);
    }
    rmt_EndCPUSample();
    return j;
}

int sig = 0;

/// Allow to close cleanly with ctrl + c
void sigintHandler(int sig_num) {
    sig = sig_num;
    printf("Interrupted\n");
}

int main( ) {
    signal(SIGINT, sigintHandler);

    Remotery *rmt;

    if( RMT_ERROR_NONE != rmt_CreateGlobalInstance(&rmt) ) {
        return -1;
    }

    while (sig == 0) {
        rmt_LogText("start profiling");
        delay();
        rmt_LogText("end profiling");
    }

    rmt_DestroyGlobalInstance(rmt);
    printf("Cleaned up and quit\n");
    return 0;
}
