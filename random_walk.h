#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include "walker.h"
#include "random_number.h"

class RandomWalk {
    public:
        RandomNumber *RN;
        Walker *wlk;

        int usage;

        RandomWalk(RandomNumber*, Walker*, int);
        
        void initialize();
        void mcSampling();
        void mcSampling2();
};

#endif //RANDOM_WALK_H
