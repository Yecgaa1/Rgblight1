//
// Created by xtx on 2020/11/25.
//

#ifndef RGBLIGHT_DEAL_H
#define RGBLIGHT_DEAL_H



void dealfirst();
#include "stm32f1xx_hal.h"
#include "main.h"
#include "tim.h"
extern UART_HandleTypeDef huart1;
void dealfirst(char *a);
void CCR1Change(float i);
void CCR2Change(float i);
void work();

#endif //RGBLIGHT_DEAL_H
