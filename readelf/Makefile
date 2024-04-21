# Compiler settings
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
DEBUGFLAGS = -g


# Target executables
TARGET_0 = 0-hreadelf  # Executable for processing ELF header information
TARGET_1 = 1-hreadelf  # Executable for processing ELF section headers
TARGET_2 = 2-hreadelf  # Executable for processing ELF program headers


# Source files for each target
SOURCE_0 = 0-elf_header-main.c 0-elf_header-details.c 0-elf_header-machine.c \
           0-elf_header-type.c 0-elf_header-abi_version.c 0-elf_header-os_abi.c \
           0-elf_header-version.c 0-elf_header-data.c 0-elf_header-class.c \
           0-elf_header-magic.c 0-elf_header-read.c 0-elf_header-endian.c

SOURCE_1 = 1-elf_sec_header-main.c 1-elf_sec_header-flags.c \
           1-elf_sec_header-handle_32.c 1-elf_sec_header-handle_64.c \
           1-elf_sec_header-handle_elf.c 1-elf_sec_header-print.c \
           1-elf_sec_header-swap.c 1-elf_sec_header-type.c \
           1-elf_sec_header-validation.c

SOURCE_2 = 2-elf_prog_header-main.c


# Main rule to build all targets
all: $(TARGET_0) $(TARGET_1) $(TARGET_2)


# Debug build
debug: CFLAGS += $(DEBUGFLAGS)
debug: all


# Rule to build each target
$(TARGET_0): $(SOURCE_0)
	$(CC) $(CFLAGS) -o $(TARGET_0) $(SOURCE_0)

$(TARGET_1): $(SOURCE_1)
	$(CC) $(CFLAGS) -o $(TARGET_1) $(SOURCE_1)

$(TARGET_2): $(SOURCE_2)
	$(CC) $(CFLAGS) -o $(TARGET_2) $(SOURCE_2)


# Clean up binary files and artifacts
clean:
	rm -f $(TARGET_0) $(TARGET_1) $(TARGET_2)
	rm -f *.o
	rm -f *.out
	rm -f *~

.PHONY: all clean debug
