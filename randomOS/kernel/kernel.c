#include "../drivers/screen.h"
#include "./cpu/gdt.h"
#include "./cpu/idt.h"

void init_screen(){
	char *str1 = "RandomOS kernel";
	char *str2 = "version : v1.0\n";

	clear_screen();
	kprint_at(str1,3,35);
	kprint_at(str2,5,35);
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