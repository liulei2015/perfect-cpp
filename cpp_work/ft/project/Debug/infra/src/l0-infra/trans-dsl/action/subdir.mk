################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/trans-dsl/action/RoleBasedAsyncAction.cpp \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/trans-dsl/action/SimpleAsyncAction.cpp \
/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/trans-dsl/action/SyncActionAdapter.cpp 

OBJS += \
./infra/src/l0-infra/trans-dsl/action/RoleBasedAsyncAction.o \
./infra/src/l0-infra/trans-dsl/action/SimpleAsyncAction.o \
./infra/src/l0-infra/trans-dsl/action/SyncActionAdapter.o 

CPP_DEPS += \
./infra/src/l0-infra/trans-dsl/action/RoleBasedAsyncAction.d \
./infra/src/l0-infra/trans-dsl/action/SimpleAsyncAction.d \
./infra/src/l0-infra/trans-dsl/action/SyncActionAdapter.d 


# Each subdirectory must supply rules for building sources it contributes
infra/src/l0-infra/trans-dsl/action/RoleBasedAsyncAction.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/trans-dsl/action/RoleBasedAsyncAction.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

infra/src/l0-infra/trans-dsl/action/SimpleAsyncAction.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/trans-dsl/action/SimpleAsyncAction.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

infra/src/l0-infra/trans-dsl/action/SyncActionAdapter.o: /Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/infra/src/l0-infra/trans-dsl/action/SyncActionAdapter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../infra/include/ -I../../../../tools/include/ -I"/Users/apple/Documents/dev/vagrant_ubuntu16/perfect_cpp/cpp_work/ft/utest/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


