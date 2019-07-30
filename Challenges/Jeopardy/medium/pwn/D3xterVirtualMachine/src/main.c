#include <stdio.h>
#include <assert.h>
#include "registers.h"

#define MAX_CODE_SIZE 0x10000


#ifdef DEBUG

void print_debug(char* s)
{
  printf("[DEBUG] %s\n", s);
}

void print_full_memory()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    printf("%8d ", get_memory(MEMORY_BASE+i) );

    if ( i % 10 == 9)
      printf("\n");
  }
}

void print_registers()
{
  printf("[NAX] = %9d   ", get_register(NAX) );
  printf("[NBX] = %9d   ", get_register(NBX) );
  printf("[NCX] = %9d   ", get_register(NCX) );
  printf("[NDX] = %9d\n", get_register(NDX) );
  printf("[NEX] = %9d   ", get_register(NEX) );
  printf("[NFX] = %9d   ", get_register(NFX) );
  printf("[NGX] = %9d   ", get_register(NGX) );
  printf("[NHX] = %9d\n", get_register(NHX) );
  printf("[NIX] = %9d   ", get_register(NIX) );
  printf("[NJX] = %9d   ", get_register(NJX) );
  printf("[NKX] = %9d   ", get_register(NKX) );
  printf("[NLX] = %9d\n", get_register(NLX) );
  printf("[NMX] = %9d   ", get_register(NMX) );
  printf("[NNX] = %9d   ", get_register(NNX) );
  printf("[NOX] = %9d   ", get_register(NOX) );
  printf("[NPX] = %9d\n", get_register(NPX) );
}

#endif


int main(int argc, char** argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setbuf(stdin, 0x0);
  setbuf(stdout,0x0);
  setbuf(stderr,0x0);

  init_registers();
  init_memory();

  char* assembly;

  assembly = (char*)malloc(MAX_CODE_SIZE*2);
  if(assembly == 0)
  {
    printf("CAN'T ALLOCATE MEMORY FOR CODE...\n");
    return 1;
  }

  printf("Insert your code in hex form.\n> ");
  char c;
  c = getchar();
  int i;
  int asm_hex_length;
  // READ UNTIL "\n"
  for (i = 0; i < MAX_CODE_SIZE && c != '\n'; i++)
  {
    assembly[i] = c;
    c = getchar();
  }
  asm_hex_length = i;

  // CORRECT MISSING 0 AT THE END
  if( asm_hex_length % 2 == 1 )
  {
    assembly[asm_hex_length] = '0';
    asm_hex_length++;
  }

  // ALLOCATE MEMORY FOR RAW ASSEMBLY
  char* new_asm;
  new_asm = (char*)malloc(asm_hex_length / 2 + 1);
  if(new_asm == 0)
  {
    printf("CAN'T ALLOCATE MEMORY FOR RAW ASSEMBLY...\n");
    return 1;
  }
  memset( new_asm, ASM_QUIT, asm_hex_length / 2 + 1 );

  char* assembly_hex = assembly;
  char* assembly_bin = new_asm;

  // CONVERT HEX ASSEMBLY TO RAW ASSEMBLY
  // 414243 -> ABC
  size_t count;
  size_t raw_assembly_length;
  for (raw_assembly_length = 0; raw_assembly_length < asm_hex_length; raw_assembly_length++)
  {
      sscanf(assembly_hex, "%2hhx", assembly_bin);
      assembly_hex += 2;
      assembly_bin ++;
  }
  free(assembly);

  assembly = new_asm;
  assembly[raw_assembly_length] = ASM_QUIT;


  #ifdef DEBUG
    printf("CODE: ");
    for (size_t i = 0; i < raw_assembly_length; i++)
      printf("%c", assembly[i] & 0xff);
    printf("\n");
  #endif

  printf("CODE Length: %d bytes\n", asm_hex_length / 2);


  int address;
  char curr_char;
  int register_, register_src;
  int value;

  for (i = 0; i < raw_assembly_length; i++)
  {
    curr_char = assembly[i] & 0xff;

    #ifdef DEBUG
      printf("FETCHED 0x%2.2X\n", curr_char & 0xff);
    #endif
    switch (curr_char & 0xff)
    {
      case ASM_SET:
        #ifdef DEBUG
          printf("ASM_SET\n");
        #endif

        i++;
        assert(i < raw_assembly_length);
        curr_char = assembly[i] & 0xff;
        switch (curr_char & 0xff)
        {
          case ASM_SET_MEMORY:

            // printf("PARSING ADDRESS: ");
            // Parse address
            address = 0;
            for (size_t jx = 0; jx < 4; jx++)
            {
              i++;
              assert(i < raw_assembly_length);
              curr_char = assembly[i];
              address = address << 8;
              address += curr_char & 0xff;
            }
            // printf("%p\n", address);

            i++;
            assert(i < raw_assembly_length);
            curr_char = assembly[i];
            register_ = curr_char & 0xff;

            #ifdef DEBUG
              printf("ASM_SET_MEMORY [%p] = REG:%d\n", address, register_);
            #endif
            set_memory_by_register( address, curr_char & 0xff );

            break;

          default:
            register_ = curr_char & 0xff;

            value = 0;
            // Parse value
            for (size_t jx = 0; jx < 4; jx++)
            {
              i++;
              assert(i < raw_assembly_length);
              curr_char = assembly[i];
              value = value << 8;
              value += curr_char & 0xff;
            }

            #ifdef DEBUG
              printf("ASM_SET_REGISTER [%d] = %d\n", register_, value);
            #endif

            set_register(register_, value);
            break;

        }
        break;

      case ASM_COPY:
        #ifdef DEBUG
          printf("ASM_COPY\n");
        #endif
        i++;
        assert(i < raw_assembly_length);
        curr_char = assembly[i];
        register_ = curr_char & 0xff;

        i++;
        assert(i < raw_assembly_length);
        curr_char = assembly[i];
        register_src = curr_char & 0xff;


        #ifdef DEBUG
          printf("ASM_COPY_REGISTER [%d] <- [%d]\n", register_&0xff, register_src&0xff);
        #endif

        copy_register(register_, register_src);
        break;

      case ASM_PRINT_INT:
        print_number();
        break;

      case ASM_PRINT_STR:
        // printf("PRINT_STRING: ");
        print_string();
        break;

      case ASM_OPEN_FD:
        open_fd();
        break;

      case ASM_READ_FD:
        read_from_fd();
        break;

      case ASM_CLOSE_FD:
        close_fd();
        break;

      case ASM_QUIT:
        #ifdef DEBUG
          printf("ASM_QUIT\n");
        #endif
        i = raw_assembly_length;
        break;

      default:
        printf("ILLEGAL ISTRUCTION 0x%2.2X\n", curr_char&0xff);
        return -1;
    }
    // END MAIN SWITCH CASE
  }

  #ifdef DEBUG
    print_debug("PRINT REGISTERS");
    print_registers();

    print_debug("PRINT FULL MEMORY");
    print_full_memory();
  #endif

  return 0;
}

