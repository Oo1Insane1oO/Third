#ifndef WALKER_H
#define WALKER_H

#include <vector>

class Walker {
    public:
        double walkProbability;
        int numberWalkers;
        int maxTrials;
        
        double dt;
        double l_0;
        int minDistance;
        int maxDistance;
        int positionSize;

        //std::vector<std::vector<double> > xyProbabilityPosition;
        std::vector<double> xProbabilityPosition;

        Walker(int, double, int, int, double, double);
        
        void output(const char*);
};

#endif //WALKER_H
