#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

enum instructions {
  ADD,
  AND,
  CMP,
  HALT,
  IN,
  JEQ,
  JG,
  JL,
  JMP,
  LOAD,
  MEMSIZE,
  NOT,
  OR,
  OUT,
  STORE,
  SUB,
  XOR,
};

struct memory {
  unsigned int size;
  uint8_t *memory;
};

struct registers {
  uint8_t *general_registers;
  uint16_t address_register;
  uint16_t instruction_pointer;
  uint8_t flags;
};

void initregs(struct registers *regs, int size) {
  regs->general_registers = (uint8_t*) malloc(size);
  regs->instruction_pointer = 0;
  regs->address_register = 0;
  regs->flags = 0;
}

void initmem(struct memory *mem, unsigned int size) {
  mem->memory = (uint8_t*) malloc(size);
  mem->size = size;
}

void destroymem(struct memory *mem) {
  free(mem->memory);
  mem->size = 0;
}

void dumpmem(struct memory *mem) {
  for(int i=0; i < mem->size; i++)
    printf("%x", mem->memory[i]);
  printf("\n");
}

void memclear(struct memory *mem, unsigned int low_bound, unsigned int high_bound) {
  for(int i=low_bound; i < high_bound; i++) 
    mem->memory[i] = 0;
}

void load(struct memory *mem, unsigned int offset, uint8_t *reg) {
  *reg = mem->memory[offset];
}

void store(struct memory *mem, unsigned int offset, uint8_t i) {
  mem->memory[offset] = i;
}

void run(struct memory *mem, struct registers *reg) {
  for(int i=reg->instruction_pointer; i < mem->size; i++) {
    uint8_t instruction = mem->memory[i];
    uint8_t args;
    if (i < mem->size)
      args = mem->memory[i+1];
    switch(instruction) {
      // Add the two registers specified in the next bit
      // If there are too few registers to accomodate it, crash.
      case ADD:
        reg->general_registers[(args & 0xf0) >> 4] += reg->general_registers[(args & 0x0f)];
        i++;
        break;
      case AND:
      case CMP:
      case HALT:
        i = mem->size;
        break;
      case IN:
      case JEQ:
      case JG:
      case JL:
      case JMP:
      case LOAD:
      case MEMSIZE:
      case NOT:
      case OR:
      case OUT:
      case STORE:
        // Takes the bottom 4 bits of the next byte to select a register
        // Then copies that to the byte specified after that
        // If you run out of memory here god help you.
        mem->memory[mem->memory[i+2]] = reg->general_registers[args & 0x0f];
        break;
      case SUB:
      case XOR:
        break;
    }
  }
}

int main(int argc, char **argv) {
  int size = 8;
  // Maximum number of registers without pain
  int num_regs = 16;
  int option;
  while((option = getopt(argc, argv, "s:r:")) != -1) {
    switch(option) {
      case 's':
        size = atoi(optarg);
        break;
      case 'r':
        if(num_regs > 16) {
          fprintf(stderr, "Maximum 16 registers.\n");
          break;
        }
        num_regs = atoi(optarg);
        break;
    }
  }

  struct memory main_memory;
  initmem(&main_memory, size);
  memclear(&main_memory, 0, main_memory.size);

  struct registers regs;
  initregs(&regs, num_regs);
  regs.general_registers[1] = 10;
  main_memory.memory[0] = ADD;
  main_memory.memory[1] = 0x01;
  main_memory.memory[2] = STORE;
  main_memory.memory[3] = 0x01;
  main_memory.memory[4] = 0xa;
  main_memory.memory[5] = HALT;
  dumpmem(&main_memory);

  run(&main_memory, &regs);

  dumpmem(&main_memory);

  destroymem(&main_memory);
  free(regs.general_registers);

  return 0;
}
