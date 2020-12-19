#include "../drivers/screen.h"
#include "../drivers/port.h"

void init_screen(){
	char *str1 = "RandomOS kernel";
	char *str2 = "v1.0";
	clear_screen();
	kprint(str1);
	kprint_at(str2,5,20);
}

void kmain(void)
{
	init_screen();
	return;
}