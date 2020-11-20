################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC.c \
../source/DAC.c \
../source/Getting\ In\ Tune.c \
../source/autocorrelate.c \
../source/fp_sine.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/test_sin.c \
../source/util.c 

OBJS += \
./source/ADC.o \
./source/DAC.o \
./source/Getting\ In\ Tune.o \
./source/autocorrelate.o \
./source/fp_sine.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/test_sin.o \
./source/util.o 

C_DEPS += \
./source/ADC.d \
./source/DAC.d \
./source/Getting\ In\ Tune.d \
./source/autocorrelate.d \
./source/fp_sine.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/test_sin.d \
./source/util.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu90 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/arpit/studies/pes/Getting In Tune/board" -I"/home/arpit/studies/pes/Getting In Tune/source" -I"/home/arpit/studies/pes/Getting In Tune" -I"/home/arpit/studies/pes/Getting In Tune/drivers" -I"/home/arpit/studies/pes/Getting In Tune/CMSIS" -I"/home/arpit/studies/pes/Getting In Tune/utilities" -I"/home/arpit/studies/pes/Getting In Tune/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/Getting\ In\ Tune.o: ../source/Getting\ In\ Tune.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu90 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/arpit/studies/pes/Getting In Tune/board" -I"/home/arpit/studies/pes/Getting In Tune/source" -I"/home/arpit/studies/pes/Getting In Tune" -I"/home/arpit/studies/pes/Getting In Tune/drivers" -I"/home/arpit/studies/pes/Getting In Tune/CMSIS" -I"/home/arpit/studies/pes/Getting In Tune/utilities" -I"/home/arpit/studies/pes/Getting In Tune/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"source/Getting In Tune.d" -MT"source/Getting\ In\ Tune.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


