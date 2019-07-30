#include <stdio.h>
#include <assert.h>
#include "registers.h"

#define MAX_CODE_SIZE 0x10000


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
        i++;
        assert(i < raw_assembly_length);
        curr_char = assembly[i] & 0xff;
        switch (curr_char & 0xff)
        {
          case ASM_SET_MEMORY:
            address = 0;
            for (size_t jx = 0; jx < 4; jx++)
            {
              i++;
              assert(i < raw_assembly_length);
              curr_char = assembly[i];
              address = address << 8;
              address += curr_char & 0xff;
            }
            i++;
            assert(i < raw_assembly_length);
            curr_char = assembly[i];
            register_ = curr_char & 0xff;
            set_memory_by_register( address, curr_char & 0xff );
            break;

          default:
            register_ = curr_char & 0xff;
            value = 0;
            for (size_t jx = 0; jx < 4; jx++)
            {
              i++;
              assert(i < raw_assembly_length);
              curr_char = assembly[i];
              value = value << 8;
              value += curr_char & 0xff;
            }
            set_register(register_, value);
            break;

        }
        break;

      case ASM_COPY:
        i++;
        assert(i < raw_assembly_length);
        curr_char = assembly[i];
        register_ = curr_char & 0xff;
        i++;
        assert(i < raw_assembly_length);
        curr_char = assembly[i];
        register_src = curr_char & 0xff;
        copy_register(register_, register_src);
        break;

      case ASM_PRINT_INT: print_number(); break;
      case ASM_PRINT_STR: print_string(); break;
      case ASM_OPEN_FD: open_fd(); break;
      case ASM_READ_FD: read_from_fd(); break;
      case ASM_CLOSE_FD: close_fd(); break;

      case ASM_QUIT: i = raw_assembly_length; break;

      default: printf("ILLEGAL ISTRUCTION 0x%2.2X\n", curr_char & 0xff); return -1;
    }
  }

  return 0;
}
