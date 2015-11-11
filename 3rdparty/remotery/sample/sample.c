#include <stdlib.h>
#include <math.h>
#include "Remotery.h"

double delay() {
    int i, end;
    double j = 0;

    rmt_BeginCPUSample(delay);
    for( i = 0, end = rand()/100; i < end; ++i ) {
        j += sin(i);
    }
    rmt_EndCPUSample();
    return j;
}


int main( int argc, const char **argv ) {
    Remotery *rmt;

    if( RMT_ERROR_NONE != rmt_CreateGlobalInstance(&rmt) ) {
        return -1;
    }

    for(;;) {
        rmt_LogText("start profiling");
        delay();
        rmt_LogText("end profiling");
    }

    rmt_DestroyGlobalInstance(rmt);
    return 0;
}
