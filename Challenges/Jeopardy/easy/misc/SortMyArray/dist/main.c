#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

#define MAX_SIZE_ARRAY 10

void print_menu()
{
  printf("=== MENU ===\n");
  printf("\n");
  printf(" 1. Edit array\n");
  printf(" 2. Print sorted array\n");
  printf(" 3. Print a sorted sub-array\n");
  printf(" 9. QUIT\n");
}

int read_choice()
{
  int ret;
  printf("> ");
  scanf("%d", &ret);
  return ret;
}

void print_array(int* arr, int init_index, int end_index_plus_one)
{
  for (int i = init_index; i < end_index_plus_one; i++) printf("%d ", arr[i] );
}

int main(int argc, char** argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);

  char* flag;
  int* arr;

  srand(time(NULL));

  flag = (char*)calloc( 35, 1 );
  memcpy( flag, "CTF{CENSORED_CENSORED_CENSORED_CE}", 34 );

  arr = (int*)calloc( MAX_SIZE_ARRAY, sizeof(int) );
  for (size_t i = 0; i < MAX_SIZE_ARRAY; i++)
    arr[i] = rand() & 0xffff ;


  int* temp_array;
  int* new_temp_array;
  int init_index;

  for(;;)
  {
    printf("Current array: ");
    print_array(arr, 0, MAX_SIZE_ARRAY);
    printf("\n\n");

    print_menu();
    switch ( read_choice() )
    {
      // EDIT ARRAY
      case 1:
        printf("Editing array...\n");
        int index;
        printf("Insert index of value to edit.\n");
        index = read_choice();
        if ( index >= MAX_SIZE_ARRAY )
        {
          printf("Ha Ha... You won't overflow... Try again... Bye.\n");
          printf("Ha Ha... You won't overflow... Try again... Bye.\n");
          printf("Ha Ha... You won't overflow... Try again... Bye.\n");
          return 0;
        }else{
          int new_value;
          printf("New value: ");
          scanf("%d", &new_value);
          arr[index] = new_value;
        }
        break;

      // PRINT SORTED ARRAY
      case 2:

        temp_array = (int*)calloc( MAX_SIZE_ARRAY, sizeof(int) );

        if( temp_array == NULL )
        {
          printf("Error allocating %d bytes for array...\n", MAX_SIZE_ARRAY * sizeof(int) );
          return 1;
        }
        memcpy(temp_array, arr, MAX_SIZE_ARRAY * sizeof(int) );

        printf("Sorting array...\n");
        merge_sort( temp_array, MAX_SIZE_ARRAY );
        printf("\nSorted array: ");
        print_array(temp_array, 0, MAX_SIZE_ARRAY);
        printf("\n\n");
        free(temp_array);
        break;

      // PRINT SORTED SUB-ARRAY
      case 3:

        printf("Insert index of array to sort.\n");
        init_index = read_choice();
        if ( init_index >= MAX_SIZE_ARRAY )
        {
          printf("Ha Ha... You won't overflow... Try again... Bye.\n");
          printf("Ha Ha... You won't overflow... Try again... Bye.\n");
          printf("Ha Ha... You won't overflow... Try again... Bye.\n");
          return 0;
        }

        int size_of_subarray;
        size_of_subarray = MAX_SIZE_ARRAY - init_index;

        new_temp_array = (int*)calloc( size_of_subarray, sizeof(int) );
        if( new_temp_array == NULL )
        {
          printf("Error allocating %d bytes for array...\n", (int)(size_of_subarray *sizeof(int)) );
          return 1;
        }
        memcpy(new_temp_array, arr + init_index, size_of_subarray * sizeof(int) );

        printf("\nSorting array...\n");
        merge_sort( new_temp_array, size_of_subarray );
        printf("Sorted array: ");
        print_array(new_temp_array, 0, size_of_subarray);
        printf("\n\n");
        free(new_temp_array);
        break;

      case 9:
        printf("BYE!\n");
        exit(0);
        break;

      default:
        printf("INVALID CHOICE...\n");
    }

  }

  return 0;
}
