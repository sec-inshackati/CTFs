#include <stdio.h>
#include "aes.h"

#define bool char

BYTE key[33];


void print_flag()
{

  // printf("&KEY: %16.16x\n", key);
  // char flag[48]; // = "CTF{h3y_nUll_byt3_mu5t_b3_1n5ide_buff3r}\x00\x00\x00\x00\x00\x00\x00\x00";

  // "1fe6188874d0ad7dca879fcc6c9677d47159106df12a40d80473f1f6e8c32b8cc0a009c2c9dff7c048aaa892a05f2857";
  char flag_encrypted[48] = { 31, 230, 24, 136, 116, 208, 173, 125, 202, 135, 159, 204, 108, 150, 119, 212, 113, 89, 16, 109, 241, 42, 64, 216, 4, 115, 241, 246, 232, 195, 43, 140, 192, 160, 9, 194, 201, 223, 247, 192, 72, 170, 168, 146, 160, 95, 40, 87 };

  // char flag_decrypted[48];

  WORD key_schedule[60];
  BYTE enc_buf[17];
	BYTE dec_buf[17];

  asm("  sub r15, 0xca5b82 ; ");
  // asm("  sub r15, 10 ; ");
  // asm("  sub r15, 6 ; ");
  // asm("  sub r15, 7 ; ");
  // asm("  sub r15, 4 ; ");
  // asm("  sub r15, 2 ; ");
  // asm("  sub r15, 3 ; ");

  asm("  mov  BYTE PTR [r15], r14b ; ");       //        # 0x6070a0 <key>
  asm("  shr r14, 8; ");
  asm("  mov  BYTE PTR [r15 + 1], r14b ; ");   //        # 0x6070a1 <key+1>
  asm("  shr r14, 8; ");
  asm("  mov  BYTE PTR [r15 + 2], r14b ; ");   //        # 0x6070a2 <key+2>
  asm("  shr r14, 8; ");
  asm("  mov  BYTE PTR [r15 + 3], r14b ; ");   //        # 0x6070a3 <key+3>
  asm("  shr r14, 8; ");
  asm("  mov  BYTE PTR [r15 + 4], r14b ; ");   //        # 0x6070a4 <key+4>
  asm("  shr r14, 8; ");
  asm("  mov  BYTE PTR [r15 + 5], r14b ; ");   //        # 0x6070a5 <key+5>
  asm("  shr r14, 8; ");
  asm("  mov  BYTE PTR [r15 + 6], r14b ; ");   //        # 0x6070a6 <key+6>
  asm("  shr r14, 8; ");
  asm("  mov  BYTE PTR [r15 + 7], r14b ; ");   //        # 0x6070a7 <key+7>
  asm("  shr r14, 8; ");

  // printf("key:         0x%16.16x\n", key);
  // printf("password+10: 0x%16.16x\n", password+10);
  // printf("is_guest:    0x%16.16x\n", &is_guest);

  aes_key_setup(key, key_schedule, 256);

  memcpy(enc_buf, flag_encrypted, 16);
  enc_buf[16] = 0;
  aes_decrypt(enc_buf, dec_buf, key_schedule, 256);
  memcpy(flag_encrypted, dec_buf, 16);

  memcpy(enc_buf, flag_encrypted+16, 16);
  enc_buf[16] = 0;
  aes_decrypt(enc_buf, dec_buf, key_schedule, 256);
  memcpy(flag_encrypted+16, dec_buf, 16);

  memcpy(enc_buf, flag_encrypted+32, 16);
  enc_buf[16] = 0;
  aes_decrypt(enc_buf, dec_buf, key_schedule, 256);
  memcpy(flag_encrypted+32, dec_buf, 16);

  flag_encrypted[49] = '\0';

  printf(" FLAG: %s\n", flag_encrypted);

  fflush(stdout);

}


int main(int argc, char** argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);

  char password[10];
  char is_guest = 1;


  memset(password, 0, 10);

  // printf("password:    0x%16.16x\n", password);
  // printf("password+10: 0x%16.16x\n", password+10);
  // printf("is_guest:    0x%16.16x\n", &is_guest);
  printf("~~~~~~~~~~~~~~~~~~~~\n");
  printf("  Reserved area...\n");
  printf("~~~~~~~~~~~~~~~~~~~~\n\n");



  printf("Insert the password to get the flag: ");

  password[ read(0, password, 10) ] = '\0';


  printf("Current status:   %d ", is_guest);
  if (is_guest)
    printf("(GUEST)\n");
  else
    printf("(ADMIN)\n");

  if( is_guest == 0 )
  {
    printf("\nYou are admin. Here you are the flag.\n");
    asm( "mov r14, 0x80cb6a9421fe9029;" );
    asm( "mov r15, 0x12abc22;" );
    print_flag();
  }else{
    printf("\nGuests can't read flags...\n");
  }

  return 0;
}
