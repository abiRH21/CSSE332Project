#include <stdio.h>
#include <string.h>
void printString(char* input);
void readString(char *line);
void readSector(buffer, 30);
void readSector(char *chars, int secNum) ;
int mod(int a, int b);
int div(int a, int b);
void handleInterrupt21(int ax, int bx, int cx, int dx);
int main (){
  makeInterrupt21();
  interrupt(0x21, 4, "shell\0", 0x2000, 0);
while(1);
}
void printString(char* input) {
  int i;
  for(i=0;input[i]!=0x0;i++){
    interrupt(0x10, 0xe*256+input[i], 0, 0, 0);
  }
  return;
}
void readString(char *line) {
  int i, lineLength, ax;
  char charRead, backSpace, enter;
  lineLength = 80;
  i = 0;
  ax = 0;
  backSpace = 0x8;
  enter = 0xd;
  charRead = interrupt(0x16, ax, 0, 0, 0);
  while (charRead != enter && i < lineLength-2) {
    if (charRead != backSpace) {
      interrupt(0x10, 0xe*256+charRead, 0, 0, 0);
      line[i] = charRead;
      i++;
    } else {
      i--;
      if (i >= 0) {
        interrupt(0x10, 0xe*256+charRead, 0, 0, 0);
        interrupt(0x10, 0xe*256+'\0', 0, 0, 0);
        interrupt(0x10, 0xe*256+backSpace, 0, 0, 0);
      }
      else {
        i = 0;
      }
    }
    charRead = interrupt(0x16, ax, 0, 0, 0);
  }
  line[i] = 0xa;
  line[i+1] = 0x0;
  printString("\r\n");
  return;
}

void writeSector(char *chars, int secNum) {
  int ah = 3;
  int al = 1;
  int ax = ah*256 +al;
  int ch = div(secNum , 36);
  int cl = mod(secNum,18) +1;
  int dh = mod(div(secNum, 18),2);
  int cx = ch*256 + cl;
  int dx = dh*256;
  interrupt(0x13, ax, chars, cx, dx);
}


void readSector(char *chars, int secNum) {
  int ah = 2;
  int al = 1;
  int ax = ah*256 +al;
  int ch = div(secNum , 36);
  int cl = mod(secNum,18) +1;
  int dh = mod(div(secNum, 18),2);
  int cx = ch*256 + cl;
  int dx = dh*256;
  interrupt(0x13, ax, chars, cx, dx);
}
int mod(int a, int b){
  int temp;
  temp = a;
  while (temp >= b) {
    temp = temp-b;
  }
  return temp;
}
int div(int a, int b){
  int quotient;
  quotient = 0;
  while ((quotient + 1) * b <= a) {
    quotient++;
  }
  return quotient;
}
int readFile(char * fnameAdd, char *  bufferAdd) {
  char *fname = fnameAdd;
  char *buffer = bufferAdd;
  int i, j, k, equalFname, sector;
  char *dir;
  char dirBuffer[512];
  readSector(&dirBuffer,  2);
  dir = dirBuffer;
  for (i = 0; i < 16; i++) {
    if (dirBuffer[i*32] == 0x0)
      continue;
    equalFname = 1;
    j = 0;
    while (fname[j] != '\0') {
      if (j == 6){
        return 0;
      }
      if (dirBuffer[i*32+j] != fname[j]) {
        equalFname = 0;
        break;
      }
      j++;
    }
    while (j < 6) {
      if (dirBuffer[i*32+j] != '\0'){
        equalFname = 0;
        break;
      }
      j++;
    }
    if (equalFname){
      for (k = 0; k < 26; k++) {
        if (dirBuffer[i*32 + 6 + k] == 0x0)
          break;
        readSector(buffer + 512*k, dirBuffer[i*32 + 6 + k]);
      }
      return k*512;
    }
  }
  return 0;
}
int executeProgram(char * name, int segment) {
  char buffer[13312];
  int i, ret;
  ret = readFile(name, buffer);
  if (!ret){
    return 1;
  }
  for (i = 0; i < ret; i++) {
    putInMemory(segment, i, buffer[i]);
  }
  launchProgram(segment);
  return 0;
}
void terminate() {
  char exShell[11];
 // interrupt(0x21, 4, exShell, 0x2000, 0);

    char dirC[6];
    dirC[0] = 's';
    dirC[1] = 'h';
    dirC[2] = 'e';
    dirC[3] = 'l';
    dirC[4] = 'l';
    dirC[5] = '\0';

  interrupt(0x21, 4, dirC, 0x2000, 0);
}
void handleInterrupt21(int ax, int bx, int cx, int dx) {
  int ret;
  switch (ax) {
    case 0:
      printString(bx);
      break;
    case 1:
      readString(bx);
      break;
    case 2:
      readSector(bx, cx);
      break;
    case 3:
      ret = readFile(bx, cx);
      break;
    case 4:
      executeProgram(bx, cx);
      break;
    case 5:
      terminate();
      break;
      case 6:
      writeSector(bx,cx);
      break;
  }
}