/*

MANUAL

SET = 0xf1
{
  REGISTER = XXXXX   VALUE = YYYYY
  MEMORY = 0xfd
  {
    ADDRESS = XXXXX   REGISTER = XXXXX
  }
}

COPY = 0xf2
{
  REGISTER_1 = XXXXX, REGISTER_2 = YYYYY
}


// XOR = 0xf3 NOT IMPLEMENTED YET
PRINT = 0xf4
OPEN_FD = 0xf5
READ_FD = 0xf6
CLOSE_FD = 0xf7

void copy_register( char reg_1, char reg_2);

void set_register( char reg, int value );

void xor_registers( char reg_1, char reg_2);

void xor_register_by_value( char reg, int value);

void set_memory_by_register( int mem, char reg );

void print_number( );

void print_string( );

void open_fd( );

void read_from_fd( );

void close_fd( );

// flag.txt
set_register(NGX, 0x67616c66);
set_memory_by_register( MEMORY_BASE + 0x20, NGX );
set_register(NGX, 0x7478742e);
set_memory_by_register( MEMORY_BASE + 0x21, NGX );

// r
set_register(NGX, 0x72);
set_memory_by_register( MEMORY_BASE + 0x40, NGX );

open_fd();

// NDX     -> fd
// NCX     <- char_read
for (int i = 0; i < 60; i++)
{
  copy_register(NDX, NMX);
  read_from_fd();
  copy_register(NGX, NCX);
  print_string();
}

close_fd();

*/

//      // set_register(NGX, 0x67616c66);
//      010667616c66
//
//      // set_memory_by_register( MEMORY_BASE + 0x20, NGX );
//      01fd56789A2006
//
//      // set_register(NGX, 0x7478742e);
//      01067478742e
//
//      // set_memory_by_register( MEMORY_BASE + 0x21, NGX );
//      01fd56789A2106
//
//      // set_register(NGX, 0x7478742e);
//      010600000072
//
//      // set_memory_by_register( MEMORY_BASE + 0x40, NGX );
//      01fd56789A4006
//
//      // open_fd();
//      65
//
//      repeated by 60
//          // copy_register(NDX, NMX);
//          DE030c
//
//          // read_from_fd();
//          86
//
//          // copy_register(NGX, NCX);
//          DE0602
//
//          // print_string();
//          37
//
//      // close_fd();
//      fa
// 010667616c6601fd56789A200601067478742e01fd56789A210601060000007201fd56789A400665DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237DE030c86DE060237fa
