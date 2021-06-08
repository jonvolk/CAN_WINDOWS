#include "encoder.h"

void setWidget(uint8_t screenNum, uint8_t valueId, uint16_t currentVal)
{

    txMsg.ExtId = CONTROL;
    txMsg.DLC = 7;
    canTx[0] = 0x11; //Force Widget Data
    canTx[1] = screenNum;
    canTx[2] = valueId;
    canTx[3] = currentVal & 0xFF;
    canTx[4] = currentVal >> 8;
    canTx[5] = 0x00; //Display Code placeholder
    canTx[6] = 0x00; // Value Active ID  0x00-not used, 0x01 Value 1 currently active
    te.currentScreen = screenNum;
    txExt(&txMsgExt, canTx);
}

void setBacklight(uint8_t level)
{
    txMsg.ExtId = CONTROL;
    txMsg.DLC = 1;
    canTx[0] = 0x80; //Screen brightness
    canTx[1] = 0xFF;
    canTx[2] = level; // value 0-100
    canTx[3] = 0xFF;
    canTx[4] = 0xFF;
    canTx[5] = 0xFF;
    canTx[6] = 0xFF;
    canTx[7] = 0xFF;
    txExt(&txMsgExt, canTx);
}

void getEvent(CAN_RxHeaderTypeDef *rxMsg, uint8_t *canRx)
{

    if (rxMsg->ExtId == EVENT)
    {
        te.currentScreen = canRx[0];
        // canRx[1] Reserved
        // canRx[2] 0x01 Events
        te.knob = canRx[3];
        te.tap = (canRx[4]) + (canRx[5] << 8);
        te.swipe = canRx[6];
    }
}

void getData(CAN_RxHeaderTypeDef *rxMsg, uint8_t *canRx)
{
    if (rxMsg->ExtId == DATA)
    {
        te.currentScreen = canRx[0];
        // canRx[1] Reserved
        te.valueId = canRx[2];
        te.currentVal = canRx[3] + (canRx[4] << 8);
        te.dispCode = canRx[5];
        te.activeId = canRx[6];
    }
}