#include "binary.h"
#include <stdio.h>

enum operation { LSB_CHECK = 0, MSB_CHECK, LEADING_ZEROS, NTH_BIT_CHECK };

int main(void)
{
  int number = 2; /* Temporary stuff */
  int bit_place = 1;
  char* message;

  enum operation type = NTH_BIT_CHECK;
  switch (type)
  {
    case LSB_CHECK:
    case MSB_CHECK: /*Supress warinngs...*/
      message = binary_is_lsb_set(number) ? "LSB present!" : "LSB not present!";
      printf("%s\n", message);
      break;
    case LEADING_ZEROS:
      printf("Number %d has %d leading zeros\n", number, binary_count_leading_zeros(number));
      break;
    case NTH_BIT_CHECK:
      message = binary_is_nth_bit_set(number, bit_place) ? "Nth bit is present" : "Nth bit is not present";
      printf("%s\n", message);
      break;
  }
  return 0;
}