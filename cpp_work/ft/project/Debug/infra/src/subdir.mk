################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/toolstubs.cpp 

OBJS += \
./infra/src/toolstubs.o 

CPP_DEPS += \
./infra/src/toolstubs.d 


# Each subdirectory must supply rules for building sources it contributes
infra/src/toolstubs.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/toolstubs.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


