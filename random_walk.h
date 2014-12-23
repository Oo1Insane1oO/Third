#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include "walker.h"
#include "random_number.h"

class RandomWalk {
    public:
        int n;
        RandomNumber *RN;
        Walker *wlk;

        RandomWalk(RandomNumber*, Walker*);
        
        void initialize();
        void mcSampling();
};

#endif //RANDOM_WALK_H
