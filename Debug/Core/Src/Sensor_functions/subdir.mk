################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Sensor_functions/Encoders.c \
../Core/Src/Sensor_functions/LV_battery.c \
../Core/Src/Sensor_functions/Potentiometers.c \
../Core/Src/Sensor_functions/Strain_gauges.c \
../Core/Src/Sensor_functions/Temperature.c 

OBJS += \
./Core/Src/Sensor_functions/Encoders.o \
./Core/Src/Sensor_functions/LV_battery.o \
./Core/Src/Sensor_functions/Potentiometers.o \
./Core/Src/Sensor_functions/Strain_gauges.o \
./Core/Src/Sensor_functions/Temperature.o 

C_DEPS += \
./Core/Src/Sensor_functions/Encoders.d \
./Core/Src/Sensor_functions/LV_battery.d \
./Core/Src/Sensor_functions/Potentiometers.d \
./Core/Src/Sensor_functions/Strain_gauges.d \
./Core/Src/Sensor_functions/Temperature.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Sensor_functions/%.o Core/Src/Sensor_functions/%.su Core/Src/Sensor_functions/%.cyclo: ../Core/Src/Sensor_functions/%.c Core/Src/Sensor_functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/User/STM32CubeIDE/VCU/ecu/Core/Inc/communication" -I"C:/Users/User/STM32CubeIDE/VCU/ecu/Core/Inc/driver_files" -I"C:/Users/User/STM32CubeIDE/VCU/ecu/Core/Inc/Sensor_functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Sensor_functions

clean-Core-2f-Src-2f-Sensor_functions:
	-$(RM) ./Core/Src/Sensor_functions/Encoders.cyclo ./Core/Src/Sensor_functions/Encoders.d ./Core/Src/Sensor_functions/Encoders.o ./Core/Src/Sensor_functions/Encoders.su ./Core/Src/Sensor_functions/LV_battery.cyclo ./Core/Src/Sensor_functions/LV_battery.d ./Core/Src/Sensor_functions/LV_battery.o ./Core/Src/Sensor_functions/LV_battery.su ./Core/Src/Sensor_functions/Potentiometers.cyclo ./Core/Src/Sensor_functions/Potentiometers.d ./Core/Src/Sensor_functions/Potentiometers.o ./Core/Src/Sensor_functions/Potentiometers.su ./Core/Src/Sensor_functions/Strain_gauges.cyclo ./Core/Src/Sensor_functions/Strain_gauges.d ./Core/Src/Sensor_functions/Strain_gauges.o ./Core/Src/Sensor_functions/Strain_gauges.su ./Core/Src/Sensor_functions/Temperature.cyclo ./Core/Src/Sensor_functions/Temperature.d ./Core/Src/Sensor_functions/Temperature.o ./Core/Src/Sensor_functions/Temperature.su

.PHONY: clean-Core-2f-Src-2f-Sensor_functions

