#include "config.h"
#include "can_driver.h"
#include "main.h"
#include "string.h"

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
#define TEMP_MONITOR 0X4A
#define POSITION_ACTUAL 0X6E
#define CURRENT_DEVICE_LOAD 0xC6

char* txFailure = "No data sent through can!\r\n";
char* rxFailure = "NO data received through can!\r\n";
char* canActivationFault = "CAN not activated!\r\n";

// data is a struct containing all the necessary CAN parameters


// function for transmission of CAN data frames on bus
void CAN_SendMessage(uint16_t id, uint8_t* data, uint8_t DLC) {
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
    				HAL_UART_Transmit(&huart1,(uint8_t*) txFailure,strlen(txFailure),HAL_MAX_DELAY);
    		}

}

void CAN_RequestData(uint16_t regID){
	uint8_t requestData[3]={MC_READ,regID,0x00};
	CAN_SendMessage(MC_RX_ADDR,requestData,3);
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
	    			error(CAN_FILTER1_FAIL);

	    	}
	    	if(HAL_FDCAN_ConfigFilter(&hfdcan1,&sFilterConfig1)!=HAL_OK){
	    			error(CAN_FILTER2_FAIL);
	    	}


	    	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0)!=HAL_OK||HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0)!=HAL_OK||HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_TT_ERROR, 0) != HAL_OK) {
	    		error(CAN_NOTIFICATION_FAIL);
	    	}

	    	if(HAL_FDCAN_Start(&hfdcan1)!=HAL_OK){
	    		error(CAN_START_FAIL);

	    	}
}


void PingPongRec(){
	uint8_t data[1]={0x54};
	CAN_SendMessage(0x102,data,1);
}


void APPS_and_BP(uint8_t *RxData0){

	if(RxData0==NULL){
		error(CAN_FIFO_NULL);
	}
	else{
		uint16_t APPS1=(RxData0[0]<<8)|RxData0[1];
		uint16_t APPS2=(RxData0[2]<<8)|RxData0[3];
		uint16_t BP=(RxData0[4]<<8)|RxData0[5];
	}
}

void LV_and_coolant(uint8_t *RxData1){
	if(RxData1==NULL){
		error(CAN_FIFO_NULL);
	}
	else{
		uint16_t LVI=(RxData1[0]<<8)|RxData1[1];
		uint16_t LVV=(RxData1[2]<<8)|RxData1[3];
		uint16_t cool1=(RxData1[4]<<8)|RxData1[5];
		uint16_t cool2=(RxData1[6]<<8)|RxData1[7];

	}
}
void Wheel_and_DampPOTs(uint8_t *RxData1){
	if(RxData1==NULL){
		error(CAN_FIFO_NULL);
	}
	else{
		uint16_t Wheel1=(RxData1[0]<<8)|RxData1[1];
		uint16_t Wheel2=(RxData1[2]<<8)|RxData1[3];
		uint16_t DampPOTs1=(RxData1[4]<<8)|RxData1[5];
		uint16_t DampPOTs2=(RxData1[6]<<8)|RxData1[7];

	}
}
void IMU(uint8_t *RxData1){
	if(RxData1==NULL){
		error(CAN_FIFO_NULL);
	}
	else{
		uint16_t roll=(RxData1[0]<<8)|RxData1[1];
		uint16_t yaw=(RxData1[2]<<8)|RxData1[3];
		uint16_t pitch=(RxData1[4]<<8)|RxData1[5];

	}
}
void IMU_coords(uint8_t *RxData1){
	if(RxData1==NULL){
		error(CAN_FIFO_NULL);
	}
	else{
		uint16_t xcoord=(RxData1[0]<<8)|RxData1[1];
		uint16_t ycoord=(RxData1[2]<<8)|RxData1[3];
		uint16_t zcoord=(RxData1[4]<<8)|RxData1[5];

	}
}
void MCprocess(uint8_t *RxData0){
	if(RxData0==NULL){
		error(CAN_FIFO_NULL);
		return;
	}
	else{
		uint8_t regID=RxData0[0];
		switch(regID){
		case SPEED_ACTUAL:{
			uint16_t speed=(RxData0[1]<<8)|RxData0[2];
			break;
		}
		case SPEED_RPMMAX_INT:{
			uint16_t rpm=(RxData0[1]<<8)|RxData0[2];
			break;
		}
		case TORQUE_COMMAND:{
			uint16_t torque=(RxData0[1]<<8)|RxData0[2];
			break;
		}
		case CURRENT_DEVICE_LOAD:{
				uint16_t CDL=(RxData0[1]<<8)|RxData0[2];
				break;
		}
		case POSITION_ACTUAL:{
				uint16_t posactual=(RxData0[1]<<8)|RxData0[2];
				break;
		default:
			error(CAN_MC_FAIL);
			break;
		}
		}
	}
}
void CANProcessIncomingMessage(FDCAN_RxHeaderTypeDef * header, uint8_t *RxData){

		switch(header->Identifier){
			case 0x181: MCprocess(RxData);break;
			case 0x101: PingPongRec();break;
			case 0x202: APPS_and_BP(RxData);break;
			case 0x301: LV_and_coolant(RxData);break;
			case 0x302: Wheel_and_DampPOTs(RxData);break;
			case 0x303: IMU(RxData);break;
			case 0x304: IMU_coords(RxData);break;
			default: error();break;
		}

}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan,uint32_t BufferIndex){
	FDCAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData0[8];

	if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData0) == HAL_OK) {
	        CANProcessIncomingMessage(&RxHeader, RxData0);
	    } else {
	    	HAL_UART_Transmit(&huart1, (uint8_t*)rxFailure,strlen(rxFailure),HAL_MAX_DELAY);
	    }
}
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan,uint32_t BufferIndex){
	FDCAN_RxHeaderTypeDef RxHeader;
		uint8_t RxData1[8];

		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &RxHeader, RxData1) == HAL_OK) {
		        CANProcessIncomingMessage(&RxHeader, RxData1);
		    } else {
		    	HAL_UART_Transmit(&huart1, (uint8_t*)rxFailure,strlen(rxFailure),HAL_MAX_DELAY);
		    }
}

