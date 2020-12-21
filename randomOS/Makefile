# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Automatically generate lists of sources using wildcards .
C_SOURCES = $(wildcard kernel/*.c kernel/cpu/*.c drivers/*.c include/*.c)
C_HEADERS = $(wildcard kernel/*.h kernel/cpu/*.h drivers/*.h include/*.h)

# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o boot/boot.o kernel/cpu/gdtS.o}

# This builds the binary of our kernel from two object files :
# - The kernel_entry , which jumps to main () in our kernel
# - The compiled C kernel
os_image : ${OBJ}
	ld -m elf_i386 -T boot/link.ld -o $@ $^

# Run qemu-system-x86_64 to simulate booting of our code.
run : os_image
	qemu-system-i386 -kernel $<


# Generic rule for compiling C code to an object file
# For simplicity, we assume C files depend on all header files.
%.o : %.c ${C_HEADERS}
	gcc -m32 -ffreestanding -c $< -o $@

# Assemble the kernel_entry.
%.o : %.asm
	nasm $< -f elf32 -o $@


clean :
	rm -rf os_image
	rm -rf kernel/*.o kernel/cpu/*.o boot/*.o drivers/*.o include/*.o