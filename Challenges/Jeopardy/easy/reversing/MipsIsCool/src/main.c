#include <stdio.h>
#include <string.h>

void print_flag()
{
  printf("\tCT");
  printf("F{");
  printf("L1");
  printf("nu");
  printf("x_");
  printf("15");
  printf("_f");
  printf("0r");
  printf("_b");
  printf("0y");
  printf("5_");
  printf("M1");
  printf("p5");
  printf("_i");
  printf("5_");
  printf("f0");
  printf("r_");
  printf("m3");
  printf("n}\n");
  // printf("\tCTF{L1nux_15_f0r_b0y5_M1p5_i5_f0r_m3n}\n");
  return;
}

int main(int argc, char** argv)
{
  const char* PASSWORD_1 = "X3";
  const char* PASSWORD_2 = "cE";
  const char* PASSWORD_3 = "tP";
  const char* PASSWORD_4 = "cK";
  const char* PASSWORD_5 = "uF";
  const char* PASSWORD_6 = "ux";
  const char* PASSWORD_7 = "D2";
  const char* PASSWORD_8 = "XE";

  char password[20];

  printf("PASSWORD: ");
  scanf("%19s", password);

  if (
    memcmp(PASSWORD_1, password      , 2) == 0 &&
    memcmp(PASSWORD_2, password + 2  , 2) == 0 &&
    memcmp(PASSWORD_3, password + 4  , 2) == 0 &&
    memcmp(PASSWORD_4, password + 6  , 2) == 0 &&
    memcmp(PASSWORD_5, password + 8  , 2) == 0 &&
    memcmp(PASSWORD_6, password + 10 , 2) == 0 &&
    memcmp(PASSWORD_7, password + 12 , 2) == 0 &&
    memcmp(PASSWORD_8, password + 14 , 2) == 0
  )
  {
    printf("\nCORRECT PASSWORD!\n");
    print_flag();
  }
  else
  {
    printf("\nWRONG PASSWORD...\n");
  }

  return 0;
}
