#include "window.h"
#include "main.h"

void windowInit(void)
{
    for (size_t i = 0; i < MAX_WINDOWS; i++)
    {
        window[i].event = 0;
        window[i].state = 0;
        window[i].sense_D = 0;
        window[i].sense_U = 0;
        window[i].senseCount_D = 0;
        window[i].senseCount_U = 0;
    }
    for (size_t i = 0; i < 8; i++)
    {
        motorCurrent[i] = 0;
    }
    stageState = ready;
    stageNextState = 0;
    
}

void windowHandler(void)
{
    eventHandler();
    stateHandler();
    for (size_t i = 0; i < MAX_WINDOWS; i++)
    {
        motorHandler(&window[i], i);
    }
    staging();
}

void stateHandler(void)
{
    window[lr].sense_U = motorCurrent[0];
    window[lr].sense_D = motorCurrent[1];
    window[rr].sense_U = motorCurrent[2];
    window[rr].sense_D = motorCurrent[3];
    window[lf].sense_U = motorCurrent[4]; // works lf down
    window[lf].sense_D = motorCurrent[5];
    window[rf].sense_U = motorCurrent[6];
    window[rf].sense_D = motorCurrent[7];

    for (size_t i = 0; i < 4; i++)
    {
        if (window[i].sense_U >= SENSE_LIMIT)
        {
            window[i].senseCount_U++;
        }
        if (window[i].sense_U < SENSE_LIMIT)
        {
            window[i].senseCount_U = 0;
        }
        if (window[i].sense_D >= SENSE_LIMIT)
        {
            window[i].senseCount_D++;
        }
        if (window[i].sense_D < SENSE_LIMIT)
        {
            window[i].senseCount_D = 0;
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        if (window[i].senseCount_U >= MAX_COUNT || window[i].senseCount_D >= MAX_COUNT)
        {
            window[i].state = idle;
        }
    }
}

void motorHandler(windowHandle_t *window, int instance)
{
    int state = window->state;
    switch (instance)
    {
    case lf:
        switch (state)
        {
        case idle:
            HAL_GPIO_WritePin(LF_U_GPIO_Port, LF_U_Pin, RESET);
            HAL_GPIO_WritePin(LF_D_GPIO_Port, LF_D_Pin, RESET);
            break;
        case up:
            HAL_GPIO_WritePin(LF_U_GPIO_Port, LF_U_Pin, RESET);
            HAL_GPIO_WritePin(LF_D_GPIO_Port, LF_D_Pin, SET);
            break;
        case down:
            HAL_GPIO_WritePin(LF_U_GPIO_Port, LF_U_Pin, SET);
            HAL_GPIO_WritePin(LF_D_GPIO_Port, LF_D_Pin, RESET);
            break;
        default:
            break;
        }
        break;
    case lr:
        switch (state)
        {
        case idle:
            HAL_GPIO_WritePin(LR_U_GPIO_Port, LR_U_Pin, RESET);
            HAL_GPIO_WritePin(LR_D_GPIO_Port, LR_D_Pin, RESET);
            break;
        case up:
            HAL_GPIO_WritePin(LR_U_GPIO_Port, LR_U_Pin, RESET);
            HAL_GPIO_WritePin(LR_D_GPIO_Port, LR_D_Pin, SET);
            break;
        case down:
            HAL_GPIO_WritePin(LR_U_GPIO_Port, LR_U_Pin, SET);
            HAL_GPIO_WritePin(LR_D_GPIO_Port, LR_D_Pin, RESET);
            break;
        default:
            break;
        }
        break;
    case rf:
        switch (state)
        {
        case idle:
            HAL_GPIO_WritePin(RF_U_GPIO_Port, RF_U_Pin, RESET);
            HAL_GPIO_WritePin(RF_D_GPIO_Port, RF_D_Pin, RESET);
            break;
        case up:
            HAL_GPIO_WritePin(RF_U_GPIO_Port, RF_U_Pin, RESET);
            HAL_GPIO_WritePin(RF_D_GPIO_Port, RF_D_Pin, SET);
            break;
        case down:
            HAL_GPIO_WritePin(RF_U_GPIO_Port, RF_U_Pin, SET);
            HAL_GPIO_WritePin(RF_D_GPIO_Port, RF_D_Pin, RESET);
            break;
        default:
            break;
        }
        break;
    case rr:
        switch (state)
        {
        case idle:
            HAL_GPIO_WritePin(RR_U_GPIO_Port, RR_U_Pin, RESET);
            HAL_GPIO_WritePin(RR_D_GPIO_Port, RR_D_Pin, RESET);
            break;
        case up:
            HAL_GPIO_WritePin(RR_U_GPIO_Port, RR_U_Pin, RESET);
            HAL_GPIO_WritePin(RR_D_GPIO_Port, RR_D_Pin, SET);
            break;
        case down:
            HAL_GPIO_WritePin(RR_U_GPIO_Port, RR_U_Pin, SET);
            HAL_GPIO_WritePin(RR_D_GPIO_Port, RR_D_Pin, RESET);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////

void eventHandler(void)
{
    if (te.currentScreen == 9 && te.valueId == 1)
    {

        switch (te.currentVal)
        {
        case FRONT_WINDOWS:
            switch (te.swipe)
            {
            case SWIPE_UP:
                window[lf].state = up;
                window[rf].state = up;
                break;

            case SWIPE_DOWN:
                window[lf].state = down;
                window[rf].state = down;
            default:
                break;
            }
            break;

        case ALL_WINDOWS:
            switch (te.swipe)
            {
            case SWIPE_UP:
                stageState = all_up;
                break;
                
            case SWIPE_DOWN:
                stageState = all_down;
                break;
            default:
                break;
            }
            break;

        case LF_WINDOW:
            switch (te.swipe)
            {
            case SWIPE_UP:
                window[lf].state = up;
                break;
            case SWIPE_DOWN:
                window[lf].state = down;
                break;

            default:
                break;
            }
            break;

        case RF_WINDOW:
            switch (te.swipe)
            {
            case SWIPE_UP:
                window[rf].state = up;
                break;
            case SWIPE_DOWN:
                window[rf].state = down;
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }

        //default:
        // break;
    }

    if (te.tap >= TAP_ANY)
    {
        stageState = ready;
        stageNextState = ready;
        for (size_t i = 0; i < 4; i++)
        {
            window[i].state = idle;
        }
    }
}

void staging(void)
{
    switch (stageState)
    {

    case ready:
        break;

    case all_up:

        switch (stageNextState)
        {
        case ready:
            stageNextState = rear_run;
            break;

        case rear_run:
            window[lr].state = up;
            window[rr].state = up;
            stageNextState = rear_done;
            break;

        case rear_done:
            if (window[lr].state == idle && window[rr].state == idle)
            {
                stageNextState = front_run;
            }
            break;

        case front_run:
            window[lf].state = up;
            window[rf].state = up;
            stageNextState = front_done;
            break;

        case front_done:
            if (window[lf].state == idle && window[rf].state == idle)
            {
                stageState = ready;
                stageNextState = ready;
            }
            break;

        default:
            break;
        }

        break;
    case all_down:

        switch (stageNextState)
        {
        case ready:
            stageNextState = front_run;
            break;

        case front_run:
            window[lf].state = down;
            window[rf].state = down;
            stageNextState = front_done;
            break;

        case front_done:
            if (window[lf].state == idle && window[rf].state == idle)
            {
                stageNextState = rear_run;
            }
            break;

        case rear_run:
            window[lr].state = down;
            window[rr].state = down;
            stageNextState = rear_done;
            break;

        case rear_done:
            if (window[lr].state == idle && window[rr].state == idle)
            {
                stageState = ready;
                stageNextState = ready;
            }
            break;

        default:
            break;
        }
        break;
    }
}
