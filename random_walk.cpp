#include "random_walk.h" //header
#include "walker.h" //header for walker
#include <iostream> //cout, endl
#include <string> //string
#include <cstring> //strcopy

RandomWalk::RandomWalk(Walker *mwlk, int use) {
    /* constructor, set objects */
    usage = use; //2D or 1D test object
    wlk = mwlk; //object Walker
    RN = RandomNumber(); //object RandomNumber
}

void RandomWalk::initialize() {
    /* initialize result vectors */
    if(usage == 0) {
        wlk->xProbabilityPosition.assign(wlk->positionSize,0);
    } else if(usage == 1) {
        wlk->xyProbabilityPosition.resize(wlk->positionSize, std::vector<double>(wlk->positionSize));
    } else {
        std::cout << "usage not specified" << std::endl;
    } //end if usage

    return;
} //end function initialize

void RandomWalk::mcSampling() {
    /* function monte-carlo sampling(random walk) */

    long seed = -1; //seed for random
    std::vector<double> xPosition (wlk->numberWalkers,0); //x-position vector
    
    RandomWalk::initialize(); //initialize probability position vector
    
    //loop over walkers
    #pragma imp parallel for
    for(int trial=0; trial<=wlk->maxTrials ;trial++) {
        //loop steps
        #pragma omp parallel for
        for(int walker=0; walker<=wlk->numberWalkers ;walker++) {
            if(xPosition[walker]<wlk->minDistance || xPosition[walker]>wlk->maxDistance) {
                /* keep walker leashed(boundary) */
                continue;
            } //end leashed

            double randomDistNum = RN.ran0(&seed); //random uniformly number
            
            if(randomDistNum<wlk->walkProbability) {
                /* make jumps */
                xPosition[walker] += wlk->l_0;
            } else {
                xPosition[walker] -= wlk->l_0;
            } //end random

            int xIndex = (xPosition[walker]-wlk->minDistance)/wlk->l_0 + 0.5;
            if(xIndex < 0 || xIndex >= wlk->positionSize) { 
                /* ignore if outside */
                continue;
            } //end if x-index

            wlk->xProbabilityPosition[xIndex] += 1; //update concentration
        } //end walker
    } //end trial

    return;
} //end function mcSampling

void RandomWalk::mcSampling2() {
    /* function, Monte Carlo sampling 2D*/

    std::string fileBuf;
    char *filename;
    
    long seed = -1; //seed for random
    std::vector<double> xPosition (wlk->numberWalkers,0); //x-position vector
    std::vector<double> yPosition (wlk->numberWalkers,0); //y-position vector
    
    RandomWalk::initialize(); //initialize probability position matrix
    
    //loop over walkers
//     #pragma omp parallel for // commented out since we write to file (I really need to learn openmpi...)
    int jumpCount = 0;
    for(int trial=0; trial<=wlk->maxTrials ;trial++) {
        /* loop time-trials */

        #pragma omp parallel for
        for(int walker=0; walker<=wlk->numberWalkers ;walker++) {
            /* loop walkers */
            if(xPosition[walker]<wlk->minDistance || xPosition[walker]>wlk->maxDistance || 
                    yPosition[walker]<wlk->minDistance || yPosition[walker]>wlk->maxDistance) {
                /* keep walker leashed(boundary) */
                continue;
            } //end leashed

            double randomDistNum = 2*RN.ran0(&seed); //random number from uniform distribution
          
            if(randomDistNum<=wlk->walkProbability) {
                /* make jumps */
                xPosition[walker] += wlk->l_0;
            } else if(randomDistNum<=2*wlk->walkProbability) {
                xPosition[walker] -= wlk->l_0;
            } else if(randomDistNum<=3*wlk->walkProbability) {
                yPosition[walker] += wlk->l_0;
            } else {
                yPosition[walker] -= wlk->l_0;
            } //end jumps

            int xIndex = (xPosition[walker]-wlk->minDistance)/wlk->l_0 + 0.5; //create x-index of moved
            int yIndex = (yPosition[walker]-wlk->minDistance)/wlk->l_0 + 0.5; //create y-index of moved
            if(xIndex<0 || xIndex>=wlk->positionSize || yIndex<0 || yIndex>=wlk->positionSize) { 
                /* ignore deserters(walkers outside of boundary) */
                continue;
            } //end if index

            wlk->xyProbabilityPosition[xIndex][yIndex] += 1; //update position grid
        } //end walkers

        if(jumpCount == 10 || jumpCount == 0) {
            /* write every 10000 */

            // create filename
            fileBuf = "tmpData/data";
            fileBuf += std::to_string(trial);
            char *tempFilename = new char[fileBuf.length() + 1];
            filename = std::strcpy(tempFilename, fileBuf.c_str() );

            // write to file
            wlk->output2(filename); // output data to file filename

            // reset jumpCount
            jumpCount = 0;
        } // end if jumpCount

        jumpCount += 1;
    } //end time-trial

    return;
} //end function mcSampling2
