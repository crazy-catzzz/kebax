# This makefile is meant to be used with a cross compiler

VERSION := 001
NAME := kebax-$(VERSION)

TARGET := i686-elf
COMPILER_DIR := /root/opt/cross/bin

CC := $(COMPILER_DIR)/$(TARGET)-gcc
LD := $(COMPILER_DIR)/$(TARGET)-ld
NASM := nasm

CC_FLAGS := -m32 -Wall -ffreestanding
LD_FLAGS := -m elf_i386

OUT := out
BUILD := bin
SOURCE := src
INCLUDE := $(SOURCE)/include

LINKFILE := link.ld

default: init_all make_all link clean_objects

# Make parts
make_all: make_drivers make_boot make_idt make_irq make_pmm make_core

make_drivers:
	$(CC) $(CC_FLAGS) -c $(SOURCE)/drv/*.c -I$(INCLUDE)
	# $(NASM) -f elf32 $(SOURCE)/drv/*.asm
	mv -f *.o $(OUT)

make_core:
	$(CC) $(CC_FLAGS) -c $(SOURCE)/core/*.c -I$(INCLUDE)
	$(NASM) -f elf32 $(SOURCE)/core/*.asm
	mv -f $(SOURCE)/core/*.o $(OUT)
	mv -f *.o $(OUT)

make_boot:
	$(NASM) -f elf32 $(SOURCE)/boot/*.asm
	mv -f $(SOURCE)/boot/*.o $(OUT)

make_idt:
	$(CC) $(CC_FLAGS) -c $(SOURCE)/boot/idt/*.c -I$(INCLUDE)
	$(NASM) -f elf32 $(SOURCE)/boot/idt/*.asm
	mv -f $(SOURCE)/boot/idt/*.o $(OUT)
	mv -f *.o $(OUT)

make_irq:
	$(NASM) -f elf32 $(SOURCE)/core/irq/*.asm
	mv -f $(SOURCE)/core/irq/*.o $(OUT)

make_pmm:
	$(CC) $(CC_FLAGS) -c $(SOURCE)/core/pmm/*.c -I$(INCLUDE)
	mv -f *.o $(OUT)

# Linking
link:
	$(LD) $(LD_FLAGS) -T $(LINKFILE) -o $(BUILD)/$(NAME) $(OUT)/*

# Cleanup
clean_all: clean_objects clean_exec

clean_objects:
	rm -rf $(OUT)

clean_exec:
	rm -rf $(BUILD)

# Directory initialization
init_all: init_objects init_exec

init_objects:
	mkdir $(OUT)

init_exec:
	mkdir $(BUILD)
