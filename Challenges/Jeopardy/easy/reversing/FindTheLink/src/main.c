#define BYTE char

#define WRONG_PASSWORD_1      0x8ed12e17
#define WRONG_PASSWORD_2      0x4fd3cde5
#define WRONG_PASSWORD_3      0x9b895c46
#define WRONG_PASSWORD_4      0x6062da3e
#define WRONG_PASSWORD_5      0xf5ae2c9d
#define WRONG_PASSWORD_6      0x38e701bf

#define CORRECT_PASSWORD  0xcafebabe

int check_password(char* password)
{
    printf("Checking password...\n");

    if ( strlen(password) != 29 ) return WRONG_PASSWORD_1;
    printf("Check 1 PASSED.\n");

    if(
      password[1] != password[2] ||
      password[1] != password[10] ||
      password[2] != password[27]
    )
      return WRONG_PASSWORD_2;

    printf("Check 2 PASSED.\n");

    if(
      password[0] != password[11] ||
      password[5] != ':' ||
      password[0] != password[22]
    )
      return WRONG_PASSWORD_3;

    printf("Check 3 PASSED.\n");

    if(
      password[4] - password[3] != 3 ||
      password[6] != password[7] ||
      password[6] != password[18]
    )
      return WRONG_PASSWORD_4;

    printf("Check 4 PASSED.\n");

    if(
      password[8] != 'g' ||
      password[10] != password[11] + 12 ||
      password[11] != 'h' ||
      password[12] != 'u' ||
      password[13] * password[16] != 10878 ||
      password[14] != '.' ||
      password[15] != 'c' ||
      password[17] != 'm'
    )
      return WRONG_PASSWORD_5;

    printf("Check 5 PASSED.\n");

    if (
      password[19] != password[28] ||
      password[4] != password[21] ||
      password[20] != 'n' ||
      password[24] - password[23] != 2 ||
      password[24] - password[26] != 2 ||
      password[25] != 'k'
    )
    return WRONG_PASSWORD_6;

    printf("Check 6 PASSED.\n");

    return CORRECT_PASSWORD;
}

void format_flag(char* password)
{
  int i;
  for (i = 0; password[i] != '\0'; i++)
  {
      if(
         password[i] == '/' ||
         password[i] == '~' ||
         password[i] == ':' ||
         password[i] == '.'
        )
      {
        password[i] = '_';
        continue;
      }

      if( password[i] == 'a' ) { password[i] = '4'; continue; }
      if( password[i] == 'e' ) { password[i] = '3'; continue; }
      if( password[i] == 'i' ) { password[i] = '1'; continue; }
      if( password[i] == 'o' ) { password[i] = '0'; continue; }

  }
}

void print_flag(char* password)
{
  format_flag(password);
  printf("  FLAG: CTF{%s_r3ver5ing_c4n_be_h4rd3r_4nd_h4rd3r}\n\n", password);
}

int main(int argc, char** argv)
{
  char password[36];
  int result;

  printf("Insert the secret link: ");
  scanf("%30s", password);
  printf("You inserted \"%s\"\n\n", password);

  result = check_password(password);

  printf("\nResult: 0x%8.8x\n", result);

  if( result != CORRECT_PASSWORD )
  {
    printf("WRONG! :(\n");
    if( result == WRONG_PASSWORD_1 )
    {
      printf("Here's an hint for you...\n");
      printf("Link: ??????/????????????in?ha??ati\n\n");
    }
    return -1;
  }

  printf("CORRECT! :)\n\n");

  print_flag(password);



  return 0;
}
