#include "park.h"

void PARK_INIT(park_structure* structure)
{
    structure->input_alpha = 0.0f;
    structure->input_beta = 0.0f;
    structure->input_theta = 0.0f;
    structure->output_d = 0.0f;
    structure->output_q = 0.0f;
}

void PARK_PROCESS(park_structure* structure, float32_t input_alpha, 
                      float32_t input_beta, float32_t input_theta)
{
    structure->input_alpha = input_alpha;
    structure->input_beta = input_beta;
    structure->input_theta = input_theta;
    structure->output_q = -(structure->input_alpha) * arm_sin_f32(structure->input_theta) +
            (structure->input_beta) * arm_cos_f32(structure->input_theta);
    structure->output_d = (structure->input_alpha) * arm_cos_f32(structure->input_theta) +
            (structure->input_beta) * arm_sin_f32(structure->input_theta);
}

