#include <stdio.h>
#include <string.h>
 


void type (char* file);
void pCommand (char* cmd);
void execute(char *file);
void dir();
 

int main()
{

	char buffer[512];

	while (1) {
		interrupt(0x21, 0, "Shell>\0",0,0);
		interrupt(0x21, 1, buffer,0,0);
		pCommand(buffer);

	}
 //  // Load config files, if any.
	// char line[80]; 
	// 	 while (1) {
	// 	 char dirC[4];
	// 	 dirC[0] = 'd';
	// 	 dirC[1] = 'i';
	// 	 dirC[2] = 'r';
	// 	 dirC[3] = '\0';

	// 	 char exC[7];
	// 	 exC[0] = 'e';
	// 	 exC[1] = 'x';
	// 	 exC[2] = 'e';
	// 	 exC[2] = 'c';
	// 	 exC[2] = 't';
	// 	 exC[2] = 'e';
	// 	 exC[3] = '\0';
		
	// 	char typeC[5];
	// 	typeC[0] = 't';
	// 	typeC[1] = 'y'
	// 	typeC[2] = 'c'
	// 	typeC[3] = 'e'
	// 	typeC[4] = '\0'
		
	//    interrupt(0x21, 0, "SHELL> \0", 0,0);

	//    interrupt(0x21, 1, line, 0,0);
	   
	//   if (compare(temp,line) ==1) {
	//   	interrupt(0x21, 0, "recognized \0", 0,0);
	//   } else if (compare(line,temp) ==0)
	//   {
	//   	interrupt(0x21, 0, "fail \0", 0,0);
	//   }

	//   if (compare(temp ))



	//   break;

 // 	}
	   
 //  return 0;




}

void pCommand(char* cmd) {
	if (cmd[0] == 't' && cmd[1] =='y' && cmd[2] == 'p' && cmd[3] =='e') {
		//interrupt(0x21, 0, "found", 0,0);
		type(cmd+5);
	} else if (cmd[0] == 'd' && cmd[1] =='i' && cmd[2] == 'r') {
		//dir();
	}else if (cmd[0] == 'e' && cmd[1] =='x' && cmd[2] == 'e'&& cmd[3] == 'c'&& cmd[4] == 'u'&& cmd[5] == 't'&& cmd[6] == 'e') {
		//interrupt(0x21, 0, "found", 0,0);
		execute(cmd + 8);
	} else {
		interrupt(0x21, 0, "comamnd not found", 0,0);
	}
}

void type(char * file) {
	char buffer[13312];
	int i ; 
	//buffer[0]='\0';
	for (i = 0 ; i <6; i++) {
		
	}
	file[6] = '\0';
	interrupt(0x21, 0, "\n", 0,0);
	interrupt(0x21,3,file,buffer,0);
	interrupt(0x21,0,buffer,0,0);
}

 void execute(char *file) {
 	 
	int i ; 
	//buffer[0]='\0';
	for (i = 0 ; i <6; i++) {
		
	}
	file[6] = '\0';
	interrupt(0x21, 0, file, 0,0);
	interrupt(0x21,4,file,0x2000,0);
    interrupt(0x21, 4, "shell\0", 0x2000, 0);
	//interrupt(0x21,0,buffer,0,0);
 }
 
 void dir () {
  //  char buffer[512];
 	// int secNum = 2;
 	//  interrupt(0x21, 2, , 2,0);
 	//  int k; 
 	//  for (k = 0 ; k < 16 ; k++) {
 	//  	if (buffer[k*32] ==0x0) {
 	//  		continue;
 	//  	}
 	//  	else {
 	 		 
 	 		 
 	//  			char name[7];
 	//  			name[0] = buffer[k*32+0];
 	//  			name[1] = buffer[k*32+1];
 	//  			name [2] = buffer[k*32+2];
 	//  			name [3] = buffer[k*32+3];
 	//  			name[4] = buffer[k*32+4];
 	//  			name[5] = buffer[k*32+5];
 	//  			name[6] = '\0';
 	//  			interrupt(0x21, 0, name, 0,0);
 	//  			interrupt(0x21, 0, "\n", 0,0);
 	 		
 	//  	}
 	//  }
 }

//Return 0 if not same other wise 1
// int compare(char a[],char b[]){
// 	int i;
//     for(i=0;a[i]!='\0';i++){
//         if(a[i]!=b[i])
//             return 0;
//     }
//     return 1;
// }
//  