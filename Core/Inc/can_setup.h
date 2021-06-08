
#ifndef __CAN_SETUP_H
#define __CAN_SETUP_H

#include "stm32f1xx_hal.h"
#include "main.h"
#include "stdio.h"
#include "encoder.h"

CAN_HandleTypeDef hcan;
CAN_FilterTypeDef data;      //= {0};  //CAN Bus Filter
CAN_FilterTypeDef event;
CAN_RxHeaderTypeDef rxMsg; //CAN Bus Transmit Header
CAN_TxHeaderTypeDef txMsg; //CAN Bus Receive Header
CAN_TxHeaderTypeDef txMsgExt;


uint8_t canRx[8]; //= {0,0,0,0,0,0,0,0};  //CAN Bus Receive Buffer

uint32_t canMailbox; //CAN Bus Mail box variable

uint8_t canTx[8];

int txCycle;  //CAN TX counter


void canSettings(void);
void tx(CAN_TxHeaderTypeDef *txMsg, uint8_t *canTx);
void txExt(CAN_TxHeaderTypeDef *txMsgExt, uint8_t *canTx);

#endif
