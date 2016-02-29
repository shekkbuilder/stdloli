TARGET = libstdloli.a

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -fno-builtin -nostdlib -I include \
		 -fdata-sections -ffunction-sections

LINKER = ar
LFLAGS = rvs

SRCDIR = src
OBJDIR = obj
BINDIR = lib

SOURCES := $(wildcard $(SRCDIR)/*.c)
SSOURCES := $(wildcard $(SRCDIR)/*.s)
USSOURCES := $(wildcard $(SRCDIR)/*.S) 

OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
SOBJECTS := $(SSOURCES:$(SRCDIR)/%.s=$(OBJDIR)/%.o)
USOBJECTS := $(USSOURCES:$(SRCDIR)/%.S=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS) $(SOBJECTS) $(USOBJECTS)
	@echo "Linking..."
	@$(LINKER) $(LFLAGS) $@ $(OBJECTS) $(SOBJECTS) $(USOBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compiling "$<"..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(SOBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.s
	@echo "Compiling ASM "$<"..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(USOBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.S
	@echo "Compiling ASM "$<" (with preprocessor)..."
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS)
	rm -f $(SOBJECTS)
	rm -f $(USOBJECTS)
	rm -f $(BINDIR)/$(TARGET)
