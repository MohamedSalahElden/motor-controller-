################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../INT0_INT1.c \
../adc.c \
../l293D.c \
../lcd.c \
../main.c \
../pwm.c 

OBJS += \
./INT0_INT1.o \
./adc.o \
./l293D.o \
./lcd.o \
./main.o \
./pwm.o 

C_DEPS += \
./INT0_INT1.d \
./adc.d \
./l293D.d \
./lcd.d \
./main.d \
./pwm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


