#ifndef SPLL_H
#define SPLL_H

#define float32_t float
#include "SecondOrder_IIR.h"
#include "park.h"

#define PI 3.1415926535f

#define LIMIT(value, min, max) (((value) > (max)) ? (max) : (((value) < (min)) ? (min) : (value)))
#define SUM_JUNC(plus, minus)   ((plus) - (minus))

static inline float pll_angle_wrap(float angle) {
    if (angle > 2*PI) {
        angle -= 2*PI;
    } else if (angle < 0.0f) {
        angle += 2*PI;
    }
    return angle;
}

typedef struct{
    
}SPLL_structure;


#endif //SPLL_H
