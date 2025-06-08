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

// Motor controller codes for data requests/commands
#define SPEED_ACTUAL 0x30
#define SPEED_RPMMAX_INT 0xCE
#define TORQUE_COMMAND 0x90
#define MC_READ 0x3D
#define MC_RX_ADDR 0x201
#define MC_TX_ADDR 0x181


char* txFailure = "No data sent through can!\r\n";
char* rxFailure = "NO data received through can!\r\n";
char* canActivationFault = "CAN not activated!\r\n";

uint8_t error_state=0;

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
    			error_state=3;
    				HAL_UART_Transmit(&huart1, txFailure,strlen(txFailure),HAL_MAX_DELAY);
    		}

}

void Startup(){


		FDCAN_FilterTypeDef sFilterConfig;
	    sFilterConfig.IdType=FDCAN_STANDARD_ID;
	    sFilterConfig.FilterIndex=0;
	    sFilterConfig.FilterType=FDCAN_FILTER_RANGE;
	    sFilterConfig.FilterConfig=FDCAN_FILTER_TO_RXFIFO0;
	    sFilterConfig.FilterID1=0x100;
	    sFilterConfig.FilterID2=0x250;

	    FDCAN_FilterTypeDef sFilterConfig1;
	    sFilterConfig1.IdType=FDCAN_STANDARD_ID;
	    sFilterConfig1.FilterIndex=1;
	    sFilterConfig1.FilterType=FDCAN_FILTER_RANGE;
	    sFilterConfig1.FilterConfig=FDCAN_FILTER_TO_RXFIFO1;
	    sFilterConfig1.FilterID1=0x300;
	    sFilterConfig1.FilterID2=0x400;


	    	if(HAL_FDCAN_ConfigFilter(&hfdcan1,&sFilterConfig)!=HAL_OK){
	    			error_state=4;

	    	}
	    	if(HAL_FDCAN_ConfigFilter(&hfdcan1,&sFilterConfig1)!=HAL_OK){
	    			error_state=5;
	    	}


	    	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0)!=HAL_OK||HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0)!=HAL_OK||HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_ERROR, 0) != HAL_OK) {
	    		error_state=2;
	    	}

	    	if(HAL_FDCAN_Start(&hfdcan1)!=HAL_OK){
	    		Error_Handler();
	    		error_state=1;
	    	}
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan){
	FDCAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData0[8];

	if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData0) == HAL_OK) {
	        CAN_ProcessIncomingMessage(&RxHeader, RxData0);
	    } else {
	    	HAL_UART_Transmit(&huart1, rxFailure,strlen(rxFailure),HAL_MAX_DELAY);
	    }
}
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan){
	FDCAN_RxHeaderTypeDef RxHeader;
		uint8_t RxData1[8];

		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &RxHeader, RxData1) == HAL_OK) {
		        CAN_ProcessIncomingMessage(&RxHeader, RxData1);
		    } else {
		    	HAL_UART_Transmit(&huart1, rxFailure,8,HAL_MAX_DELAY);
		    }
}


void CANProcessIncomingMessage(FDCAN_RxHeaderTypeDef * header, uint8_t *data){

		switch(header->Identifier){
			case 0x181: MCprocess(data);break;
			case 0x101: PingPongRec();break;
			case 0x202: APPS_and_BP(data);break;
			case 0x301: LV_and_coolant(data);break;
			case 0x302: Wheel_and_DampPOTs(data);break;
			case 0x303: IMU(data);break;
			case 0x304: IMU_coords(data);break;
			default: error();break;
		}

}


void PingPongRec(){
	uint8_t data[3]=0x54;
	CAN_SendMessage(0x102,data,2);
}
