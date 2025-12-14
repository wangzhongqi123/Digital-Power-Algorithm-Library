#ifndef PARK_H
#define PARK_H

#define float32_t float 

typedef struct{
    volatile float32_t input_alpha;
    volatile float32_t input_beta;
    volatile float32_t input_theta;
    volatile float32_t output_d;
    volatile float32_t output_q;
}park_structure;

void PARK_INIT(park_structure* structure);

void PARK_PROCESS(park_structure* structure, float32_t input_alpha, 
                      float32_t input_beta, float32_t input_theta);




#endif //PARK_H
