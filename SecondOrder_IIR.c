#include "SecondOrder_IIR.h"

/*
Y(z)/X(z) = [b0_alpha*z^0 + b1_alpha*z^(-1) + b2_alpha*z^(-2)]/[a0_alpha*z^0 + a1_alpha*z^(-1) + a2_alpha*z^(-2)]
*/


//Init Filter coefficients which come from MATLAB's c2d

void SecondOrder_IIR_INIT(SecondOrder_IIR_structure* structure, float32_t* a_vector, float32_t* b_vector)
{
    structure->a0 = a_vector[0];
    structure->a1 = a_vector[1];
    structure->b0 = b_vector[0];
    structure->b1 = b_vector[1];

    structure->x_n = 0.0f;
    structure->x_n_1 = 0.0f;
    structure->y_n = 0.0f;
    structure->y_n_1 = 0.0f;

}

float32_t SecondOrder_IIR_PROCESS(SecondOrder_IIR_structure* structure, float32_t input_signal)
{
    SecondOrder_IIR_structure* s = structure;
    
    s->x_n = input_signal;

    //Computing Logic
    float32_t inverse_of_a0 = 1.0f/s->a0;

    float32_t temp;
    temp = (s->b0)*(s->x_n)+(s->b1)*(s->x_n_1)-(s->a1)*(s->y_n_1);
    s->y_n = temp * inverse_of_a0;


    //Updating Logic
    s->x_n_1 = s->x_n;
    s->y_n_1 = s->y_n;


    return s->y_n;
}



