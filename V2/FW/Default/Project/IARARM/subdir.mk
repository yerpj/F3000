################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Project/IARARM/startup_stm32f2xx.s 

OBJS += \
./Project/IARARM/startup_stm32f2xx.o 


# Each subdirectory must supply rules for building sources it contributes
Project/IARARM/%.o: ../Project/IARARM/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mthumb -mfloat-abi=soft -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


