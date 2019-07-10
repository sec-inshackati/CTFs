#include "lock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_keyhole( KEYHOLE keyhole )
{
  // INIT KEYHOLE WITH SAME PSEUDORANDOM VALUES
  srand(8);

  for (unsigned i = 0; i < LOCKSIZE; i++)
  {
    for (unsigned j = 0; j < LOCKSIZE; j++)
    {
      keyhole[i][j] = rand() % 2;
    }
  }
}

void try_to_open(LOCK lock, KEYHOLE keyhole, LOCK result)
{
  // printf("\nLOCK:\n");
  // print_lock( lock );
  // printf("\nKEYHOLE:\n");
  // print_lock( keyhole );

  for (unsigned i = 0; i < LOCKSIZE; i++)
  {
    for (unsigned j = 0; j < LOCKSIZE; j++)
    {
      result[i][j] = ( lock[i][j] ^ ( keyhole[i][j] ^ 1) );
      // printf("%1x ^ %1x == %1x\n", lock[i][j], ( keyhole[i][j] ^ 1), result[i][j] );
    }
  }

}

bool is_unlocked( LOCK lock_result )
{
  bool lock_ok = true;

  for (unsigned i = 0; lock_ok && i < LOCKSIZE; i++)
  {
    for (unsigned j = 0; lock_ok && j < LOCKSIZE; j++)
    {
      if ( lock_result[i][j] )
        lock_ok = false;
    }
  }

  return lock_ok;
}

void print_lock( LOCK lock )
{
  for (unsigned i = 0; i < LOCKSIZE; i++)
  {
    for (unsigned j = 0; j < LOCKSIZE; j++)
    {
      if ( lock[i][j] )
        printf(" @");
      else
        printf(" -");

      // printf(" %c", lock[i][j] );
    }
    printf("\n");
  }
}

void parse_image_key(char* buff, LOCK image_key)
{
  char tmp_char;
  for (unsigned i = 0; i < LOCKSIZE; i++)
  {
    for (unsigned j = 0; j < LOCKSIZE; j++)
    {
      tmp_char = buff[ i * LOCKSIZE + j ];
      if (tmp_char != '0' && tmp_char != '1')
      {
        printf("Invalid char found (%c)... Bye.\n", tmp_char);
        exit(2);
      }

      image_key[i][j] = buff[ i * LOCKSIZE + j ] % 2;
      // printf("image_key[%d][%d] = %d\n", i, j, image_key[i][j]);
    }
  }
}

void simulate_loading()
{
  //
  for (unsigned i = 0; i < 60; i++)
  {
    printf(".");
    usleep(10000);
    printf(" ");
    usleep(10000);
  }
  printf("\n");
}
