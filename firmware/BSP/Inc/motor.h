#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

// 电机编号
#define MOTOR_LEFT  0
#define MOTOR_RIGHT 1

// 初始化电机
void Motor_Init(void);

// 设置电机速度
// motor_id: MOTOR_LEFT 或 MOTOR_RIGHT
// speed: -1000 ~ 1000（正数正转，负数反转，0停止）
void Motor_SetSpeed(uint8_t motor_id, int16_t speed);

// 紧急刹车
void Motor_Brake(uint8_t motor_id);

// 停止（滑行）
void Motor_Stop(uint8_t motor_id);

#endif