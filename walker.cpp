#include "walker.h" //header file
#include <cmath> //sqrt
#include <fstream> //ofstream
#include <iostream> //cout, endl
#include <cstdlib> //exit

Walker::Walker(int nw, double mdt, int mad, int mid, double wp, double time) {
    /* constructor, set parameters */
    numberWalkers = nw; //number of walkers
    dt = mdt; //time-step
    maxDistance = mad; //upper boundary
    minDistance = mid; //lower boundary
    walkProbability = wp; //jump probability

    maxTrials = int (time/dt + 0.5); //number of trials(time iterations)
    l_0 = std::sqrt(2*dt); //step-length as defined
    positionSize = (maxDistance-minDistance)/l_0 + 1; //size of position vector
}

void Walker::output(const char *filename) {
    /* function, output results to file */

    std::ofstream outputfile(filename); //initialize file

    if(outputfile.is_open()) {
        /* check if file is open, else exit */
        for(int i=0; i<positionSize; i++) {
            /* loop through results and write to file */
            outputfile << xProbabilityPosition[i] << '\n';
        } //end for write
    } else {
        std::cout << "error opening file" << std::endl;
        exit(EXIT_FAILURE);
    } //end if is_open

    outputfile.close(); //close file

    return;
} //end function output
