################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/view/camera.cpp \
../src/view/image.cpp \
../src/view/view.cpp 

OBJS += \
./src/view/camera.o \
./src/view/image.o \
./src/view/view.o 

CPP_DEPS += \
./src/view/camera.d \
./src/view/image.d \
./src/view/view.d 


# Each subdirectory must supply rules for building sources it contributes
src/view/%.o: ../src/view/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -std=c++11 -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


