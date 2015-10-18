################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/bowl.cpp \
../src/model/bowlingMachine.cpp \
../src/model/model.cpp \
../src/model/pin.cpp \
../src/model/pinSet.cpp \
../src/model/place.cpp 

OBJS += \
./src/model/bowl.o \
./src/model/bowlingMachine.o \
./src/model/model.o \
./src/model/pin.o \
./src/model/pinSet.o \
./src/model/place.o 

CPP_DEPS += \
./src/model/bowl.d \
./src/model/bowlingMachine.d \
./src/model/model.d \
./src/model/pin.d \
./src/model/pinSet.d \
./src/model/place.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/%.o: ../src/model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -std=c++11 -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