void error(uint8_t error_code) {
   ;  // Store error state globally for debugging

    switch (error_code) {
    	//CAN Errors
    switch (error_code) {
        case CAN_START_FAIL:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: CAN failed to start!\r\n", 30, HAL_MAX_DELAY);
            break;

        case CAN_NOTIFICATION_FAIL:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: Failed to activate CAN notifications!\r\n", 46, HAL_MAX_DELAY);
            break;

        case CAN_TRANSMISSION_FAIL:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: CAN data transmission failed!\r\n", 38, HAL_MAX_DELAY);
            break;

        case CAN_RECEPTION_FAIL:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: CAN reception failed!\r\n", 31, HAL_MAX_DELAY);
            break;

        case CAN_FILTER1_FAIL:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: CAN Filter 1 configuration failed!\r\n", 43, HAL_MAX_DELAY);
            break;

        case CAN_FILTER2_FAIL:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: CAN Filter 2 configuration failed!\r\n", 43, HAL_MAX_DELAY);
            break;

        case CAN_FIFO_NULL:
            HAL_UART_Transmit(&huart1, (uint8_t*)"WARNING: Received NULL FIFO data!\r\n", 36, HAL_MAX_DELAY);
            break;
        case CAN_MC_FAIL:
        	HAL_UART_Transmit(&huart1, (uint8_t*)"WARNING: MC commands failed!\r\n", 30, HAL_MAX_DELAY);
        	break;
    }
        // APPS Errors
        case ERROR_APPS_IMPLAUSIBILITY:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: APPS Potentiometer failure!\r\n", 35, HAL_MAX_DELAY);
            break;
        case ERROR_APPS_OUT_OF_RANGE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: APPS Out of Range Value!\r\n", 33, HAL_MAX_DELAY);
            break;

        // Wheel Speed Sensor Errors
        case ERROR_WHEEL_SPEED_IMPLAUSIBLE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: Wheel Speed Sensor Calibration Fault!\r\n", 45, HAL_MAX_DELAY);
            break;
        case ERROR_WHEEL_SPEED_MISMATCH:
            HAL_UART_Transmit(&huart1, (uint8_t*)"WARNING: Mismatched Wheel Speeds!\r\n", 36, HAL_MAX_DELAY);
            break;

        // Brake Pressure Sensor Errors
        case ERROR_BRAKE_LOSS:
            HAL_UART_Transmit(&huart1, (uint8_t*)"CRITICAL: Sudden Brake Pressure Drop!\r\n", 40, HAL_MAX_DELAY);

            break;
        case ERROR_BRAKE_OUT_OF_RANGE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: Brake Pressure Sensor Out of Range!\r\n", 43, HAL_MAX_DELAY);
            break;

        // IMU Errors
        case ERROR_IMU_UNRESPONSIVE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"WARNING: IMU Not Responding on CAN Bus!\r\n", 40, HAL_MAX_DELAY);
            break;
        case ERROR_IMU_IMPLAUSIBLE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: IMU Garbage Values Detected!\r\n", 38, HAL_MAX_DELAY);
            break;

        // Power & Battery Management Errors
        case ERROR_BATTERY_OVERHEAT:
            HAL_UART_Transmit(&huart1, (uint8_t*)"CRITICAL: Battery Overheating Detected!\r\n", 42, HAL_MAX_DELAY);
            triggerEmergencyShutdown();  // Example safety mechanism
            break;
        case ERROR_BATTERY_OVERCHARGE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"CRITICAL: Battery Overcharging Detected!\r\n", 43, HAL_MAX_DELAY);
            triggerEmergencyShutdown();
            break;

        // UART / Communication Errors
        case ERROR_UART_SPI_FAILURE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"WARNING: UART/SPI Communication Error!\r\n", 40, HAL_MAX_DELAY);
            break;

        // General ECU Failure
        case ERROR_ADC_NOISE:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: ADC Noise Detected!\r\n", 29, HAL_MAX_DELAY);
            break;

        // Unknown Errors
        default:
            HAL_UART_Transmit(&huart1, (uint8_t*)"ERROR: Unknown Fault Detected!\r\n", 30, HAL_MAX_DELAY);
            break;
    }
}
