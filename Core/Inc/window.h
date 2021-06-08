#if !defined(__WINDOW_H)
#define __WINDOW_H


#include "encoder.h"

#define MAX_WINDOWS 4
#define SENSE_LIMIT 1590 // 12 bit ADC, maxl value 4095, WAS 1590
#define MAX_COUNT 6


uint32_t motorCurrent[8];
uint8_t stageState;
uint8_t stageNextState;


typedef struct windowHandle
{
    uint8_t state;
    uint8_t event;
    uint16_t sense_U;
    uint16_t sense_D;
    uint16_t senseCount_U;
    uint16_t senseCount_D;

} windowHandle_t;
windowHandle_t window[4];

typedef enum tag
{
    lf,
    lr, 
    rf, 
    rr,
} tag_t;

typedef enum states
{
    idle,
    up,
    down,
} states_t;

typedef enum staging
{
    ready,
    all_down,
    all_up,
    fronts,
    rears,
} staging_t;



void windowInit(void); //initialize values to zero
void eventHandler(void); 
void windowHandler(void);
void stateHandler(void);
void motorHandler(windowHandle_t *window, int instance);
void staging(void);

#endif // __WINDOW_H
