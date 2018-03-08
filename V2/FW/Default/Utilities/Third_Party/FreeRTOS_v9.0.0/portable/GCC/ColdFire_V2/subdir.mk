################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/port.c 

S_UPPER_SRCS += \
../Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/portasm.S 

OBJS += \
./Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/port.o \
./Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/portasm.o 

S_UPPER_DEPS += \
./Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/portasm.d 

C_DEPS += \
./Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/port.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/%.o: ../Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -DUSE_BREADBOARD_ -DUSE_CU -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT -DSTM32F2XX -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Project/inc" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Project/src" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/CMSIS/CM3/CoreSupport" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/STM32F2xx_StdPeriph_Driver/inc" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ADC" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/bargraph" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/FLASH" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/GEAR" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/Indicator" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ITS" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/LEDbuffer" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ParamCollection" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/SEG7" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/tempSensor" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/timer" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Bluetooth" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/CLI" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Console" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/I2C" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/ioext" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Pushbutton" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Serial" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/UID" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/libs" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Third_Party/FreeRTOS_v9.0.0/include" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ARM_CM3" -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/%.o: ../Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ColdFire_V2/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -DUSE_BREADBOARD_ -DUSE_CU -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT -DSTM32F2XX -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Project/inc" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Project/src" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/CMSIS/CM3/CoreSupport" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/STM32F2xx_StdPeriph_Driver/inc" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ADC" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/bargraph" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/FLASH" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/GEAR" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/Indicator" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ITS" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/LEDbuffer" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ParamCollection" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/SEG7" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/tempSensor" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/timer" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Bluetooth" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/CLI" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Console" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/I2C" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/ioext" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Pushbutton" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Serial" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/UID" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/libs" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Third_Party/FreeRTOS_v9.0.0/include" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ARM_CM3" -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


