################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/ftest/src/ft/feature/CelluarMachine/FtCelluarMachine.cpp 

OBJS += \
./test/ftest/src/ft/feature/CelluarMachine/FtCelluarMachine.o 

CPP_DEPS += \
./test/ftest/src/ft/feature/CelluarMachine/FtCelluarMachine.d 


# Each subdirectory must supply rules for building sources it contributes
test/ftest/src/ft/feature/CelluarMachine/FtCelluarMachine.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/ftest/src/ft/feature/CelluarMachine/FtCelluarMachine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


