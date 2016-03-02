# ------------------------------------------------------------------------------
# Generic Makefile for stdloli programs
# 
# Version: 1.0
# Author: Franc[e]sco
# Description:
# Compiles all .c, .s and .S files in SRCDIR to obj files in OBJDIR, then links
# everything against stdloli and gets rid of unused code as well as useless 
# ELF sections to minimize executable size.
# ------------------------------------------------------------------------------
TARGET = cat

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -fno-builtin \
		 -I ../../include -L ../../lib \
		 -fdata-sections -ffunction-sections -fno-stack-protector

LINKER = gcc -o 
LFLAGS = -L ../../lib -lstdloli -Wl,--gc-sections -nostdlib

SRCDIR = .
OBJDIR = obj
BINDIR = .

SOURCES := $(wildcard $(SRCDIR)/*.c)
SSOURCES := $(wildcard $(SRCDIR)/*.s)
USSOURCES := $(wildcard $(SRCDIR)/*.S) 

OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
SOBJECTS := $(SSOURCES:$(SRCDIR)/%.s=$(OBJDIR)/%.o)
USOBJECTS := $(USSOURCES:$(SRCDIR)/%.S=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): dirs $(OBJECTS) $(SOBJECTS) $(USOBJECTS)
	@echo "Linking..."
	@$(LINKER) $@ $(OBJECTS) $(SOBJECTS) $(USOBJECTS) $(LFLAGS)
	@echo "Stripping..."
	@strip -R .eh_frame -R .eh_frame_hdr -R .comment $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compiling "$<"..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(SOBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.s
	@echo "Compiling ASM "$<"..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(USOBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.S
	@echo "Compiling ASM "$<" (with preprocessor)..."
	@$(CC) $(CFLAGS) -c $< -o $@

dirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

.PHONEY: clean
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS)
	rm -f $(SOBJECTS)
	rm -f $(USOBJECTS)
	rm -f $(BINDIR)/$(TARGET)
