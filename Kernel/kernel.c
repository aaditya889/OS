extern void print_at(char*,char);
extern void print(char*);
extern void select(unsigned char);
extern void unselect(unsigned char);
extern unsigned short get_cursor();
extern void set_stop();
extern unsigned char get_stop();


unsigned char sel;

void main(){

print("Inside kernel!\n");
sel=get_cursor()/160;
select(sel);
set_stop(sel);
while(1){;}

}

void next_sel(unsigned char key){

switch(key){
case 72:
if(sel==get_stop())
return;
unselect(sel--);
select(sel);
break;

case 80:
if(sel==24)
return;
unselect(sel++);
select(sel);
break;
}

}








