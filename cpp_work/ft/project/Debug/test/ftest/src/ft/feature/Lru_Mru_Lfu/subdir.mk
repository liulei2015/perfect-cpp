################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/ftest/src/ft/feature/Lru_Mru_Lfu/FtLruMruLfu.cpp 

OBJS += \
./test/ftest/src/ft/feature/Lru_Mru_Lfu/FtLruMruLfu.o 

CPP_DEPS += \
./test/ftest/src/ft/feature/Lru_Mru_Lfu/FtLruMruLfu.d 


# Each subdirectory must supply rules for building sources it contributes
test/ftest/src/ft/feature/Lru_Mru_Lfu/FtLruMruLfu.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/ftest/src/ft/feature/Lru_Mru_Lfu/FtLruMruLfu.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


