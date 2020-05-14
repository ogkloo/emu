#include "instr.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {
  uint8_t tape[6];
  tape[0] = XOR;
  tape[1] = 0x00;
  tape[2] = ADDI;
  tape[3] = 0x10;
  tape[4] = 0xff;
  tape[5] = HALT;
  for(int i=0; i<6; i++) {
    printf("%02x", tape[i]);
  }
  printf("\n");
}
