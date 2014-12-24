#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include "walker.h"
#include "random_number.h"

class RandomWalk {
    public:
        //RandomNumber *RN;
        Walker *wlk;
        RandomNumber RN;

        int usage;

        RandomWalk(Walker*, int);
        
        void initialize();
        void mcSampling();
        void mcSampling2();
};

#endif //RANDOM_WALK_H
