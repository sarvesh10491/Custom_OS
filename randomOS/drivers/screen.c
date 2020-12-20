#include "screen.h"
#include "../include/port.h"

char *screen = (char*)VIDEO_ADDRESS;
int screen_size = MAX_COLS * MAX_ROWS;

// Declaration of private functions
int print_char(char c, int row, int col);
int get_cursor_offset();
void set_cursor_offset(int offset);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// /**********************************************************
//  * Public Kernel API functions                            *
//  **********************************************************/

void clear_screen(){
    int i = 0;

    for(i = 0; i < screen_size; i++){
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }

    set_cursor_offset(get_offset(0, 0));
}


void kprint_at(char *message, int row, int col){
    int i = 0, j = 0;

    if(col >= 0 && row >= 0)
        i = get_offset(col, row);
    else{
        i = get_cursor_offset();
        row = get_offset_row(i);
        col = get_offset_col(i);
    }

    /* This loop writes the string to video memory */
	while(message[j] != '\0') {
        i = print_char(message[j], row, col);
        row = get_offset_row(i);
        col = get_offset_col(i);
		++j;
	}
}


void kprint(char *message){
    kprint_at(message, -1, -1);
}


// /**********************************************************
//  * Private kernel functions                               *
//  **********************************************************/
int print_char(char c, int row, int col){
    /* Error control: print a red 'E' if the coords aren't right */
    if(col >= MAX_COLS || row >= MAX_ROWS){
        screen[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        screen[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;

    if (col >= 0 && row >= 0) 
        offset = get_offset(col, row);
    else 
        offset = get_cursor_offset();

    if(c == '\n'){
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } 
    else{
        screen[offset] = c;
        screen[offset+1] = WHITE_ON_BLACK;
        offset += 2;
    }
    set_cursor_offset(offset);

    return offset;
}


int get_cursor_offset(){
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;    // High byte: << 8
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    
    return offset * 2;      // Position * size of character cell 
}


void set_cursor_offset(int offset){
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row){ 
    return 2 * (row * MAX_COLS + col); 
}

int get_offset_row(int offset){ 
    return offset / (2 * MAX_COLS); 
}

int get_offset_col(int offset){ 
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; 
}