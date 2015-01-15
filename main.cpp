#include "walker.h" //walker
#include "random_walk.h" //Monte Carlo sampling
#include "random_number.h" //random generator
#include <cstdlib> //atoi, atof
#include <iostream> //cout, endl
#include <chrono> // timer(high_precision_clock)

int main(int argc, const char** argv) {
    /* main function */
   
    if(argc < 5) {
        std::cout << "USAGE: ./main 'numberWalker' 'time-step' 'total time' 'outputfile name' 'usage'" 
            << std::endl;
    } //end if less

    //aquire parameters as args
    int numberWalkers = atoi(argv[1]); //number of walkers
    double dt = atof(argv[2]); //time-step
    double totalTime = atof(argv[3]); //step-length
    const char *filename = argv[4]; //name of outputfile
    
    double walkProbability = 0.5; //jump probability
    int maxDistance = 1; int minDistance = 0; //max- and min distance

    //initialize Walker
    Walker wlk = Walker(numberWalkers, dt, maxDistance, minDistance, walkProbability, totalTime);

    int usage = atoi(argv[5]);
    RandomWalk RW = RandomWalk(&wlk, usage); //set randomWalk
   
    if(usage == 1) {
        auto start = std::chrono::high_resolution_clock::now(); //start clock
        
        RW.mcSampling2(); //start 2D sampling
        
        auto finish = std::chrono::high_resolution_clock::now(); //end clock 
        std::cout << "time sampling 2D: "
            << std::chrono::duration_cast<std::chrono::seconds>(finish - start).count() << "s" 
            << std::endl; //print time
        std::cout << "\n"; //space

        wlk.output2(filename); //output 1D to file
    } else if(usage == 0) {
        RW.mcSampling(); //start sampling 1D
        wlk.output(filename); //output 1D to file
    } else {
        std::cout << "specify usage" << std::endl;
    } //end if usage

    return 0;
} //end function main
