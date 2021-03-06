# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Automatically generate lists of sources using wildcards .
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
C_HEADERS = $(wildcard kernel/*.h drivers/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# # Defaul build target
# all : os_image

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
os_image.bin : boot/bootloader.bin kernel/kernel.bin
	cat $^ > $@

# This builds the binary of our kernel from two object files :
# - The kernel_entry , which jumps to main () in our kernel
# - The compiled C kernel
kernel/kernel.bin : kernel/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Run qemu-system-x86_64 to simulate booting of our code.
run : os_image.bin
	qemu-system-i386 -fda $<


# Generic rule for compiling C code to an object file
# For simplicity, we assume C files depend on all header files.
%.o : %.c ${C_HEADERS}
	gcc -ffreestanding -c $< -o $@

# Assemble the kernel_entry.
%.o : %.asm
	nasm $< -f elf64 -o $@

# Generate bootloader bin.
%.bin : %.asm
	nasm $< -f bin -o $@


clean :
	rm -rf *.bin
	rm -rf kernel/*.o kernel/*.bin boot/*.bin drivers/*.o