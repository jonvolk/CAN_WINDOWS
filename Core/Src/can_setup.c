#include <can_setup.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

    extern CAN_RxHeaderTypeDef rxMsg;
    extern uint8_t canRx[8];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxMsg, canRx) != HAL_OK)
    {
        Error_Handler();
    }

    getEvent(&rxMsg, canRx);
    getData(&rxMsg, canRx);

    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void canSettings(void)
{

    txMsg.IDE = CAN_ID_STD;
    txMsg.RTR = CAN_RTR_DATA;
    txMsg.TransmitGlobalTime = DISABLE;

    // EXAMPLE FROM https://community.st.com/s/question/0D50X0000APYsgG/can-setup-and-filters-using-hal
    data.FilterBank = 0;
    data.FilterMode = CAN_FILTERMODE_IDLIST; //CAN_FILTERMODE_IDLIST;
    data.FilterScale = CAN_FILTERSCALE_32BIT;
    data.FilterIdLow = ((DATA <<3) & 0xFFF8) | 4; // THIS is the tricky part  //0xffff;
    data.FilterIdHigh = (DATA >>13) & 0xFFFF; // THIS is the tricky part  //0x1fff;
    data.FilterMaskIdLow = ((EVENT <<3) & 0xFFF8) | 4; // THIS is the tricky part//0xffff;
    data.FilterMaskIdHigh = (EVENT >>13) & 0xFFFF; // THIS is the tricky part//0x1fff;
    data.FilterFIFOAssignment = CAN_RX_FIFO0;
    data.SlaveStartFilterBank = 0;
    data.FilterActivation = ENABLE;
    if (HAL_CAN_ConfigFilter(&hcan, &data) != HAL_OK)
    {
        Error_Handler();
    }
    /*
    event.FilterBank = 1;
    event.FilterMode = CAN_FILTERMODE_IDLIST; //CAN_FILTERMODE_IDLIST;
    event.FilterScale = CAN_FILTERSCALE_32BIT;
    event.FilterIdLow = ((EVENT <<3) & 0xFFF8) | 4; // THIS is the tricky part//0xffff;
    event.FilterIdHigh = (EVENT >>13) & 0xFFFF; // THIS is the tricky part//0x1fff;
    event.FilterMaskIdLow = 0xFFFC;//0x0000;
    event.FilterMaskIdHigh = 0xFFFF;//0x0000;
    event.FilterFIFOAssignment = CAN_RX_FIFO0;
    event.SlaveStartFilterBank = 0;
    event.FilterActivation = ENABLE;
    if (HAL_CAN_ConfigFilter(&hcan, &event) != HAL_OK)
    {
        Error_Handler();
    }
    */

    if (HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tx(CAN_TxHeaderTypeDef *txMsg, uint8_t *canTx)
{

    HAL_CAN_AddTxMessage(&hcan, txMsg, canTx, &canMailbox);
    txCycle++;
    if (txCycle >= 3)
    {
        HAL_Delay(1);
        txCycle = 0;
    }
}

void txExt(CAN_TxHeaderTypeDef *txMsgExt, uint8_t *canTx)
{

    HAL_CAN_AddTxMessage(&hcan, txMsgExt, canTx, &canMailbox);
    txCycle++;
    if (txCycle >= 3)
    {
        HAL_Delay(1);
        txCycle = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
