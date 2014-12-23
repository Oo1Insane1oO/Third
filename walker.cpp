#include "walker.h"
#include <cmath>

Walker::Walker(int nw, double mdt, int mad, int mid, double wp, double time) {
    /* constructor, set parameters */
    numberWalkers = nw; //number of walkers
    dt = mdt; //time-step
    l_0 = ml0; //step-length
    maxDistance = mad; //upper boundary
    minDistance = mid; //lower boundary
    walkProbability = wp; //jump probability

    maxTrials = int (time/dt + 0.5); //number of trials(time iterations)
    l_0 = std::sqrt(2*dt); //step-length as defined
    positionSize = (maxDistance-minDistance)/l_0 + 1 //size of position vector
}

void Walker::output() {
    /* function for output results to file */
    return;
}
