################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/benchmark/src/CopyCompareWithMove/CopyAndMoveTest.cpp 

OBJS += \
./test/benchmark/src/CopyCompareWithMove/CopyAndMoveTest.o 

CPP_DEPS += \
./test/benchmark/src/CopyCompareWithMove/CopyAndMoveTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/benchmark/src/CopyCompareWithMove/CopyAndMoveTest.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/benchmark/src/CopyCompareWithMove/CopyAndMoveTest.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


