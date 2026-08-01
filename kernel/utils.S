.globl delay
delay:
	subs x0, x0, #1
	bne delay
	ret

.globl mmio_write
.globl put32
mmio_write:
put32:
	str w1,[x0]
	ret

.globl mmio_read
.globl get32
mmio_read:
get32:
	ldr w0,[x0]
	ret