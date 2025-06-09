################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/driver_files/ADC_driver.c \
../Core/Src/driver_files/can_driver.c \
../Core/Src/driver_files/comm_driver.c 

OBJS += \
./Core/Src/driver_files/ADC_driver.o \
./Core/Src/driver_files/can_driver.o \
./Core/Src/driver_files/comm_driver.o 

C_DEPS += \
./Core/Src/driver_files/ADC_driver.d \
./Core/Src/driver_files/can_driver.d \
./Core/Src/driver_files/comm_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/driver_files/%.o Core/Src/driver_files/%.su Core/Src/driver_files/%.cyclo: ../Core/Src/driver_files/%.c Core/Src/driver_files/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/VCUdev/VCU/Core/Inc/communication" -I"C:/Users/Admin/VCUdev/VCU/Core/Inc/driver_files" -I"C:/Users/Admin/VCUdev/VCU/Core/Inc/Sensor_functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-driver_files

clean-Core-2f-Src-2f-driver_files:
	-$(RM) ./Core/Src/driver_files/ADC_driver.cyclo ./Core/Src/driver_files/ADC_driver.d ./Core/Src/driver_files/ADC_driver.o ./Core/Src/driver_files/ADC_driver.su ./Core/Src/driver_files/can_driver.cyclo ./Core/Src/driver_files/can_driver.d ./Core/Src/driver_files/can_driver.o ./Core/Src/driver_files/can_driver.su ./Core/Src/driver_files/comm_driver.cyclo ./Core/Src/driver_files/comm_driver.d ./Core/Src/driver_files/comm_driver.o ./Core/Src/driver_files/comm_driver.su

.PHONY: clean-Core-2f-Src-2f-driver_files

