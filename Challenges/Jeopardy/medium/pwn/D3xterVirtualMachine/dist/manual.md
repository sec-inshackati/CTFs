# D3xter98's Virtual Machine
_____

## Manual

| OPERATOR           |     CODE    | Description                     |
| ------------------ | :---------: | ------------------------------- |
| `ASM_SET`          |  `0x01`   | *Moves a value in a register.*  |
| `ASM_SET_MEMORY`   |  `0x01FD` | *Moves the value of a register in a memory region. * |
| `ASM_COPY`         |  `0xDE`   | *Copies the value of a register to another register.* |
| `ASM_QUIT`         |  `0xCD`   | *Quits the program.* |
| `ASM_PRINT_INT`    |  `0x14`   | *Prints the value of register*  `NFX` *as integer.*  |
| `ASM_PRINT_STR`    |  `0x37`   | *Prints the value of register*  `NGX` *as string.* |
| `ASM_OPEN_FILE_FD` |  `0x65`   | *Open file stored at* `memory:0x56789A20` with permissions stored at `memory:0x56789A40` |
| `ASM_READ_FD`      |  `0x86`   | *Reads one byte from file descriptor stored in `NDX` and puts result in register `NCX`.* |
| `ASM_CLOSE_FD`     |  `0xFA`   | *Closes file descriptor stored in `NMX` register.* |

_____

## Example usage

### ASM_SET
`SET REGISTER, VALUE;`

| Assembly | Hex Code |
| - | - |
| `SET NAX, 0x41424344;` | `010041424344` |
| `SET NBX, 0x41424344;` | `010141424344` |

_____

### ASM_SET_MEMORY
`SET_MEMORY MEMORY_ADDRESS, REGISTER;`

| Assembly | Hex Code |
| - | - |
| `SET_MEMORY 0x56789A00, NAX;` | `01FD56789A0000` |
| `SET_MEMORY 0x56789A22, NBX;` | `01FD56789A2201` |

_____

### ASM_COPY
`COPY_REGISTER REGISTER_1, REGISTER_2;`

| Assembly | Hex Code |
| - | - |
| `COPY_REGISTER NAX, NBX;` | `DE0001` |
| `COPY_REGISTER NFX, NHX;` | `DE0507` |

_____


### ASM_QUIT
`QUIT;`

| Assembly | Hex Code |
| - | - |
| `QUIT;` | `CD` |

_____

### ASM_PRINT_INT
`PRINT_INT;`

| Assembly | Hex Code |
| - | - |
| `PRINT_INT;` | `14` |

_____

### ASM_PRINT_STR
`PRINT_STR;`

| Assembly | Hex Code |
| - | - |
| `PRINT_STR;` | `37` |

_____

### ASM_OPEN_FILE_FD
`OPEN_FILE;`

| Assembly | Hex Code |
| - | - |
| `OPEN_FILE;` | `65` |

_____

### ASM_READ_FD
`READ_CHAR_FROM_FD;`

| Assembly | Hex Code |
| - | - |
| `READ_CHAR_FROM_FD;` | `86` |

_____

### ASM_CLOSE_FD
`CLOSE_FILE;`

| Assembly | Hex Code |
| - | - |
| `CLOSE_FILE;` | `FA` |
