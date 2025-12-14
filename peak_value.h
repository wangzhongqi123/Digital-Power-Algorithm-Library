#ifndef PEAK_VALUE_REFACTORING_H
#define PEAK_VALUE_REFACTORING_H

#define float32_t float
#define uint8_t char

typedef struct {
    volatile float32_t current_value;
    volatile float32_t previous_value;
    volatile float32_t prev_prev_value;
    volatile float32_t active_peak;
    volatile float32_t tracking_peak;
    volatile uint8_t rise_counter;
    volatile uint8_t fall_counter;
    volatile uint8_t start_switching;
    volatile uint8_t start_tracking;
    uint8_t RISE_CONFIRM_COUNT;
    uint8_t FALL_CONFIRM_COUNT;
    float32_t SLOPE_THRESHOLD;
    float32_t MAX_PEAK_DELTA;
}PEAK_DETECTION_structure;

void INIT_PEAK_DETECTION(PEAK_DETECTION_structure* structure, uint8_t FALL_CONFIRM_COUNT, 
    uint8_t RISE_CONFIRM_COUNT, float32_t SLOPE_THRESHOLD, float32_t MAX_PEAK_DELTA);

float32_t PEAK_DETECTION_PROCESS(PEAK_DETECTION_structure* structure, float32_t input_value);

#endif //PEAK_VALUE_REFACTORING_H

