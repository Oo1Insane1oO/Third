#ifndef WALKER_H
#define WALKER_H

class Walker {
    public:
        double walkProbability;
        int numberWalkers;
        int maxTrials;
        
        double dt;
        double l_0;
        double minDistance;
        double maxDistance;
        int positionSize;

        std::vector<double> xProbabilityPosition;
        std::vector<double> yProbabilityPosition;
        std::vector<double> zProbabilityPosition;
        
        RandomNumber *RN;

        Walker(int, double, double, double, double, double, RandomNumber*);
        
        void output();
};
#endif //WALKER_H
