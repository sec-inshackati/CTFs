#include <stdio.h>
#include <string.h>
#include "lock.h"

int main(int argc, char** argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);

  KEYHOLE keyhole;
  LOCK image_key;

  init_keyhole(keyhole);

  printf("Give me the right image key to unlock the lock and get the flag.\n");

  char buff[ LOCKSIZE * LOCKSIZE + 1 ];

  printf("Insert your image key (%d chars): ", LOCKSIZE * LOCKSIZE);
  fgets(buff, LOCKSIZE * LOCKSIZE + 1, stdin);

  buff[ LOCKSIZE * LOCKSIZE ] = 0x00;

  if( strlen(buff) != LOCKSIZE * LOCKSIZE )
  {
    printf("You must insert %d chars...\n", LOCKSIZE * LOCKSIZE);
    return 1;
  }

  parse_image_key(buff, image_key);

  printf("\nHere you are your image key.\n\n");
  print_lock(image_key);

  LOCK lock_result;

  printf("\nTrying to open the lock...\n\n");
  try_to_open(image_key, keyhole, lock_result);
  simulate_loading();

  printf("==== DEBUG - LOCK RESULT ====\n");
  print_lock( lock_result );
  printf("========= END DEBUG =========\n\n");

  if( is_unlocked(lock_result) )
  {
    printf("Congratulations! Door unlocked.\n");
    // CENSORED
    const char FLAG[] = "CTF{XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX}\x00";
    printf("\t%s\n\n", FLAG );
  }else{
    printf("Ohh.. This is not the right key! Door locked.\n");
  }

  return 0;
}
