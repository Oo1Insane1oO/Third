#include "random_walk.h" //header
#include "walker.h" //header for walker
#include "random_number.h" //header for random_number

RandomWalk::RandomWalk(RandomNumber *mRN, Walker *mwlk) {
    /* constructor, set objects */
    
    RN = mRN;
    wlk = mwlk;
}

void RandomWalk::initialize() {
    /* initialize result vectors */
    wlk->xProbabilityPosition.assign(wlk->positionSize,0); 

    return;
} //end function initialize

void RandomWalk::mcSampling() {
    /* function monte-carlo sampling(random walk) */

    long seed = -1; //seed for random
    std::vector<double> xPosition (wlk->numberWalkers,0); //x-position vector
    
    RandomWalk::initialize(); //initialize probability position vector
    
    //loop over walkers
    for(int trial=0; trial<=wlk->maxTrials ;trial++) {
        //loop steps
        for(int walker=0; walker<=wlk->numberWalkers ;walker++) {
            if(xPosition[walker]<wlk->minDistance || xPosition[walker]>wlk->maxDistance) {
                /* keep walker leashed(boundary) */
                continue;
            } //end leashed

            double randomDistNum = RN->ran0(&seed); //random uniformly number
            
            if(randomDistNum<wlk->walkProbability) {
                xPosition[walker] += wlk->l_0;
            } else {
                xPosition[walker] -= wlk->l_0;
            } //end random

            int xIndex = (xPosition[walker]-wlk->minDistance)/wlk->l_0 + 0.5;
            if(xIndex < 0 || xIndex >= wlk->positionSize) { 
                /* ignore if outside */
                continue;
            } //end if x-index

            //update cumulative positions
            wlk->xProbabilityPosition[xIndex] += 1;
        } //end walker
    } //end trial

    return;
} //end function mcSampling
