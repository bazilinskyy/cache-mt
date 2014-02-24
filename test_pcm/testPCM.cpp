#include "cpucounters.h"

#include 
#define F 10000

#define C 10000
using namespace std;
int

main(){

    cout<<"Launcing PCM"<
    PCM * m = PCM::getInstance();
    cout<<"PCM initialised"<
    // program counters, and on a failure just exit

    if (m->program() != PCM::Success) return -1;

    cout<<"Launcing program"<
    SystemCounterState before_sstate = getSystemCounterState();  
    // Begin of custom code
    double matrix[F][C];
    for(int i=0;i
        for(int j=0;j
            matrix[F][C] = 1.0;

        }

    }
    // End of custom code

    SystemCounterState after_sstate = getSystemCounterState();  
    cout << "RESULTADOS:"<
    cout << "Instructions per clock:" << getIPC(before_sstate,after_sstate)

         << "L3 cache hit ratio:" << getL3CacheHitRatio(before_sstate,after_sstate)

         << "Bytes read:"<< getBytesReadFromMC(before_sstate,after_sstate);

}