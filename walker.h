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

        std::vector<double> xProbabilityPosition;
        std::vector<std::vector<double> > xyProbabilityPosition;

        Walker(int, double, int, int, double, double);
       
        void normalizer2();
        void output(const char*);
        void output2(const char*);
};

#endif //WALKER_H
