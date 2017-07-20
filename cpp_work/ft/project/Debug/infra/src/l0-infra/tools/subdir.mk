################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/tools/EnvHelper.cpp \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/tools/ToolsCpuControlStrategy.cpp 

OBJS += \
./infra/src/l0-infra/tools/EnvHelper.o \
./infra/src/l0-infra/tools/ToolsCpuControlStrategy.o 

CPP_DEPS += \
./infra/src/l0-infra/tools/EnvHelper.d \
./infra/src/l0-infra/tools/ToolsCpuControlStrategy.d 


# Each subdirectory must supply rules for building sources it contributes
infra/src/l0-infra/tools/EnvHelper.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/tools/EnvHelper.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

infra/src/l0-infra/tools/ToolsCpuControlStrategy.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/tools/ToolsCpuControlStrategy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


