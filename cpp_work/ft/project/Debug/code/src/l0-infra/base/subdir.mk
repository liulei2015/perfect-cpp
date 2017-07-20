################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/CacheManager.cpp \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/CacheNode.cpp \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/LFUWeedOutStrategy.cpp \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/LRUWeedOutStrategy.cpp \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/MRUWeedOutStrategy.cpp 

OBJS += \
./code/src/l0-infra/base/CacheManager.o \
./code/src/l0-infra/base/CacheNode.o \
./code/src/l0-infra/base/LFUWeedOutStrategy.o \
./code/src/l0-infra/base/LRUWeedOutStrategy.o \
./code/src/l0-infra/base/MRUWeedOutStrategy.o 

CPP_DEPS += \
./code/src/l0-infra/base/CacheManager.d \
./code/src/l0-infra/base/CacheNode.d \
./code/src/l0-infra/base/LFUWeedOutStrategy.d \
./code/src/l0-infra/base/LRUWeedOutStrategy.d \
./code/src/l0-infra/base/MRUWeedOutStrategy.d 


# Each subdirectory must supply rules for building sources it contributes
code/src/l0-infra/base/CacheManager.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/CacheManager.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/src/l0-infra/base/CacheNode.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/CacheNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/src/l0-infra/base/LFUWeedOutStrategy.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/LFUWeedOutStrategy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/src/l0-infra/base/LRUWeedOutStrategy.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/LRUWeedOutStrategy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

code/src/l0-infra/base/MRUWeedOutStrategy.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/code/src/l0-infra/base/MRUWeedOutStrategy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


