################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/file_worker.o \
../src/hr_timer.o \
../src/mac_clock_gettime.o \
../src/test_1.o 

C_SRCS += \
../src/file_worker.c \
../src/hr_timer.c \
../src/mac_clock_gettime.c \
../src/test_1.c 

OBJS += \
./src/file_worker.o \
./src/hr_timer.o \
./src/mac_clock_gettime.o \
./src/test_1.o 

C_DEPS += \
./src/file_worker.d \
./src/hr_timer.d \
./src/mac_clock_gettime.d \
./src/test_1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


