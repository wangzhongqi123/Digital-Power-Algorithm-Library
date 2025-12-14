#ifndef SOGI_H
#define SOGI_H
//其实就是三阶IIR滤波器
//Discretized coefficients generated based on MATLAB's c2d

#define float32_t float
/*
Y(z)/X(z) = [b0_alpha*z^0 + b1_alpha*z^(-1) + b2_alpha*z^(-2)]/[a0_alpha*z^0 + a1_alpha*z^(-1) + a2_alpha*z^(-2)]
*/
typedef struct {
    //alpha-axis data
    float32_t b0_alpha, b1_alpha, b2_alpha;
    float32_t a0_alpha, a1_alpha, a2_alpha;
    volatile float32_t x_n_alpha, x_n_1_alpha, x_n_2_alpha;
    volatile float32_t y_n_alpha, y_n_1_alpha, y_n_2_alpha;
    //beta-axis data
    float32_t b0_beta, b1_beta, b2_beta;
    float32_t a0_beta, a1_beta, a2_beta;
    volatile float32_t x_n_beta, x_n_1_beta, x_n_2_beta;
    volatile float32_t y_n_beta, y_n_1_beta, y_n_2_beta;
    //output[0]==>output_alpha  output[1]==>output_beta
    volatile float32_t output[2];
}SOGI_structure;

//a0 a1 a2
extern float32_t a_vector_alpha[3];
extern float32_t a_vector_beta[3];
//b0 b1 b2
extern float32_t b_vector_alpha[3];
extern float32_t b_vector_beta[3];

void SOGI_INIT(SOGI_structure* sogi_structure, float32_t* a_vector_alpha, float32_t* b_vector_alpha,
                                    float32_t* a_vector_beta, float32_t* b_vector_beta);


volatile float32_t* SOGI_PROCESS(SOGI_structure* sogi_structure, float32_t input_signal);

#endif //SOGI_H

