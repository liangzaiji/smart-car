#ifndef __BOARD_H
#define __BOARD_H

#include "main.h"

#define MOTOR_L_PWM_TIM        htim1
#define MOTOR_L_PWM_CH         TIM_CHANNEL_1
#define MOTOR_R_PWM_TIM        htim1
#define MOTOR_R_PWM_CH         TIM_CHANNEL_4

#define MOTOR_L_IN1_GPIO       GPIOB
#define MOTOR_L_IN1_PIN        GPIO_PIN_0
#define MOTOR_L_IN2_GPIO       GPIOB
#define MOTOR_L_IN2_PIN        GPIO_PIN_1
#define MOTOR_R_IN1_GPIO       GPIOB
#define MOTOR_R_IN1_PIN        GPIO_PIN_12
#define MOTOR_R_IN2_GPIO       GPIOB
#define MOTOR_R_IN2_PIN        GPIO_PIN_13
#define MOTOR_STBY_GPIO        GPIOB
#define MOTOR_STBY_PIN         GPIO_PIN_14

#define ENCODER_L_TIM          htim2
#define ENCODER_R_TIM          htim4

#define GRAY_ADC_HANDLE        hadc1
#define GRAY_CH_NUM            5

#define VISION_UART            huart3
#define DEBUG_UART             huart1

#define OLED_SCL_GPIO          GPIOB
#define OLED_SCL_PIN           GPIO_PIN_8
#define OLED_SDA_GPIO          GPIOB
#define OLED_SDA_PIN           GPIO_PIN_9

#define KEY_GPIO               GPIOB
#define KEY_PIN                GPIO_PIN_15
#define LED_GPIO               GPIOC
#define LED_PIN                GPIO_PIN_13
#define BEEP_GPIO              GPIOC
#define BEEP_PIN               GPIO_PIN_15

#endif