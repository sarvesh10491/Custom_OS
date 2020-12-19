#include "../drivers/screen.h"
#include "../drivers/port.h"

void main(){
    clear_screen();
    const char *str = "BareboneOS";
    char* vidptr = (char*) 0xb8000;
    *vidptr = 'X';
    // kprint_at(str, 40, 20);

    // int i = 0, j = 0;
    // while(str[j] != '\0') {
	// 	/* the character's ascii */
	// 	vidptr[i] = str[j];
	// 	/* attribute-byte: give character black bg and light grey fg */
	// 	vidptr[i+1] = 0x07;
	// 	++j;
	// 	i = i + 2;
	// }

}