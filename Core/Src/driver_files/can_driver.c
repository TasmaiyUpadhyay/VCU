#include "config.h"
#include "can_driver.h"
#include "main.h"

#ifdef RECU
extern FDCAN_HandleTypeDef hfdcan1;
extern UART_HandleTypeDef huart1;

#elif (FECU)
extern FDCAN_HandleTypeDef hfdcan1;
extern UART_HandleTypeDef huart1;

#endif



// data is a struct containing all the necessary CAN parameters


// function for transmission of CAN data frames on bus
void CAN_SendMessage(uint16_t id, uint8_t *data, uint8_t DLC) {
    FDCAN_TxHeaderTypeDef TxHeader;
    TxHeader.Identifier = id;
    TxHeader.IdType = FDCAN_STANDARD_ID;
    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;

    switch(DLC){
    case 8: TxHeader.DataLength=FDCAN_DLC_BYTES_8;break;
    case 6: TxHeader.DataLength=FDCAN_DLC_BYTES_6;break;
    case 5: TxHeader.DataLength=FDCAN_DLC_BYTES_5;break;
    case 2: TxHeader.DataLength=FDCAN_DLC_BYTES_2;break;
    default: TxHeader.DataLength=FDCAN_DLC_BYTES_8;
    }
    if(HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, data)!=HAL_OK){
    	Error_Handler();
    }


}

void Startup(){



	HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 1, 0);
	 HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);

	MX_FDCAN1_Init();

	FDCAN_FilterTypeDef sFilterConfig;
	    sFilterConfig.IdType=FDCAN_STANDARD_ID;
	    sFilterConfig.FilterIndex=0;
	    sFilterConfig.FilterType=FDCAN_FILTER_RANGE;
	    sFilterConfig.FilterConfig=FDCAN_FILTER_TO_RXFIFO0;
	    sFilterConfig.FilterID1=0x100;
	    sFilterConfig.FilterID2=0x300;

	 FDCAN_FilterTypeDef sFilterConfig1;
	 sFilterConfig1.IdType=FDCAN_STANDARD_ID;
	 sFilterConfig1.FilterIndex=1;
	 sFilterConfig1.FilterType=FDCAN_FILTER_RANGE;
	 sFilterConfig1.FilterConfig=FDCAN_FILTER_TO_RXFIFO1;
	 sFilterConfig1.FilterID1=0x100;
	 sFilterConfig1.FilterID2=0x300;



if(HAL_FDCAN_ConfigFilter(&hfdcan1,&sFilterConfig)!=HAL_OK){
	Error_Handler();
}
if(HAL_FDCAN_ConfigFilter(&hfdcan1,&sFilterConfig1)!=HAL_OK){
	Error_Handler();
}

if(HAL_FDCAN_Start(&hfdcan1)!=HAL_OK){
	Error_Handler();
}

if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
        Error_Handler();
    }
if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK) {
        Error_Handler();
   }
if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_ERROR, 0) != HAL_OK) {
       Error_Handler();
   }

}
