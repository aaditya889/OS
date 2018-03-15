#define DIS_CTRL 0x3D4
#define DIS_DAT 0X3D5
#define MAX_ROW 25
#define MAX_COL 80
#define CHAR_SIZE 2
#define WHITE_ON_BLACK 0x0F
#define VIDEO_MEM 0xB8000
#include"headers/port_io.h"
extern void next_sel(unsigned char);

unsigned char stop_line;


unsigned short get_cursor(){
int offset;
port_byte_out(DIS_CTRL,14);
offset = port_byte_in(DIS_DAT)<<8;
port_byte_out(DIS_CTRL,15);
offset+=port_byte_in(DIS_DAT);

return offset*CHAR_SIZE;	//This returns the cell offset, i.e, we can directly write the next char data in the offset of video memory.
}

unsigned int get_offset(unsigned int row,unsigned int col){
unsigned int offset;
offset = row*MAX_COL+col;
return offset;

}

void set_cursor(int row,int col){

int offset;
offset = row*MAX_COL+col;

port_byte_out(DIS_CTRL,14);
port_byte_out(DIS_DAT,offset>>8);
port_byte_out(DIS_CTRL,15);
port_byte_out(DIS_DAT,offset);

}

void set_cursor_offset(unsigned int offset){

offset/=CHAR_SIZE;

port_byte_out(DIS_CTRL,14);
port_byte_out(DIS_DAT,offset>>8);
port_byte_out(DIS_CTRL,15);
port_byte_out(DIS_DAT,offset);

}

void init_display(){
char *vid_mem=(char *)VIDEO_MEM;
stop_line=0;
for(int i=0;i<=MAX_ROW*MAX_COL*CHAR_SIZE;i+=CHAR_SIZE){
vid_mem[i]=0;
vid_mem[i+1]=0x0f;
}
set_cursor(0,0);
}

void inc_cursor(unsigned int x){
int curr = get_cursor();
curr+=(x*CHAR_SIZE);
set_cursor_offset(curr);
}

void dec_cursor(unsigned int x){
int curr = get_cursor();
curr-=(x*CHAR_SIZE);
set_cursor_offset(curr);
}


void clearscr(){
init_display();
}

void strncpy(char *dest,char *sour,int num){					//write in another file!!
for(int i=0;i<num;i++)
*(dest++)=*(sour++);
}

void scroll(){
char *str2,*str1 = (char*)VIDEO_MEM;

if(stop_line>0)
stop_line--;

str2=str1+MAX_COL*CHAR_SIZE;
for(int i=0;i<MAX_ROW-1;i++){
strncpy(str1,str2,MAX_COL*CHAR_SIZE);
str1+=MAX_COL*CHAR_SIZE;
str2+=MAX_COL*CHAR_SIZE;
}
str2-=MAX_COL*CHAR_SIZE;
for(int i=0;i<MAX_COL;i++){
*(str2++)=0;
*(str2++)=0x0f;
set_cursor(MAX_ROW-1,0);
}
next_sel(72);
}


void print_len(char *str,int num,char attr){				//optimise for better performance!

int offset;
unsigned char line;
int x,y;
char *vid_mem = (char*)VIDEO_MEM;
if(attr==-1)
attr=0x0f;

while((num--)!=0){
offset = get_cursor();

if(*str == '\n'){
vid_mem[offset++]=' ';
vid_mem[offset++]=0x0f;
x = offset-CHAR_SIZE;
x/=MAX_COL*CHAR_SIZE;
if(x==MAX_ROW-1){
scroll();
x--;}
set_cursor(x+1,0);
str++;
continue; 
}

vid_mem[offset++] = *(str++);
vid_mem[offset++] = attr;
if(offset>MAX_COL*MAX_ROW*CHAR_SIZE-CHAR_SIZE)
scroll();
else
inc_cursor(1);
}
}


void print(char *str){
int len=0;
char *p=str;
while(*(p++)!=0)
len++;
print_len(str,len,-1);
}

void print_at(char *str,int att){
int len=0;
char *p=str;
while(*(p++)!=0)
len++;
print_len(str,len,att);
}


void print_char(char *c){
print_len(c,1,-1);
}

char get_char(int off){
char *vid_mem =(char*) VIDEO_MEM;
return vid_mem[off];
}


void backspace(){
int offset;
char x;
char *vid_mem;
vid_mem = (char*)VIDEO_MEM;
offset=get_cursor();
if(stop_line*MAX_COL*CHAR_SIZE>=offset)
return;
offset-=CHAR_SIZE;
if(vid_mem[offset]!=0){
vid_mem[offset++]=0;
vid_mem[offset++]=0x0f;
set_cursor_offset(offset-CHAR_SIZE);
return;
}

while(!get_char(offset))
offset-=CHAR_SIZE;

//offset+=CHAR_SIZE;

vid_mem[offset++]=0;
vid_mem[offset++]=0x0f;
set_cursor_offset(offset-CHAR_SIZE);

}



void select(unsigned char line){
char *vid_mem = (char*)VIDEO_MEM;
vid_mem+=line*MAX_COL*CHAR_SIZE;
for(int i=0;i<MAX_COL*CHAR_SIZE;i+=CHAR_SIZE)
vid_mem[i+1]=0xf0;
}


void unselect(unsigned char line){
char *vid_mem = (char*)VIDEO_MEM;
vid_mem+=line*MAX_COL*CHAR_SIZE;
for(int i=0;i<MAX_COL*CHAR_SIZE;i+=CHAR_SIZE)
vid_mem[i+1]=0x0f;
}

void set_stop(unsigned char x){
stop_line = x;
}

unsigned char get_stop(){
return stop_line;
}







