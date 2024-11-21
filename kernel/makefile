CCflags = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMflags = -Iinclude
Bdir = out

all: kernel8.img

./$(Bdir)/%_c.o: ./%.c
	mkdir -p $(@D)
	aarch64-elf-gcc $(CCflags) -MMD -c $< -o $@ 

./$(Bdir)/%_s.o: ./%.S
	aarch64-elf-gcc $(ASMflags) -MMD -c $< -o $@

Cfiles = $(wildcard ./*.c)
Sfiles = $(wildcard ./*.S)
Ofiles = $(Cfiles:./%.c=./$(Bdir)/%_c.o)
Ofiles += $(Sfiles:./%.S=./$(Bdir)/%_s.o)

kernel8.img: ./linker.ld $(Ofiles)
	aarch64-elf-ld -T ./linker.ld -o $(Bdir)/kernel8.elf $(Ofiles)
	aarch64-elf-objcopy $(Bdir)/kernel8.elf -O binary $(Bdir)/kernel8.img

.PHONY: clean
clean:
	rm -r $(Bdir)

.PHONY: run
run:
	qemu-system-aarch64 -M raspi3 -serial null -serial stdio -device loader,file=$(Bdir)/kernel8.img

.PHONY: open-docs
open-docs:
	xdg-open ../bcm2835-peripherals.pdf
