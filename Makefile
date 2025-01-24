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
make_all: make_drivers make_boot make_core

make_drivers:
	$(CC) $(CC_FLAGS) -c $(SOURCE)/drv/*.c -I$(INCLUDE)
	mv *.o $(OUT)

make_core:
	$(CC) $(CC_FLAGS) -c $(SOURCE)/core/*.c -I$(INCLUDE)
	mv *.o $(OUT)

make_boot:
	$(NASM) -f elf32 $(SOURCE)/boot/*.asm
	mv $(SOURCE)/boot/*.o $(OUT)

# Linking
link:
	$(LD) $(LD_FLAGS) -T $(LINKFILE) -o $(BUILD)/$(NAME) $(OUT)/*

# Cleanup
clean_all: clean_objects clean_exec

clean_objects:
	rm -r $(OUT)

clean_exec:
	rm -r $(BUILD)

# Directory initialization
init_all: init_objects init_exec

init_objects:
	mkdir $(OUT)

init_exec:
	mkdir $(BUILD)
