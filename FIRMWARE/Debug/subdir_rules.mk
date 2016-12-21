################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DELAY.obj: ../DELAY.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="DELAY.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HDC1080.obj: ../HDC1080.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="HDC1080.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

PPD42NJ.obj: ../PPD42NJ.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="PPD42NJ.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

TLC59116.obj: ../TLC59116.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="TLC59116.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpio_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/gpio_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="gpio_if.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2c_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/i2c_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="i2c_if.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pinmux.obj: ../pinmux.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="pinmux.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer_if.obj: C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common/timer_if.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.2.0/cc3200-sdk/inc" -g --define=cc3200 --define=ccs --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="timer_if.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


