#if !defined(__ENCODER__H__)
#define __ENCODER__H__

#include "main.h"
#include "can_setup.h"

//#include "stm32f1xx_hal.h"

//event ID
#define EVENT 0x18FF0FF2
#define DATA 0x18FF11F2
#define CONTROL 0x18EFF221
//SCREEN DEFINES
#define HOME 10
#define WINDOWS 9  
//WINDOW SWITCH DEFINES
#define FRONT_WINDOWS 0x8001
#define ALL_WINDOWS 0X8004
#define LF_WINDOW 0x8008
#define RF_WINDOW 0x8002  
//SWIPE DEFINES
#define SWIPE_DOWN 0x82
#define SWIPE_UP 0x81
#define SWIPE_LEFT 0x83
#define SWIPE_RIGHT 0x84
//TAP DEFINES 
#define TAP_ANY 0X8000  // >= TAP_ANY 
//TURN DEFINES




//#define  NULL 0x00

typedef struct te
{
    // Set Values
    uint8_t currentScreen; // 0x00 Screen 0, 0x01 Screen 1, etc
    uint8_t knob;          // = 0x00;
    uint16_t tap;          // = 0x00;
    uint8_t swipe;         // = 0x00;
    uint8_t valueId;       // 0x00 no values, 0x01 value 1, etc
    uint16_t currentVal;
    uint8_t dispCode;
    uint8_t activeId;
} encoder_t;

encoder_t te;

void setWidget(uint8_t screenNum, uint8_t valueId, uint16_t currentVal);
void setBacklight(uint8_t level);
void getEvent(CAN_RxHeaderTypeDef *rxMsg, uint8_t *canRx);
void getData(CAN_RxHeaderTypeDef *rxMsg, uint8_t *canRx);

#endif // __ENCODER__H__
