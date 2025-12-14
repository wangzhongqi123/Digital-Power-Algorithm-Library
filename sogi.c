#include "sogi.h"
/*
Y(z)/X(z) = [b0_alpha*z^0 + b1_alpha*z^(-1) + b2_alpha*z^(-2)]/[a0_alpha*z^0 + a1_alpha*z^(-1) + a2_alpha*z^(-2)]
*/


//Init Filter coefficients which come from MATLAB's c2d
float32_t a_vector_alpha[3] = {0.0f, 0.0f, 0.0f};
float32_t b_vector_alpha[3] = {0.0f, 0.0f, 0.0f};
float32_t a_vector_beta[3] = {0.0f, 0.0f, 0.0f};
float32_t b_vector_beta[3] = {0.0f, 0.0f, 0.0f};

void SOGI_INIT(SOGI_structure* sogi_structure, float32_t* a_vector_alpha, float32_t* b_vector_alpha,
                                    float32_t* a_vector_beta, float32_t* b_vector_beta)
{
    //Init Alpha-axis's Filter coefficients
    sogi_structure->a0_alpha = a_vector_alpha[0];
    sogi_structure->a1_alpha = a_vector_alpha[1];
    sogi_structure->a2_alpha = a_vector_alpha[2];
    sogi_structure->b0_alpha = b_vector_alpha[0];
    sogi_structure->b1_alpha = b_vector_alpha[1];
    sogi_structure->b2_alpha = b_vector_alpha[2];

    //Init Beta-axis's Filter coefficients
    sogi_structure->a0_beta = a_vector_beta[0];
    sogi_structure->a1_beta = a_vector_beta[1];
    sogi_structure->a2_beta = a_vector_beta[2];
    sogi_structure->b0_beta = b_vector_beta[0];
    sogi_structure->b1_beta = b_vector_beta[1];
    sogi_structure->b2_beta = b_vector_beta[2];

    //Init Alpha-axis's computing data
    sogi_structure->x_n_alpha = 0.0f;
    sogi_structure->x_n_1_alpha = 0.0f;
    sogi_structure->x_n_2_alpha = 0.0f;
    sogi_structure->y_n_alpha = 0.0f;
    sogi_structure->y_n_1_alpha = 0.0f;
    sogi_structure->y_n_2_alpha = 0.0f;

    //Init Beta-axis's computing data
    sogi_structure->x_n_beta = 0.0f;
    sogi_structure->x_n_1_beta = 0.0f;
    sogi_structure->x_n_2_beta = 0.0f;
    sogi_structure->y_n_beta = 0.0f;
    sogi_structure->y_n_1_beta = 0.0f;
    sogi_structure->y_n_2_beta = 0.0f;

    //Init SOGI's output data
    sogi_structure->output[0] = 0.0f;
    sogi_structure->output[1] = 0.0f;
}

volatile float32_t* SOGI_PROCESS(SOGI_structure* sogi_structure, float32_t input_signal)
{
    SOGI_structure* s = sogi_structure;
    
    s->x_n_alpha = input_signal;
    s->x_n_beta = input_signal;

    //Computing Logic
    float32_t inverse_of_a0_alpha = 1.0f/s->a0_alpha;
    float32_t inverse_of_a0_beta = 1.0f/s->a0_beta;

    float32_t temp_alpha, temp_beta;
    temp_alpha = (s->b0_alpha)*(s->x_n_alpha)+(s->b1_alpha)*(s->x_n_1_alpha)+(s->b2_alpha)*(s->x_n_2_alpha)+
                    -(s->a1_alpha)*(s->y_n_1_alpha)-(s->a2_alpha)*(s->y_n_2_alpha);
    temp_beta = (s->b0_beta)*(s->x_n_beta)+(s->b1_beta)*(s->x_n_1_beta)+(s->b2_beta)*(s->x_n_2_beta)+
                    -(s->a1_beta)*(s->y_n_1_beta)-(s->a2_beta)*(s->y_n_2_beta);
    s->y_n_alpha = temp_alpha * inverse_of_a0_alpha;
    s->y_n_beta = temp_beta * inverse_of_a0_beta;

    s->output[0] = s->y_n_alpha;    s->output[1] = s->y_n_beta;

    //Updating Logic
    s->x_n_2_alpha = s->x_n_1_alpha;
    s->x_n_1_alpha = s->x_n_alpha;
    s->y_n_2_alpha = s->y_n_1_alpha;
    s->y_n_1_alpha = s->y_n_alpha;

    s->x_n_2_beta = s->x_n_1_beta;
    s->x_n_1_beta = s->x_n_beta;
    s->y_n_2_beta = s->y_n_1_beta;
    s->y_n_1_beta = s->y_n_beta;

    return &((s->output)[0]);
}

