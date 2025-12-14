#ifndef PI_COMPENSATOR_H
#define PI_COMPENSATOR_H

//可以实现各种二阶IIR滤波器,还有各种二阶补偿器PI,PD等等
//Discretized coefficients generated based on MATLAB's c2d

#define float32_t float
/*
Y(z)/X(z) = [b0_alpha*z^0 + b1_alpha*z^(-1) + b2_alpha*z^(-2)]/[a0_alpha*z^0 + a1_alpha*z^(-1) + a2_alpha*z^(-2)]
*/
typedef struct {
    float32_t b0, b1;
    float32_t a0, a1;
    volatile float32_t x_n, x_n_1;
    volatile float32_t y_n, y_n_1;
	//输出就是y_n
}SecondOrder_IIR_structure;

//a0 a1
extern float32_t a_vector[2];
//b0 b1
extern float32_t b_vector[2];

void SecondOrder_IIR_INIT(SecondOrder_IIR_structure* structure, float32_t* a_vector, float32_t* b_vector);

float32_t SecondOrder_IIR_PROCESS(SecondOrder_IIR_structure* structure, float32_t input_signal);


#endif //PI_COMPENSATOR_H
