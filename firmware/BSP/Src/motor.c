#include "motor.h"
#include "board.h"
#include <stdlib.h> // 用于 abs()

// 初始化电机
void Motor_Init(void)
{
    // 1. 使能 TB6612（STBY 拉高）
    HAL_GPIO_WritePin(MOTOR_STBY_GPIO, MOTOR_STBY_PIN, GPIO_PIN_SET);

    // 2. 初始状态：停止
    HAL_GPIO_WritePin(MOTOR_L_IN1_GPIO, MOTOR_L_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_L_IN2_GPIO, MOTOR_L_IN2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_R_IN1_GPIO, MOTOR_R_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_R_IN2_GPIO, MOTOR_R_IN2_PIN, GPIO_PIN_RESET);
    
    // 3. 启动 PWM 输出
    HAL_TIM_PWM_Start(&MOTOR_L_PWM_TIM, MOTOR_L_PWM_CH);
    HAL_TIM_PWM_Start(&MOTOR_R_PWM_TIM, MOTOR_R_PWM_CH);
}

// 设置电机速度
void Motor_SetSpeed(uint8_t motor_id, int16_t speed)
{
    // 1. 限幅，防止超过 PWM 最大值（我们设定的 Counter Period 是 999）
    if (speed > 1000)  speed = 1000;
    if (speed < -1000) speed = -1000;

    // 2. 根据速度正负，设置方向和 PWM 占空比
    if (motor_id == MOTOR_LEFT)
    {
        if (speed > 0) // 正转
        {
            HAL_GPIO_WritePin(MOTOR_L_IN1_GPIO, MOTOR_L_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_L_IN2_GPIO, MOTOR_L_IN2_PIN, GPIO_PIN_SET);
        }
        else if (speed < 0) // 反转
        {
            HAL_GPIO_WritePin(MOTOR_L_IN1_GPIO, MOTOR_L_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_L_IN2_GPIO, MOTOR_L_IN2_PIN, GPIO_PIN_RESET);
        }
        else // 停止
        {
            HAL_GPIO_WritePin(MOTOR_L_IN1_GPIO, MOTOR_L_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_L_IN2_GPIO, MOTOR_L_IN2_PIN, GPIO_PIN_RESET);
        }
        // 设置 PWM 占空比（取绝对值）
        __HAL_TIM_SET_COMPARE(&MOTOR_L_PWM_TIM, MOTOR_L_PWM_CH, abs(speed));
    }
    else if (motor_id == MOTOR_RIGHT)
    {
        if (speed > 0) // 正转
        {
            HAL_GPIO_WritePin(MOTOR_R_IN1_GPIO, MOTOR_R_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_R_IN2_GPIO, MOTOR_R_IN2_PIN, GPIO_PIN_SET);
        }
        else if (speed < 0) // 反转
        {
            HAL_GPIO_WritePin(MOTOR_R_IN1_GPIO, MOTOR_R_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_R_IN2_GPIO, MOTOR_R_IN2_PIN, GPIO_PIN_RESET);
        }
        else // 停止
        {
            HAL_GPIO_WritePin(MOTOR_R_IN1_GPIO, MOTOR_R_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_R_IN2_GPIO, MOTOR_R_IN2_PIN, GPIO_PIN_RESET);
        }
        // 设置 PWM 占空比
        __HAL_TIM_SET_COMPARE(&MOTOR_R_PWM_TIM, MOTOR_R_PWM_CH, abs(speed));
    }
}

// 刹车（急停）
void Motor_Brake(uint8_t motor_id)
{
    if (motor_id == MOTOR_LEFT)
    {
        HAL_GPIO_WritePin(MOTOR_L_IN1_GPIO, MOTOR_L_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_L_IN2_GPIO, MOTOR_L_IN2_PIN, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&MOTOR_L_PWM_TIM, MOTOR_L_PWM_CH, 0);
    }
    else if (motor_id == MOTOR_RIGHT)
    {
        HAL_GPIO_WritePin(MOTOR_R_IN1_GPIO, MOTOR_R_IN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR_R_IN2_GPIO, MOTOR_R_IN2_PIN, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&MOTOR_R_PWM_TIM, MOTOR_R_PWM_CH, 0);
    }
}

// 停止（滑行）
void Motor_Stop(uint8_t motor_id)
{
    Motor_SetSpeed(motor_id, 0);
}