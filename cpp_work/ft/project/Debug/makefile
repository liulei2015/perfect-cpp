################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include test/utest/src/util/template/subdir.mk
-include test/utest/src/util/mutex/subdir.mk
-include test/utest/src/util/inner_class/subdir.mk
-include test/utest/src/util/future/subdir.mk
-include test/utest/src/util/function/subdir.mk
-include test/utest/src/util/forward/subdir.mk
-include test/utest/src/util/decltype/subdir.mk
-include test/utest/src/util/chrono/subdir.mk
-include test/utest/src/util/subdir.mk
-include test/utest/src/mock/subdir.mk
-include test/utest/src/cpplinq/subdir.mk
-include test/ftest/src/stubs/subdir.mk
-include test/ftest/src/ft/feature/service/subdir.mk
-include test/ftest/src/ft/feature/Lru_Mru_Lfu/subdir.mk
-include test/ftest/src/ft/feature/CelluarMachine/subdir.mk
-include test/ftest/src/subdir.mk
-include test/benchmark/src/StrSplitTest/subdir.mk
-include test/benchmark/src/CopyCompareWithMove/subdir.mk
-include infra/src/l0-infra/util/subdir.mk
-include infra/src/l0-infra/trans-dsl/utils/subdir.mk
-include infra/src/l0-infra/trans-dsl/sched/trans/subdir.mk
-include infra/src/l0-infra/trans-dsl/sched/concept/subdir.mk
-include infra/src/l0-infra/trans-dsl/sched/action/subdir.mk
-include infra/src/l0-infra/trans-dsl/role/subdir.mk
-include infra/src/l0-infra/trans-dsl/listener/subdir.mk
-include infra/src/l0-infra/trans-dsl/ext/signal/impl/subdir.mk
-include infra/src/l0-infra/trans-dsl/ext/signal/action/subdir.mk
-include infra/src/l0-infra/trans-dsl/ext/restart/subdir.mk
-include infra/src/l0-infra/trans-dsl/ext/mutex/impl/subdir.mk
-include infra/src/l0-infra/trans-dsl/ext/mutex/action/subdir.mk
-include infra/src/l0-infra/trans-dsl/ext/multi-thread/trans/subdir.mk
-include infra/src/l0-infra/trans-dsl/ext/multi-thread/action/subdir.mk
-include infra/src/l0-infra/trans-dsl/action/subdir.mk
-include infra/src/l0-infra/tools/subdir.mk
-include infra/src/l0-infra/state/subdir.mk
-include infra/src/l0-infra/proc/subdir.mk
-include infra/src/l0-infra/multi-thread/subdir.mk
-include infra/src/l0-infra/mo/subdir.mk
-include infra/src/l0-infra/mem-dbs/subdir.mk
-include infra/src/l0-infra/log/subdir.mk
-include infra/src/l0-infra/event/impl/subdir.mk
-include infra/src/l0-infra/event/concept/subdir.mk
-include infra/src/l0-infra/codec/s1ap/trans/subdir.mk
-include infra/src/l0-infra/codec/asn.1/subdir.mk
-include infra/src/l0-infra/codec/ap/trans/subdir.mk
-include infra/src/l0-infra/codec/ap/subdir.mk
-include infra/src/l0-infra/codec/subdir.mk
-include infra/src/l0-infra/base/subdir.mk
-include infra/src/l0-infra/auto-msg/subdir.mk
-include infra/src/subdir.mk
-include code/src/module_entry/subdir.mk
-include code/src/l1-domain/celluar_machine/subdir.mk
-include code/src/l1-domain/celluar/subdir.mk
-include code/src/l0-infra/util/subdir.mk
-include code/src/l0-infra/base/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: perfect-cpp

# Tool invocations
perfect-cpp: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "perfect-cpp" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) perfect-cpp
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
