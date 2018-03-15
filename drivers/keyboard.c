extern void port_byte_out(unsigned short,unsigned char);
extern unsigned char port_byte_in(unsigned short);
extern void print_char(char*);
extern void backspace();
extern void next_sel(unsigned char);
#define KEYBOARD_STATUS 0X64
#define KEYBOARD_DATA 0X60


char scan_codes[100];

void keyboard_driver(){
/*We first read port 0x64 to get the status. If the lowest bit of the status is 0, it means the buffer is empty and there is no data to read. In other cases, we can read the data port 0x60. This port will give us a keycode of the key pressed. Each keycode corresponds to each key on the keyboard. */
//scan code: Q-P = 16-25 A-L = 30-38 Z-M = 44-50

unsigned char stat;
char key;
port_byte_out(0x20,0x20);
stat = port_byte_in(KEYBOARD_STATUS);
if(stat&0x01){
key = port_byte_in(KEYBOARD_DATA);
if(key<0)
return;
if(key==14){
backspace();
return;}

if(key==72 || key==80){
next_sel((unsigned char)key);
return;
}

if(key>=16 && key<=57)
print_char(&scan_codes[key]);

}
}

