#include "../drivers/screen.h"
#include "./cpu/gdt.h"
#include "./cpu/idt.h"

void init_screen(){
	char *str1 = "RandomOS kernel";
	char *str2 = "v1.0";

	clear_screen();
	kprint(str1);
	kprint_at(str2,5,20);
}

void init_descriptor_tables(){
	init_gdt();
	init_idt();
}

void kmain(void)
{
	init_descriptor_tables();
	init_screen();
	/* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");

	return;
}