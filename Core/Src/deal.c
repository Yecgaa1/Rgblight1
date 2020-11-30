//
// Created by xtx on 2020/11/25.
//

#include <string.h>
#include <stdio.h>
#include "deal.h"
#include "usart.h"

extern float Fspeed;
extern float tmultiple;

void dealfirst(char *a) {
    /*
    if (sizeof(a) == 4) {
        if (strcmp(a, "AF") == 0)//forward
            Fspeed = 1.0;
            //HAL_UART_Transmit(&huart1, a, sizeof(a), 0xFFFF);
        else if (strcmp(a, "BF") == 0)//backward
            Fspeed = -1.0;
        else if (strcmp(a, "CF") == 0)//turn left
            tmultiple = 0.5;
        else if (strcmp(a, "DF") == 0)//turn right
            tmultiple = 1.5;
        else if (strcmp(a, "LO") == 0)//light on
            tmultiple = 1.5;
        else if (strcmp(a, "LF") == 0)//light off
            tmultiple = 1.5;
    }
    else if(sizeof(a) == 8)
    {
        char dest1[2] = {""};
        strncpy(dest1, a, 2);
        char dest2[2] = {""};
        strncpy(dest2, a+2, 2);
        char dest3[2] = {""};
        strncpy(dest3, a+4, 2);
        int i=0;
        sscanf(dest1, "%x", &i);
        htim2.Instance->CCR2 =(i/255)*4999;
        sscanf(dest2, "%x", &i);
        htim2.Instance->CCR1 =(i/255)*4999;
        sscanf(dest3, "%x", &i);
        htim2.Instance->CCR3 =(i/255)*4999;


    }
    else
    {
        char i[80];
        strcat(a,"Out of image!");
        HAL_UART_Transmit(&huart1, i, sizeof(i), 0xFFFF);

    }
    //HAL_Delay(10);
    //HAL_Delay(1);
     */
    if(sizeof(a) == 8)
    {
        char dest1[2] = {""};
        strncpy(dest1, a, 2);
        char dest2[2] = {""};
        strncpy(dest2, a+2, 2);
        char dest3[2] = {""};
        strncpy(dest3, a+4, 2);
        int i=0;
        sscanf(dest1, "%x", &i);
        htim2.Instance->CCR1 =(0.02392*i+0.545)*999;//red
        sscanf(dest2, "%x", &i);
        if(i>128)
            i=127;
        htim2.Instance->CCR2 =(0.0242*i+0.969)*999;//green
        sscanf(dest3, "%x", &i);
        if(i>128)
            i=127;
        htim2.Instance->CCR3 =(0.0242*i+0.969)*999;//blue


    }
}
void work()
{
    if(Fspeed>0)
    {

        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET);
        CCR1Change(Fspeed);//left
        CCR2Change(Fspeed);//right
        Fspeed-=0.2;
    }
    else if(Fspeed<0)
    {
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET);
        CCR1Change(-Fspeed);
        CCR2Change(-Fspeed);
        Fspeed+=0.2;
    }
    if(tmultiple<1)//turn left
    {
        CCR1Change(Fspeed*tmultiple);
        tmultiple+=0.1;
        //CCR2Change(Fspeed/tmultiple);
    }
    else if(tmultiple>1)//turn right
    {
        //CCR1Change(Fspeed/tmultiple);
        CCR2Change(Fspeed/tmultiple);
        tmultiple-=0.1;
    }
}
void CCR1Change(float i)//left
{
    htim2.Instance->CCR1 =i*2799;
}
void CCR2Change(float i)//right
{
    htim2.Instance->CCR2 =i*2799;
}