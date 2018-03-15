
// "= a " ( result ) means : put AL register in variable RESULT when finished
// " d " ( port ) means : load EDX with port
// " a " ( val ) means : load EAX with val


void port_byte_out(unsigned short port,unsigned char val){

__asm__("out %%al, %%dx" : : "a" (val), "d"(port));

}

void port_word_out(unsigned short port,unsigned short val){

__asm__("out %%ax, %%dx" : : "a"(val), "d"(port));

}

unsigned char port_byte_in(unsigned short port){
unsigned char result;

__asm__("in %%dx, %%al" : "=a"(result) : "d"(port));

return result;

}

unsigned short port_word_in(unsigned short port){
unsigned short result;

__asm__("in %%dx, %%ax" : "=a"(result) : "d"(port));

return result;

}
