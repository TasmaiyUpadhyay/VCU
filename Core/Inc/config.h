#define RECU	1
#define FECU	0


//error codes and their definitions
// CAN Errors(0xAX)
#define CAN_START_FAIL					0xA1
#define CAN_NOTIFICATION_FAIL			0xA2
#define CAN_TRANSMISSION_FAIL			0xA3
#define CAN_RECEPTION_FAIL				0XA4
#define CAN_FILTER1_FAIL				0xA5
#define CAN_FILTER2_FAIL				0xA6
#define CAN_FIFO_NULL					0XA7
#define CAN_MC_FAIL						0xA8

// APPS Errors (0x0X)
#define ERROR_APPS_IMPLAUSIBILITY        0x06  // Potentiometer failure
#define ERROR_APPS_OUT_OF_RANGE          0x03  // Potentiometer returns an out-of-range value

// Damper Potentiometer Errors (0x1X)
#define ERROR_DAMPER_OUT_OF_RANGE        0x13  // Potentiometer returns an out-of-range value
#define ERROR_DAMPER_INCORRECT_READING   0x05  // Improper sensor calibration
#define ERROR_DAMPER_OFFSET_ERROR        0x09  // Shift in zero point or overload damage
#define ERROR_DAMPER_REVERSE_POLARITY    0x0A  // Reverse polarity protection failure

// Strain Gauge Errors (0x2X)
#define ERROR_STRAIN_OUT_OF_RANGE        0x23  // Strain gauge returns an out-of-range value
#define ERROR_STRAIN_INCORRECT_READING   0x45  // Improper sensor calibration
#define ERROR_STRAIN_OFFSET_ERROR        0x49  // Shift in zero point or overload damage

// Wheel Speed Sensor Errors (0x3X)
#define ERROR_WHEEL_SPEED_IMPLAUSIBLE    0x35  // Sensor not calibrated properly
#define ERROR_WHEEL_SPEED_MISMATCH       0x36  // Mismatched wheel speed
#define ERROR_WHEEL_SPEED_INCORRECT      0x35  // Incorrect sensor readings
#define ERROR_WHEEL_SPEED_ENCODER_FAULT  0x34  // Faulty encoder pulses due to noise
#define ERROR_WHEEL_SPEED_OFFSET_ERROR   0x39  // Zero point shift or overload damage

// Steering Position Sensor Errors (0x4X)
#define ERROR_STEERING_OUT_OF_RANGE      0x43  // Steering potentiometer returns an implausible value

// Brake Pressure Sensor Errors (0x5X)
#define ERROR_BRAKE_LOSS                 0x56  // Sudden loss of hydraulic pressure
#define ERROR_BRAKE_OUT_OF_RANGE         0x53  // Sensor returns an implausible value

// IMU Errors (0x6X)
#define ERROR_IMU_UNRESPONSIVE           0x66  // IMU doesn't send messages on the CAN line
#define ERROR_IMU_IMPLAUSIBLE            0x35  // IMU returns garbage values

// Coolant Temperature Sensor Errors (0x1X)
#define ERROR_COOLANT_INCORRECT_READING  0x15  // Improper sensor calibration
#define ERROR_COOLANT_OFFSET_ERROR       0x19  // Shift in zero point or overload damage

// Low Voltage / Current Tap Errors (0x2X)
#define ERROR_LV_OFFSET_ERROR            0x29  // Voltage/current taps offset error

// MAF Sensor Errors (0x5X)
#define ERROR_MAF_INCORRECT_READING      0x55  // Improper sensor calibration
#define ERROR_MAF_OFFSET_ERROR           0x59  // Shift in zero point or overload damage

// Power & Safety System Errors (0x6X)
#define ERROR_BATTERY_OVERHEAT           0x63  // Li-ion battery overheating
#define ERROR_BATTERY_OVERCHARGE         0x63  // Li-ion battery overcharging
#define ERROR_POWER_SHUTOFF_FAIL         0x66  // High-voltage supply fails to shut off

// ECU Hardware Errors (0x7X)
#define ERROR_ADC_NOISE                  0x74  // Poor analog-to-digital conversion

// Battery Management System (BMS) Errors (0x8X)
#define ERROR_BMS_OVERCURRENT            0x83  // Overcharging detected
#define ERROR_BMS_OVERHEAT               0x83  // Battery overheating detected

// Insulation Monitoring Device (IMD) Errors (0x9X)
#define ERROR_IMD_INSULATION_FAILURE     0x86  // Insulation failure due to wiring damage or moisture

// General Errors (0xFX)
#define ERROR_UART_SPI_FAILURE           0xF1  // UART/I2C/SPI error due to signal loss or corruption


//HAL UART TRANSMIT Macro definition

#define LOG(x,y) HAL_UART_Transmit(&huart4,x,y,500)
