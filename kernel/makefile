ARMGNU ?= aarch64-linux-gnu
CCflags = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMflags = -Iinclude
Bdir = out

all: kernel8.img

./$(Bdir)/%_c.o: ./%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(CCflags) -MMD -c $< -o $@ 

./$(Bdir)/%_s.o: ./%.S
	$(ARMGNU)-gcc $(ASMflags) -MMD -c $< -o $@

Cfiles = $(wildcard ./*.c)
Sfiles = $(wildcard ./*.S)
Ofiles = $(Cfiles:./%.c=./$(Bdir)/%_c.o)
Ofiles += $(Sfiles:./%.S=./$(Bdir)/%_s.o)

kernel8.img: ./linker.ld $(Ofiles)
	$(ARMGNU)-ld -T ./linker.ld -o $(Bdir)/kernel8.elf $(Ofiles)
	$(ARMGNU)-objcopy $(Bdir)/kernel8.elf -O binary $(Bdir)/kernel8.img

.PHONY: clean
clean:
	rm -r $(Bdir)