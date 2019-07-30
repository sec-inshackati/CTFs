#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include "registers.h"

// REGISTRY OPERATIONS

void init_registers()
{
  print_debug("INIT REGISTERS");
  for (int i = 0; i < N_REGISTERS; i++)
    xor_registers( i, i );
}

void copy_register( char reg_1, char reg_2)
{
  assert( reg_1 >= 0 && reg_1 < N_REGISTERS );
  registers[reg_1] = get_register(reg_2);
}


int get_register( char reg )
{
  assert( reg >= 0 && reg < N_REGISTERS );
  return registers[reg];
}

void set_register( char reg, int value )
{
  assert( reg >= 0 && reg < N_REGISTERS );
  registers[reg] = value;
}

void xor_registers( char reg_1, char reg_2)
{
  registers[reg_1] = get_register(reg_1) ^ get_register(reg_2);
}

void xor_register_by_value( char reg, int value)
{
  registers[reg] = get_register(reg) ^ value;
}



// MEMORY OPERATIONS
void init_memory()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    set_memory(MEMORY_BASE+i, 0);
}

int is_valid_memory_index( int mem )
{
  return ( mem >= 0 && mem < MEMORY_SIZE );
}

int get_real_memory_index( int mem )
{
  mem -= MEMORY_BASE;
  assert( mem >= 0 && mem < MEMORY_SIZE );
  return mem;
}

int get_memory( int mem )
{
  mem = get_real_memory_index(mem);
  return memory[mem];
}

void set_memory( int mem, int value )
{
  mem = get_real_memory_index(mem);
  // printf("SET [%d] to %d \n", mem, value);
  memory[mem] = value;
}

void set_memory_by_register( int mem, char reg )
{
  set_memory(mem, get_register(reg) );
}

int get_real_memory_address( int index )
{
  assert( index >= 0 && index < MEMORY_SIZE );
  return memory + index;
}

// PRINT FUNCTION OPERATIONS
void print_number( )
{
  printf("%d\n", *NFX_PTR );
}

// prints a string from memory pointed to register NGX
void print_string( )
{
  // printf("REGISTER_TO_PRINT: %d", get_register(NGX) );
  printf("%s\n", NGX_PTR );
}


// FILE OPERATIONS
void open_fd( )
{
  // memory[0x20] -> flag.txt
  // memory[0x40] -> r
  // NMX          <- fd
  FILE* fp;
  // printf("%p\n", get_real_memory_address(0x20));
  // printf("%s\n", get_real_memory_address(0x20));
  // printf("%p\n", get_real_memory_address(0x40));
  // printf("%s\n", get_real_memory_address(0x40));
  fp = fopen( get_real_memory_address(0x20), get_real_memory_address(0x40) );
  if( fp == NULL)
  {
    print_debug("CANT OPEN FILE");
    set_register( NMX, 0 );
    return;
  }
  print_debug("FILE OPENED");
  set_register( NMX, fp );
}

void read_from_fd( )
{
  // NDX     -> fd
  // NCX     <- char_read
  char c;

  if( get_register(NDX) == 0 )
    return;

  c = fgetc( get_register(NDX) );

  if( feof( get_register(NDX) ) )
  {
    print_debug("END OF FILE");
    set_register( NCX, 0 );
    return;
  }

  set_register( NCX, c );

}


void close_fd( )
{
  // NMX          -> fd
  FILE* fp = get_register(NMX);
  if( fp == NULL) return;
  print_debug("FILE CLOSED");
  fclose(fp);
}
