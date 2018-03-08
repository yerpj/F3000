################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/gcc_ride7/startup_stm32f2xx.s 

OBJS += \
./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/gcc_ride7/startup_stm32f2xx.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/gcc_ride7/%.o: ../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/gcc_ride7/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mthumb -mfloat-abi=soft -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


