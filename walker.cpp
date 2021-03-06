#include "walker.h" //header file
#include <cmath> //sqrt, fabs
#include <cstdio> //fopen, fprintf, fclose
#include <iostream> //cout, endl
#include <cstdlib> //exit
#include <algorithm> //max_element

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
} // end constructor

void Walker::normalizer2() {
    /* function for normalizing columns */

    // make a copy 
    xyProbabilityPositionTempCopy.resize(positionSize, std::vector<double>(positionSize) );
    #pragma omp parallel for
    for(int i=0; i<positionSize ;i++) {
        /* assign values to copy vector */
        xyProbabilityPositionTempCopy[i] = xyProbabilityPosition[i];
    } // end for i<positionSize

    // normalize original
    double eps = 1e-10;
    double maxValue;
    for (int i=0; i<positionSize; i++) {
        maxValue = *std::max_element(xyProbabilityPosition[i].begin(), xyProbabilityPosition[i].end() );
        if (maxValue <= eps) {
            /* ignore zero (assume all values are positive) */
            continue;
        } // end if maxValue
        for (int j=0; j<positionSize ;j++) {
            xyProbabilityPosition[i][j] = xyProbabilityPosition[i][j] / maxValue;
        } // end for j
    } // end for i positionSize

    return;
} // end function normalizer2

void Walker::output(const char *filename) {
    /* function, output results to file */

    FILE *outputfile = fopen(filename, "w");
    if(outputfile) {
        /* check if file is open, else exit */
        #pragma omp parallel for
        for(int i=0; i<positionSize; i++) {
            /* loop through results and write to file */
            std::fprintf(outputfile, "%15f %15f \n", i*l_0, xProbabilityPosition[i]);
        } //end for write
    } else {
        std::cout << "error opening file" << std::endl;
        exit(EXIT_FAILURE);
    } //end if is_open

    fclose(outputfile); //close file

    return;
} //end function output

void Walker::output2(const char *filename) {
    /* function, output 2D results */

    Walker::normalizer2(); // normalize before output

    FILE *outputfile = fopen(filename, "w");
    std::fprintf(outputfile, "%i\n", positionSize);
    if(outputfile) {
        /* check if file is open, else exit */
        for(int i=0; i<positionSize; i++) {
            for(int j=0; j<positionSize; j++) {
                std::fprintf(outputfile, "%15f\n", xyProbabilityPosition[i][j]);
            } //end for i
        } //end for j
    } //end if outputfile

    std::fclose(outputfile); //close file
    for (int i = 0; i < positionSize; i++) {
        /* reset to unnormalized */
        xyProbabilityPosition[i] = xyProbabilityPositionTempCopy[i];
    }

    xyProbabilityPositionTempCopy.clear(); // clear temp vector

    return;
} //end function output2
