################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/communication/Raspi.c \
../Core/Src/communication/debug.c 

OBJS += \
./Core/Src/communication/Raspi.o \
./Core/Src/communication/debug.o 

C_DEPS += \
./Core/Src/communication/Raspi.d \
./Core/Src/communication/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/communication/%.o Core/Src/communication/%.su Core/Src/communication/%.cyclo: ../Core/Src/communication/%.c Core/Src/communication/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/VCUdev/VCU/Core/Inc/communication" -I"C:/Users/Admin/VCUdev/VCU/Core/Inc/driver_files" -I"C:/Users/Admin/VCUdev/VCU/Core/Inc/Sensor_functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-communication

clean-Core-2f-Src-2f-communication:
	-$(RM) ./Core/Src/communication/Raspi.cyclo ./Core/Src/communication/Raspi.d ./Core/Src/communication/Raspi.o ./Core/Src/communication/Raspi.su ./Core/Src/communication/debug.cyclo ./Core/Src/communication/debug.d ./Core/Src/communication/debug.o ./Core/Src/communication/debug.su

.PHONY: clean-Core-2f-Src-2f-communication

