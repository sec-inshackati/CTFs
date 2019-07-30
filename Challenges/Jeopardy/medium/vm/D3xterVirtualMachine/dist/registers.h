#ifndef REGISTERS_H
#define REGISTERS_H

#define N_REGISTERS 16
int registers[ N_REGISTERS ];

#define MEMORY_SIZE 0x60
#define MEMORY_BASE 0x56789A00
int memory[ MEMORY_SIZE ];


#define ASM_SET        0x01
#define ASM_COPY       0xDE
#define ASM_QUIT       0xCD
#define ASM_SET_MEMORY 0xFD
#define ASM_PRINT_INT  0x14
#define ASM_PRINT_STR  0x37
#define ASM_OPEN_FD    0x65
#define ASM_READ_FD    0x86
#define ASM_CLOSE_FD   0xFA

#define NAX 0
#define NBX 1
#define NCX 2
#define NDX 3
#define NEX 4
#define NFX 5
#define NGX 6
#define NHX 7
#define NIX 8
#define NJX 9
#define NKX 10
#define NLX 11
#define NMX 12
#define NNX 13
#define NOX 14
#define NPX 15

#define NAX_PTR &( registers[NAX] )
#define NBX_PTR &( registers[NBX] )
#define NCX_PTR &( registers[NCX] )
#define NDX_PTR &( registers[NDX] )
#define NEX_PTR &( registers[NEX] )
#define NFX_PTR &( registers[NFX] )
#define NGX_PTR &( registers[NGX] )
#define NHX_PTR &( registers[NHX] )
#define NIX_PTR &( registers[NIX] )
#define NJX_PTR &( registers[NJX] )
#define NKX_PTR &( registers[NKX] )
#define NLX_PTR &( registers[NLX] )
#define NMX_PTR &( registers[NMX] )
#define NNX_PTR &( registers[NNX] )
#define NOX_PTR &( registers[NOX] )
#define NPX_PTR &( registers[NPX] )

void init_registers();
void init_memory();

// REGISTERS OPERATIONS
void copy_register( char reg_1, char reg_2);
int get_register( char reg );
void set_register( char reg, int value );

// MEMORY OPERATIONS
int is_valid_memory_index( int mem );
int get_real_memory_index( int mem );
int get_memory( int mem );
void set_memory( int mem, int value );
void set_memory_by_register( int mem, char reg );
int get_real_memory_address( int index );

// PRINT FUNCTION OPERATIONS
void print_number( );
void print_string( );

// FILE OPERATIONS
void open_fd( );
void read_from_fd( );
void close_fd( );


#endif
