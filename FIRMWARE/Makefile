all: firmware.elf

RM = rm
ECHO = @echo

comma := ,
empty :=
space := $(empty) $(empty)

CROSS_COMPILE = arm-none-eabi-

AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size

CPU := cortex-m4

AFLAGS   += -mthumb -mcpu=$(CPU)
CFLAGS   += -mthumb -mcpu=$(CPU)
CXXFLAGS += -mthumb -mcpu=$(CPU)
LDFLAGS  += --entry=ResetISR --gc-sections

CFLAGS += -ffunction-sections -fdata-sections -Wall -std=c11
CXXFLAGS += -ffunction-sections -fdata-sections -Wall

SDK_PATH = sdk
DRIVERLIB = $(SDK_PATH)/driverlib
OSLIB = $(SDK_PATH)/oslib
FREERTOS = $(SDK_PATH)/third_party/FreeRTOS
COMMON = $(SDK_PATH)/example/common

DEFINES += -Dgcc=1

INC  = -I$(SDK_PATH)
INC += -I$(SDK_PATH)/inc
INC += -I$(DRIVERLIB)
INC += -I$(COMMON)

CPPFLAGS = $(DEFINES) $(INC)

#arm-none-eabi-gcc
#-I.
#-Isdk
#-Isdk/inc
#-Isdk/driverlib
#-Isdk/example/common
#-Isdk/oslib
#-Isdk/simplelink
#-Isdk/simplelink/include
#-Isdk/simplelink_extlib/provisioninglib
#-Isdk/third_party/FreeRTOS/source/include
#-Isdk/third_party/FreeRTOS/source/portable/GCC/ARM_CM4
#
#-Dgcc
#-DUSE_FREERTOS
#-DSL_PLATFORM_MULTI_THREADED
#-o /home/dhylands/Dropbox/sensorweb/cc3200-rs/target/thumbv7em-none-eabi/debug/build/cc3200-sys-82ab4104954fd6fd/out/sdk/third_party/FreeRTOS/source/tasks.o
#-c sdk/third_party/FreeRTOS/source/tasks.c

BUILD = build

SRC = 	main.c \
	DELAY.c \
	HDC1080.c \
	pinmux.c \
	PPD42NJ.c \
	TLC59116.c

OBJ = $(patsubst %.c, $(BUILD)/%.o, $(SRC))

OBJ += $(addprefix $(BUILD)/$(COMMON)/, \
	startup_gcc.o \
	gpio_if.o \
	i2c_if.o \
	timer_if.o \
	uart_if.o \
	)

OBJ += $(addprefix $(BUILD)/$(DRIVERLIB)/, \
	adc.o \
	aes.o \
	camera.o \
	cpu.o \
	crc.o \
	des.o \
	flash.o \
	gpio.o \
	hwspinlock.o \
	i2c.o \
	interrupt.o \
	i2s.o \
	pin.o \
	prcm.o \
	sdhost.o \
	shamd5.o \
	spi.o \
	systick.o \
	timer.o \
	uart.o \
	udma.o \
	utils.o \
	wdt.o \
	)

OBJDIRS = $(sort $(dir $(OBJ)))
$(OBJ): | $(OBJDIRS)
$(OBJDIRS):
	mkdir -p $@

LDFLAGS  += --entry=ResetISR --gc-sections
LDFLAGS += -T layout.ld -Map=$(@:.elf=.map) --cref

firmware.elf: $(OBJ)
	echo "Linking $@"
	$(CC) $(CFLAGS) -Wl,$(subst $(space),$(comma),$(LDFLAGS)) -o $@ $^ $(LIBS)
	$(SIZE) $@

${BUILD}/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -g -O0 -o $@ -c $<

clean:
	$(RM) -rf $(BUILD)
