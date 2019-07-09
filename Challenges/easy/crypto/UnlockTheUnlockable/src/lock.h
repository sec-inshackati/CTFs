#ifndef LOCK_H
#define LOCK_H
#include <stdbool.h>

#define LOCKSIZE 5

// typedef unsigned char LOCK_DATA;
typedef bool LOCK_DATA;

typedef LOCK_DATA LOCK[LOCKSIZE][LOCKSIZE];
typedef LOCK_DATA KEYHOLE[LOCKSIZE][LOCKSIZE];
// typedef bool LOCK[LOCKSIZE][LOCKSIZE];

void print_lock( LOCK lock );

void init_keyhole( KEYHOLE keyhole );
bool is_unlocked( LOCK lock_result );
void try_to_open( LOCK lock, KEYHOLE keyhole, LOCK result );
void parse_image_key( char* buff, LOCK image_key );

void simulate_loading();

#endif
