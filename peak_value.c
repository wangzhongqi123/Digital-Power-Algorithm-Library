#include "peak_value.h"
void INIT_PEAK_DETECTION(PEAK_DETECTION_structure* structure, uint8_t FALL_CONFIRM_COUNT, 
    uint8_t RISE_CONFIRM_COUNT, float32_t SLOPE_THRESHOLD, float32_t MAX_PEAK_DELTA)
{
    structure->current_value = 0.0f;
    structure->previous_value = 0.0f;
    structure->prev_prev_value = 0.0f;

    structure->active_peak = 0.0f;
    structure->tracking_peak = 0.0f;

    structure->rise_counter = 0;
    structure->fall_counter = 0;

    structure->start_switching = 1;
    structure->start_tracking = 0;

    structure->FALL_CONFIRM_COUNT = FALL_CONFIRM_COUNT;
    structure->RISE_CONFIRM_COUNT = RISE_CONFIRM_COUNT;
    structure->SLOPE_THRESHOLD = SLOPE_THRESHOLD;
    structure->MAX_PEAK_DELTA = MAX_PEAK_DELTA;
}
    
float32_t PEAK_DETECTION_PROCESS(PEAK_DETECTION_structure* structure, float32_t input_value)
{
    structure->current_value = input_value;
    float slope = structure->current_value - structure->previous_value;

    if(structure->rise_counter < structure->RISE_CONFIRM_COUNT && slope > structure->SLOPE_THRESHOLD) {
        structure->rise_counter++;	structure->fall_counter = 0;
    }else if(structure->fall_counter < structure->FALL_CONFIRM_COUNT && slope < -(structure->SLOPE_THRESHOLD)){
        structure->fall_counter++;	structure->rise_counter = 0;
    }

    if(structure->fall_counter == structure->FALL_CONFIRM_COUNT && structure->start_switching != 1){
        structure->start_switching = 1;
        structure->start_tracking = 0;

        float delta = structure->tracking_peak - structure->active_peak;

        //就是单纯两个峰值相减,如果大于最大差值,则不变
        if ((delta >= 0 ? delta : -delta) <= structure->MAX_PEAK_DELTA) {
            structure->active_peak = structure->tracking_peak;
        }
        // 否则：什么都不做，保持 structure->active_peak 不变
    }
    if(structure->start_switching == 1 && structure->start_tracking != 1){
        if(structure->rise_counter == structure->RISE_CONFIRM_COUNT){
            structure->start_tracking = 1;	structure->start_switching = 0;
        }
    }
    if(structure->start_tracking == 1 && structure->start_switching != 1){
        //if(structure->current_value >= structure->previous_value){
            //structure->tracking_peak = structure->current_value;
        //}
        //更新:从原先的两数相比变成三数相比 稳定性精准性更好
        if (structure->previous_value > structure->prev_prev_value && 
            structure->previous_value > structure->current_value) {
            structure->tracking_peak = structure->previous_value;
        }
    }

    structure->prev_prev_value = structure->previous_value;
    structure->previous_value = structure->current_value;
    return structure->active_peak;
}

