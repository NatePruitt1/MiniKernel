CCflags = -Wall -Wextra
Optimization = -O2
Cfiles = kernel.c mmio.c kuart.c kdebug.c
Bootloader = boot.S
Ofiles = $(Cfiles:%.c=%.o)
BootObj = $(Bootloader:%.S=%.o)
Outname = natekernel.elf

$(Outname): $(Ofiles) $(BootObj)
	aarch64-elf-gcc -T linker.ld -o $(Outname) -ffreestanding $(Optimization) -nostdlib $^ -lgcc

$(Ofiles): $(Cfiles)
	aarch64-elf-gcc -ffreestanding -c $^ $(Optimization) $(CCflags)

$(BootObj): $(Bootloader)
	aarch64-elf-as -c $^ -o $@

.PHONY: clean
clean:
	rm $(Ofiles)
	rm $(BootObj)
	rm $(Outname)

.PHONY: run
run:
	qemu-system-aarch64 -M raspi3 -serial null -serial stdio -kernel $(Outname)

.PHONY: open-docs
open-docs:
	xdg-open bcm2835-peripherals.pdf
