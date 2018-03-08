################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/libs/subdir.mk
-include Utilities/Third_Party/FreeRTOS_v9.0.0/portable/MemMang/subdir.mk
-include Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ARM_CM3/subdir.mk
-include Utilities/Third_Party/FreeRTOS_v9.0.0/portable/Common/subdir.mk
-include Utilities/Third_Party/FreeRTOS_v9.0.0/subdir.mk
-include Utilities/Third_Party/FatFs_vR0.08a/option/subdir.mk
-include Utilities/Third_Party/FatFs_vR0.08a/subdir.mk
-include Utilities/Common/ioext/subdir.mk
-include Utilities/Common/UID/subdir.mk
-include Utilities/Common/Serial/subdir.mk
-include Utilities/Common/Pushbutton/subdir.mk
-include Utilities/Common/I2C/subdir.mk
-include Utilities/Common/Console/subdir.mk
-include Utilities/Common/CLI/subdir.mk
-include Utilities/Common/Bluetooth/subdir.mk
-include Utilities/CU/timer/subdir.mk
-include Utilities/CU/tempSensor/subdir.mk
-include Utilities/CU/bargraph/subdir.mk
-include Utilities/CU/SEG7/subdir.mk
-include Utilities/CU/ParamCollection/subdir.mk
-include Utilities/CU/LEDbuffer/subdir.mk
-include Utilities/CU/Indicator/subdir.mk
-include Utilities/CU/ITS/subdir.mk
-include Utilities/CU/GEAR/subdir.mk
-include Utilities/CU/FLASH/subdir.mk
-include Utilities/CU/ADC/subdir.mk
-include Utilities/CU/subdir.mk
-include Project/src/subdir.mk
-include Project/IARARM/Debug/Obj/subdir.mk
-include Project/IARARM/subdir.mk
-include Libraries/STM32F2xx_StdPeriph_Driver/src/subdir.mk
-include Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/iar/subdir.mk
-include Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/gcc_ride7/subdir.mk
-include Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/arm/subdir.mk
-include Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/startup/TrueSTUDIO/subdir.mk
-include Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx/subdir.mk
-include Libraries/CMSIS/CM3/CoreSupport/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: F3000CU

# Tool invocations
F3000CU: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU G++ Linker'
	arm-none-eabi-g++ -mthumb -mfloat-abi=soft -Wl,-Map=output.map -Wl,--gc-sections -fno-exceptions -fno-rtti -o "F3000CU" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
