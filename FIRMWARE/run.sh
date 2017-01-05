#!/bin/bash

set -x
arm-none-eabi-gdb -x gdbinit firmware.elf
