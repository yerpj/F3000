################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Third_Party/FatFs_vR0.08a/option/cc932.c \
../Utilities/Third_Party/FatFs_vR0.08a/option/cc936.c \
../Utilities/Third_Party/FatFs_vR0.08a/option/cc949.c \
../Utilities/Third_Party/FatFs_vR0.08a/option/cc950.c \
../Utilities/Third_Party/FatFs_vR0.08a/option/ccsbcs.c \
../Utilities/Third_Party/FatFs_vR0.08a/option/syscall.c 

OBJS += \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc932.o \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc936.o \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc949.o \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc950.o \
./Utilities/Third_Party/FatFs_vR0.08a/option/ccsbcs.o \
./Utilities/Third_Party/FatFs_vR0.08a/option/syscall.o 

C_DEPS += \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc932.d \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc936.d \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc949.d \
./Utilities/Third_Party/FatFs_vR0.08a/option/cc950.d \
./Utilities/Third_Party/FatFs_vR0.08a/option/ccsbcs.d \
./Utilities/Third_Party/FatFs_vR0.08a/option/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Third_Party/FatFs_vR0.08a/option/%.o: ../Utilities/Third_Party/FatFs_vR0.08a/option/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mthumb -mfloat-abi=soft -DUSE_BREADBOARD_ -DSTM32 -DDEBUG -DUSE_GCC -DUSE_CU -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT -DSTM32F2XX -DSTM32F2 -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Project/inc" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Project/src" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F2xx" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/CMSIS/CM3/CoreSupport" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Libraries/STM32F2xx_StdPeriph_Driver/inc" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ADC" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/bargraph" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/FLASH" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/GEAR" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/Indicator" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ITS" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/LEDbuffer" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/ParamCollection" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/SEG7" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/tempSensor" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/CU/timer" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Bluetooth" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/CLI" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Console" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/I2C" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/ioext" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Pushbutton" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/Serial" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Common/UID" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/libs" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Third_Party/FreeRTOS_v9.0.0/include" -I"C:/Users/jeanphil.rey/Documents/JP/Perso/F3000/F3000git/V2/FW/Utilities/Third_Party/FreeRTOS_v9.0.0/portable/GCC/ARM_CM3" -O0 -g -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


