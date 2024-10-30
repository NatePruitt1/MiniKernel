CCflags = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
Optimization = -O2
Cfiles = $(wildcard ./*.c)
Bootloader = $(wildcard ./*.S)
Ofiles = $(Cfiles:%.c=%.o)
BootObj = $(Bootloader:%.S=%.o)
Outname = ./out/natekernel.elf
Img = ./out/kernel8.img

$(Img): $(Outname)
	aarch64-elf-objcopy $< -O binary $@

$(Outname): $(Ofiles) $(BootObj)
	aarch64-elf-gcc -T linker.ld -o $(Outname) -ffreestanding $(Optimization) -nostdlib $^ -lgcc

$(Ofiles): $(Cfiles)
	aarch64-elf-gcc -c $^ $(Optimization) $(CCflags)

$(BootObj): $(Bootloader)
	aarch64-elf-gcc -Iinclude -c $^ -o $@

.PHONY: clean
clean:
	rm $(Ofiles)
	rm $(BootObj)
	rm $(Outname)
	rm $(Img)

.PHONY: open-docs
open-docs:
	xdg-open bcm2835-peripherals.pdf
