extern void print(char*);
extern void print_at(char*,char);
extern void port_byte_out(unsigned short,unsigned char);
extern void load_idt(void *);
extern void keyboard_handler_asm();
extern void init_display();
extern void clearscr();
extern void main();
#include"load_data.c"


void keyboard_handler();

struct idt_entry{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


struct idt_entry idt[250];
struct idt_ptr idtp;


void init_idtentry(){
char *a;
a = (char*)&idt;
for(int i=0;i<256*sizeof(struct idt_entry);i++)
a[i]=0;

idtp.limit = (sizeof(struct idt_entry)*250)-1;
idtp.base =(unsigned int) &idt;

}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void init_pic(){
//1. Initialise the PIC (ICW1):
port_byte_out(0x0020,0x11);
port_byte_out(0x00A0,0x11);
//2. Send the offset numbers (ICW2): 0x21 and 0xA1 are the data ports of PIC1 and PIC2, 0x20 and 0xA0 were the command ports of the same PICs.
port_byte_out(0x0021,0x20);
port_byte_out(0x00A1,0x28);
//3. ICW3 cascading:
port_byte_out(0x0021,0x04);
port_byte_out(0x00A1,0x02);
//4. ICW4 environment information:
port_byte_out(0x0021,0x01);
port_byte_out(0x00A1,0x01);
//5. Masking
//The keyboard IRQ line is 1 in PIC1, so to only allow keyboard interrupts to occur, mask the data port of A1 with 0xff and 0x21 with 0xFD.
port_byte_out(0x0021,0xFD);
port_byte_out(0x00A1,0xFF);
}

void make_idt(){
init_display();
clearscr();
print("Successfully loaded 32 bit protected mode from 16 bit real mode...\nUsing port I/O for Cursor control!\n");
print("Changing front and background colour...\n");
print_at("Colour changed\n",77);
print("Inside make_idt()\nInitialising idt and pic...");
init_idtentry();
init_pic();

print("Initialised idt and pic!\nMaking keyboard handler entry...\n");
idt_set_gate(0x21,(unsigned long)&keyboard_handler_asm,0x08,0x8e);			//0x8e is for interrupt gate, 0x08 is the entry in gdt.
print("keyboard entry made, loading idt...\n");
load_idt((void *)&idtp);    //remove comments when idt has been made!
print("idt loaded!\n");
load_data();
print("Launching the kernel...\n");
main();
}





















